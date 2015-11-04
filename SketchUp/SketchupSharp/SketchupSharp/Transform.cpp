/*

SketchUpSharp - a managed C++ Wrapper for the SketchUp C API
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
#include <msclr/marshal.h>
#include <slapi/model/component_instance.h>
#include <vector>

#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpSharp
{
	public ref class Transform
	{
	public:

		array<double^>^ Data;
	
		double Scale;
		double X;
		double Y;
		double Z;

		Transform(array<double^>^ data)
		{
			this->Data = data;
			this->Scale = *data[15];
			this->Z =* data[14];
			this->Y =* data[13];
			this->X =* data[12];

		};

		Transform(){};
	internal:
		static Transform^ FromSU(SUTransformation transformation)
		{
			double* data = transformation.values;

			array<double^>^ ar = gcnew array<double^>(16);
			for (int i = 0; i < 16; i++)
				ar[i] = data[i];

			Transform^ v = gcnew Transform(ar);

			return v;
		};

	};


}