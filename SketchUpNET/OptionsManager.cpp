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
#include <SketchUpAPI/model/layer.h>
#include <msclr/marshal.h>
#include <vector>
#include <SketchUpAPI/model/options_provider.h>
#include <SketchUpAPI/model/options_manager.h>
#include "Utilities.h"
#include "OptionsProvider.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpNET
{
	public ref class OptionsManager
	{
	public:
		List<OptionsProvider^>^ OptionsProviders;
		OptionsManager() {};
		OptionsManager(List<OptionsProvider^>^ providers) {
			this->OptionsProviders = providers;
		};

	internal:
		static OptionsManager^ FromModel(SUModelRef model) {
			List<OptionsProvider^>^ providers = gcnew List<OptionsProvider^>();
			SUOptionsManagerRef om = SU_INVALID;
			SUModelGetOptionsManager(model, &om);
			size_t ctr = 0;
			SUOptionsManagerGetNumOptionsProviders(om, &ctr);
			if (ctr > 0)
			{
				SUStringRef optionmanagernames[] = SU_INVALID;
				size_t omn_ctr = 0;
				SUOptionsManagerGetOptionsProviderNames(om, ctr, optionmanagernames, &omn_ctr);

				for (size_t i = 0; i < omn_ctr; i++) {
					SUOptionsProviderRef provider_ref = SU_INVALID;
					SUOptionsManagerGetOptionsProviderByName(om, Utilities::ToCharArray(optionmanagernames[i]), &provider_ref);
					providers->Add(OptionsProvider::FromSU(provider_ref));
				}
			}
			return gcnew OptionsManager(providers);
		};
	};


}