// Copyright 2015 Trimble Navigation Ltd. All rights reserved.

#ifndef SKETCHUP_UTILS_MATH_HELPERS_H_
#define SKETCHUP_UTILS_MATH_HELPERS_H_

#include <SketchUpAPI/common.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
@brief Converts a value from degrees to radians.
@param[in] value A value in degrees.
@return    The value converted to radians.
*/
SU_EXPORT double DegreesToRadians(double value);

/**
@brief Converts a value from radians to degrees.
@param[in] value A value in radians.
@return    The value converted to degrees.
*/
SU_EXPORT double RadiansToDegrees(double value);

/**
@brief Compares two values for equality with a tolerance.
@param[in] val1 The first value.
@param[in] val2 The second value.
@return    True if the values are equal.
*/
SU_EXPORT bool Equals(double val1, double val2);

/**
@brief Compares two values with a tolerance to see if val1 is less than val2.
@param[in] val1 The first value.
@param[in] val2 The second value.
@return    True if val1 is less than val2.
*/
SU_EXPORT bool LessThan(double val1, double val2);

/**
@brief Compares two values with a tolerance to see if val1 is less than or equal
       to val2.
@param[in] val1 The first value.
@param[in] val2 The second value.
@return    True if val1 is less than or equal to val2.
*/
SU_EXPORT bool LessThanOrEqual(double val1, double val2);

/**
@brief Compares two values with a tolerance to see if val1 is greater than val2.
@param[in] val1 The first value.
@param[in] val2 The second value.
@return    True if val1 is greater than val2.
*/
SU_EXPORT bool GreaterThan(double val1, double val2);

/**
@brief Compares two values with a tolerance to see if val1 is greater than or
       equal to val2.
@param[in] val1 The first value.
@param[in] val2 The second value.
@return    True if val1 is greater than or equal to val2.
*/
SU_EXPORT bool GreaterThanOrEqual(double val1, double val2);

#ifdef __cplusplus
}  // end extern "C"
#endif  // __cplusplus

#endif // SKETCHUP_UTILS_MATH_HELPERS_H_
