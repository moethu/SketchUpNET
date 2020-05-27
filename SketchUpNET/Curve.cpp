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
#include <SketchUpAPI/model/curve.h>
#include <msclr/marshal.h>
#include <vector>
#include "edge.h"

#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpNET
{
	public ref class Curve
	{
	public:

		List<Edge^>^ Edges = gcnew List<Edge^>();
		bool isArc;

		Curve(List<Edge^>^ edges, bool isarc)
		{
			this->Edges = edges;
			this->isArc = isarc;
		};

		Curve(){};

	internal:

		static Curve^ FromSU(SUCurveRef curve)
		{
			List<Edge^>^ edgelist = gcnew List<Edge^>();

			size_t edgecount = 0;
			SUCurveGetNumEdges(curve, &edgecount);
			if (edgecount > 0)
			{
				std::vector<SUEdgeRef> edges(edgecount);
				SUCurveGetEdges(curve, edgecount, &edges[0], &edgecount);

				for (size_t j = 0; j < edgecount; j++)
				{
					edgelist->Add(Edge::FromSU(edges[j]));
				}
			}

			SUCurveType type = SUCurveType::SUCurveType_Simple;
			SUCurveGetType(curve, &type);
			bool isArc = false;
			if (type == SUCurveType::SUCurveType_Arc) isArc = true;


			Curve^ v = gcnew Curve(edgelist, isArc);

			return v;
		};
		
		SUCurveRef ToSU()
		{
			SUCurveRef curve = SU_INVALID;
			size_t size = this->Edges->Count;

			SUEdgeRef * edges = (SUEdgeRef *)malloc(*&size * sizeof(SUEdgeRef));
	
			for (int i = 0; i < size; i++)
			{
				edges[i] = this->Edges[i]->ToSU();
			}
			SUCurveCreateWithEdges(&curve, edges, size);
			return curve;
		}

		static SUCurveRef* ListToSU(List<Curve^>^ curves)
		{
			size_t size = curves->Count;
			SUCurveRef * result = (SUCurveRef *)malloc(*&size * sizeof(SUCurveRef));
			for (int i = 0; i < size; i++)
			{
				result[i] = curves[i]->ToSU();
			}
			return result;
		}

		static List<Curve^>^ GetEntityCurves(SUEntitiesRef entities)
		{
			List<Curve^>^ curves = gcnew List<Curve^>();

			// GetCurves
			size_t curveCount = 0;
			SUEntitiesGetNumCurves(entities, &curveCount);
			if (curveCount > 0)
			{
				std::vector<SUCurveRef> curvevector(curveCount);
				SUEntitiesGetCurves(entities, curveCount, &curvevector[0], &curveCount);


				for (size_t i = 0; i < curveCount; i++) {
					Curve^ curve = Curve::FromSU(curvevector[i]);
					curves->Add(curve);
				}
			}

			return curves;
		}


	};




}