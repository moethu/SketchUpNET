// Copyright 2017 Trimble Inc. All Rights Reserved.

#ifndef SKETCHUP_GEOMETRY_POINT2D_H_
#define SKETCHUP_GEOMETRY_POINT2D_H_


#include <SketchUpAPI/common.h>
#include <SketchUpAPI/geometry.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
@brief Creates a vector between two point objects.
@since SketchUp 2017, API 5.0
@deprecated The functionality is replaced by SUVector2DCreate.
@param[in]  point1   The first point object.
@param[in]  point2   The second point object.
@param[out] vector   The vector from point1 to point2.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if point1 or point2 is NULL
- \ref SU_ERROR_NULL_POINTER_OUTPUT if vector is NULL
 */
SU_DEPRECATED_FUNCTION("6.0")
SU_RESULT SUPoint2DToSUPoint2D(const struct SUPoint2D* point1,
                               const struct SUPoint2D* point2,
                               struct SUVector2D* vector);

/**
@brief Determines if two points are equal.
@since SketchUp 2017, API 5.0
@param[in]  point1 The first point object.
@param[in]  point2 The second point object.
@param[out] equal  Whether the two points are the same.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if point1 or point2 is NULL
- \ref SU_ERROR_NULL_POINTER_OUTPUT if equal is NULL
*/
SU_RESULT SUPoint2DGetEqual(const struct SUPoint2D* point1,
                            const struct SUPoint2D* point2,
                            bool* equal);

/**
@brief Creates a new point that is offset from another point.
@since SketchUp 2017, API 5.0
@param[in]  point1 The point object.
@param[in]  vector The offset vector object.
@param[out] point2 The new point.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if point1 or vector is NULL
- \ref SU_ERROR_NULL_POINTER_OUTPUT if point2 is NULL
 */
SU_RESULT SUPoint2DOffset(const struct SUPoint2D* point1,
                          const struct SUVector2D* vector,
                          struct SUPoint2D* point2);

/**
@brief Gets the distance between two point objects.
@since SketchUp 2017, API 5.0
@param[in]  point1   The first point object.
@param[in]  point2   The second point object.
@param[out] distance The distance between the two points.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if point1 or point2 is NULL
- \ref SU_ERROR_NULL_POINTER_OUTPUT if distance is NULL
 */
SU_RESULT SUPoint2DDistanceToSUPoint2D(const struct SUPoint2D* point1,
                                       const struct SUPoint2D* point2,
                                       double* distance);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // SKETCHUP_GEOMETRY_POINT2D_H_
