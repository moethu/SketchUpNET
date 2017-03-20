// Copyright 2015 Trimble Navigation Ltd. All Rights Reserved.

#ifndef SKETCHUP_MODEL_STYLES_H_
#define SKETCHUP_MODEL_STYLES_H_

#include <SketchUpAPI/common.h>
#include <SketchUpAPI/geometry.h>
#include <SketchUpAPI/model/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
@struct SUStylesRef
@brief A styles entity reference.
@since SketchUp 2017, API 5.0
*/

/**
@brief Adds a new style to the styles with the specified name.
@since SketchUp 2017, API 5.0
@param[in] styles   The styles object.
@param[in] path     The string specifying the file path to the new style.
@param[in] activate If true activate the style
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if styles is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if name is NULL
- \ref SU_ERROR_DUPLICATE if the name corresponds to an existing style
*/
SU_RESULT SUStylesAddStyle(SUStylesRef styles, const char* path,
    bool activate);

/**
@brief Retrieves the number of styles in a styles object.
@since SketchUp 2017, API 5.0
@param[in]  styles The styles object.
@param[out] count  The number of style objects available.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if styles is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if count is NULL
*/
SU_RESULT SUStylesGetNumStyles(SUStylesRef styles, size_t* count);

/**
@brief Retrieves all the styles associated with a styles object.
@since SketchUp 2017, API 5.0
@param[in]  styles      The styles object.
@param[in]  len         The number of style objects to retrieve.
@param[out] style_array The style objects retrieved.
@param[out] count       The number of style objects retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if styles is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if style_array or count is NULL
*/
SU_RESULT SUStylesGetStyles(SUStylesRef styles, size_t len,
    SUStyleRef style_array[], size_t* count);

/**
@brief Retrieves the active style.
@since SketchUp 2017, API 5.0
@param[in]  styles The styles object.
@param[out] style  Pointer to a \ref SUStyleRef for returning the style.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if styles is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if style is NULL
*/
SU_RESULT SUStylesGetActiveStyle(SUStylesRef styles,
    SUStyleRef* style);

/**
@brief Retrieves the selected style.
@since SketchUp 2017, API 5.0
@param[in]  styles The styles object.
@param[out] style  Pointer to a \ref SUStyleRef for returning the style.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if styles is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if style is NULL
*/
SU_RESULT SUStylesGetSelectedStyle(SUStylesRef styles,
    SUStyleRef* style);

/**
@brief Retrieves the style corresponding to the specified Guid.
@since SketchUp 2017, API 5.0
@param[in]  styles The styles object.
@param[in]  guid   The string specifying a style by Guid.
@param[out] style  Pointer to a \ref SUStyleRef for returning the style.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if styles is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if guid is NULL
- \ref SU_ERROR_NULL_POINTER_OUTPUT if style is NULL
*/
SU_RESULT SUStylesGetStyleByGuid(SUStylesRef styles,
    const char* guid, SUStyleRef* style);

/**
@brief Retrieves the style corresponding to the specified path.
@since SketchUp 2017, API 5.0
@param[in]  styles The styles object.
@param[in]  path   The string specifying a style by path.
@param[out] style  Pointer to a \ref SUStyleRef for returning the style.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if styles is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if path is NULL
- \ref SU_ERROR_NULL_POINTER_OUTPUT if style is NULL
- \ref SU_ERROR_NO_DATA if no style in styles matches the style at path.
*/
SU_RESULT SUStylesGetStyleByPath(SUStylesRef styles,
    const char* path, SUStyleRef* style);

/**
@brief Retrieves a bolean indicating if the active style has changed.
@since SketchUp 2017, API 5.0
@param[in]  styles  The styles object.
@param[out] changed Returns true if the active style was changed.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if styles is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if changed is NULL
*/
SU_RESULT SUStylesGetActiveStyleChanged(SUStylesRef styles, bool* changed);

/**
@brief Applies the specified style to the specified scene
@since SketchUp 2017, API 5.0
@param[in] styles The styles object.
@param[in] style  The style to be applied to a scene.
@param[in] scene  The scene to which the style will be applied.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if any of styles, style, or scene are not
                              valid objects
*/
SU_RESULT SUStylesApplyStyleToScene(SUStylesRef styles, SUStyleRef style,
    SUSceneRef scene);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // SKETCHUP_MODEL_STYLES_H_
