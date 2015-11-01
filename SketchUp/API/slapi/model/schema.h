// Copyright 2014 Trimble Navigation Ltd. All Rights Reserved.

#ifndef SLAPI_MODEL_SCHEMA_H_
#define SLAPI_MODEL_SCHEMA_H_

#include <slapi/slapi.h>
#include <slapi/model/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

  /**
  @struct SUSchemaRef
  @brief  Used to manage a Schema object
  */

  /**
  @brief Gets a schema type from a schema.
  @param[in]  schema_ref       The schema object.
  @param[in]  schema_type_name The name of the schema type to get.
  @param[out] schema_type_ref  The schema type retrieved.
  @return
  - \ref SU_ERROR_NONE on success
  - \ref SU_ERROR_INVALID_INPUT if schema_ref is not a valid object
  - \ref SU_ERROR_NULL_POINTER_INPUT if schema_type_name is NULL
  - \ref SU_ERROR_INVALID_INPUT if schema_type_name is not a type from this
    schema
  - \ref SU_ERROR_NULL_POINTER_OUTPUT if schema_type_ref is not a valid object
  */
  SU_RESULT SUSchemaGetSchemaType(SUSchemaRef schema_ref,
                                  const char* schema_type_name,
                                  SUSchemaTypeRef* schema_type_ref);

#ifdef __cplusplus
}
#endif

#endif  // SLAPI_MODEL_SCHEMA_H_
