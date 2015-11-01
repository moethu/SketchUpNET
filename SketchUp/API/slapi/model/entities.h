// Copyright 2013 Trimble Navigation Ltd. All Rights Reserved.
#ifndef SLAPI_MODEL_ENTITIES_H_
#define SLAPI_MODEL_ENTITIES_H_

#include <slapi/geometry.h>
#include <slapi/slapi.h>
#include <slapi/unicodestring.h>
#include <slapi/model/curve.h>
#include <slapi/model/defs.h>

#pragma pack(push, 8)
#ifdef __cplusplus
extern "C" {
#endif

/**
@struct SUEntitiesRef
@brief References a container object for all entities in a model,
       component definition or a group.
*/

/**
@brief SUEntitiesFill is the fastest way to populate an entities object. The
       important precondition is that no duplicate data should be given.
@param[in] entities      The entities to populate. Must be an empty entities
                         object.
@param[in] geom_input    The geometry input that the entities object is to be
                         populated with.
@param[in] weld_vertices Flag indicating whether to join coincident vertices.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities or geom_input are invalid objects
*/
SU_RESULT SUEntitiesFill(SUEntitiesRef entities,
                         SUGeometryInputRef geom_input,
                         bool weld_vertices);

/**
@brief Retrieves the bounding box of the entities.
@param[in]  entities The entities object.
@param[out] bbox     The bounding box retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if bbox is NULL
*/
SU_RESULT SUEntitiesGetBoundingBox(SUEntitiesRef entities,
                                   struct SUBoundingBox3D* bbox);

/**
@brief Retrieves the number of faces in the entities object.
@param[in] entities The entities object.
@param[out] count   The number of faces.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if count is NULL
*/
SU_RESULT SUEntitiesGetNumFaces(SUEntitiesRef entities, size_t* count);

/**
@brief Retrieves the faces in the entities object.
@param[in]  entities The entities object.
@param[in]  len      The number of faces to retrieve.
@param[out] faces    The faces retrieved.
@param[out] count    The number of faces retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if faces or count is NULL
*/
SU_RESULT SUEntitiesGetFaces(SUEntitiesRef entities,
                             size_t len,
                             SUFaceRef faces[],
                             size_t*  count);

/**
@brief Retrieves the number of curves in the entities object that are not
       associated with a face.
@param[in]  entities The entities object.
@param[out] count    The number of curves.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if count is NULL
*/
SU_RESULT SUEntitiesGetNumCurves(SUEntitiesRef entities, size_t* count);

/**
@brief Retrieves the curves in the entities object that are not associated with
       a face.
@param[in]  entities The entities object.
@param[in]  len      The number of curves to retrieve.
@param[out] curves   The curves retrieved.
@param[out] count    The number of curves retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if curves or count is NULL
*/
SU_RESULT SUEntitiesGetCurves(SUEntitiesRef entities,
                              size_t len,
                              SUCurveRef curves[],
                              size_t* count);


/**
@brief Retrieves the number of guide points in the entities object.
@since SketchUp 2014 M1, API 2.1
@param[in]  entities The entities object.
@param[out] count    The number of guide_points.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if count is NULL
*/
SU_RESULT SUEntitiesGetNumGuidePoints(SUEntitiesRef entities,
                                      size_t* count);

/**
@brief Retrieves the guide points in the entities object.
@since SketchUp 2014 M1, API 2.1
@param[in]  entities     The entities object.
@param[in]  len          The number of guide points to retrieve.
@param[out] guide_points The guide_points retrieved.
@param[out] count        The number of guide_points retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if guide_points or count is NULL
*/
SU_RESULT SUEntitiesGetGuidePoints(SUEntitiesRef entities,
                                   size_t len,
                                   SUGuidePointRef guide_points[],
                                   size_t* count);

/**
@brief Retrieves the number of edges in the entities object.
@param[in]  entities        The entities object.
@param[in]  standalone_only Whether to count all edges (false) or only the edges
                            not attached to curves and faces (true).
@param[out] count           The number of edges.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if count is NULL
*/
SU_RESULT SUEntitiesGetNumEdges(SUEntitiesRef entities,
                                bool standalone_only,
                                size_t* count);

/**
@brief Retrieves the edges in the entities object.
@param[in]  entities        The entities object.
@param[in]  standalone_only Whether to get all edges (false) or only the edges
                            not attached to curves and faces (true).
@param[in]  len             The number of edges to retrieve.
@param[out] edges           The edges retrieved.
@param[out] count           The number of edges retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if edges or count is NULL
*/
SU_RESULT SUEntitiesGetEdges(SUEntitiesRef entities,
                             bool standalone_only, size_t len,
                             SUEdgeRef edges[], size_t* count);

/**
@brief Retrieves the number of polyline3d's in the entities object.
@param[in]  entities The entities object.
@param[out] count    The the number of polyline3d's.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if count is NULL
*/
SU_RESULT SUEntitiesGetNumPolyline3ds(SUEntitiesRef entities,
                                      size_t* count);

/**
@brief Retrieves the polyline3d's in the entities object.
@param[in]  len      The number of polyline3d's to retrieve.
@param[in]  entities The entities object.
@param[out] lines    The polyline3d's retrieved.
@param[out] count    The number of polyline3d's retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if lines or count is NULL
*/
SU_RESULT SUEntitiesGetPolyline3ds(SUEntitiesRef entities,
                                   size_t len,
                                   SUPolyline3dRef lines[],
                                   size_t* count);

/**
@brief Adds face objects to a entities object.
@param[in] entities The entities object.
@param[in] len      The length of the array of face objects.
@param[in] faces    The array of face objects to add.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if faces is NULL
*/
SU_RESULT SUEntitiesAddFaces(SUEntitiesRef entities,
                             size_t len,
                             const SUFaceRef faces[]);

/**
@brief Adds edge objects to an entities object.
@param[in] entities The entities object.
@param[in] len      The length of the array of edge objects.
@param[in] edges    The array of edge objects to add.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if edges is NULL
*/
SU_RESULT SUEntitiesAddEdges(SUEntitiesRef entities,
                             size_t len,
                             const SUEdgeRef edges[]);

/**
@brief Adds curve objects to an entities object.
@param[in] entities The entities object.
@param[in] len      The length of the array of curve objects.
@param[in] curves   The array of curve objects to add.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if curves is NULL
*/
SU_RESULT SUEntitiesAddCurves(SUEntitiesRef entities,
                              size_t len,
                              const SUCurveRef curves[]);


/**
@brief Adds guide point objects to an entities object.
@since SketchUp 2014 M1, API 2.1
@param[in] entities     The entities object.
@param[in] len          The length of the array of guide point objects.
@param[in] guide_points The array of guide point objects to add.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if guide_points is NULL
*/
SU_RESULT SUEntitiesAddGuidePoints(SUEntitiesRef entities, size_t len,
    const SUGuidePointRef guide_points[]);

/**
@brief Adds a group object to an entities object.
@param[in] entities The entities object.
@param[in] group    The group object to add.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities or group is not a valid object
*/
SU_RESULT SUEntitiesAddGroup(SUEntitiesRef entities, SUGroupRef group);

/**
@brief Adds an image object to an entities object.
@param[in] entities The entities object.
@param[in] image    The image object to add.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities or image is not a valid object
*/
SU_RESULT SUEntitiesAddImage(SUEntitiesRef entities, SUImageRef image);

/**
@brief Adds a component instance object to the entities.
@param[in]  entities The entities object.
@param[in]  instance The component instance object to add.
@param[out] name     The unique name that is assigned to definition of the
                     component instance. This can be NULL in which case the
                     caller does not need to retrieve the assigned name.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities or instance is not a valid object
- \ref SU_ERROR_INVALID_OUTPUT if name (when not NULL) does not refer to a valid
  \ref SUStringRef object
*/
SU_RESULT SUEntitiesAddInstance(SUEntitiesRef entities,
                                SUComponentInstanceRef instance,
                                SUStringRef* name);

/**
@brief Retrieves the number of groups in the entities.
@param[in]  entities The entities object.
@param[out] count    The number of groups.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is an invalid entities object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if count is NULL
*/
SU_RESULT SUEntitiesGetNumGroups(SUEntitiesRef entities, size_t* count);

/**
@brief Retrieves the groups in the entities.
@param[in]  entities The entities object.
@param[in]  len      The number of groups to retrieve.
@param[out] groups   The groups retrieved.
@param[out] count    The number of groups retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if groups or count is NULL
*/
SU_RESULT SUEntitiesGetGroups(SUEntitiesRef entities,
                              size_t len,
                              SUGroupRef groups[],
                              size_t* count);

/**
@brief Retrieves the number of images in the entities.
@param[in]  entities  The entities object.
@param[out] count     The number of image objects.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if count is NULL
*/
SU_RESULT SUEntitiesGetNumImages(SUEntitiesRef entities, size_t* count);

/**
@brief Retrieves the array of image objects of a entities object.
@param[in]  entities The entities object.
@param[in]  len      The number of image objects to retrieve.
@param[out] images   The image objects retrieved.
@param[out] count    The number of image objects retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if images or count is NULL
*/
SU_RESULT SUEntitiesGetImages(SUEntitiesRef entities,
                              size_t len,
                              SUImageRef images[],
                              size_t* count);

/**
@brief Retrieves the number of component instances in the entities.
@param[in] entities The entities object.
@param[out] count   The number of component instances.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is an invalid entities object.
- \ref SU_ERROR_NULL_POINTER_OUTPUT if count is NULL
*/
SU_RESULT SUEntitiesGetNumInstances(SUEntitiesRef entities, size_t* count);

/**
@brief Retrieves the component instances in the entities.
@param[in]  entities  The entities object.
@param[in]  len       The number of component instances to retrieve.
@param[out] instances The component instances retrieved.
@param[out] count     The number of component instances retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entities is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if instances or count is NULL
*/
SU_RESULT SUEntitiesGetInstances(SUEntitiesRef entities,
                                 size_t len,
                                 SUComponentInstanceRef instances[],
                                 size_t* count);

#ifdef __cplusplus
}  // extern "C"
#endif
#pragma pack(pop)

#endif  // SLAPI_MODEL_ENTITIES_H_
