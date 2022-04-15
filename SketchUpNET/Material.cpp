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
#include <SketchUpAPI/model/vertex.h>
#include <SketchUpAPI/color.h>
#include <SketchUpAPI/model/drawing_element.h>
#include <SketchUpAPI/model/material.h>
#include <msclr/marshal.h>
#include <vector>
#include "loop.h"
#include "vertex.h"
#include "vector.h"
#include "utilities.h"
#include "Color.h"
#include "Texture.h"

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
		Texture^ MaterialTexture;

		Material( System::String^ name, Color^ color, bool useOpacity, double opacity, bool usesColor, bool usesTexture, Texture^ texture)
		{
			this->Colour = color;
			this->Name = name;
			this->Opacity = opacity;
			this->UseOpacity = useOpacity;
			this->UsesColor = usesColor;
			this->UsesTexture = usesTexture;
			this->MaterialTexture = texture;
		};

		Material() { 
			this->Name = ""; 
			this->Colour = gcnew Color(0, 0, 0, 0);
			this->Opacity = 0;
			this->UseOpacity = false;
			this->UsesColor = true;
			this->UsesTexture = false;
			this->MaterialTexture = gcnew Texture();
		};

		virtual String^ ToString() override
		{
			return this->Name;
		}

	internal:

		SUMaterialRef ToSU() {
			SUMaterialRef mat = SU_INVALID;
			SUMaterialCreate(&mat);
			SUMaterialSetName(mat, Utilities::ToString(this->Name));
			SUMaterialSetUseOpacity(mat, this->UseOpacity);
			SUMaterialSetOpacity(mat, this->Opacity);
			if (this->UsesColor && !this->UsesTexture) {
				SUMaterialSetType(mat, SUMaterialType::SUMaterialType_Colored);
			}
			if (this->UsesColor && this->UsesTexture) {
				SUMaterialSetType(mat, SUMaterialType::SUMaterialType_ColorizedTexture);
			}
			if (!this->UsesColor && this->UsesTexture) {
				SUMaterialSetType(mat, SUMaterialType::SUMaterialType_Textured);
			}
			const SUColor c = this->Colour->ToSU();
			SUMaterialSetColor(mat,&c);
			
			return mat;
		}



		static SUMaterialRef* ListToSU(List<Material^>^ list)
		{
			size_t size = list->Count;
			SUMaterialRef* result = (SUMaterialRef*)malloc(*&size * sizeof(SUMaterialRef));
			for (int i = 0; i < size; i++)
			{
				result[i] = list[i]->ToSU();
			}
			return result;
		}

		static SUMaterialRef FindMaterial(SUModelRef model, System::String^ materialname) {
			size_t matCount = 0;
			SUModelGetNumMaterials(model, &matCount);

			if (matCount > 0) {
				std::vector<SUMaterialRef> materials(matCount);
				SUModelGetMaterials(model, matCount, &materials[0], &matCount);

				for (size_t i = 0; i < matCount; i++) {
					Material^ mat = Material::FromSU(materials[i]);
					if (mat->Name->Equals(materialname))
						return materials[i];
				}
			}

			return SU_INVALID;
		}

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
			
			SUTextureRef texture = SU_INVALID;
			SUMaterialGetTexture(material, &texture);
			Texture^ txtr = Texture::FromSU(texture);

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

			Material^ v = gcnew Material(n, c, useopacity, opacity, usesColor, usesTexture, txtr);

			return v;
		}


	};


}