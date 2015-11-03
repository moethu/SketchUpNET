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
#include <msclr/marshal.h>
#include <vector>
#include "Vertex.h"
#include "Corner.h"
#include "Surface.h"
#include "Component.h"
#include "Layer.h"
#include "Group.h"
#include "Instance.h"

#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpSharp
{
	/// <summary>
	/// ArrayFireSharp
	/// </summary>
	public ref class SketchUp
	{

	



	public:
		/// <summary>
		/// Surfaces
		/// </summary>
		System::Collections::Generic::List<Surface^>^ Surfaces;

		/// <summary>
		/// Layers
		/// </summary>
		System::Collections::Generic::List<Layer^>^ Layers;

		/// <summary>
		/// Groups
		/// </summary>
		System::Collections::Generic::List<Group^>^ Groups;

		/// <summary>
		/// Component Definitions
		/// </summary>
		System::Collections::Generic::Dictionary<String^, Component^>^ Components;

		/// <summary>
		/// Component Instances
		/// </summary>
		System::Collections::Generic::List<Instance^>^ Instances;

		/// <summary>
		/// Load SKP Model
		/// </summary>
		bool LoadModel(System::String^ filename)
		{
			msclr::interop::marshal_context oMarshalContext;

			const char* path = oMarshalContext.marshal_as<const char*>(filename);

			SUInitialize();


			SUModelRef model = SU_INVALID;

			SUResult res = SUModelCreateFromFile(&model, path);



			if (res != SU_ERROR_NONE)
				return false;

			Surfaces = gcnew System::Collections::Generic::List<Surface^>();
			Layers = gcnew System::Collections::Generic::List<Layer^>();
			Groups = gcnew System::Collections::Generic::List<Group^>();
			Components = gcnew System::Collections::Generic::Dictionary<String^,Component^>();
			Instances = gcnew System::Collections::Generic::List<Instance^>();

			SUEntitiesRef entities = SU_INVALID;
			SUModelGetEntities(model, &entities);
			size_t faceCount = 0;
			SUEntitiesGetNumFaces(entities, &faceCount);
			


			if (faceCount > 0) {
				std::vector<SUFaceRef> faces(faceCount);
				SUEntitiesGetFaces(entities, faceCount, &faces[0], &faceCount);
				

				for (size_t i = 0; i < faceCount; i++) {
					Surface^ surface = Surface::FromSU(faces[i]);
					Surfaces->Add(surface);
				}
			}
			
			//Get All Layers

			size_t layerCount = 0;
			SUModelGetNumLayers(model, &layerCount);

			if (layerCount > 0) {
				std::vector<SULayerRef> layers(layerCount);
				SUModelGetLayers(model, layerCount, &layers[0], &layerCount);

				for (size_t i = 0; i < layerCount; i++) {
					Layer^ layer = Layer::FromSU(layers[i]);
					Layers->Add(layer);
				}
			}




			//Get All Groups
		
			size_t groupCount = 0;
			SUEntitiesGetNumGroups(entities, &groupCount);

			if (groupCount > 0) {
				std::vector<SUGroupRef> groups(groupCount);
				SUEntitiesGetGroups(entities, groupCount, &groups[0], &groupCount);

				for (size_t i = 0; i < groupCount; i++) {
					Group^ group = Group::FromSU(groups[i]);
					Groups->Add(group);
				}

			}

			// Get all Components
			size_t compCount = 0;
			SUModelGetNumComponentDefinitions(model, &compCount);

			if (compCount > 0) {
				std::vector<SUComponentDefinitionRef> comps(compCount);
				SUModelGetComponentDefinitions(model, compCount, &comps[0], &compCount);

				for (size_t i = 0; i < compCount; i++) {
					Component^ component = Component::FromSU(comps[i]);
					Components->Add(component->Guid,component);
				}
			}

			//Get All Component Instances

			size_t instanceCount = 0;
			SUEntitiesGetNumInstances(entities, &instanceCount);

			if (instanceCount > 0) {
				std::vector<SUComponentInstanceRef> instances(instanceCount);
				SUEntitiesGetInstances(entities, instanceCount, &instances[0], &instanceCount);
				
				for (size_t i = 0; i < instanceCount; i++) {
					Instance^ inst = Instance::FromSU(instances[i],Components);
					Instances->Add(inst);
				}

			}



			SUModelRelease(&model);
			SUTerminate();
			return true;

		};




	};

}