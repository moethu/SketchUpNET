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

		Surface(System::Collections::Generic::List<Corner^>^ corners, Vector^ normal)
		{
			this->Corners = corners;
			this->Normal = normal;
		};

		Surface(){};
	internal:
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



			Surface^ v = gcnew Surface(corners, normal);

			return v;
		};

	};


}