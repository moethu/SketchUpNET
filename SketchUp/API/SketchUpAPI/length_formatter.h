// Copyright 2017 Trimble Inc. All Rights Reserved.
#ifndef SKETCHUP_LENGTH_FORMATTER_H_
#define SKETCHUP_LENGTH_FORMATTER_H_

#include <SketchUpAPI/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
@struct SULengthFormatterRef
@brief References a length formatter object. Length formatters are used to
       generate formatted strings (optionally with units) from length, area,
       and volume values. Additionally length formatters can be used to
       translate a formatted length/area/volume string into a value. Accessors
       and setters are exposed for some of the key formatting properties,
       facilitating customization of the formater. In cases when users want the
       formatter to reflect the properties of a model, SUModelGetLengthFormatter
       should be used to more efficiently extract/copy the relevant properties
       from the model to the formatter.
@since SketchUp 2018, API 6.0
*/

/**
@enum SULengthFormatType
@brief Indicates the different supported length string formatting types
@since SketchUp 2018, API 6.0
*/
enum SULengthFormatType {
  SU_LFORMAT_DECIMAL,
  SU_LFORMAT_ARCHITECTURAL,
  SU_LFORMAT_ENGINEERING,
  SU_LFORMAT_FRACTIONAL
};

/**
@enum SULengthUnitType
@brief Indicates the different supported length string formatting units
@since SketchUp 2018, API 6.0
*/
enum SULengthUnitType {
  SU_LUNIT_INCHES,
  SU_LUNIT_FEET,
  SU_LUNIT_MILLIMETER,
  SU_LUNIT_CENTIMETER,
  SU_LUNIT_METER
};

/**
@brief Creates a new length formatter with default properties.
@since SketchUp 2018, API 6.0
@param[out] formatter The formatter object created.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_OUTPUT if formatter is NULL
- \ref SU_ERROR_OVERWRITE_VALID if formatter already references a valid object
*/
SU_RESULT SULengthFormatterCreate(SULengthFormatterRef* formatter);

/**
@brief Releases a length formatter object.
@since SketchUp 2018, API 6.0
@param[in] formatter The formatter object.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if formatter is an invalid object
- \ref SU_ERROR_NULL_POINTER_INPUT if formatter is NULL
*/
SU_RESULT SULengthFormatterRelease(SULengthFormatterRef* formatter);

/**
@brief Retrieves the precision of a length formatter.
@since SketchUp 2018, API 6.0
@param[in]  formatter The formatter object.
@param[out] precision The precision retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if formatter is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if precision is NULL
 */
SU_RESULT SULengthFormatterGetPrecision(SULengthFormatterRef formatter,
    size_t* precision);

/**
@brief Sets the precision of a length formatter.
@since SketchUp 2018, API 6.0
@param[in] formatter The formatter object.
@param[in] precision The precision to be set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if formatter is not a valid object
 */
SU_RESULT SULengthFormatterSetPrecision(SULengthFormatterRef formatter,
    size_t precision);

/**
@brief Retrieves the format of a length formatter.
@since SketchUp 2018, API 6.0
@param[in]  formatter The formatter object.
@param[out] format    The format retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if formatter is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if format is NULL
 */
SU_RESULT SULengthFormatterGetFormat(SULengthFormatterRef formatter,
    enum SULengthFormatType* format);

/**
@brief Sets the format of a length formatter.
@since SketchUp 2018, API 6.0
@param[in] formatter The formatter object.
@param[in] format    The format to be set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if formatter is not a valid object
- \ref SU_ERROR_OUT_OF_RANGE if format is not a supported option
 */
SU_RESULT SULengthFormatterSetFormat(SULengthFormatterRef formatter,
    enum SULengthFormatType format);

/**
@brief Retrieves the units of a length formatter.
@since SketchUp 2018, API 6.0
@param[in]  formatter The formatter object.
@param[out] units     The unit type retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if formatter is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if units is NULL
 */
SU_RESULT SULengthFormatterGetUnits(SULengthFormatterRef formatter,
    enum SULengthUnitType* units);

/**
@brief Sets the units of a length formatter.
@since SketchUp 2018, API 6.0
@param[in] formatter The formatter object.
@param[in] units     The unit type to be set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if formatter is not a valid object
- \ref SU_ERROR_OUT_OF_RANGE if units is not a supported option
 */
SU_RESULT SULengthFormatterSetUnits(SULengthFormatterRef formatter,
    enum SULengthUnitType units);

/**
@brief Retrieves whether units are suppressed.
@since SketchUp 2018, API 6.0
@param[in]  formatter The formatter object.
@param[out] suppress  The unit suppression flag retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if formatter is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if suppress is NULL
*/
SU_RESULT SULengthFormatterGetSuppressUnits(SULengthFormatterRef formatter,
    bool* suppress);

/**
@brief Sets whether units are suppressed.
@since SketchUp 2018, API 6.0
@param[in] formatter The formatter object.
@param[in] suppress  The unit suppression flag to be set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if formatter is not a valid object
*/
SU_RESULT SULengthFormatterSetSuppressUnits(SULengthFormatterRef formatter,
    bool suppress);

/**
@brief Retrieves a formatted length string from the provided length value.
@since SketchUp 2018, API 6.0
@param[in]  formatter The formatter object.
@param[in]  length    The length value.
@param[in]  strip     Whether to strip trailing zeros, leading ~, and decimal
                      point if it is the last character.
@param[out] string    The formatted string retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if formatter is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if suppress is string
- \ref SU_ERROR_INVALID_OUTPUT if *string is not a valid object
*/
SU_RESULT SULengthFormatterGetLengthString(SULengthFormatterRef formatter,
    double length, bool strip, SUStringRef* string);

/**
@brief Retrieves a formatted area string from the provided area value.
@since SketchUp 2018, API 6.0
@param[in]  formatter The formatter object.
@param[in]  area      The area value.
@param[out] string    The formatted string retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if formatter is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if suppress is string
- \ref SU_ERROR_INVALID_OUTPUT if *string is not a valid object
*/
SU_RESULT SULengthFormatterGetAreaString(SULengthFormatterRef formatter,
    double area, SUStringRef* string);

/**
@brief Retrieves a formatted volume string from the provided volume value.
@since SketchUp 2018, API 6.0
@param[in]  formatter The formatter object.
@param[in]  volume    The volume value.
@param[out] string    The formatted string retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if formatter is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if suppress is string
- \ref SU_ERROR_INVALID_OUTPUT if *string is not a valid object
*/
SU_RESULT SULengthFormatterGetVolumeString(SULengthFormatterRef formatter,
    double volume, SUStringRef* string);

/**
@brief Parses a formatted length string getting the numeric value.
@since SketchUp 2018, API 6.0
@param[in]  formatter The formatter object.
@param[in]  string    The formatted string.
@param[out] value     The numeric value retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if formatter or string are not a valid objects
- \ref SU_ERROR_NULL_POINTER_OUTPUT if value is NULL
- \ref SU_ERROR_INVALID_ARGUMENT if the string could not be parsed
*/
SU_RESULT SULengthFormatterParseString(SULengthFormatterRef formatter,
    SUStringRef string, double* value);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // SKETCHUP_LENGTH_FORMATTER_H_
