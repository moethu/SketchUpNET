/*

SketchUpSharp - a managed C++ Wrapper for the SketchUp C API
Copyright(C) 2015, Autor: Maximilian Thumfart

This program is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.

*/

#include <slapi/slapi.h>
#include <slapi/geometry.h>
#include <slapi/initialize.h>
#include <slapi/unicodestring.h>
#include <slapi/model/model.h>
#include <slapi/model/entities.h>
#include <slapi/model/face.h>
#include <slapi/model/edge.h>
#include <slapi/model/vertex.h>
#include <slapi/model/component_instance.h>
#include <slapi/model/component_definition.h>
#include <msclr/marshal.h>
#include <vector>
#include "surface.h"
#include "transform.h"
#include "component.h"


#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpSharp
{
	public ref class Instance
	{
	public:
		System::String^ Name;
		Transform^ Transformation;
		Component^ Parent;
		System::String^ Guid;

		Instance(System::String^ name, System::String^ guid, Component^ parent, Transform^ transformation)
		{
			this->Name = name;
			this->Transformation = transformation;
			this->Parent = parent;
			this->Guid = guid;
		};

		Instance(){};
	internal:
		static Instance^ FromSU(SUComponentInstanceRef comp, Dictionary<String^,Component^>^ components)
		{
			SUStringRef name = SU_INVALID;
			SUStringCreate(&name);
			SUComponentInstanceGetName(comp, &name);
			
			SUComponentDefinitionRef definition = SU_INVALID;
			SUComponentInstanceGetDefinition(comp, &definition);

			SUStringRef instanceguid = SU_INVALID;
			SUStringCreate(&instanceguid);
			SUComponentInstanceGetGuid(comp, &instanceguid);
			size_t instanceguid_length = 0;
			SUStringGetUTF8Length(instanceguid, &instanceguid_length);
			char* instanceguid_utf8 = new char[instanceguid_length + 1];
			SUStringGetUTF8(instanceguid, instanceguid_length + 1, instanceguid_utf8, &instanceguid_length);
			SUStringRelease(&instanceguid);

			SUStringRef guid = SU_INVALID;
			SUStringCreate(&guid);
			SUComponentDefinitionGetGuid(definition, &guid);
			size_t guid_length = 0;
			SUStringGetUTF8Length(guid, &guid_length);
			char* guid_utf8 = new char[guid_length + 1];
			SUStringGetUTF8(guid, guid_length + 1, guid_utf8, &guid_length);
			SUStringRelease(&guid);
			
			Component^ parent = components[gcnew String(guid_utf8)];

			size_t name_length = 0;
			SUStringGetUTF8Length(name, &name_length);
			char* name_utf8 = new char[name_length + 1];
			SUStringGetUTF8(name, name_length + 1, name_utf8, &name_length);
			SUStringRelease(&name);

			SUTransformation transform = SU_INVALID;
			SUComponentInstanceGetTransform(comp, &transform);


			Instance^ v = gcnew Instance(gcnew String(name_utf8), gcnew String(instanceguid_utf8), parent, Transform::FromSU(transform));

			return v;
		};

	};


}