/*

SketchUpNET - a C++ Wrapper for the Trimble(R) SketchUp(R) C API
Copyright(C) 2018, Autor: Maximilian Thumfart

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
#include <SketchUpAPI/model/texture.h>
#include <SketchUpAPI/color.h>
#include <msclr/marshal.h>
#include <vector>
#include "loop.h"
#include "vertex.h"
#include "vector.h"
#include "utilities.h"
#include "Color.h"


#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpNET
{
	public ref class Texture
	{
	public:

		Color ^ Colour;
		System::String^ Name;
		double Opacity;
		bool useAlpha;
		int Height;
		int Width;
		double ScaleH;
		double ScaleW;

		Texture(System::String^ name, Color^ color, bool useAlpha, int height, int width, double scaleH, double scaleW)
		{
			this->Colour = color;
			this->Name = name;
			this->useAlpha = useAlpha;
			this->Width = width;
			this->Height = height;
			this->ScaleH = scaleH;
			this->ScaleW = scaleW;
		};

		Texture() {
			this->Name = "";
			this->Colour = gcnew Color(0, 0, 0, 0);
			this->Opacity = 0;
			this->useAlpha = false;
			this->Width = 0;
			this->Height = 0;
			this->ScaleH = 0;
			this->ScaleW = 0;
		};


	internal:


		static Texture^ FromSU(SUTextureRef texture)
		{
			SUStringRef name = SU_INVALID;
			SUStringCreate(&name);
			SUTextureGetFileName(texture, &name);
			String^ n = SketchUpNET::Utilities::GetString(name);


			bool usealphachannel = false;
			SUTextureGetUseAlphaChannel(texture, &usealphachannel);

			SUColor color = SU_INVALID;
			SUTextureGetAverageColor(texture, &color);

			Color^ c = Color::FromSU(color);

			size_t h = 0;
			size_t w = 0;
			double scaleh = 0;
			double scalew = 0;
			SUTextureGetDimensions(texture, &w, &h, &scalew, &scaleh);

			Texture^ v = gcnew Texture(n, c, usealphachannel, h,w,scaleh, scalew);

			return v;
		}


	};


}