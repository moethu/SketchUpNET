/*

SketchUpSharp - a managed C++ Wrapper for the SketchUp C API
Copyright(C) 2015, Autor: Maximilian Thumfart

This program is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.

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
#include <msclr/marshal.h>
#include <vector>
#include "Corner.h"
#include "Layer.h"
#include "Vector.h"

#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpSharp
{
	public ref class Surface
	{
	public:

		System::Collections::Generic::List<Corner^>^ Corners;

		Vector^ Normal;
		Vertex^ Centroid;

		Surface(System::Collections::Generic::List<Corner^>^ corners, Vector^ normal, Vertex^ centroid)
		{
			this->Corners = corners;
			this->Normal = normal;
			this->Centroid = centroid;
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

		static Surface^ FromSU(SUFaceRef face)
		{
			System::Collections::Generic::List<Corner^>^ corners = gcnew System::Collections::Generic::List<Corner^>();

			size_t edgeCount = 0;
			SUFaceGetNumEdges(face, &edgeCount);
			if (edgeCount > 0)
			{
				std::vector<SUEdgeRef> edges(edgeCount);
				SUFaceGetEdges(face, edgeCount, &edges[0], &edgeCount);

				for (size_t j = 0; j < edgeCount; j++)
				{
					corners->Add(Corner::FromSU(edges[j]));
				}
			}

			SUVector3D vector = SU_INVALID;
			SUFaceGetNormal(face, &vector);
			Vector^ normal = Vector::FromSU(vector);

			//size_t openingsCount = 0;
			//SUFaceGetNumOpenings(face, &openingsCount);
			//if (openingsCount > 0)
			//{
			//	std::vector<SUOpeningRef> openings(openingsCount);
			//	SUFaceGetOpenings(face, openingsCount, &openings[0], &openingsCount);
			//}

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

			Surface^ v = gcnew Surface(corners, normal, centroid);

			return v;
		};

	};


}