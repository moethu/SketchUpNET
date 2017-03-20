// Copyright 2013 Trimble Navigation Ltd., All rights reserved.

#ifndef SKETCHUP_MODEL_GEOMETRY_H_
#define SKETCHUP_MODEL_GEOMETRY_H_

#include <SketchUpAPI/geometry.h>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
/**
@brief Transforms the provided 3D point by applying the provided 3D
       transformation.
@since SketchUp 2016, API 4.0
@param[in]     transform The transformation to be applied.
@param[in,out] point     The point to be transformed.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if transform is NULL
- \ref SU_ERROR_NULL_POINTER_OUTPUT if point NULL
*/
SU_RESULT SUPoint3DTransform(const struct SUTransformation* transform,
                             struct SUPoint3D* point);

/**
@brief Gets the position on the plane closest to the origin.
@since SketchUp 2016, API 4.0
@param[in]  plane    The plane from which to get the position.
@param[out] position The 3D point struct retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if plane is NULL
- \ref SU_ERROR_NULL_POINTER_OUTPUT if position NULL
*/
SU_RESULT SUPlane3DGetPosition(const struct SUPlane3D* plane,
                               struct SUPoint3D* position);

/**
@brief Gets the plane's unit normal vector.
@since SketchUp 2017, API 5.0
@param[in]  plane  The plane from which to get the normal.
@param[out] normal The 3D vector struct retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if plane is NULL
- \ref SU_ERROR_NULL_POINTER_OUTPUT if normal NULL
*/
SU_RESULT SUPlane3DGetNormal(const struct SUPlane3D* plane,
                             struct SUVector3D* normal);

/**
@brief Sets the transformation based on the provided point and normal vector.
       The resulting transformation transforms points/vectors to a new 
       coordinate system where the provided point is the new origin and the
       vector is the new z-axis. The other two axes in the transformed space
       are computed using the "Arbitrary axis algorithm".
@since SketchUp 2017, API 5.0
@param[out] transform The transformation to be set.
@param[in]  point     The point specifying the translation component of the
                      transformation.
@param[in]  normal    The 3D vector specifying the rotation component of the
                      transformation. This is treated as a unit vector, so any
                      scaling will be ignored.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_OUTPUT if transform is NULL
- \ref SU_ERROR_NULL_POINTER_INPUT if point or normal are NULL
*/
SU_RESULT SUTransformationSetFromPointAndNormal(
    struct SUTransformation* transform,
    const struct SUPoint3D* point,
    const struct SUVector3D* normal);

#ifdef __cplusplus
}  // end extern "C"
#endif  // __cplusplus

#endif  // SKETCHUP_MODEL_GEOMETRY_H_
