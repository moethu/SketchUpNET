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
#include <SketchUpAPI/model/vertex.h>
#include <SketchUpAPI/model/camera.h>
#include <SketchUpAPI/model/drawing_element.h>
#include <msclr/marshal.h>
#include "utilities.h"
#include "Vector.h"
#include "Vertex.h"


using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpNET
{
	public ref class Camera
	{
	public:

		Vector^ Up;
		Vertex^ Position;
		Vertex^ Target;
		bool Perspective;
		double FOV;

		Camera(Vertex ^ position, Vertex ^ target, Vector^ up, bool perspective, double fov)
		{
			this->Up = up;
			this->Position = position;
			this->Target = target;
			this->FOV = fov;
			this->Perspective = perspective;
		};

		Camera() {};
	internal:
		static Camera^ FromSU(SUCameraRef cam)
		{
			SUPoint3D pos = SU_INVALID;
			SUPoint3D target = SU_INVALID;
			SUVector3D up = SU_INVALID;
			SUCameraGetOrientation(cam, &pos, &target, &up);
			
			
			double fov = 0;
			SUCameraGetPerspectiveFrustumFOV(cam, &fov);
			bool persp = true;
			SUCameraGetPerspective(cam, &persp);

			Camera^ c = gcnew Camera(Vertex::FromSU(pos), Vertex::FromSU(target), Vector::FromSU(up), persp, fov);
			return c;
		};

	};




}