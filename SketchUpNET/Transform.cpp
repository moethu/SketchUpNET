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
#include <SketchUpAPI/model/geometry_input.h>
#include <SketchUpAPI/transformation.h>
#include <msclr/marshal.h>
#include <SketchUpAPI/model/component_instance.h>
#include <vector>
#include "vertex.h"
#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpNET
{
	public ref class Transform
	{
	public:

		Vertex^ GetTransformed(Vertex^ point)
		{

			Vertex^ transformedPoint = gcnew Vertex(point->X, point->Y, point->Z);

			double uniform_scale_factor = 1.0 / this->Scale;

			transformedPoint->X = (this->Data[0] * point->X) + (point->Y*this->Data[4]) + (point->Z*this->Data[8]) + this->Data[12];
			transformedPoint->Y = (this->Data[1] * point->X) + (point->Y*this->Data[5]) + (point->Z*this->Data[9]) + this->Data[13];
			transformedPoint->Z = (this->Data[2] * point->X) + (point->Y*this->Data[6]) + (point->Z*this->Data[10]) + this->Data[14];

			transformedPoint->X = transformedPoint->X* this->Scale;
			transformedPoint->Y = transformedPoint->Y* this->Scale;
			transformedPoint->Z = transformedPoint->Z* this->Scale;

			return transformedPoint;
		}


		array<double>^ Data;
	
		double Scale;
		double X;
		double Y;
		double Z;

		Transform(array<double>^ data)
		{
			this->Data = data;
			this->Scale = data[15];
			this->Z = data[14];
			this->Y = data[13];
			this->X = data[12];

		};

		Transform(){};
	internal:
		static Transform^ FromSU(SUTransformation transformation)
		{
			double* data = transformation.values;

			array<double>^ ar = gcnew array<double>(16);
			for (int i = 0; i < 16; i++)
				if (i == 12 || i==13 ||i==14)
					ar[i] = data[i] * 0.0254;
				else
					ar[i] = data[i];

			Transform^ v = gcnew Transform(ar);

			return v;

		};

	};


}