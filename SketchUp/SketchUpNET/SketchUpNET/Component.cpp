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

#include <SketchUpAPI/slapi.h>
#include <SketchUpAPI/geometry.h>
#include <SketchUpAPI/initialize.h>
#include <SketchUpAPI/unicodestring.h>
#include <SketchUpAPI/model/model.h>
#include <SketchUpAPI/model/entities.h>
#include <SketchUpAPI/model/face.h>
#include <SketchUpAPI/model/edge.h>
#include <SketchUpAPI/model/vertex.h>
#include <SketchUpAPI/model/component_definition.h>
#include <msclr/marshal.h>
#include <vector>
#include "surface.h"
#include "edge.h"
#include "group.h"
#include "curve.h"
#include "utilities.h"
#include "Transform.h"
#include "Instance.h"


#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpNET
{
	public ref class Component
	{
	public:
		System::String^ Name;
		System::String^ Description;
		List<Surface^>^ Surfaces;
		List<Instance^>^ Instances;
		System::String^ Guid;
		List<Curve^>^ Curves;
		List<Edge^>^ Edges;
		List<Group^>^ Groups;

		Component(System::String^ name, System::String^ guid, List<Surface^>^ surfaces, List<Curve^>^ curves, List<Edge^>^ edges, List<Instance^>^ instances, System::String^ desc, List<Group^>^ groups)
		{
			this->Name = name;
			this->Surfaces = surfaces;
			this->Guid = guid;
			this->Curves = curves;
			this->Edges = edges;
			this->Description = desc;
			this->Instances = instances;
			this->Groups = groups;
		};

		Component(){};
	internal:
		static Component^ FromSU(SUComponentDefinitionRef comp, bool includeMeshes, System::Collections::Generic::Dictionary<String^, Material^>^ materials)
		{
			SUStringRef name = SU_INVALID;
			SUStringCreate(&name);
			SUComponentDefinitionGetName(comp, &name);

			SUStringRef desc = SU_INVALID;
			SUStringCreate(&desc);
			SUComponentDefinitionGetDescription(comp, &desc);

			SUEntitiesRef entities = SU_INVALID;
			SUComponentDefinitionGetEntities(comp, &entities);

			size_t faceCount = 0;
			SUEntitiesGetNumFaces(entities, &faceCount);

			
			SUStringRef guid = SU_INVALID;
			SUStringCreate(&guid);
			SUComponentDefinitionGetGuid(comp, &guid);

			List<Surface^>^ surfaces = Surface::GetEntitySurfaces(entities, includeMeshes, materials);
			List<Curve^>^ curves = Curve::GetEntityCurves(entities);
			List<Edge^>^ edges = Edge::GetEntityEdges(entities);
			List<Instance^>^ instances = Instance::GetEntityInstances(entities);
			List<Group^>^ grps = Group::GetEntityGroups(entities, includeMeshes, materials);
			
			

			Component^ v = gcnew Component(Utilities::GetString(name), Utilities::GetString(guid), surfaces, curves, edges,instances, Utilities::GetString(desc), grps);

			return v;
		};

	};


}