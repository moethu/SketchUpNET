/*

SketchUpNET - a managed C++ Wrapper for the SketchUp C API
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
#include <slapi/model/component_definition.h>
#include <msclr/marshal.h>
#include <vector>
#include "surface.h"


#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpNET
{
	public ref class Component
	{
	public:
		System::String^ Name;
		System::Collections::Generic::List<Surface^>^ Surfaces;
		System::String^ Guid;
		System::Collections::Generic::List<Curve^>^ Curves;
		System::Collections::Generic::List<Edge^>^ Edges;

		Component(System::String^ name, System::String^ guid, System::Collections::Generic::List<Surface^>^ surfaces, System::Collections::Generic::List<Curve^>^ curves, System::Collections::Generic::List<Edge^>^ edges)
		{
			this->Name = name;
			this->Surfaces = surfaces;
			this->Guid = guid;
			this->Curves = curves;
			this->Edges = edges;
		};

		Component(){};
	internal:
		static Component^ FromSU(SUComponentDefinitionRef comp)
		{
			SUStringRef name = SU_INVALID;
			SUStringCreate(&name);
			SUComponentDefinitionGetName(comp, &name);


			SUEntitiesRef entities = SU_INVALID;
			SUComponentDefinitionGetEntities(comp, &entities);

			size_t faceCount = 0;
			SUEntitiesGetNumFaces(entities, &faceCount);


			
			SUStringRef guid = SU_INVALID;
			SUStringCreate(&guid);
			SUComponentDefinitionGetGuid(comp, &guid);


			System::Collections::Generic::List<Surface^>^ surfaces = gcnew System::Collections::Generic::List<Surface^>();

			size_t curveCount = 0;
			SUEntitiesGetNumCurves(entities, &curveCount);
			System::Collections::Generic::List<Curve^>^ curves = gcnew System::Collections::Generic::List<Curve^>();
			if (curveCount > 0)
			{
				std::vector<SUCurveRef> curvevector(curveCount);
				SUEntitiesGetCurves(entities, curveCount, &curvevector[0], &curveCount);


				for (size_t i = 0; i < curveCount; i++) {
					Curve^ curve = Curve::FromSU(curvevector[i]);
					curves->Add(curve);
				}
			}


			size_t edgeCount = 0;
			SUEntitiesGetNumEdges(entities,false, &edgeCount);
			System::Collections::Generic::List<Edge^>^ edges = gcnew System::Collections::Generic::List<Edge^>();
			if (edgeCount > 0)
			{
				std::vector<SUEdgeRef> edgevector(edgeCount);
				SUEntitiesGetEdges(entities, false,edgeCount, &edgevector[0], &edgeCount);


				for (size_t i = 0; i < edgeCount; i++) {
					Edge^ edge = Edge::FromSU(edgevector[i]);
					edges->Add(edge);
				}
			}



			if (faceCount > 0) {
				std::vector<SUFaceRef> faces(faceCount);
				SUEntitiesGetFaces(entities, faceCount, &faces[0], &faceCount);


				for (size_t i = 0; i < faceCount; i++) {
					Surface^ surface = Surface::FromSU(faces[i]);
					surfaces->Add(surface);
				}
			}


			Component^ v = gcnew Component(SketchUpNET::Utilities::GetString(name), SketchUpNET::Utilities::GetString(guid), surfaces, curves,edges);

			return v;
		};

	};


}