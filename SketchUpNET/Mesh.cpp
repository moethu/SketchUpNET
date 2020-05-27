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
#include <SketchUpAPI/model/layer.h>
#include <SketchUpAPI/model/drawing_element.h>
#include <SketchUpAPI/model/mesh_helper.h>
#include <msclr/marshal.h>
#include <vector>
#include "loop.h"
#include "vertex.h"
#include "vector.h"
#include "utilities.h"
#include "MeshFace.h"


#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpNET
{
	public ref class Mesh
	{
	public:

		List<Vertex^>^ Vertices;
		List<Vector^>^ Normals;
		List<MeshFace^>^ Faces;

		System::String^ Layer;

		Mesh(List<Vertex^>^ vs, List<Vector^>^ ns, List<MeshFace^>^ faces, System::String^ layer)
		{
			this->Vertices = vs;
			this->Normals = ns;
			this->Faces = faces;
			this->Layer = layer;
		};

		Mesh() {};
	internal:



		static Mesh^ FromSU(SUFaceRef face)
		{
			List<Vertex^>^ vertices = gcnew List<Vertex^>();
			List<Vector^>^ vectors = gcnew List<Vector^>();
			List<MeshFace^>^ faces = gcnew List<MeshFace^>();
			
			// Layer
			SULayerRef layer = SU_INVALID;
			SUDrawingElementGetLayer(SUFaceToDrawingElement(face), &layer);

			System::String^ layername = gcnew System::String("");
			if (!SUIsInvalid(layer))
			{
				layername = Utilities::GetLayerName(layer);
			}
			
			SUMeshHelperRef helper = SU_INVALID;
			SUMeshHelperCreate(&helper, face);

			size_t vCount = 0;
			SUMeshHelperGetNumVertices(helper, &vCount);
			if (vCount > 0)
			{
				std::vector<SUPoint3D> vs(vCount);
				SUMeshHelperGetVertices(helper,vCount, &vs[0], &vCount);

				for (size_t j = 0; j < vCount; j++)
				{
					vertices->Add(Vertex::FromSU(vs[j]));
				}
			}



			size_t fCount = 0;
			size_t ret = 0;
			SUMeshHelperGetNumTriangles(helper, &fCount);
			if (fCount > 0)
			{
				
				std::vector<size_t> fs(3 * fCount);
				SUMeshHelperGetVertexIndices(helper, 3*fCount, &fs[0], &ret);

				for (size_t j = 0; j < 3*fCount; j=j+3)
				{
					faces->Add(gcnew MeshFace(fs[j], fs[j+1], fs[j + 2]));
				}
			}


			size_t nCount = 0;
			SUMeshHelperGetNumTriangles(helper, &nCount);
			if (nCount > 0)
			{
				std::vector<SUVector3D> norms(nCount);
				SUMeshHelperGetNormals(helper, nCount, &norms[0], &nCount);

				for (size_t j = 0; j < nCount; j++)
				{
					vectors->Add(Vector::FromSU(norms[j]));
				}
			}

			SUMeshHelperRelease(&helper);

			Mesh^ m = gcnew Mesh(vertices,vectors, faces, layername);

			return m;
		}


	};


}