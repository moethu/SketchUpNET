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
#include <SketchUpAPI/model/layer.h>
#include <SketchUpAPI/model/group.h>
#include "utilities.h"
#include <msclr/marshal.h>
#include <vector>
#include "Surface.h"
#include "Edge.h"
#include "curve.h"
#include "Instance.h"


#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpNET
{
	public ref class Group
	{
	public:
		System::String^ Name;

		/// <summary>
		/// Surfaces
		/// </summary>
		List<Surface^>^ Surfaces;
		List<Edge^>^ Edges;
		List<Curve^>^ Curves;
		List<Instance^>^ Instances;
		List<Group^>^ Groups;
		Transform^ Transformation;
		System::String^ Layer;

		Group(System::String^ name, List<Surface^>^ surfaces, List<Curve^>^ curves, List<Edge^>^ edges, List<Instance^>^ insts, List<Group^>^ group, Transform^ transformation, System::String^ layername)
		{
			this->Name = name;
			this->Surfaces = surfaces;
			this->Edges = edges;
			this->Curves = curves;
			this->Instances = insts;
			this->Groups = group;
			this->Transformation = transformation;
			this->Layer = layername;
		};

		Group(){};
	internal:
		static Group^ FromSU(SUGroupRef group, bool includeMeshes, System::Collections::Generic::Dictionary<String^, Material^>^ materials)
		{
			SUStringRef name = SU_INVALID;
			SUStringCreate(&name);
			SUGroupGetName(group, &name);


			SUEntitiesRef entities = SU_INVALID;
			SUGroupGetEntities(group, &entities);

			size_t faceCount = 0;
			SUEntitiesGetNumFaces(entities, &faceCount);

			SUTransformation transform = SU_INVALID;
			SUGroupGetTransform(group, &transform);
			
			List<Surface^>^ surfaces = Surface::GetEntitySurfaces(entities, includeMeshes, materials);
			List<Edge^>^ edges = Edge::GetEntityEdges(entities);
			List<Curve^>^ curves = Curve::GetEntityCurves(entities);
			List<Instance^>^ inst = Instance::GetEntityInstances(entities);
			List<Group^>^ grps = Group::GetEntityGroups(entities, includeMeshes, materials);
			
			// Layer
			SULayerRef layer = SU_INVALID;
			SUDrawingElementGetLayer(SUGroupToDrawingElement(group), &layer);

			System::String^ layername = gcnew System::String("");
			if (!SUIsInvalid(layer))
			{
				layername = SketchUpNET::Utilities::GetLayerName(layer);
			}

			Group^ v = gcnew Group(SketchUpNET::Utilities::GetString(name), surfaces, curves, edges, inst, grps, Transform::FromSU(transform), layername);

			return v;
		};

		static List<Group^>^ GetEntityGroups(SUEntitiesRef entities, bool includeMeshes, System::Collections::Generic::Dictionary<String^, Material^>^ materials)
		{
			List<Group^>^ groups = gcnew List<Group^>();

			size_t instanceCount = 0;
			SUEntitiesGetNumGroups(entities, &instanceCount);

			if (instanceCount > 0) {
				std::vector<SUGroupRef> instances(instanceCount);
				SUEntitiesGetGroups(entities, instanceCount, &instances[0], &instanceCount);

				for (size_t i = 0; i < instanceCount; i++) {
					Group^ inst = Group::FromSU(instances[i], includeMeshes, materials);
					groups->Add(inst);
				}

			}

			return groups;
		}
	};


}