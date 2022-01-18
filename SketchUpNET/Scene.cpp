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
#include <SketchUpAPI/model/scene.h>
#include <SketchUpAPI/model/drawing_element.h>
#include <msclr/marshal.h>
#include "utilities.h"
#include "Camera.h"
#include "Layer.h"


using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpNET
{
	public ref class Scene
	{
	public:

		Vertex ^ Start;
		Vertex^ End;
		System::String^ Layer;

		Scene(Vertex ^ start, Vertex ^ end, System::String^ layer)
		{
			this->Start = start;
			this->End = end;
			this->Layer = layer;
		};

		Scene() {};
	internal:
		static Scene^ FromSU(SUSceneRef scene)
		{
			SUStringRef name = SU_INVALID;
			SUStringCreate(&name);
			SUSceneGetName(scene, &name);
			String^ n = SketchUpNET::Utilities::GetString(name);

			SUCameraRef cam = SU_INVALID;
			SUSceneGetCamera(scene, &cam);


			//Get All Layers
			size_t layerCount = 0;
			SUSceneGetNumLayers(scene, &layerCount);

			if (layerCount > 0) {
				std::vector<SULayerRef> layers(layerCount);
				SUSceneGetLayers(scene, layerCount, &layers[0], &layerCount);

				for (size_t i = 0; i < layerCount; i++) {
					Layer^ layer = Layer::FromSU(layers[i]);
					layer.Name

				}
			}

		};




	};




}