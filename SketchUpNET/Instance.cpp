/*

SketchUpNET - a C++ Wrapper for the Trimble(R) SketchUp(R) C API
Copyright(C) 2015, Autor: Maximilian Thumfart

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/
#pragma once
#include <SketchUpAPI/slapi.h>
#include <SketchUpAPI/geometry.h>
#include <SketchUpAPI/initialize.h>
#include <SketchUpAPI/unicodestring.h>
#include <SketchUpAPI/model/model.h>
#include <SketchUpAPI/model/entities.h>
#include <SketchUpAPI/model/face.h>
#include <SketchUpAPI/model/edge.h>
#include <SketchUpAPI/model/layer.h>
#include <SketchUpAPI/model/vertex.h>
#include <SketchUpAPI/model/component_instance.h>
#include <SketchUpAPI/model/component_definition.h>
#include <SketchUpAPI/model/drawing_element.h>
#include <msclr/marshal.h>
#include <vector>
#include "transform.h"
#include "utilities.h"
#include "Material.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpNET
{
	public ref class Instance
	{
	public:
		System::String^ Name;
		Transform^ Transformation;
		String^ ParentID;
		System::String^ Guid;
		System::Object^ Parent;
		System::String^ Layer;
		SketchUpNET::Material^ Material;

		Instance(System::String^ name, System::String^ guid, String^ parent, Transform^ transformation, System::String^ layername, SketchUpNET::Material^ mat)
		{
			this->Name = name;
			this->Transformation = transformation;
			this->ParentID = parent;
			this->Guid = guid;
			this->Layer = layername;
			this->Material = mat;
		};


		Instance(){};
	internal:
		static Instance^ FromSU(SUComponentInstanceRef comp, System::Collections::Generic::Dictionary<String^, SketchUpNET::Material^>^ materials)
		{
			SUStringRef name = SU_INVALID;
			SUStringCreate(&name);
			SUComponentInstanceGetName(comp, &name);

			SUComponentDefinitionRef definition = SU_INVALID;
			SUComponentInstanceGetDefinition(comp, &definition);

			SUStringRef instanceguid = SU_INVALID;
			SUStringCreate(&instanceguid);
			SUComponentInstanceGetGuid(comp, &instanceguid);


			SUMaterialRef mat = SU_INVALID;
			SUDrawingElementGetMaterial(SUComponentInstanceToDrawingElement(comp), &mat);
			SUStringRef matNameRef = SU_INVALID;
			SUStringCreate(&matNameRef);
			SUMaterialGetName(mat, &matNameRef);
			System::String^ matName = SketchUpNET::Utilities::GetString(matNameRef);
			SketchUpNET::Material^ groupMat = (materials->ContainsKey(matName)) ? materials[matName] : SketchUpNET::Material::FromSU(mat);
			

			// Layer
			SULayerRef layer = SU_INVALID;
			SUDrawingElementGetLayer(SUComponentInstanceToDrawingElement(comp), &layer);

			System::String^ layername = gcnew System::String("");
			if (!SUIsInvalid(layer))
			{
				layername = Utilities::GetLayerName(layer);
			}

			SUStringRef guid = SU_INVALID;
			SUStringCreate(&guid);
			SUComponentDefinitionGetGuid(definition, &guid);
			System::String^ guidstring = SketchUpNET::Utilities::GetString(guid);

			String^ parent = guidstring;


			SUTransformation transform = SU_INVALID;
			SUComponentInstanceGetTransform(comp, &transform);
			

			Instance^ v = gcnew Instance(SketchUpNET::Utilities::GetString(name), SketchUpNET::Utilities::GetString(instanceguid), parent, Transform::FromSU(transform), layername, groupMat);

			return v;
		};
		static List<Instance^>^ GetEntityInstances(SUEntitiesRef entities, System::Collections::Generic::Dictionary<String^, SketchUpNET::Material^>^ materials)
		{
			List<Instance^>^ instancelist = gcnew List<Instance^>();

			//Get All Component Instances

			size_t instanceCount = 0;
			SUEntitiesGetNumInstances(entities, &instanceCount);

			if (instanceCount > 0) {
				std::vector<SUComponentInstanceRef> instances(instanceCount);
				SUEntitiesGetInstances(entities, instanceCount, &instances[0], &instanceCount);

				for (size_t i = 0; i < instanceCount; i++) {
					Instance^ inst = Instance::FromSU(instances[i], materials);
					instancelist->Add(inst);
				}

			}

			return instancelist;
		}
	};


}