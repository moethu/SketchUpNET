// Copyright 2015 Trimble Navigation Ltd. All Rights Reserved.

#ifndef SKETCHUP_GEOMETRY_POINT2D_H_
#define SKETCHUP_GEOMETRY_POINT2D_H_


#include <SketchUpAPI/common.h>
#include <SketchUpAPI/geometry.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief          Creates a vector between two point objects.
 * @param point1   The first point object.
 * @param point2   The second point object.
 * @param vector   The vector from point1 to point2.
 * @return         Returns SU_ERROR_NONE on success.
 */
SU_RESULT SUPoint2DToSUPoint2D(const struct SUPoint2D* point1,
                               const struct SUPoint2D* point2,
                               struct SUVector2D* vector);

/**
* @brief        Determines if two points are equal.
* @param point1 The first point object.
* @param point2 The second point object.
* @param equal  Whether the two points are the same.
* @return       Returns SU_ERROR_NONE on success.
*/
SU_RESULT SUPoint2DGetEqual(const struct SUPoint2D* point1,
                            const struct SUPoint2D* point2,
                            bool* equal);

/**
 * @brief          Creates a new point that is offset from another point.
 * @param point1   The point object.
 * @param vector   The offset vector object.
 * @param point2   The new point.
 * @return         Returns SU_ERROR_NONE on success.
 */
SU_RESULT SUPoint2DOffset(const struct SUPoint2D* point1,
                          const struct SUVector2D* vector,
                          struct SUPoint2D* point2);

/**
 * @brief          Creates a vector between two point objects.
 * @param point1   The first point object.
 * @param point2   The second point object.
 * @param distance The distance between the two points.
 * @return         Returns SU_ERROR_NONE on success.
 */
SU_RESULT SUPoint2DDistanceToSUPoint2D(const struct SUPoint2D* point1,
                                       const struct SUPoint2D* point2,
                                       double* distance);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // SKETCHUP_GEOMETRY_POINT2D_H_
