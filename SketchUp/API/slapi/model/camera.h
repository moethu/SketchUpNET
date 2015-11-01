// Copyright 2013 Trimble Navigation Ltd. All Rights Reserved.
#ifndef SLAPI_MODEL_CAMERA_H_
#define SLAPI_MODEL_CAMERA_H_

#include <slapi/geometry.h>
#include <slapi/slapi.h>
#include <slapi/unicodestring.h>
#include <slapi/model/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
@struct SUCameraRef
@brief  References the camera object of a SketchUp model.
*/

/**
@brief  Creates a default camera object.
@since SketchUp 2015, API 3.0
@param[out] camera The camera object created.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if camera is NULL
- \ref SU_ERROR_OVERWRITE_VALID if camera already refers to a valid object
*/
SU_RESULT SUCameraCreate(SUCameraRef* camera);

/**
@brief  Releases a camera object created by SUCameraCreate.
@since SketchUp 2015, API 3.0
@param[in] camera The camera object.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if camera is an invalid object
- \ref SU_ERROR_NULL_POINTER_INPUT if camera is NULL
*/
SU_RESULT SUCameraRelease(SUCameraRef* camera);

/**
@brief Retrieves the orientation of a camera object.
@param[in]  camera    The camera object.
@param[out] position  The position retrieved.
@param[out] target    The target retrieved.
@param[out] up_vector The up direction retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if camera is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if position, target, or up_vector is NULL
*/
SU_RESULT SUCameraGetOrientation(SUCameraRef camera,
                                 struct SUPoint3D* position,
                                 struct SUPoint3D* target,
                                 struct SUVector3D* up_vector);

/**
@brief Sets the position of a camera object.
@param[in] camera    The camera object.
@param[in] position  The new eye position.
@param[in] target    The new target position.
@param[in] up_vector The new up direction.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if camera is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if position, target or up_vector is NULL
*/
SU_RESULT SUCameraSetOrientation(SUCameraRef camera,
                                 const struct SUPoint3D* position,
                                 const struct SUPoint3D* target,
                                 const struct SUVector3D* up_vector);

/**
@brief Sets the field of view angle of a camera object. If the camera object is
       an orthographic camera, the camera object subsequently becomes a
       perspective camera. The field of view is measured along the vertical
       direction of the camera.
@param[in] camera The camera object.
@param[in] fov    The field of view angle in degrees.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if camera is not a valid object
*/
SU_RESULT SUCameraSetPerspectiveFrustumFOV(SUCameraRef camera, double fov);

/**
@brief Retrieves the field of view in degrees of a camera object. The field of
       view is measured along the vertical direction of the camera.
@param[in] camera The camera object.
@param[out] fov   The field of view retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if camera is not a valid object
- \ref SU_ERROR_NO_DATA if camera is not a perspective camera (orthographic
       camera)
- \ref SU_ERROR_NULL_POINTER_OUTPUT if fov is NULL
*/
SU_RESULT SUCameraGetPerspectiveFrustumFOV(SUCameraRef camera, double* fov);

/**
@brief Retrieves the aspect ratio of a camera object.
@param[in]  camera       The camera object.
@param[out] aspect_ratio The aspect ratio retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if camera is not a valid object
- \ref SU_ERROR_NO_DATA if the camera uses the screen aspect ratio
- \ref SU_ERROR_NULL_POINTER_OUTPUT if aspect_ratio is NULL
*/
SU_RESULT SUCameraGetAspectRatio(SUCameraRef camera, double* aspect_ratio);

/**
@brief Sets the height of a camera object which is used to calculate the
       orthographic projection of a camera object. If the camera object is a
       perspective camera, the camera subsequently becomes an orthographic
       camera.
@param[in] camera The camera object.
@param[in] height The height of the camera view.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if camera is not a valid object
*/
SU_RESULT SUCameraSetOrthographicFrustumHeight(SUCameraRef camera,
                                               double height);

/**
@brief Retrieves the height of an orthographic camera object.
@param[in]  camera The camera object.
@param[out] height The height retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if camera is not a valid object
- \ref SU_ERROR_NO_DATA if camera is not an orthographic camera (perspective
       camera)
- \ref SU_ERROR_NULL_POINTER_OUTPUT if height is NULL
*/
SU_RESULT SUCameraGetOrthographicFrustumHeight(SUCameraRef camera,
                                               double* height);

/**
@brief Sets a camera object perspective or orthographic.
@param[in] camera      The camera object.
@param[in] perspective The perspective flag.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if camera is not a valid object
*/
SU_RESULT SUCameraSetPerspective(SUCameraRef camera, bool perspective);

/**
@brief Retrieves whether a camera object is a perspective camera or not
       (i.e. orthographic).
@param[in]  camera      The camera object.
@param[out] perspective The perspective flag retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if camera is an invalid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT perspective is NULL
*/
SU_RESULT SUCameraGetPerspective(SUCameraRef camera, bool* perspective);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // SLAPI_MODEL_CAMERA_H_
