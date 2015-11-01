// Copyright 2013 Trimble Navigation Ltd. All Rights Reserved.

#ifndef SLAPI_MODEL_COMPONENT_INSTANCE_H_
#define SLAPI_MODEL_COMPONENT_INSTANCE_H_

#include <slapi/slapi.h>
#include <slapi/unicodestring.h>
#include <slapi/transformation.h>
#include <slapi/model/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
@struct SUComponentInstanceRef
@brief  References a component instance, i.e. an instance of a component
        definition.
*/

/**
@brief Converts from an \ref SUComponentInstanceRef to an \ref SUEntityRef.
       This is essentially an upcast operation.
@param[in] instance The given component instance reference.
@return
- The converted \ref SUEntityRef if instance is a valid component instance
- If not, the returned reference will be invalid
*/
SU_EXPORT SUEntityRef SUComponentInstanceToEntity(
    SUComponentInstanceRef instance);

/**
@brief Converts from an \ref SUEntityRef to an \ref SUComponentInstanceRef.
       This is essentially a downcast operation so the given entity must be
       convertible to a component instance.
@param[in] entity The given entity reference.
@return
- The converted \ref SUComponentInstanceRef if the downcast operation succeeds
- If not, the returned reference will be invalid
*/
SU_EXPORT SUComponentInstanceRef SUComponentInstanceFromEntity(
    SUEntityRef entity);

/**
@brief Converts from an \ref SUComponentInstanceRef to an \ref
       SUDrawingElementRef. This is essentially an upcast operation.
@param[in] instance The given component instance reference.
@return
- The converted \ref SUEntityRef if instance is a valid component instance
- If not, the returned reference will be invalid
*/
SU_EXPORT SUDrawingElementRef SUComponentInstanceToDrawingElement(
    SUComponentInstanceRef instance);

/**
@brief Converts from an \ref SUDrawingElementRef to an \ref
       SUComponentInstanceRef. This is essentially a downcast operation so the
       given element must be convertible to a component instance.
@param[in] drawing_elem The given drawing element reference.
@return
- The converted \ref SUComponentInstanceRef if the downcast operation succeeds
- If not, the returned reference will be invalid
*/
SU_EXPORT SUComponentInstanceRef SUComponentInstanceFromDrawingElement(
    SUDrawingElementRef drawing_elem);

/**
@brief Sets the name of a component instance object.
@param[in] instance The component instance object.
@param[in] name     The name string to set the component instance object.
                    Assumed to be UTF-8 encoded.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if instance is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if name is NULL
*/
SU_RESULT SUComponentInstanceSetName(SUComponentInstanceRef instance,
                                     const char* name);

/**
@brief Deallocates a component instance object created with \ref
       SUComponentDefinitionCreateInstance.

The instance object must not be associated with a parent object. That is, if
\ref SUEntitiesAddInstance is called with the instance object, then the
instance object must not be released explicitly.
@param[in] instance The component instance object.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_OUTPUT if instance is NULL
*/
SU_RESULT SUComponentInstanceRelease(SUComponentInstanceRef* instance);

/**
@brief Retrieves the name of a component instance object.
@param[in]  instance The component instance object.
@param[out] name     The name retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if instance is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if name is NULL
- \ref SU_ERROR_INVALID_OUTPUT if name does not point to a valid \ref
  SUStringRef object
*/
SU_RESULT SUComponentInstanceGetName(SUComponentInstanceRef instance,
                                     SUStringRef* name);

/**
@brief Sets the globally unique identifier (guid) string of a instance object.
@since SketchUp 2015, API 3.0
@param[in]  instance The component instance object.
@param[in]  guid     The utf-8 formatted guid string.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if instance is not a valid object
- \ref SU_ERROR_INVALID_INPUT if guid is NULL or invalid
*/
SU_RESULT SUComponentInstanceSetGuid(SUComponentInstanceRef instance,
                                     const char* guid);

/**
@brief Retrieves the globally unique identifier (guid) string of a instance object.
@param[in]  instance The component instance object.
@param[out] guid     The guid retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if instance is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if guid is NULL
- \ref SU_ERROR_INVALID_OUTPUT if guid does not point to a valid \ref
  SUStringRef object
*/
SU_RESULT SUComponentInstanceGetGuid(SUComponentInstanceRef instance,
                                     SUStringRef* guid);

/**
@brief Sets the transform of a component instance object.

The transform is relative to the parent component. If the parent component is
the root component of a model, then the transform is relative to absolute
coordinates.
@param[in] instance  The component instance object.
@param[in] transform The affine transform to set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if instance is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if transform is NULL
*/
SU_RESULT SUComponentInstanceSetTransform(
    SUComponentInstanceRef instance,
    const struct SUTransformation* transform);

/**
@brief Retrieves the transform of a component instance object.

See description of \ref SUComponentInstanceSetTransform for a discussion of
component instance transforms.
@param[in]  instance  The component instance object.
@param[out] transform The transform retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if instance is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if transform is NULL
*/
SU_RESULT SUComponentInstanceGetTransform(SUComponentInstanceRef instance,
                                          struct SUTransformation* transform);

/**
@brief Retrieves the component definition of a component instance object.
@param[in]  instance  The component instance object.
@param[out] component The component definition retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if instance is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if component is NULL
*/
SU_RESULT SUComponentInstanceGetDefinition(
    SUComponentInstanceRef instance,
    SUComponentDefinitionRef* component);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // SLAPI_MODEL_COMPONENT_INSTANCE_H_
