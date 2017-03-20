// Copyright 2013 Trimble Navigation Ltd. All Rights Reserved.
#ifndef SKETCHUP_MODEL_GEOMETRY_INPUT_H_
#define SKETCHUP_MODEL_GEOMETRY_INPUT_H_

#include <SketchUpAPI/geometry.h>
#include <SketchUpAPI/common.h>
#include <SketchUpAPI/model/defs.h>
#include <SketchUpAPI/model/curve.h>

#pragma pack(push, 8)
#ifdef __cplusplus
extern "C" {
#endif

/**
@struct SUGeometryInputRef
@brief  References a geometry input object. It is used as an input to
        /ref SUEntitiesFill.
*/

/**
@struct SULoopInputRef
@brief  References a loop input object.
*/
DEFINE_SU_TYPE(SULoopInputRef)

/**
@brief SUMaterialInput contains information that is needed to apply a
       material to a face. The conventional method for applying a material to
       a face is to use 1 to 4 UV coordinates, which are Cartesian textures
       coordinates and corresponding vertex indices on the face. The vertices
       are referenced by index into the top level SUGeometryInputRef's vertex
       array. The member variable 'material' must be a valid material object,
       and once the material input is used (e.g. with /ref SUEntitiesFill),
       the material object must not be released since it will be associated
       with a parent object.
*/
struct SUMaterialInput {
  size_t num_uv_coords; ///< Number of texture coordinates. 0 if no texture.
                        ///< 1 to 4 otherwise.

  struct SUPoint2D uv_coords[4]; ///< Texture coordinates.

  size_t vertex_indices[4]; ///< Vertex indices corresponding to the texture
                            ///< coordinates. Should reference the vertex array
                            ///< of the parent SUGeometryInputRef.

  SUMaterialRef material; ///< Material to be applied.
};

/**
@brief Creates a geometry input object.
@param[out] geom_input The object created. This object can be passed into
                       \ref SUEntitiesFill to populate an entities object.
                       It should be released subsequently by calling
                       \ref SUGeometryInputRelease.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_OUTPUT if geom_input is NULL
- \ref SU_ERROR_OVERWRITE_VALID if geom_input already references a valid object
*/
SU_RESULT SUGeometryInputCreate(SUGeometryInputRef* geom_input);

/**
@brief Deallocates a geometry input object.
@param[in] geom_input The object to deallocate.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if geom_input is NULL
- \ref SU_ERROR_INVALID_INPUT if geom_input points to an invalid object
*/
SU_RESULT SUGeometryInputRelease(SUGeometryInputRef* geom_input);

/**
@brief Adds a vertex to a geometry input object.
@param[in] geom_input The geometry input object.
@param[in] point      The location of the vertex to be added.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if geom_input is not valid
- \ref SU_ERROR_NULL_POINTER_INPUT if point is NULL
*/
SU_RESULT SUGeometryInputAddVertex(SUGeometryInputRef geom_input,
                                   const struct SUPoint3D* point);

/**
@brief Sets all vertices of a geometry input object. Any existing vertices will
       be overridden.
@param[in] geom_input   The geometry input object.
@param[in] num_vertices The number of vertices in the given point array.
@param[in] points       The points array containing the location of vertices.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if geom_input is not valid
- \ref SU_ERROR_NULL_POINTER_INPUT if points is NULL
*/
SU_RESULT SUGeometryInputSetVertices(SUGeometryInputRef geom_input,
                                     size_t num_vertices,
                                     const struct SUPoint3D points[]);

/**
@brief Adds an edge to a geometry input object. This method is intended for
       specifying edges which are not associated with loop inputs. For
       specifying edge properties on a face use the SULoopInput interface.
@since SketchUp 2017, API 5.0
@param[in]  geom_input       The geometry input object.
@param[in]  vertex0_index    The vertex index of the edge's first vertex.
@param[in]  vertex1_index    The vertex index of the edge's last vertex.
@param[out] added_edge_index (optional) If not NULL, returns the index of the
                             added edge.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if geom_input is not valid
- \ref SU_ERROR_OUT_OF_RANGE if vertex0_index or vertex1_index are greater than
       the total vertex count
- \ref SU_ERROR_INVALID_ARGUMENT if vertex0_index and vertex1_index are equal
*/
SU_RESULT SUGeometryInputAddEdge(SUGeometryInputRef geom_input,
                                 size_t vertex0_index,
                                 size_t vertex1_index,
                                 size_t* added_edge_index);

/**
@brief Sets the hidden flag of an edge in a geometry input object which is not
       associated with a loop input.
@since SketchUp 2017, API 5.0
@param[in] geom_input The geometry input object.
@param[in] edge_index The zero-based index of the edge which is not associated
                      with a loop input.
@param[in] hidden     The flag to set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if geom_input is not valid
- \ref SU_ERROR_OUT_OF_RANGE if edge_index references beyond the current total
       number of edges which are not associated with loop inputs
*/
SU_RESULT SUGeometryInputEdgeSetHidden(SUGeometryInputRef geom_input,
                                       size_t edge_index,
                                       bool hidden);

/**
@brief Sets the soft flag of an edge in a geometry input object which is not
       associated with a loop input.
@since SketchUp 2017, API 5.0
@param[in] geom_input The geometry input object.
@param[in] edge_index The zero-based index of the edge which is not associated
                      with a loop input.
@param[in] soft       The flag to set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if geom_input is not valid
- \ref SU_ERROR_OUT_OF_RANGE if edge_index references beyond the current total
       number of edges which are not associated with loop inputs
*/
SU_RESULT SUGeometryInputEdgeSetSoft(SUGeometryInputRef geom_input,
                                     size_t edge_index,
                                     bool soft);

/**
@brief Sets the smooth flag of an edge in a geometry input object which is not
       associated with a loop input.
@since SketchUp 2017, API 5.0
@param[in] geom_input The geometry input object.
@param[in] edge_index The zero-based index of the edge which is not associated
                      with a loop input.
@param[in] smooth     The flag to set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if geom_input is not valid
- \ref SU_ERROR_OUT_OF_RANGE if edge_index references beyond the current total
       number of edges which are not associated with loop inputs
*/
SU_RESULT SUGeometryInputEdgeSetSmooth(SUGeometryInputRef geom_input,
                                       size_t edge_index,
                                       bool smooth);

/**
@brief Sets the material of an edge in the geometry input.
@since SketchUp 2017, API 5.0
@param[in] geom_input The geometry input object.
@param[in] edge_index Index of the edge to set the material.
@param[in] material   The material to be set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if geom_input or material is not valid
- \ref SU_ERROR_OUT_OF_RANGE if edge_index references an edge beyond the total
edge count of geom_input
*/
SU_RESULT SUGeometryInputEdgeSetMaterial(SUGeometryInputRef geom_input,
                                         size_t edge_index,
                                         SUMaterialRef material);

/**
@brief Sets the layer of an edge in the geometry input.
@since SketchUp 2017, API 5.0
@param[in] geom_input The geometry input object.
@param[in] edge_index Index of the edge to set the layer.
@param[in] layer      The layer to be set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if geom_input or layer is not valid
- \ref SU_ERROR_OUT_OF_RANGE if edge_index references an edge beyond the total
edge count of geom_input
*/
SU_RESULT SUGeometryInputEdgeSetLayer(SUGeometryInputRef geom_input,
                                      size_t edge_index,
                                      SULayerRef layer);

/**
@brief Adds a curve to a geometry input object. This method is intended for
       specifying curves which are not associated with loop inputs. For
       specifying curves on faces use the SULoopInput interface.
@since SketchUp 2017, API 5.0
@param[in]  geom_input        The geometry input object.
@param[in]  num_edges         The number of edges to be used in the curve.
@param[in]  edge_indices      The edge indices to be used in defining the curve.
@param[out] added_curve_index (optional) If not NULL, returns the index of the
                               added curve.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if geom_input is not valid
- \ref SU_ERROR_NULL_POINTER_INPUT if edge_indices is NULL
- \ref SU_ERROR_OUT_OF_RANGE if any of the indices in edge_indices are greater
       than the total number of edges which are not associated with loop inputs
*/
SU_RESULT SUGeometryInputAddCurve(SUGeometryInputRef geom_input,
                                  size_t num_edges,
                                  const size_t edge_indices[],
                                  size_t* added_curve_index);

/**
@brief Creates a loop input object.
@param[out] loop_input The object created.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_OUTPUT if loop_input is NULL
- \ref SU_ERROR_OVERWRITE_VALID if loop_input already references a valid object
*/
SU_RESULT SULoopInputCreate(SULoopInputRef* loop_input);

/**
@brief Deallocates a loop input object.
@param[in] loop_input The object to deallocate.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if loop_input is NULL
- \ref SU_ERROR_INVALID_INPUT if loop_input points to an invalid object
*/
SU_RESULT SULoopInputRelease(SULoopInputRef* loop_input);

/**
@brief Adds a vertex index to a loop input object.
@param[in] loop_input   The loop input object.
@param[in] vertex_index The vertex index to add. This references a vertex within
                        the parent geometry input's vertex collection (as a
                        zero- based index).
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if loop_input is not valid
- \ref SU_ERROR_INVALID_INPUT if vertex_index already exists in the loop
*/
SU_RESULT SULoopInputAddVertexIndex(SULoopInputRef loop_input,
                                    size_t vertex_index);

/**
@brief Sets the hidden flag of an edge in a loop input object.
@param[in] loop_input The loop input object.
@param[in] edge_index The zero-based index of the edge within the loop.
@param[in] hidden     The flag to set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if loop_input is not valid
- \ref SU_ERROR_OUT_OF_RANGE if edge_index references beyond the current edge
  count
*/
SU_RESULT SULoopInputEdgeSetHidden(SULoopInputRef loop_input,
                                   size_t edge_index,
                                   bool hidden);

/**
@brief Sets the soft flag of an edge in a loop input object.
@param[in] loop_input The loop input object.
@param[in] edge_index The zero-based index of the edge within the loop.
@param[in] soft       The flag to set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if loop_input is not valid
- \ref SU_ERROR_OUT_OF_RANGE if edge_index references beyond the current edge
  count
*/
SU_RESULT SULoopInputEdgeSetSoft(SULoopInputRef loop_input,
                                 size_t edge_index,
                                 bool soft);

/**
@brief Sets the smooth flag of an edge in a loop input object.
@param[in] loop_input The loop input object.
@param[in] edge_index The zero-based index of the edge within the loop.
@param[in] smooth     The flag to set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if loop_input is not valid
- \ref SU_ERROR_OUT_OF_RANGE if edge_index references beyond the current edge
  count
*/
SU_RESULT SULoopInputEdgeSetSmooth(SULoopInputRef loop_input,
                                   size_t edge_index,
                                   bool smooth);

/**
@brief Sets the material of an edge in the loop input.
@since SketchUp 2017, API 5.0
@param[in] loop_input The loop input object.
@param[in] edge_index Index of the edge to set the material.
@param[in] material   The material to be set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if loop_input or material is not valid
- \ref SU_ERROR_OUT_OF_RANGE if edge_index references an edge beyond the total
edge count of loop_input
*/
SU_RESULT SULoopInputEdgeSetMaterial(SULoopInputRef loop_input,
                                     size_t edge_index,
                                     SUMaterialRef material);

/**
@brief Sets the layer of an edge in the loop input.
@since SketchUp 2017, API 5.0
@param[in] loop_input The loop input object.
@param[in] edge_index Index of the edge to set the layer.
@param[in] layer      The layer to be set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if loop_input or layer is not valid
- \ref SU_ERROR_OUT_OF_RANGE if edge_index references an edge beyond the total
edge count of loop_input
*/
SU_RESULT SULoopInputEdgeSetLayer(SULoopInputRef loop_input,
                                  size_t edge_index,
                                  SULayerRef layer);

/**
@brief Adds a simple curve to a loop input object.
@param[in] loop_input       The loop input object.
@param[in] first_edge_index First edge index to be associated with the curve.
@param[in] last_edge_index  Last edge index to be associated with the curve.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if loop_input is not valid
- \ref SU_ERROR_OUT_OF_RANGE if first_edge_index or last_edge_index reference an
  edge beyond the loop's total edge count
*/
SU_RESULT SULoopInputAddCurve(SULoopInputRef loop_input,
                              size_t first_edge_index,
                              size_t last_edge_index);

/**
@brief Adds a face to a geometry input object with a given outer loop for the
       face.
@param[in]  geom_input       The geometry input object.
@param[in]  outer_loop       The outer loop to be set for the face. If the
                             function succeeds (i.e. returns SU_ERROR_NONE),
                             this loop will be deallocated.
@param[out] added_face_index (optional) If not NULL, returns the index of the
                              added face.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if geom_input is not valid
- \ref SU_ERROR_NULL_POINTER_INPUT if outer_loop is NULL
*/
SU_RESULT SUGeometryInputAddFace(SUGeometryInputRef geom_input,
                                 SULoopInputRef* outer_loop,
                                 size_t* added_face_index);

/**
@brief Sets a flag in the geometry input that, when true, will create a face by
       reversing the orientations of all of its loops.
@param[in] geom_input The geometry input object.
@param[in] face_index Index of the face to be reversed.
@param[in] reverse    The given reverse flag.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if geom_input is not valid
- \ref SU_ERROR_OUT_OF_RANGE if face_index references a face beyond the total
  face count of geom_input
*/
SU_RESULT SUGeometryInputFaceSetReverse(SUGeometryInputRef geom_input,
                                        size_t face_index,
                                        bool reverse);

/**
@brief Sets the layer of a face in the geometry input.
@param[in] geom_input The geometry input object.
@param[in] face_index Index of the face to be reversed.
@param[in] layer      The layer to be set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if geom_input or layer is not valid
- \ref SU_ERROR_OUT_OF_RANGE if face_index references a face beyond the total
  face count of geom_input
*/
SU_RESULT SUGeometryInputFaceSetLayer(SUGeometryInputRef geom_input,
                                      size_t face_index,
                                      SULayerRef layer);

/**
@brief Adds an inner loop to a face in the geometry input.
@param[in] geom_input The geometry input object.
@param[in] face_index Index of the face to receive the inner loop.
@param[in] loop_input The inner loop to be added. If the function succeeds
                      (i.e. returns SU_ERROR_NONE), this loop will be
                      deallocated.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if geom_input is not valid
- \ref SU_ERROR_OUT_OF_RANGE if face_index references a face beyond the total
  face count of geom_input. Returns SU_ERROR_NULL_POINTER_INPUT if loop_input is
  NULL
*/
SU_RESULT SUGeometryInputFaceAddInnerLoop(SUGeometryInputRef geom_input,
                                          size_t face_index,
                                          SULoopInputRef* loop_input);

/**
@brief Sets the front material of a face in the geometry input.
@param[in] geom_input     The geometry input object.
@param[in] face_index     Index of the face to receive the material.
@param[in] material_input The material input to set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if geom_input is not valid
- \ref SU_ERROR_OUT_OF_RANGE if face_index references a face beyond the total
  face count of geom_input
- \ref SU_ERROR_NULL_POINTER_INPUT if material_input is NULL
*/
SU_RESULT SUGeometryInputFaceSetFrontMaterial(
    SUGeometryInputRef geom_input,
    size_t face_index,
    const struct SUMaterialInput* material_input);

/**
@brief Sets the back material of a face in the geometry input.
@param[in] geom_input     The geometry input object.
@param[in] face_index     Index of the face to receive the material.
@param[in] material_input The material input to set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if geom_input is not valid
- \ref SU_ERROR_OUT_OF_RANGE if face_index references a face beyond the total
  face count of geom_input
- \ref SU_ERROR_NULL_POINTER_INPUT if material_input is NULL
*/
SU_RESULT SUGeometryInputFaceSetBackMaterial(
    SUGeometryInputRef geom_input,
    size_t face_index,
    const struct SUMaterialInput* material_input);

/**
@brief Sets a flag in the geometry input that, when true, will create a hidden
       face.
@since SketchUp 2017, API 5.0
@param[in] geom_input The geometry input object.
@param[in] face_index Index of the face to be hidden.
@param[in] hidden     The given hidden flag.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if geom_input is not valid
- \ref SU_ERROR_OUT_OF_RANGE if face_index references a face beyond the total
       face count of geom_input
*/
SU_RESULT SUGeometryInputFaceSetHidden(SUGeometryInputRef geom_input,
                                       size_t face_index, bool hidden);

#ifdef __cplusplus
}  // extern "C"
#endif
#pragma pack(pop)

#endif  // SKETCHUP_MODEL_GEOMETRY_INPUT_H_
