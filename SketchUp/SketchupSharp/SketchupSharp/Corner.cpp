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
#include <msclr/marshal.h>
#include <vector>
#include "Vertex.h"

#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpSharp
{
	public ref class Corner
	{
	public:

		Vertex^ Start;
		Vertex^ End;

		Corner(Vertex ^ start, Vertex ^ end)
		{
			this->Start = start;
			this->End = end;
		};

		Corner(){};

		static Corner^ FromSU(SUEdgeRef edge)
		{
			SUVertexRef startVertex = SU_INVALID;
			SUVertexRef endVertex = SU_INVALID;
			SUEdgeGetStartVertex(edge, &startVertex);
			SUEdgeGetEndVertex(edge, &endVertex);
			SUPoint3D start;
			SUPoint3D end;
			SUVertexGetPosition(startVertex, &start);
			SUVertexGetPosition(endVertex, &end);
			
			Corner^ v = gcnew Corner(Vertex::FromSU(start), Vertex::FromSU(end));

			return v;
		};

	};


}