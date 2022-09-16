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
#include <SketchUpAPI/model/entity.h>
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
#include "Mesh.h"
#include "Material.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace SketchUpNET
{
	public ref class Surface
	{
	public:
		/// <summary>
		/// The outer edges of the surface in a closed loop
		/// </summary>
		Loop^ OuterEdges;

		/// <summary>
		/// List of closed inner loops, representing holes
		/// </summary>
		List<Loop^>^ InnerEdges;

		/// <summary>
		/// All vertices of the surfaces are stored here
		/// </summary>
		List<Vertex^>^ Vertices;

		/// <summary>
		/// Meshed surface if read meshes has been activated when opening the model
		/// </summary>
		Mesh^ FaceMesh;

		/// <summary>
		/// Area of the surface
		/// </summary>
		double Area;

		/// <summary>
		/// Normal vector of the surface pointing upwards
		/// </summary>
		Vector^ Normal;

		/// <summary>
		/// Back side material
		/// </summary>
		Material^ BackMaterial;

		/// <summary>
		/// Front side material
		/// </summary>
		Material^ FrontMaterial;

		System::String^ Layer;

		/// <summary>
		/// Persistent ID (interhited from SUEntityRef)
		/// </summary>
		int64_t PersistentID;

		Surface(Loop^ outer, List<Loop^>^ inner, Vector^ normal, double area, List<Vertex^>^ vertices, Mesh^ m, System::String^ layername, Material^ backmat, Material^ frontmat, int64_t persistentID)
		{
			this->OuterEdges = outer;
			this->InnerEdges = inner;
			this->Normal = normal;
			this->FaceMesh = m;
			this->BackMaterial = backmat;
			this->FrontMaterial = frontmat;
			this->Area = area;
			this->Vertices = vertices;
			this->Layer = layername;
			this->PersistentID = persistentID;
		};

		Surface(){};

		/// <summary>
		/// Creates a new SketchUp Surface or Face from outer edges.
		/// This is the most simple method to create a new surface.
		/// Make sure the outer edges loop is closed and ordered.
		/// All lines need to be connected from start- to endpoints,
		/// the direction, CW or CCW doesn't matter.
		/// </summary>
		/// <param name="outer">Closed loop of outer edges</param>
		Surface(Loop^ outer) {
			this->OuterEdges = outer;
			this->InnerEdges = gcnew List<Loop^>();
		};

		/// <summary>
		/// Creates a new SketchUp Surface or Face from outer and inner edges.
		/// Make sure all edges of each loop are closed and ordered.
		/// All lines need to be connected from start- to endpoints,
		/// the direction, CW or CCW doesn't matter.
		/// </summary>
		/// <param name="outer">Closed loop of outer edges</param>
		/// <param name="inner">List of closed loops of inner edges</param>
		Surface(Loop^ outer, List<Loop^>^ inner) {
			this->InnerEdges = inner;
			this->OuterEdges = outer;
		};

	internal:

		static Vertex^ GetCentroid(List<Vertex^>^ vertices, int vertexCount)
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
			SUFaceRef face = SU_INVALID;
			SULoopInputRef outer_loop = SU_INVALID;
			SULoopInputCreate(&outer_loop);

			int count = OuterEdges->Edges->Count;
			if (count > 0) {
				SUPoint3D* points = (SUPoint3D*)malloc(*&count * sizeof(SUPoint3D));
				for (int i = 0; i < count; ++i) {
					SULoopInputAddVertexIndex(outer_loop, i);
					points[i] = OuterEdges->Edges[i]->Start->ToSU();
				}
				SUFaceCreate(&face, points, &outer_loop);
			} else {
				// Maintaining backwards compatibility for 
				// surfaces only consisting of outer vertices
				count = Vertices->Count;
				SUPoint3D* points = (SUPoint3D*)malloc(*&count * sizeof(SUPoint3D));
				for (int i = 0; i < count; ++i) {
					SULoopInputAddVertexIndex(outer_loop, i);
					points[i] = Vertices[i]->ToSU();
				}
				SUFaceCreate(&face, points, &outer_loop);
			}
			
			int innner_count = InnerEdges->Count;
			if (innner_count > 0) {
				for (int i = 0; i < innner_count; ++i) {
					SULoopInputRef inner_loop = SU_INVALID;
					SULoopInputCreate(&inner_loop);
					int count = InnerEdges[i]->Edges->Count;
					SUPoint3D* points = (SUPoint3D*)malloc(*&count * sizeof(SUPoint3D));
					for (int j = 0; j < count; ++j) {
						SULoopInputAddVertexIndex(inner_loop, j);
						points[j] = InnerEdges[i]->Edges[j]->Start->ToSU();
					}
					SUFaceAddInnerLoop(face, points, &inner_loop);
				}
			}		
			
			return face;
		}

		static SUFaceRef* ListToSU(List<Surface^>^ list)
		{
			size_t size = list->Count;
			SUFaceRef * result = (SUFaceRef *)malloc(*&size * sizeof(SUFaceRef));
			for (int i = 0; i < size; i++)
			{
				result[i] = list[i]->ToSU();
			}
			return result;
		}

		static Surface^ FromSU(SUFaceRef face, bool includeMeshes, System::Collections::Generic::Dictionary<String^, Material^>^ materials)
		{
			List<Loop^>^ inner = gcnew List<Loop^>();
			
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
				layername = Utilities::GetLayerName(layer);
			}
			
			int64_t persistentID;
			SUEntityGetPersistentID(SUFaceToEntity(face), &persistentID);
			
			List<Vertex^>^ vertices = gcnew List<Vertex^>();

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

			Mesh^ m = (includeMeshes)? Mesh::FromSU(face) : nullptr;

			SUMaterialRef mback = SU_INVALID;
			SUFaceGetBackMaterial(face, &mback);
			SUStringRef mbackNameRef = SU_INVALID;
			SUStringCreate(&mbackNameRef);
			SUMaterialGetName(mback, &mbackNameRef);
			System::String^ mbackName = SketchUpNET::Utilities::GetString(mbackNameRef);

			SUMaterialRef minner = SU_INVALID;
			SUFaceGetFrontMaterial(face, &minner);
			SUStringRef minnerNameRef = SU_INVALID;
			SUStringCreate(&minnerNameRef);
			SUMaterialGetName(minner, &minnerNameRef);
			
			System::String^ minnerName = SketchUpNET::Utilities::GetString(minnerNameRef);

			Material^ backMat = (materials->ContainsKey(mbackName)) ? materials[mbackName] : Material::FromSU(mback);
			Material^ frontMat = (materials->ContainsKey(minnerName)) ? materials[minnerName] : Material::FromSU(minner);

			Surface^ v = gcnew Surface(Loop::FromSU(outer), inner, normal, area, vertices,m, layername, backMat, frontMat, persistentID);

			return v;
		}


		static List<Surface^>^ GetEntitySurfaces(SUEntitiesRef entities, bool includeMeshes, System::Collections::Generic::Dictionary<String^, Material^>^ materials)
		{
			List<Surface^>^ surfaces = gcnew List<Surface^>();

			size_t faceCount = 0;
			SUEntitiesGetNumFaces(entities, &faceCount);

			if (faceCount > 0) {
				std::vector<SUFaceRef> faces(faceCount);
				SUEntitiesGetFaces(entities, faceCount, &faces[0], &faceCount);


				for (size_t i = 0; i < faceCount; i++) {
					Surface^ surface = Surface::FromSU(faces[i], includeMeshes, materials);
					surfaces->Add(surface);
				}
			}

			return surfaces;
		}

	};


}