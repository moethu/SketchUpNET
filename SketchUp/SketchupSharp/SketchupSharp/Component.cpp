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
#include <slapi/model/component_definition.h>
#include <msclr/marshal.h>
#include <vector>
#include "surface.h"


#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpSharp
{
	public ref class Component
	{
	public:
		System::String^ Name;
		System::Collections::Generic::List<Surface^>^ Surfaces;
		System::String^ Guid;

		Component(System::String^ name, System::String^ guid,System::Collections::Generic::List<Surface^>^ surfaces)
		{
			this->Name = name;
			this->Surfaces = surfaces;
			this->Guid = guid;
		};

		Component(){};
	internal:
		static Component^ FromSU(SUComponentDefinitionRef comp)
		{
			SUStringRef name = SU_INVALID;
			SUStringCreate(&name);
			SUComponentDefinitionGetName(comp, &name);
			size_t name_length = 0;
			SUStringGetUTF8Length(name, &name_length);
			char* name_utf8 = new char[name_length + 1];
			SUStringGetUTF8(name, name_length + 1, name_utf8, &name_length);
			SUStringRelease(&name);

			SUEntitiesRef entities = SU_INVALID;
			SUComponentDefinitionGetEntities(comp, &entities);

			size_t faceCount = 0;
			SUEntitiesGetNumFaces(entities, &faceCount);

			SUStringRef guid = SU_INVALID;
			SUStringCreate(&guid);
			SUComponentDefinitionGetGuid(comp, &guid);
			size_t guid_length = 0;
			SUStringGetUTF8Length(guid, &guid_length);
			char* guid_utf8 = new char[guid_length + 1];
			SUStringGetUTF8(guid, guid_length + 1, guid_utf8, &guid_length);
			SUStringRelease(&guid);


			System::Collections::Generic::List<Surface^>^ surfaces = gcnew System::Collections::Generic::List<Surface^>();

			if (faceCount > 0) {
				std::vector<SUFaceRef> faces(faceCount);
				SUEntitiesGetFaces(entities, faceCount, &faces[0], &faceCount);


				for (size_t i = 0; i < faceCount; i++) {
					Surface^ surface = Surface::FromSU(faces[i]);
					surfaces->Add(surface);
				}
			}


			Component^ v = gcnew Component(gcnew String(name_utf8), gcnew String(guid_utf8), surfaces);

			return v;
		};

	};


}