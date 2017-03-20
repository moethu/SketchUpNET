// Copyright 2013 Trimble Navigation Ltd. All Rights Reserved.
#ifndef SKETCHUP_MODEL_ENTITY_H_
#define SKETCHUP_MODEL_ENTITY_H_

#include <SketchUpAPI/common.h>
#include <SketchUpAPI/model/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
@struct SUEntityRef
@brief  References an entity, which is an abstract base type for most API types.
*/

/**
@brief Returns the concrete type of the given entity.
@param[in] entity The entity.
@return
- The concrete type of the given entity reference.
- \ref SURefType_Unknown if entity is not valid.
*/
SU_EXPORT enum SURefType SUEntityGetType(SUEntityRef entity);

/**
@brief Retrieves the id of the entity.
@param[in]  entity    The entity.
@param[out] entity_id The id retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entity is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if entity_id is NULL.
*/
SU_RESULT SUEntityGetID(SUEntityRef entity, int32_t* entity_id);

/**
@brief Retrieves the persistent id of the entity.
@param[in]  entity      The entity.
@param[out] entity_pid  The persistent id retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entity is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if entity_pid is NULL.
*/
SU_RESULT SUEntityGetPersistentID(SUEntityRef entity, int64_t* entity_pid);

/**
@brief Retrieves the number of attribute dictionaries of an entity.
@param[in]  entity The entity.
@param[out] count  The number of attribute dictionaries.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entity is not a valid entity
- \ref SU_ERROR_NULL_POINTER_OUTPUT if count is NULL
*/
SU_RESULT SUEntityGetNumAttributeDictionaries(SUEntityRef entity,
                                              size_t* count);

/**
@brief Retrieves the attribute dictionaries of an entity.
@param[in]  entity       The entity.
@param[in]  len          The number of attribute dictionaries to retrieve.
@param[out] dictionaries The dictionaries retrieved.
@param[out] count        The number of dictionaries retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entity is not a valid entity
- \ref SU_ERROR_NULL_POINTER_OUTPUT if dictionaries or count is NULL
*/
SU_RESULT SUEntityGetAttributeDictionaries(
    SUEntityRef entity,
    size_t len,
    SUAttributeDictionaryRef dictionaries[],
    size_t* count);

/**
@brief Retrieves the attribute dictionary of an entity that has the given name.

If a dictionary with the given name does not exist, one is added to the entity.
@param[in]  entity The entity.
@param[in]  name   The name of the retrieved attribute dictionary.
                   Assumed to be UTF-8 encoded.
@param[out] dictionary The destination of the retrieved dictionary object.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if entity is not a valid entity
- \ref SU_ERROR_NULL_POINTER_INPUT if name is NULL
- \ref SU_ERROR_NULL_POINTER_OUTPUT if dictionary is NULL
*/
SU_RESULT SUEntityGetAttributeDictionary(
    SUEntityRef entity,
    const char* name,
    SUAttributeDictionaryRef* dictionary);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // SKETCHUP_MODEL_ENTITY_H_
