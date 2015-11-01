// Copyright 2013 Trimble Navigation Ltd. All Rights Reserved.

#ifndef SLAPI_MODEL_SCENE_H_
#define SLAPI_MODEL_SCENE_H_

#include <slapi/slapi.h>
#include <slapi/unicodestring.h>
#include <slapi/model/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
@struct SUSceneRef
@brief  Used to get and set a scene's camera views, using the \ref SUCameraRef
        object.
*/

/**
@brief  Converts from an \ref SUSceneRef to an \ref SUEntityRef.  This is
        essentially an upcast operation.
@param[in] scene The given scene reference.
@return
- The converted \ref SUEntityRef if scene is a valid object. If not, the
  returned reference will be invalid.
*/
SU_EXPORT SUEntityRef SUSceneToEntity(SUSceneRef scene);

/**
@brief  Converts from an \ref SUEntityRef to an \ref SUSceneRef. This is
        essentially a downcast operation so the given \ref SUEntityRef must be
        convertible to an \ref SUSceneRef.
@param[in] entity The entity reference.
@return
- The converted \ref SUSceneRef if the downcast operation succeeds. If not, the
  returned reference will be invalid.
*/
SU_EXPORT SUSceneRef SUSceneFromEntity(SUEntityRef entity);

/**
@brief  Creates an empty scene object.
@param[out] scene The scene object created.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if scene is NULL
- \ref SU_ERROR_OVERWRITE_VALID if face already refers to a valid object
*/
SU_RESULT SUSceneCreate(SUSceneRef* scene);

/**
@brief  Releases a scene object.
@param[in] scene The scene object.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is an invalid object
- \ref SU_ERROR_NULL_POINTER_INPUT if scene is NULL
*/
SU_RESULT SUSceneRelease(SUSceneRef* scene);

/**
@brief  Retrieves the 'use camera' setting of a scene object.
@param[in]  scene      The scene object.
@param[out] use_camera The setting retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if use_camera is NULL
*/
SU_RESULT SUSceneGetUseCamera(SUSceneRef scene, bool* use_camera);

/**
@brief  Retrieves the camera of a scene object.
@param[in]  scene  The scene object.
@param[out] camera The camera object retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if camera is NULL
*/
SU_RESULT SUSceneGetCamera(SUSceneRef scene, SUCameraRef* camera);

/**
@brief  Retrieves the name of a scene object.
@param[in]  scene The scene object.
@param[out] name  The name retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is an invalid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if name is NULL
- \ref SU_ERROR_INVALID_OUTPUT if name does not point to a valid \ref
  SUStringRef object
*/
SU_RESULT SUSceneGetName(SUSceneRef scene, SUStringRef* name);

/**
@brief  Sets the name of a scene object.
@param[in] scene      The scene object.
@param[in] scene_name The name of the scene object. Assumed to be UTF-8 encoded.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is an invalid object
- \ref SU_ERROR_NULL_POINTER_INPUT if scene_name is NULL
*/
SU_RESULT SUSceneSetName(SUSceneRef scene, const char* scene_name);

/**
@brief  Retrieves the rendering options for the scene object.
@param[in]  scene   The scene object.
@param[out] options The options retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is an invalid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if options is NULL
- \ref SU_ERROR_NO_DATA if the scene does not use rendering options
*/
SU_RESULT SUSceneGetRenderingOptions(SUSceneRef scene,
                                     SURenderingOptionsRef* options);

/**
@brief  Retrieves the shadow info of a scene.
@since SketchUp 2015, API 3.0
@param[in]  scene       The scene object.
@param[out] shadow_info The shadow info object retrieved. This object is owned
                        by the scene and must not be explicitly released.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if shadow_info is NULL
- \ref SU_ERROR_NO_DATA if no shadow info is available
*/
SU_RESULT SUSceneGetShadowInfo(SUSceneRef scene,
                               SUShadowInfoRef* shadow_info);

/**
@brief  Retrieves the "use shadow info" setting of a scene object.
@since SketchUp 2015, API 3.0
@param[in]  scene           The scene object.
@param[out] use_shadow_info The current setting for whether or not shadow info
                            is used.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if use_shadow_info is NULL
*/
SU_RESULT SUSceneGetUseShadowInfo(SUSceneRef scene,
                                  bool* use_shadow_info);

/**
@brief  Sets the "use shadow info" setting of a scene object.
@since SketchUp 2015, API 3.0
@param[in]  scene           The scene object.
@param[out] use_shadow_info The new setting for whether or not shadow info
                            is used.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
*/
SU_RESULT SUSceneSetUseShadowInfo(SUSceneRef scene,
                                  bool use_shadow_info);

#ifdef __cplusplus
}
#endif

#endif  // SLAPI_MODEL_SCENE_H_
