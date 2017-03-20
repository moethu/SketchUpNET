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
#include <slapi/model/layer.h>
#include <slapi/model/group.h>
#include "utilities.h"
#include <msclr/marshal.h>
#include <vector>
#include "Surface.h"
#include "Edge.h"
#include "curve.h"



#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpNET
{
	public ref class Group
	{
	public:
		System::String^ Name;

		/// <summary>
		/// Surfaces
		/// </summary>
		List<Surface^>^ Surfaces;
		List<Edge^>^ Edges;
		List<Curve^>^ Curves;

		Group(System::String^ name, List<Surface^>^ surfaces, List<Curve^>^ curves, List<Edge^>^ edges)
		{
			this->Name = name;
			this->Surfaces = surfaces;
			this->Edges = edges;
			this->Curves = curves;
		};

		Group(){};
	internal:
		static Group^ FromSU(SUGroupRef group, bool includeMeshes, System::Collections::Generic::Dictionary<String^, Material^>^ materials)
		{
			SUStringRef name = SU_INVALID;
			SUStringCreate(&name);
			SUGroupGetName(group, &name);


			SUEntitiesRef entities = SU_INVALID;
			SUGroupGetEntities(group, &entities);

			size_t faceCount = 0;
			SUEntitiesGetNumFaces(entities, &faceCount);


			List<Surface^>^ surfaces = Surface::GetEntitySurfaces(entities, includeMeshes, materials);
			List<Edge^>^ edges = Edge::GetEntityEdges(entities);
			List<Curve^>^ curves = Curve::GetEntityCurves(entities);

			Group^ v = gcnew Group(SketchUpNET::Utilities::GetString(name), surfaces, curves, edges);

			return v;
		};

	};


}