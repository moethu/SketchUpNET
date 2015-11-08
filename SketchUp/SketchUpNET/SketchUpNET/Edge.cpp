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
#include <slapi/model/curve.h>
#include <msclr/marshal.h>
#include <vector>
#include "Vertex.h"

#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpNET
{
	public ref class Edge
	{
	public:

		Vertex^ Start;
		Vertex^ End;

		bool isArc;

		Edge(Vertex ^ start, Vertex ^ end, bool isarc)
		{
			this->Start = start;
			this->End = end;
			this->isArc = isarc;
		};

		Edge(){};
	internal:
		static Edge^ FromSU(SUEdgeRef edge)
		{
			SUVertexRef startVertex = SU_INVALID;
			SUVertexRef endVertex = SU_INVALID;
			SUEdgeGetStartVertex(edge, &startVertex);
			SUEdgeGetEndVertex(edge, &endVertex);
			SUPoint3D start;
			SUPoint3D end;
			SUVertexGetPosition(startVertex, &start);
			SUVertexGetPosition(endVertex, &end);

			SUCurveRef curve = SU_INVALID;
			SUEdgeGetCurve(edge, &curve);
			SUCurveType type = SUCurveType::SUCurveType_Simple;
			SUCurveGetType(curve, &type);
			bool isarc = false;
			if (type == SUCurveType::SUCurveType_Arc) isarc = true;

			Edge^ v = gcnew Edge(Vertex::FromSU(start), Vertex::FromSU(end), isarc);

			return v;
		};




	};




}