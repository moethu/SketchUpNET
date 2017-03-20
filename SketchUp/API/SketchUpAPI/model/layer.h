// Copyright 2013 Trimble Navigation Ltd. All Rights Reserved.
#ifndef SKETCHUP_MODEL_LAYER_H_
#define SKETCHUP_MODEL_LAYER_H_

#include <SketchUpAPI/common.h>
#include <SketchUpAPI/unicodestring.h>
#include <SketchUpAPI/model/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
@struct SULayerRef
@brief References a layer object.
*/

/**
@brief Converts from an \ref SULayerRef to an \ref SUEntityRef.
       This is essentially an upcast operation.
@param[in] layer  The given layer reference.
@return
- The converted \ref SUEntityRef if layer is a valid layer
- If not, the returned reference will be invalid
*/
SU_EXPORT SUEntityRef SULayerToEntity(SULayerRef layer);

/**
@brief Converts from an \ref SUEntityRef to an \ref SULayerRef.
       This is essentially a downcast operation so the given
       SUEntityRef must be convertible to an \ref SULayerRef.
@param[in] entity The given entity reference.
@return
- The converted \ref SULayerRef if the downcast operation succeeds
- If not, the returned reference will be invalid
*/
SU_EXPORT SULayerRef SULayerFromEntity(SUEntityRef entity);

/**
@brief Creates a new layer object.

Layers associated with a SketchUp model must not be explicitly deallocated.
Layers that are not associated with a SketchUp model must be deallocated with
\ref SULayerRelease.
@param[out] layer The layer object created.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_OUTPUT if layer is NULL
*/
SU_RESULT SULayerCreate(SULayerRef* layer);

/**
@brief Deallocates a layer object.

The layer object to be deallocated must not be associated with a SketchUp model.
@param[in] layer The layer object.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if layer points to an invalid object
- \ref SU_ERROR_NULL_POINTER_INPUT if layer is NULL
*/
SU_RESULT SULayerRelease(SULayerRef* layer);

/**
@brief Retrieves the name of a layer object.
@param[in]  layer The layer object.
@param[out] name  The name retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if layer is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if name is NULL
- \ref SU_ERROR_INVALID_OUTPUT if name does not point to a valid \ref
  SUStringRef object
*/
SU_RESULT SULayerGetName(SULayerRef layer, SUStringRef* name);

/**
@brief Assigns the name of a layer object.
@param[in] layer The layer object.
@param[in] name  The new name of the layer object. Assumed to be UTF-8 encoded.
@return
- \ref SU_ERROR_NONE if layer is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if name is NULL
*/
SU_RESULT SULayerSetName(SULayerRef layer, const char* name);

/**
@brief Retrieves the material object associated with a layer object.

The retrieved material object must not be deallocated by the caller since it is
owned by the layer object.
@param[in]  layer    The layer object.
@param[out] material The material object retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if layer is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if material is NULL
*/
SU_RESULT SULayerGetMaterial(SULayerRef layer, SUMaterialRef* material);

/**
@brief Retrieves the boolean flag indicating whether a layer object is visible.
@param[in]  layer   The layer object.
@param[out] visible The visibility flag retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if layer is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if visibility is NULL
*/
SU_RESULT SULayerGetVisibility(SULayerRef layer, bool* visible);

/**
@brief Sets the boolean flag indicating whether a layer object is visible.
@param[in] layer   The layer object.
@param[in] visible The visibility flag to set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if layer is not a valid object.
*/
SU_RESULT SULayerSetVisibility(SULayerRef layer, bool visible);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // SKETCHUP_MODEL_LAYER_H_
