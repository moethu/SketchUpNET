// Copyright 2013 Trimble Navigation Ltd.  All Rights Reserved

#ifndef SLAPI_MODEL_OPTIONS_PROVIDER_H_
#define SLAPI_MODEL_OPTIONS_PROVIDER_H_

#include <slapi/slapi.h>
#include <slapi/unicodestring.h>
#include <slapi/model/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
@struct SUOptionsProviderRef
@brief  Provides ability to get and set options on an options provider object.
        Available options providers are: PageOptions, SlideshowOptions,
        UnitsOptions, NamedOptions, and PrintOptions.
*/

/**
@brief  Gets the number of available option keys.
@param[in]  options_provider The options provider object.
@param[out] count            The number of keys available.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if options_provider is not valid
- \ref SU_ERROR_NULL_POINTER_OUTPUT if count is NULL
 */
SU_RESULT SUOptionsProviderGetNumKeys(SUOptionsProviderRef options_provider,
                                      size_t* count);

/**
@brief  Retrieves options providers associated with the options manager.
@param[in]  options_provider The options provider object.
@param[in]  len              The number of keys to retrieve.
@param[out] keys             The keys retrieved.
@param[out] count            The number of keys retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if options_provider is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if keys or count is NULL
- \ref SU_ERROR_INVALID_OUTPUT if any of the strings in the keys array are
  invalid.
 */
SU_RESULT SUOptionsProviderGetKeys(SUOptionsProviderRef options_provider,
                                   size_t len,
                                   SUStringRef keys[],
                                   size_t* count);

/**
@brief  Gets the value of the given option.
@param[in]  options_provider The options provider object.
@param[in]  key              The key that indicates which option to get.
@param[out] value            The value to get the current option setting.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if options_provider is not valid
- \ref SU_ERROR_NULL_POINTER_INPUT if key is NULL
- \ref SU_ERROR_NULL_POINTER_OUTPUT if value is NULL
- \ref SU_ERROR_INVALID_OUTPUT if value is invalid

The breakdown of options and value types for each options provider is shown
in the table below.

Options Provider | Option               | Value Type              | Meaning
---------------- | -------------------- | ----------------------- | -------
NamedOptions     | &nbsp;               | &nbsp;                  | Provides ability to save arbitrary named option values. There are no default options for this provider.
PageOptions      | &nbsp;               | &nbsp;                  | Options for the Scene
&nbsp;           | ShowTransition       | SUTypedValueType_Bool   | Show scene transitions
&nbsp;           | TransitionTime       | SUTypedValueType_Double | Number of seconds between each scene transition
SlideshowOptions | &nbsp;               | &nbsp;                  | Options for the slideshow
&nbsp;           | LoopSlideshow        | SUTypedValueType_Bool   | Causes the slideshow to loop
&nbsp;           | SlideTime            | SUTypedValueType_Double | Number of seconds that each slide is shown
UnitsOptions     | &nbsp;               | &nbsp;                  | Options for units display in the model
&nbsp;           | LengthPrecision      | SUTypedValueType_Int32  | Number of decimal places of precision shown for length
&nbsp;           | LengthFormat         | SUTypedValueType_Int32  | Default units format for the model
&nbsp;           | LengthUnit           | SUTypedValueType_Int32  | Units format for the model
&nbsp;           | LengthSnapEnabled    | SUTypedValueType_Bool   | Indicates whether length snapping is enabled
&nbsp;           | LengthSnapLength     | SUTypedValueType_Double | Controls the snapping length size increment
&nbsp;           | AnglePrecision       | SUTypedValueType_Int32  | Number of decimal places of precision shown for angles
&nbsp;           | AngleSnapEnabled     | SUTypedValueType_Bool   | Indicates whether angle snapping is enabled
&nbsp;           | SnapAngle            | SUTypedValueType_Double | Controls the angle snapping size increment
&nbsp;           | SuppressUnitsDisplay | SUTypedValueType_Bool   | Display the units format if LengthFormat is Decimal or Fractional
&nbsp;           | ForceInchDisplay     | SUTypedValueType_Bool   | Force displaying 0" if LengthFormat is Architectural

Some of the options map to enumerated values, as shown in the table below.

Option       | Value | Meaning
------------ | ----- | -------
LengthFormat | 0:    | Decimal
&nbsp;       | 1:    | Architectural
&nbsp;       | 2:    | Engineering
&nbsp;       | 3:    | Fractional
LengthUnit   | 0:    | Inches
&nbsp;       | 1:    | Feet
&nbsp;       | 2:    | Millimeter
&nbsp;       | 3:    | Centimeter
&nbsp;       | 4:    | Meter

Note that LengthUnit will be overridden by LengthFormat if LengthFormat is not
set to Decimal. Architectural defaults to inches, Engineering defaults to feet,
and Fractional defaults to inches.
 */
SU_RESULT SUOptionsProviderGetValue(SUOptionsProviderRef options_provider,
                                    const char* key,
                                    SUTypedValueRef* value);

/**
@brief  Sets the value of the given option.
@param[in] options_provider The options provider object.
@param[in] key              The key that indicates which option to set.
@param[in] value            The value to set the option to.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if options_provider or value is not valid
- \ref SU_ERROR_NULL_POINTER_INPUT if key is NULL
 */
SU_RESULT SUOptionsProviderSetValue(SUOptionsProviderRef options_provider,
                                    const char* key,
                                    SUTypedValueRef value);

#ifdef __cplusplus
}  //  extern "C" {
#endif

#endif  // SLAPI_MODEL_OPTIONS_PROVIDER_H_
