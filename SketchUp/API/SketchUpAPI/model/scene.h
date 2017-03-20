// Copyright 2013 Trimble Navigation Ltd. All Rights Reserved.

#ifndef SKETCHUP_MODEL_SCENE_H_
#define SKETCHUP_MODEL_SCENE_H_

#include <SketchUpAPI/common.h>
#include <SketchUpAPI/unicodestring.h>
#include <SketchUpAPI/model/defs.h>

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
@brief  Retrieves the "use camera" setting of a scene object.
@since SketchUp 2016, API 4.0
@param[in]  scene      The scene object.
@param[out] use_camera The setting retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if use_camera is NULL
*/
SU_RESULT SUSceneGetUseCamera(SUSceneRef scene, bool* use_camera);

/**
@brief  Sets the "use camera" setting of a scene object.
@since SketchUp 2016, API 4.0
@param[in] scene      The scene object.
@param[in] use_camera The current setting for whether or not the camera is used.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
*/
SU_RESULT SUSceneSetUseCamera(SUSceneRef scene, bool use_camera);

/**
@brief  Retrieves the camera of a scene object. The returned camera object
        points to scene's internal camera. So the camera must not be released
        via \ref SUCameraRelease.
@param[in]  scene  The scene object.
@param[out] camera The camera object retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if camera is NULL
*/
SU_RESULT SUSceneGetCamera(SUSceneRef scene, SUCameraRef* camera);

/**
@brief  Sets a given scene's camera object.  The scene does not take ownership
        of the provided camera, it just copies the properties to the scene's
        owned camera.  If the input camera was created using \ref
        SUCameraCreate it must be released using \ref SUCameraRelease.
@since SketchUp 2016, API 4.0
@param[in] scene  The scene object.
@param[in] camera The camera object to be set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene or camera are not a valid objects
*/
SU_RESULT SUSceneSetCamera(SUSceneRef scene, SUCameraRef camera);

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
@param[in] scene           The scene object.
@param[in] use_shadow_info The new setting for whether or not shadow info
                            is used.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
*/
SU_RESULT SUSceneSetUseShadowInfo(SUSceneRef scene,
                                  bool use_shadow_info);

/**
@brief  Retrieves the "use rendering options" setting of a scene object.
@since SketchUp 2016, API 4.0
@param[in]  scene                 The scene object.
@param[out] use_rendering_options The current setting for whether or not
                                  rendering options are used.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if use_shadow_info is NULL
*/
SU_RESULT SUSceneGetUseRenderingOptions(SUSceneRef scene,
                                        bool* use_rendering_options);

/**
@brief  Sets the "use rendering options" setting of a scene object.
@since SketchUp 2016, API 4.0
@param[in] scene                 The scene object.
@param[in] use_rendering_options The new setting for whether or not rendering
                                  options are used.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
*/
SU_RESULT SUSceneSetUseRenderingOptions(SUSceneRef scene,
                                        bool use_rendering_options);

/**
@brief  Retrieves the "use hidden layers" setting of a scene object.
@since SketchUp 2016, API 4.0
@param[in]  scene             The scene object.
@param[out] use_hidden_layers The current setting for whether or not hidden
                              layer are used.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if use_rendering_options is NULL
*/
SU_RESULT SUSceneGetUseHiddenLayers(SUSceneRef scene,
                                    bool* use_hidden_layers);

/**
@brief  Sets the "use hidden layers" setting of a scene object.
@since SketchUp 2016, API 4.0
@param[in] scene             The scene object.
@param[in] use_hidden_layers The new setting for whether or not hidden layers
                             are used.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
*/
SU_RESULT SUSceneSetUseHiddenLayers(SUSceneRef scene,
                                    bool use_hidden_layers);

/**
@brief Retrieves the number of layers in the scene object.
@since SketchUp 2016, API 4.0
@param[in]  scene The scene object.
@param[out] count The number of layers.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if count is NULL
*/
SU_RESULT SUSceneGetNumLayers(SUSceneRef scene, size_t* count);

/**
@brief Retrieves the layers in the scene object.
@since SketchUp 2016, API 4.0
@param[in]  scene  The entities object.
@param[in]  len    The number of layers to retrieve.
@param[out] layers The layers retrieved.
@param[out] count  The number of layers retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if layers or count is NULL
*/
SU_RESULT SUSceneGetLayers(SUSceneRef scene,
                           size_t len,
                           SULayerRef layers[],
                           size_t*  count);

/**
@brief  Adds the specified layer to the provided scene. This function does not
        take ownership of the specified layer.
@since SketchUp 2016, API 4.0
@param[in] scene The scene object.
@param[in] layer The new layer to be added to the scene.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene or layer is not a valid object
- \ref SU_ERROR_NO_DATA if the scene is not owned by a valid model
- \ref SU_ERROR_GENERIC if the scene's model does not contain the layer
*/
SU_RESULT SUSceneAddLayer(SUSceneRef scene, SULayerRef layer);

/**
@brief  Removes the specified layer from the provided scene. Scenes do not own
        their layers so removing them doesn't release them.
@since SketchUp 2016, API 4.0
@param[in] scene The scene object.
@param[in] layer The layer to be removed from the scene.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene or layer is not a valid object
*/
SU_RESULT SUSceneRemoveLayer(SUSceneRef scene, SULayerRef layer);

/**
@brief  Clears out the provided scene's layers vector. Scenes do not own their
        layers so removing them does not release them.
@since SketchUp 2016, API 4.0
@param[in] scene The scene object.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
*/
SU_RESULT SUSceneClearLayers(SUSceneRef scene);

/**
@brief Retrieves the axes of a scene object.
@param[in]  scene The scene object.
@param[out] axes  The axes object retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if axes is NULL
- \ref SU_ERROR_NO_DATA if the scene doesn't have an axes
*/
SU_RESULT SUSceneGetAxes(SUSceneRef scene, SUAxesRef* axes);

/**
@brief  Sets the "use axes" setting of a scene object.
@since SketchUp 2017, API 5.0
@param[in] scene    The scene object.
@param[in] use_axes The new setting for whether or not the axes is used.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
*/
SU_RESULT SUSceneSetUseAxes(SUSceneRef scene, bool use_axes);

/**
@brief  Retrieves the "use axes" setting of a scene object.
@since SketchUp 2017, API 5.0
@param[in]  scene    The scene object.
@param[out] use_axes The setting retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if use_axes is NULL
*/
SU_RESULT SUSceneGetUseAxes(SUSceneRef scene, bool* use_axes);

/**
@brief Retrieves the number of hidden entities in the scene object.
@since SketchUp 2017, API 5.0
@param[in]  scene The scene object.
@param[out] count The number of hidden entities.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if count is NULL
*/
SU_RESULT SUSceneGetNumHiddenEntities(SUSceneRef scene, size_t* count);

/**
@brief Retrieves the hidden entities in the scene object.
@since SketchUp 2017, API 5.0
@param[in]  scene    The entities object.
@param[in]  len      The number of hidden entities to retrieve.
@param[out] entities The hidden entities retrieved.
@param[out] count    The number of hidden entities retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if entities or count is NULL
*/
SU_RESULT SUSceneGetHiddenEntities(SUSceneRef scene,
    size_t len,
    SUEntityRef entities[],
    size_t* count);

/**
@brief  Sets the flags for a scene object.
                           there should be some explanation on how to use them.
@since SketchUp 2017, API 5.0
@param[in] scene The scene object.
@param[in] flags The flags to be set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
*/
SU_RESULT SUSceneSetFlags(SUSceneRef scene, uint32_t flags);

/**
@brief Retrieves the flags in the scene object.
@since SketchUp 2017, API 5.0
@param[in]  scene The scene object.
@param[out] flags The flags.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if flags is NULL
*/
SU_RESULT SUSceneGetFlags(SUSceneRef scene, uint32_t* flags);

/**
@brief  Sets the "sketch axes displayed" setting of a scene object.
@since SketchUp 2017, API 5.0
@param[in] scene     The scene object.
@param[in] displayed The new setting for whether or not sketch axes should be
                     displayed.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
*/
SU_RESULT SUSceneSetSketchAxesDisplayed(SUSceneRef scene, bool displayed);

/**
@brief  Retrieves the "sketch axes displayed" setting of a scene object.
@since SketchUp 2017, API 5.0
@param[in]  scene     The scene object.
@param[out] displayed The setting retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if displayed is NULL
*/
SU_RESULT SUSceneGetSketchAxesDisplayed(SUSceneRef scene, bool* displayed);

/**
@brief  Retrieves the "photo matched image displayed" setting of a scene object.
@since SketchUp 2017, API 5.0
@param[in]  scene     The scene object.
@param[out] displayed The setting retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if displayed is NULL
*/
SU_RESULT SUSceneGetPhotoMatchImageDisplayed(SUSceneRef scene,
    bool* displayed);

/**
@brief  Clears the provided scene's photo match image.
@since SketchUp 2017, API 5.0
@param[in] scene The scene object.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
*/
SU_RESULT SUSceneClearPhotoMatchImage(SUSceneRef scene);

/**
@brief Retrieves the scene's style.
@since SketchUp 2017, API 5.0
@param[in]  scene The scene object.
@param[out] style The style object retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if style is NULL
- \ref SU_ERROR_NO_DATA if the scene doesn't have a style
*/
SU_RESULT SUSceneGetStyle(SUSceneRef scene, SUStyleRef* style);

/**
@brief  Copies the data from copy_scene to scene.
@since SketchUp 2017, API 5.0
@param[in] scene      The scene object to be altered.
@param[in] copy_scene The scene to be copied.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene or camera are not a valid objects
*/
SU_RESULT SUSceneCopy(SUSceneRef scene, SUSceneRef copy_scene);

/**
@brief  Activates the provided scene.
@since SketchUp 2017, API 5.0
@param[in] scene The scene object.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if scene is not a valid object
*/
SU_RESULT SUSceneActivate(SUSceneRef scene);

#ifdef __cplusplus
}
#endif

#endif  // SKETCHUP_MODEL_SCENE_H_
