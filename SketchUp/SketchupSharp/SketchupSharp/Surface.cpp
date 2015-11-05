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
#include <slapi/model/layer.h>
#include <slapi/model/drawing_element.h>
#include <msclr/marshal.h>
#include <vector>
#include "Corner.h"
#include "Layer.h"
#include "Vector.h"
#include "Utilities.h"
#include "loop.h"

#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpSharp
{
	public ref class Surface
	{
	public:
		Loop^ OuterEdges;
		System::Collections::Generic::List<Loop^>^ InnerEdges;
		System::Collections::Generic::List<Vertex^>^ Vertices;
		double Area;
		Vector^ Normal;
		Vertex^ Centroid;
		System::String^ Layer;

		Surface(Loop^ outer, System::Collections::Generic::List<Loop^>^ inner, Vector^ normal, Vertex^ centroid, double area, System::Collections::Generic::List<Vertex^>^ vertices, System::String^ layername)
		{
			this->OuterEdges = outer;
			this->InnerEdges = inner;
			this->Normal = normal;
			this->Centroid = centroid;
			this->Area = area;
			this->Vertices = vertices;
			this->Layer = layername;
		};

		Surface(){};
	internal:

		static Vertex^ GetCentroid(System::Collections::Generic::List<Vertex^>^ vertices, int vertexCount)
		{
			Vertex^ centroid = gcnew Vertex(0, 0, vertices[0]->Z);
			double signedArea = 0.0;
			double x0 = 0.0; // Current vertex X
			double y0 = 0.0; // Current vertex Y
			double x1 = 0.0; // Next vertex X
			double y1 = 0.0; // Next vertex Y
			double a = 0.0;  // Partial signed area

			// For all vertices except last
			int i = 0;
			for (i = 0; i<vertexCount - 1; ++i)
			{ 
				x0 = vertices[i]->X;
				y0 = vertices[i]->Y;
				x1 = vertices[i + 1]->X;
				y1 = vertices[i + 1]->Y;
				a = x0*y1 - x1*y0;
				signedArea += a;
				centroid->X += (x0 + x1)*a;
				centroid->Y += (y0 + y1)*a;
			}

			// Do last vertex separately to avoid performing an expensive
			// modulus operation in each iteration.
			x0 = vertices[i]->X;
			y0 = vertices[i]->Y;
			x1 = vertices[0]->X;
			y1 = vertices[0]->Y;
			a = x0*y1 - x1*y0;
			signedArea += a;
			centroid->X += (x0 + x1)*a;
			centroid->Y += (y0 + y1)*a;

			signedArea *= 0.5;
			centroid->X /= (6.0*signedArea);
			centroid->Y /= (6.0*signedArea);

			return centroid;
		}

		SUFaceRef ToSU()
		{
			int count = Vertices->Count;

			SULoopInputRef outer_loop = SU_INVALID;
			SULoopInputCreate(&outer_loop);

			SUPoint3D * points = (SUPoint3D *)malloc(*&count * sizeof(SUPoint3D));
			
			for (size_t i = 0; i < count; ++i) {
				SULoopInputAddVertexIndex(outer_loop, i);

				points[i] = Vertices[i]->ToSU();
			}

			SUFaceRef face = SU_INVALID;
			SUFaceCreate(&face, points, &outer_loop);

			return face;
		}

		static Surface^ FromSU(SUFaceRef face)
		{
			System::Collections::Generic::List<Loop^>^ inner = gcnew System::Collections::Generic::List<Loop^>();
			
			SULoopRef outer = SU_INVALID;
			SUFaceGetOuterLoop(face, &outer);
			
			size_t edgeCount = 0;
			SUFaceGetNumInnerLoops(face, &edgeCount);
			if (edgeCount > 0)
			{
				std::vector<SULoopRef> loops(edgeCount);
				SUFaceGetInnerLoops(face, edgeCount, &loops[0], &edgeCount);
			
				for (size_t j = 0; j < edgeCount; j++)
				{
					inner->Add(Loop::FromSU(loops[j]));
				}
			}


			SUVector3D vector = SU_INVALID;
			SUFaceGetNormal(face, &vector);
			Vector^ normal = Vector::FromSU(vector);

			double area = 0;
			SUFaceGetArea(face, &area);

			// Layer
			SULayerRef layer = SU_INVALID;
			SUDrawingElementGetLayer(SUFaceToDrawingElement(face),&layer);
			
			System::String^ layername = gcnew System::String("");
			if (!SUIsInvalid(layer))
			{
				layername = SketchUpSharp::Utilities::GetLayerName(layer);
			}
				

			System::Collections::Generic::List<Vertex^>^ vertices = gcnew System::Collections::Generic::List<Vertex^>();

			size_t verticesCount = 0;
			SUFaceGetNumVertices(face, &verticesCount);
			if (verticesCount > 0)
			{
				std::vector<SUVertexRef> vs(verticesCount);
				SUFaceGetVertices(face, verticesCount, &vs[0], &verticesCount);
				
				for (size_t j = 0; j < verticesCount; j++)
				{
					SUPoint3D pt = SU_INVALID;
					SUVertexGetPosition(vs[j], &pt);
					vertices->Add(Vertex::FromSU(pt));
				}
			}

			Vertex^ centroid = GetCentroid(vertices, vertices->Count);

			Surface^ v = gcnew Surface(Loop::FromSU(outer), inner, normal, centroid,area, vertices, layername);

			return v;
		};

	};


}