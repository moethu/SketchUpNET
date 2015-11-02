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
#include <msclr/marshal.h>
#include <vector>
#include "surface.h"
#include "transform.h"


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

		Instance(System::String^ name, Transform^ transformation)
		{
			this->Name = name;
			this->Transformation = transformation;
		};

		Instance(){};

		static Instance^ FromSU(SUComponentInstanceRef comp)
		{
			SUStringRef name = SU_INVALID;
			SUStringCreate(&name);
			SUComponentInstanceGetName(comp, &name);
			size_t name_length = 0;
			SUStringGetUTF8Length(name, &name_length);
			char* name_utf8 = new char[name_length + 1];
			SUStringGetUTF8(name, name_length + 1, name_utf8, &name_length);
			SUStringRelease(&name);

			SUTransformation transform = SU_INVALID;
			SUComponentInstanceGetTransform(comp, &transform);


			Instance^ v = gcnew Instance(gcnew String(name_utf8), Transform::FromSU(transform));

			return v;
		};

	};


}