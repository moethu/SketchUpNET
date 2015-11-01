// Copyright 2013 Trimble Navigation Ltd. All Rights Reserved.

#ifndef SLAPI_MODEL_POLYLINE3D_H_
#define SLAPI_MODEL_POLYLINE3D_H_

#include <slapi/slapi.h>
#include <slapi/geometry.h>
#include <slapi/model/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
@struct SUPolyline3dRef
@brief  A polyline3d object. These are curve-like entities that do not
        generate inference snaps or affect geometry in any way.
*/

/**
@brief  Converts from an \ref SUPolyline3dRef to an \ref SUEntityRef. This is
        essentially an upcast operation.
@param[in] line The polyline3d object.
@return
- The converted \ref SUEntityRef if line is a valid object. If not, the returned
  reference will be invalid.
*/
SU_EXPORT SUEntityRef SUPolyline3dToEntity(SUPolyline3dRef line);

/**
@brief  Converts from an \ref SUEntityRef to an \ref SUPolyline3dRef. This is
        essentially a downcast operation so the given entity must be convertible
        to an \ref SUPolyline3dRef.
@param[in] entity The given entity reference.
@return
- The converted \ref SUPolyline3dRef if the downcast operation succeeds. If not,
  the returned reference will be invalid.
*/
SU_EXPORT SUPolyline3dRef SUPolyline3dFromEntity(SUEntityRef entity);

/**
@brief  Converts from an \ref SUPolyline3dRef to an \ref SUDrawingElementRef.
        This is essentially an upcast operation.
@param[in] line The polyline3d object.
@return
- The converted \ref SUEntityRef if line is a valid object. If not, the returned
  reference will be invalid.
*/
SU_EXPORT SUDrawingElementRef SUPolyline3dToDrawingElement(SUPolyline3dRef
                                                           line);

/**
@brief  Converts from an \ref SUDrawingElementRef to an \ref SUPolyline3dRef.
        This is essentially a downcast operation so the given element must be
        convertible to an \ref SUPolyline3dRef.
@param[in] drawing_elem The drawing element object.
@return
- The converted \ref SUPolyline3dRef if the downcast operation succeeds. If not,
  the returned reference will be invalid.
*/
SU_EXPORT SUPolyline3dRef SUPolyline3dFromDrawingElement(SUDrawingElementRef
                                                         drawing_elem);

/**
@brief  Retrieves the number of points contained by a polyline3d.
@param[in]  line  The polyline3d object.
@param[out] count The number of points available.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if line is an invalid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if count is NULL
*/
SU_RESULT SUPolyline3dGetNumPoints(SUPolyline3dRef line, size_t* count);

/**
@brief  Retrieves the points in the polyline3d object.
@param[in]  line   The polyline3d object.
@param[in]  len    The maximum number of points to retrieve.
@param[out] points The points retrieved.
@param[out] count  The number of points retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if line is an invalid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if points or count is NULL
*/
SU_RESULT SUPolyline3dGetPoints(SUPolyline3dRef line,
                                size_t len,
                                struct SUPoint3D points[],
                                size_t* count);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // SLAPI_MODEL_POLYLINE3D_H_
