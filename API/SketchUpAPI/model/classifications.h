// Copyright 2014 Trimble Navigation Ltd. All Rights Reserved.

#ifndef SKETCHUP_MODEL_CLASSIFICATIONS_H_
#define SKETCHUP_MODEL_CLASSIFICATIONS_H_

#include <SketchUpAPI/common.h>
#include <SketchUpAPI/model/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
@struct SUClassificationsRef
@brief  Used to manage a Classifications object
*/

/**
@brief Loads a schema into a classification object.
@param[in]  classifications  The classification object.
@param[in]  schema_file_name The full path of the schema to load.
@related SUClassificationsRef
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if classifications is not a valid object
- \ref SU_ERROR_INVALID_INPUT if schema_file_name is not a valid path to a schema
       or is NULL
*/
SU_RESULT SUClassificationsLoadSchema(SUClassificationsRef classifications,
                                      const char* schema_file_name);

/**
@brief Gets a schema from a classification object.
@param[in]  classifications  The classification object.
@param[in]  schema_name      The name of the schema to get.
@param[out] schema_ref       The schema retrieved.
@related SUClassificationsRef
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if classifications is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if schema_name is NULL
- \ref SU_ERROR_INVALID_INPUT if schema_name is not a loaded schema
- \ref SU_ERROR_NULL_POINTER_OUTPUT if schema_ref is NULL
*/
SU_RESULT SUClassificationsGetSchema(SUClassificationsRef classifications,
                                     const char* schema_name,
                                     SUSchemaRef* schema_ref);

#ifdef __cplusplus
}
#endif

#endif  // SKETCHUP_MODEL_CLASSIFICATIONS_H_
