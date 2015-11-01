// Copyright 2013 Trimble Navigation Ltd.  All Rights Reserved

#ifndef SLAPI_INITIALIZE_H_
#define SLAPI_INITIALIZE_H_

#include <slapi/slapi.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
@brief Initializes the slapi interface. Must be called before calling any other
       API function.
*/
SU_EXPORT void SUInitialize();

/**
@brief Signals termination of use of the slapi interface. Must be called when
       done using API functions.
*/
SU_EXPORT void SUTerminate();

/**
@brief Returns the major and minor API version numbers.
@param[out] major The major version number retrieved.
@param[out] minor The minor version number retrieved.
*/
SU_EXPORT void SUGetAPIVersion(size_t* major, size_t* minor);

#ifdef __cplusplus
}  //  extern "C" {
#endif

#endif  // SLAPI_INITIALIZE_H_
