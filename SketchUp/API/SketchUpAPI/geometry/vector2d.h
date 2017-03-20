// Copyright 2015 Trimble Navigation Ltd. All Rights Reserved.

#ifndef SKETCHUP_GEOMETRY_VECTOR2D_H_
#define SKETCHUP_GEOMETRY_VECTOR2D_H_


#include <SketchUpAPI/common.h>
#include <SketchUpAPI/geometry.h>

#ifdef __cplusplus
extern "C" {
#endif

  /**
  * @brief        Determines if a vector is valid.
  * @param vector The vector object.
  * @param valid  Whether the vector is valid.
  * @return       Returns SU_ERROR_NONE on success.
  */
SU_RESULT SUVector2DIsValid(const struct SUVector2D* vector,
                            bool* valid);

/**
* @brief          Determines if two vectors are parallel.
* @param vector1  The first vector object.
* @param vector2  The second vector object.
* @param parallel Whether the vectors are parallel.
* @return         Returns SU_ERROR_NONE on success.
*/
SU_RESULT SUVector2DIsParallelTo(const struct SUVector2D* vector1,
                                 const struct SUVector2D* vector2,
                                 bool* parallel);

/**
* @brief               Determines if two vectors are perpendicular.
* @param vector1       The first vector object.
* @param vector2       The second vector object.
* @param perpendicular Whether the vectors are perpendicular.
* @return              Returns SU_ERROR_NONE on success.
*/
SU_RESULT SUVector2DIsPerpendicularTo(const struct SUVector2D* vector1,
                                      const struct SUVector2D* vector2,
                                      bool* perpendicular);

/**
* @brief                Determines if two vectors are pointing the same direction.
* @param vector1        The first vector object.
* @param vector2        The second vector object.
* @param same_direction Whether the vectors are pointing in the same direction.
* @return               Returns SU_ERROR_NONE on success.
*/
SU_RESULT SUVector2DIsSameDirectionAs(const struct SUVector2D* vector1,
                                      const struct SUVector2D* vector2,
                                      bool* same_direction);

/**
* @brief         Determines if two vectors are equal.
* @param vector1 The first vector object.
* @param vector2 The second vector object.
* @param equal   Whether the vectors are equal.
* @return        Returns SU_ERROR_NONE on success.
*/
SU_RESULT SUVector2DIsEqual(const struct SUVector2D* vector1,
                            const struct SUVector2D* vector2,
                            bool* equal);

/**
 * @brief        Normalizes a vector.
 * @param vector The vector object.
 * @return       Returns SU_ERROR_NONE on success.
 */
SU_RESULT SUVector2DNormalize(struct SUVector2D* vector);

/**
 * @brief        Reverses a vector.
 * @param vector The vector object.
 * @return       Returns SU_ERROR_NONE on success.
 */
SU_RESULT SUVector2DReverse(struct SUVector2D* vector);

/**
 * @brief         Computes the dot product of two vectors.
 * @param vector1 The first vector object.
 * @param vector2 The second vector object.
 * @param dot     The value of vector1.Dot(vector2).
 * @return        Returns SU_ERROR_NONE on success.
 */
SU_RESULT SUVector2DDot(const struct SUVector2D* vector1,
                        const struct SUVector2D* vector2,
                        double* dot);

/**
 * @brief         Computes the cross product of two vectors.
 * @param vector1 The first vector object.
 * @param vector2 The second vector object.
 * @param cross   The value of vector1.Cross(vector2).
 * @return        Returns SU_ERROR_NONE on success.
 */
SU_RESULT SUVector2DCross(const struct SUVector2D* vector1,
                          const struct SUVector2D* vector2,
                          double* cross);

/**
* @brief                Determines if a vector has a length of one.
* @param vector         The vector object.
* @param is_unit_vector Whether the vector has a length of one.
* @return               Returns SU_ERROR_NONE on success.
*/
SU_RESULT SUVector2DIsUnitVector(const struct SUVector2D* vector,
                                 bool* is_unit_vector);

/**
* @brief        Gets the length of a vector.
* @param vector The vector object.
* @param length The length of the vector.
* @return       Returns SU_ERROR_NONE on success.
*/
SU_RESULT SUVector2DGetLength(const struct SUVector2D* vector, double* length);
  
/**
 * @brief        Sets the length of a vector.
 * @param vector The vector object.
 * @param length The new length the vector should be.
 * @return       Returns SU_ERROR_NONE on success.
 */
SU_RESULT SUVector2DSetLength(struct SUVector2D* vector, double length);

/**
* @brief         Gets the angle between two vectors.
* @param vector1 The first vector object.
* @param vector2 The second vector object.
* @param angle   The angle between the vectors.
* @return        Returns SU_ERROR_NONE on success.
*/
SU_RESULT SUVector2DAngleBetween(const struct SUVector2D* vector1,
                                 const struct SUVector2D* vector2,
                                 double* angle);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // SKETCHUP_GEOMETRY_VECTOR2D_H_
