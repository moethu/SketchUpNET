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

#include <slapi/slapi.h>
#include <slapi/geometry.h>
#include <slapi/initialize.h>
#include <slapi/unicodestring.h>
#include <slapi/model/model.h>
#include <slapi/model/entities.h>
#include <slapi/model/face.h>
#include <slapi/model/edge.h>
#include <slapi/model/vertex.h>
#include <slapi/color.h>
#include <slapi/model/drawing_element.h>
#include <slapi/model/material.h>
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
	public ref class Material
	{
	public:

		Color^ Colour;
		System::String^ Name;
		double Opacity;
		bool UseOpacity;
		bool UsesColor;
		bool UsesTexture;

		Material( System::String^ name, Color^ color, bool useOpacity, double opacity, bool usesColor, bool usesTexture)
		{
			this->Colour = color;
			this->Name = name;
			this->Opacity = opacity;
			this->UseOpacity = useOpacity;
			this->UsesColor = usesColor;
			this->UsesTexture = usesTexture;
		};

		Material() { 
			this->Name = ""; 
			this->Colour = gcnew Color(0, 0, 0, 0);
			this->Opacity = 0;
			this->UseOpacity = false;
			this->UsesColor = true;
			this->UsesTexture = false;
		};

		
	internal:


		static Material^ FromSU(SUMaterialRef material)
		{
			SUStringRef name = SU_INVALID;
			SUStringCreate(&name);
			SUMaterialGetName(material, &name);
			String^ n = SketchUpNET::Utilities::GetString(name);


			bool useopacity = false;
			SUMaterialGetUseOpacity(material, &useopacity);

			SUColor color = SU_INVALID;
			SUMaterialGetColor(material, &color);

			SUMaterialType type = SUMaterialType::SUMaterialType_Colored;
			SUMaterialGetType(material, &type);
			
			bool usesColor = false;
			bool usesTexture = false;

			if (type == SUMaterialType::SUMaterialType_Colored)
			{
				usesColor = true;
				usesTexture = false;
			}

			if (type == SUMaterialType::SUMaterialType_ColorizedTexture)
			{
				usesColor = true;
				usesTexture = true;
			}

			if (type == SUMaterialType::SUMaterialType_Textured)
			{
				usesColor = false;
				usesTexture = true;
			}

			double opacity = 0;
			SUMaterialGetOpacity(material, &opacity);

			Color^ c = Color::FromSU(color);

			Material^ v = gcnew Material(n, c, useopacity, opacity, usesColor, usesTexture);

			return v;
		}


	};


}