#include <slapi/slapi.h>
#include <slapi/geometry.h>
#include <slapi/initialize.h>
#include <slapi/unicodestring.h>
#include <slapi/model/model.h>
#include <slapi/model/entities.h>
#include <slapi/model/face.h>
#include <slapi/model/edge.h>
#include <slapi/model/vertex.h>
#include <vector>

namespace SketchUpSharp
{

	void Open(){}

	int main() {
		// Always initialize the API before using it
		SUInitialize();
		// Load the model from a file
		SUModelRef model = SU_INVALID;
		SUResult res = SUModelCreateFromFile(&model, "model.skp");
		// It's best to always check the return code from each SU function call.
		// Only showing this check once to keep this example short.
		if (res != SU_ERROR_NONE)
			return 1;
		// Get the entity container of the model.
		SUEntitiesRef entities = SU_INVALID;
		SUModelGetEntities(model, &entities);
		// Get all the faces from the entities object
		size_t faceCount = 0;
		SUEntitiesGetNumFaces(entities, &faceCount);
		if (faceCount > 0) {
			std::vector<SUFaceRef> faces(faceCount);
			SUEntitiesGetFaces(entities, faceCount, &faces[0], &faceCount);
			// Get all the edges in this face
			for (size_t i = 0; i < faceCount; i++) {
				size_t edgeCount = 0;
				SUFaceGetNumEdges(faces[i], &edgeCount);
				if (edgeCount > 0) {
					std::vector<SUEdgeRef> edges(edgeCount);
					SUFaceGetEdges(faces[i], edgeCount, &edges[0], &edgeCount);
					// Get the vertex positions for each edge
					for (size_t j = 0; j < edgeCount; j++) {
						SUVertexRef startVertex = SU_INVALID;
						SUVertexRef endVertex = SU_INVALID;
						SUEdgeGetStartVertex(edges[j], &startVertex);
						SUEdgeGetEndVertex(edges[j], &endVertex);
						SUPoint3D start;
						SUPoint3D end;
						SUVertexGetPosition(startVertex, &start);
						SUVertexGetPosition(endVertex, &end);
						// Now do something with the point data
					}
				}
			}
		}
		// Get model name
		SUStringRef name = SU_INVALID;
		SUStringCreate(&name);
		SUModelGetName(model, &name);
		size_t name_length = 0;
		SUStringGetUTF8Length(name, &name_length);
		char* name_utf8 = new char[name_length + 1];
		SUStringGetUTF8(name, name_length + 1, name_utf8, &name_length);
		// Now we have the name in a form we can use
		SUStringRelease(&name);
		delete[]name_utf8;
		// Must release the model or there will be memory leaks
		SUModelRelease(&model);
		// Always terminate the API when done using it
		SUTerminate();
		return 0;
	}
}