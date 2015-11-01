// Copyright 2013 Trimble Navigation Ltd. All Rights Reserved.

#ifndef SLAPI_MODEL_GROUP_H_
#define SLAPI_MODEL_GROUP_H_

#include <slapi/slapi.h>
#include <slapi/unicodestring.h>
#include <slapi/transformation.h>
#include <slapi/model/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
@struct SUGroupRef
@brief  References a group object.
*/

/**
@brief Converts from an \ref SUGroupRef to an \ref SUEntityRef.
       This is essentially an upcast operation.
@param[in] group The given group reference.
@return
- The converted \ref SUEntityRef if group is a valid group
- If not, the returned reference will be invalid
*/
SU_EXPORT SUEntityRef SUGroupToEntity(SUGroupRef group);

/**
@brief Converts from an \ref SUEntityRef to an \ref SUGroupRef.
       This is essentially a downcast operation so the given entity must be
       convertible to an SUGroupRef.
@param[in] entity The given entity reference.
@return
- The converted \ref SUGroupRef if the downcast operation succeeds
- If not, the returned reference will be invalid
*/
SU_EXPORT SUGroupRef SUGroupFromEntity(SUEntityRef entity);

/**
@brief Converts from an \ref SUGroupRef to an \ref SUDrawingElementRef.
       This is essentially an upcast operation.
@param[in] group The given group reference.
@return
- The converted \ref SUEntityRef if group is a valid group
- If not, the returned reference will be invalid
*/
SU_EXPORT SUDrawingElementRef SUGroupToDrawingElement(SUGroupRef group);

/**
@brief Converts from an \ref SUDrawingElementRef to an \ref SUGroupRef.
       This is essentially a downcast operation so the given element must be
       convertible to an SUGroupRef.
@param[in] drawing_elem The given element reference.
@return
- The converted \ref SUGroupRef if the downcast operation succeeds
- If not, the returned reference will be invalid
*/
SU_EXPORT SUGroupRef SUGroupFromDrawingElement(SUDrawingElementRef
                                               drawing_elem);

/**
@brief Creates a new group object.

The created group must be subsequently added to the Entities of a model,
component definition or a group.
@param[out] group The group object created.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_OUTPUT if group is NULL
*/
SU_RESULT SUGroupCreate(SUGroupRef* group);

/**
@brief Sets the name of a group object.
@param[in] group The group object.
@param[in] name  The name string to set the group object.
                 Assumed to be UTF-8 encoded.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if group is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if name is NULL
*/
SU_RESULT SUGroupSetName(SUGroupRef group, const char* name);

/**
@brief Retrieves the name of a group object.
@param[in]  group The group object.
@param[out] name  The name retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if group is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if name is NULL
- \ref SU_ERROR_INVALID_OUTPUT if name does not point to a valid \ref
  SUStringRef object
*/
SU_RESULT SUGroupGetName(SUGroupRef group, SUStringRef* name);

/**
@brief Retrieves the globally unique identifier (guid) string of a group object.
@since SketchUp 2015, API 3.0
@param[in]  group   The group object.
@param[out] guid    The guid retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if group is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if guid is NULL
- \ref SU_ERROR_INVALID_OUTPUT if guid does not point to a valid \ref
  SUStringRef object
*/
SU_RESULT SUGroupGetGuid(SUGroupRef group, SUStringRef* guid);

/**
@brief Sets the globally unique identifier (guid) string of a group object.
@since SketchUp 2015, API 3.0
@param[in]  group    The group object.
@param[in]  guid_str The utf-8 formatted guid string.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if group is not a valid object
- \ref SU_ERROR_INVALID_INPUT if guid is NULL or invalid
*/
SU_RESULT SUGroupSetGuid(SUGroupRef group, const char* guid_str);

/**
@brief Sets the transform of a group object.

The transform is relative to the parent component. If the parent component is
the root component of a model, then the transform is relative to absolute
coordinates.
@param[in] group     The group object.
@param[in] transform The affine transform to set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if group is not a valid object.
- \ref SU_ERROR_NULL_POINTER_INPUT if transform is NULL.
*/
SU_RESULT SUGroupSetTransform(SUGroupRef group,
                              const struct SUTransformation* transform);

/**
@brief Retrieves the transform of a group object.

See description of SUGroupSetTransform for a discussion of group transforms.
@param[in]  group     The group object.
@param[out] transform The transform retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if group is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if transform is NULL
*/
SU_RESULT SUGroupGetTransform(SUGroupRef group,
                              struct SUTransformation* transform);

/**
@brief Retrieves the entities of the group object.
@param[in]  group    The group object.
@param[out] entities The entities retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if group is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if entities is NULL
*/
SU_RESULT SUGroupGetEntities(SUGroupRef group,
                             SUEntitiesRef* entities);

/* The cond/endcond block will ensure that any code or comment keywords will be
ignored by the Doxygen parser and will not appear in any documentation */
/**@cond
@brief Retrieves the component definition of a group object.
@since SketchUp 2014, API 2.0
@param[in]  group     The group object.
@param[out] component The component definition retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if group is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if component is NULL
*/
SU_RESULT SUGroupGetDefinition(
  SUGroupRef group,
  SUComponentDefinitionRef* component);
/** @endcond */


#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // SLAPI_MODEL_GROUP_H_
