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
#include <SketchUpAPI/model/scene.h>
#include <SketchUpAPI/model/entity.h>
#include <msclr/marshal.h>
#include "utilities.h"
#include "Layer.h"

#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpNET
{
	public ref class Scene
	{
	public:

		System::String^ Name;
		List<Int32>^ hiddenInstanceIds;

		Scene(System::String^ name, List<Int32>^ hiddenInstanceIds)
		{
			this->Name = name;
			this->hiddenInstanceIds = hiddenInstanceIds;
		};

		Scene() {};
	internal:
		static Scene^ FromSU(SUSceneRef scene)
		{
			SUStringRef name = SU_INVALID;
			SUStringCreate(&name);
			SUSceneGetName(scene, &name);

			size_t eCount = 0;
			SUSceneGetNumHiddenEntities(scene, &eCount);
			List<Int32>^ instancelist = gcnew List<Int32>();

			if (eCount > 0) {
				std::vector<SUEntityRef> ents(eCount);
				SUSceneGetHiddenEntities(scene, eCount, &ents[0], &eCount);
				
				for (size_t i = 0; i < eCount; i++) {
					int32_t id = -1;
					SUEntityGetID(ents[i], &id);
					instancelist->Add(id);
				}
			}

			return gcnew Scene(SketchUpNET::Utilities::GetString(name), instancelist);
		};
	};

}