// Copyright 2013 Trimble Navigation Ltd. All Rights Reserved.
#ifndef SLAPI_MODEL_COMPONENT_H_
#define SLAPI_MODEL_COMPONENT_H_

#include <slapi/geometry.h>
#include <slapi/slapi.h>
#include <slapi/unicodestring.h>
#include <slapi/model/curve.h>
#include <slapi/model/defs.h>

#pragma pack(push, 8)
#ifdef __cplusplus
extern "C" {
#endif

/**
@struct SUComponentDefinitionRef
@brief  References a component definition.
*/

/**
@struct SUComponentBehavior
@brief  Describes how the component behaves in the SketchUp rendering scene.
*/
struct SUComponentBehavior {
  /**
  @enum SUSnapToBehavior
  @brief Describes how the component instance is placed when it is first
         instantiated in the rendering scene. For example a window component
         instance should snap to a vertical plane when instantiated in the
         rendering scene.
  */
  enum SUSnapToBehavior {
    SUSnapToBehavior_None = 0,
    SUSnapToBehavior_Any,
    SUSnapToBehavior_Horizontal,
    SUSnapToBehavior_Vertical,
    SUSnapToBehavior_Sloped 
  };
  enum SUSnapToBehavior component_snap;
  bool component_cuts_opening; ///< Whether the component creates an opening
                               ///< when placed on a surface, e.g. a window
                               ///< frame component.
  bool component_always_face_camera; ///< Whether the component behaves like a
                                     ///< billboard, where the component always
                                     ///< presents a 2D surface perpendicular
                                     ///< to the direction of camera.
  bool component_shadows_face_sun; ///< Whether the component always casts a
                                   ///< shadow as if it were facing the
                                   ///< direction of the sun.
};

/**
@brief Converts from an \ref SUComponentDefinitionRef to an \ref SUEntityRef.
       This is essentially an upcast operation.
@param[in] comp_def The given component definition reference.
@return
- The converted \ref SUEntityRef if comp_def is a valid component
- If not, the returned reference will be invalid
*/
SU_EXPORT SUEntityRef SUComponentDefinitionToEntity(
    SUComponentDefinitionRef comp_def);

/**
@brief Converts from an \ref SUEntityRef to an \ref SUComponentDefinitionRef.
       This is essentially a downcast operation so the given entity must be
       convertible to an \ref SUComponentDefinitionRef.
@param[in] entity The given entity reference.
@return
- The converted \ref SUComponentDefinitionRef if the downcast operation succeeds
- If not, the returned reference will be invalid
*/
SU_EXPORT SUComponentDefinitionRef SUComponentDefinitionFromEntity(
    SUEntityRef entity);

/**
@brief Converts from an \ref SUComponentDefinitionRef to an \ref
       SUDrawingElementRef. This is essentially an upcast operation.
@param[in] comp_def The given component definition reference.
@return
- The converted \ref SUEntityRef if comp_def is a valid component
- If not, the returned reference will be invalid
*/
SU_EXPORT SUDrawingElementRef SUComponentDefinitionToDrawingElement(
    SUComponentDefinitionRef comp_def);

/**
@brief Converts from an \ref SUDrawingElementRef to an \ref
       SUComponentDefinitionRef. This is essentially a downcast operation so the
       given element must be convertible to an \ref SUComponentDefinitionRef.
@param[in] drawing_elem The given element reference.
@return
- The converted \ref SUComponentDefinitionRef if the downcast operation succeeds
- If not, the returned reference will be invalid
*/
SU_EXPORT SUComponentDefinitionRef SUComponentDefinitionFromDrawingElement(
    SUDrawingElementRef drawing_elem);

/**
@brief Creates a new component definition.

The created definition must be released with \ref SUComponentDefinitionRelease,
or attached to either a parent component or parent model. A definition that has
been attached to a parent component or parent model must not be released.
@param[out] comp_def The component object created.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_OUTPUT if comp_def is NULL
*/
SU_RESULT SUComponentDefinitionCreate(SUComponentDefinitionRef* comp_def);

/**
@brief Releases a component definition object and its associated resources. The
       object must not be associated with a parent component or model.
@param[in] comp_def The component definition object.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if comp_def is NULL
- \ref SU_ERROR_INVALID_OUTPUT if comp_def points to an invalid object
*/
SU_RESULT SUComponentDefinitionRelease(SUComponentDefinitionRef* comp_def);

/**
@brief Retrieves the name of a component definition.
@param[in] comp_def The component definition object.
@param[out] name The name retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if comp_def or name is an object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if name is NULL
- \ref SU_ERROR_INVALID_OUTPUT if name does not point to a valid \ref
  SUStringRef object
*/
SU_RESULT SUComponentDefinitionGetName(SUComponentDefinitionRef comp_def,
                                       SUStringRef* name);

/**
@brief Sets the name of a component definition.
@param[in] comp_def The component definition object.
@param[in] name The name of the component definition. Assumed to be UTF-8
                encoded.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if comp_def is an invalid object
- \ref SU_ERROR_NULL_POINTER_INPUT if name is NULL
*/
SU_RESULT SUComponentDefinitionSetName(SUComponentDefinitionRef comp_def,
                                       const char* name);

/**
@brief Retrieves the globally unique identifier (guid) string of a component
       definition.
@since SketchUp 2015, API 3.0
@param[in]  comp_def The component definition object.
@param[out] guid_ref The guid retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if instance is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if guid is NULL
- \ref SU_ERROR_INVALID_OUTPUT if guid does not point to a valid \ref
  SUStringRef object
*/
SU_RESULT SUComponentDefinitionGetGuid(SUComponentDefinitionRef comp_def,
                                       SUStringRef* guid_ref);

/**
@brief Retrieves the entities of the component definition.
@param[in]  comp_def The component definition object.
@param[out] entities The entities retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if comp_def is an invalid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if entities is NULL
*/
SU_RESULT SUComponentDefinitionGetEntities(
    SUComponentDefinitionRef comp_def,
    SUEntitiesRef* entities);

/**
@brief Retrieves the description of the component definition.
@param[in]  comp_def The component definition object.
@param[out] desc     The description retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if comp_def or desc is an invalid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if desc is NULL
- \ref SU_ERROR_INVALID_OUTPUT if desc does not point to a valid \ref
  SUStringRef object
*/
SU_RESULT SUComponentDefinitionGetDescription(
    SUComponentDefinitionRef comp_def,
    SUStringRef* desc);

/**
@brief Sets the description of the component definition.
@param[in] comp_def The component definition object.
@param[in] desc     The description to be set. Assumed to be UTF-8 encoded.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if comp_def is an invalid object
- \ref SU_ERROR_NULL_POINTER_INPUT if desc is NULL
*/
SU_RESULT SUComponentDefinitionSetDescription(
    SUComponentDefinitionRef comp_def,
    const char* desc);

/**
@brief Create an instance of a component definition.
@param[in]  comp_def The component definition object.
@param[out] instance The instance created.
return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if comp_def is an invalid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if instance is NULL
- \ref SU_ERROR_GENERIC if comp_def is not the definition of a type that can be
  instantiated
*/
SU_RESULT SUComponentDefinitionCreateInstance(
    SUComponentDefinitionRef comp_def,
    SUComponentInstanceRef* instance);

/**
@brief Retrieves the behavior of a component definition.
@param[in]  comp_def The component definition object.
@param[out] behavior The component behavior retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if comp_def is not a valid object
*/
SU_RESULT SUComponentDefinitionGetBehavior(
    SUComponentDefinitionRef comp_def,
    struct SUComponentBehavior* behavior);

/**
@brief Sets the component behavior of a component definition.
@param[in] comp_def The component definition object.
@param[in] behavior The behavior to set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if comp_def is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if behavior is NULL
*/
SU_RESULT SUComponentDefinitionSetBehavior(
    SUComponentDefinitionRef comp_def,
    const struct SUComponentBehavior* behavior);

/**
@brief Applies a schema type from a schema to a component definition.
@param[in] comp_def The component definition object.
@param[in] schema_ref The schema that owns the schema type to apply.
@param[in] schema_type_ref The schema type to apply.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if comp_def is not a valid object
- \ref SU_ERROR_INVALID_INPUT if schema_ref is not a valid object
- \ref SU_ERROR_INVALID_INPUT if schema_type_ref is not a valid object
*/
SU_RESULT SUComponentDefinitionApplySchemaType(
    SUComponentDefinitionRef comp_def,
    SUSchemaRef schema_ref,
    SUSchemaTypeRef schema_type_ref);

#ifdef __cplusplus
}  // extern "C"
#endif
#pragma pack(pop)

#endif  // SLAPI_MODEL_COMPONENT_H_
