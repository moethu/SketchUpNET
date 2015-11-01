// Copyright 2013 Trimble Navigation Ltd. All Rights Reserved.

#ifndef SLAPI_MODEL_MODEL_H_
#define SLAPI_MODEL_MODEL_H_

#include <slapi/slapi.h>
#include <slapi/unicodestring.h>
#include <slapi/model/defs.h>

#pragma pack(push, 8)

#ifdef __cplusplus
extern "C" {
#endif

/**
@struct SUModelRef
@brief  A SketchUp model.
*/

/**
@struct SUModelStatistics
@brief  Contains an array of entity counts that can be indexed per entity type.
*/
struct SUModelStatistics {
/**
@enum SUEntityType
@brief  Types of \ref SUEntityRef objects.
*/
  enum SUEntityType {
    SUEntityType_Edge = 0,
    SUEntityType_Face,
    SUEntityType_ComponentInstance,
    SUEntityType_Group,
    SUEntityType_Image,
    SUEntityType_ComponentDefinition,
    SUEntityType_Layer,
    SUEntityType_Material,
    SUNumEntityTypes
  };
  int entity_counts[SUNumEntityTypes];
};

/**
@enum SUModelUnits
@brief  Units options settings
*/
enum SUModelUnits {
  SUModelUnits_Inches,
  SUModelUnits_Feet,
  SUModelUnits_Millimeters,
  SUModelUnits_Centimeters,
  SUModelUnits_Meters
};

/**
@enum SUModelVersion
@brief  SketchUp model file format version
@since SketchUp 2014, API 2.0
*/
enum SUModelVersion {
  SUModelVersion_SU3,
  SUModelVersion_SU4,
  SUModelVersion_SU5,
  SUModelVersion_SU6,
  SUModelVersion_SU7,
  SUModelVersion_SU8,
  SUModelVersion_SU2013,
  SUModelVersion_SU2014,
  SUModelVersion_SU2015
};

/**
@brief  Creates an empty model object for the purposes of writing a SketchUp
        document. This model object must be released with \ref SUModelRelease.
@param[out] model The model object created.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_OUTPUT if model is NULL
- \ref SU_ERROR_OVERWRITE_VALID if model is already a valid object
*/
SU_RESULT SUModelCreate(SUModelRef* model);

/**
@brief  Creates a model from a SketchUp file on local disk.  This model object
        must be released with \ref SUModelRelease.
@param[out] model     The model object created.
@param[in]  file_path The source file path of the SketchUp file. Assumed to be
                      UTF-8 encoded.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if file_path is NULL
- \ref SU_ERROR_NULL_POINTER_OUTPUT if model is NULL
- \ref SU_ERROR_OVERWRITE_VALID if model is already a valid object
- \ref SU_ERROR_SERIALIZATION if an error occurs during reading of the file
- \ref SU_ERROR_MODEL_INVALID if the file specified by file_path is an invalid
  model. (since SketchUp 2014, API 2.0)
- \ref SU_ERROR_MODEL_VERSION if the file has objects that have a newer version
  than is supported by the current build of slapi. (since SketchUp 2014, API 2.0)
*/
SU_RESULT SUModelCreateFromFile(SUModelRef* model, const char* file_path);

/**
@brief Releases a model object and its associated resources. The root component
       of the model object and all its child objects must not be released
       explicitly
@param[in] model The model object.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is an invalid object
- \ref SU_ERROR_NULL_POINTER_INPUT if model is NULL
*/
SU_RESULT SUModelRelease(SUModelRef* model);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/**
@brief  Returns a model reference for a given internal model representation.
        This model object must NOT be released with \ref SUModelRelease.
@param[in] data Internal model representation.
@return The created model reference.
*/
SU_EXPORT SUModelRef SUModelFromExisting(uintptr_t data);
#endif // DOXYGEN_SHOULD_SKIP_THIS

/**
@brief  Retrieves model entities.
@param[in]  model    The model object.
@param[out] entities The entities retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is an invalid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if entities is NULL
*/
SU_RESULT SUModelGetEntities(SUModelRef model,
                             SUEntitiesRef* entities);

/**
@brief  Retrieves the number of materials in a model object.
@param[in]  model The model object.
@param[out] count The number of material objects available.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if count is NULL
*/
SU_RESULT SUModelGetNumMaterials(SUModelRef model, size_t* count);

/**
@brief  Retrieves all the materials associated with a model object.
@param[in]  model     The model object.
@param[in]  len       The number of material objects to retrieve.
@param[out] materials The material objects retrieved.
@param[out] count     The number of material objects retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if materials or count is NULL
*/
SU_RESULT SUModelGetMaterials(SUModelRef model, size_t len,
                              SUMaterialRef materials[], size_t* count);

/**
@brief  Adds materials to a model object.
@param[in] model     The model object.
@param[in] len       The number of material objects to add.
@param[in] materials The array of material objects to add.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if materials is NULL
*/
SU_RESULT SUModelAddMaterials(SUModelRef model, size_t len,
                              const SUMaterialRef materials[]);

/**
@brief  Retrieves the number of components associated with a model.
@param[in]  model The model object.
@param[out] count The number of components available.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if count is NULL
*/
SU_RESULT SUModelGetNumComponentDefinitions(SUModelRef model,
                                            size_t* count);

/**
@brief  Retrieves the components that are associated with a model.
@param[in]  model      The model object.
@param[in]  len        The number of components to retrieve.
@param[out] components The components retrieved.
@param[out] count      The number of components retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if components or count is NULL
*/
SU_RESULT SUModelGetComponentDefinitions(SUModelRef model, size_t len,
                                         SUComponentDefinitionRef components[],
                                         size_t* count);

/**
@brief  Adds component definitions to a model object.
@param[in] model      The model object.
@param[in] len        The number of component definitions to add.
@param[in] components The array of component definitions to add.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if components is NULL
*/
SU_RESULT SUModelAddComponentDefinitions(SUModelRef model, size_t len,
    const SUComponentDefinitionRef components[]);

/**
@brief  Saves the model to a file.
@param[in] model     The model object.
@param[in] file_path The file path destination of the serialization operation.
                     Assumed to be UTF-8 encoded.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if file_path is NULL
- \ref SU_ERROR_SERIALIZATION if the serialization operation itself fails
*/
SU_RESULT SUModelSaveToFile(SUModelRef model, const char* file_path);

/**
@brief  Saves the model to a file using a specific SketchUp version format.
@since SketchUp 2014, API 2.0
@param[in] model     The model object.
@param[in] file_path The file path destination of the serialization operation.
                     Assumed to be UTF-8 encoded.
@param[in] version   The SKP file format version to use when saving.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_MODEL_VERSION if version is invalid
- \ref SU_ERROR_NULL_POINTER_INPUT if file_path is NULL
- \ref SU_ERROR_SERIALIZATION if the serialization operation itself fails
*/
SU_RESULT SUModelSaveToFileWithVersion(SUModelRef model, const char* file_path,
                                       enum SUModelVersion version);

/**
@brief  Retrieves the camera of a model object.
@param[in]  model  The model object.
@param[out] camera The camera object retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if camera is NULL
*/
SU_RESULT SUModelGetCamera(SUModelRef model, SUCameraRef* camera);

/**
@brief  Retrieves the number of scene cameras of a model object.
@param[in]  model      The model object.
@param[out] num_scenes The number of scenes available.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if num_scenes is NULL
*/
SU_RESULT SUModelGetNumScenes(SUModelRef model, size_t* num_scenes);

/**
@brief  Retrieves the number of layers in a model object.
@param[in]  model The model object.
@param[out] count The number of layers available.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT of model is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if count is NULL
*/
SU_RESULT SUModelGetNumLayers(SUModelRef model, size_t* count);

/**
@brief  Retrieves the layers in a model object.
@param[in]  model  The model object.
@param[in]  len    The number of layers to retrieve.
@param[out] layers The layers retrieved.
@param[out] count  The number of layers retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT of model is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if layers or count is NULL
*/
SU_RESULT SUModelGetLayers(SUModelRef model, size_t len,
                           SULayerRef layers[], size_t* count);

/**
@brief  Adds layer objects to a model object.
@param[in] model  The model object.
@param[in] len    The number of layers to add.
@param[in] layers The layers to add.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT of model is not a valid object
- \ref SU_ERROR_INVALID_INPUT if any item in layers is not a valid object
*/
SU_RESULT SUModelAddLayers(SUModelRef model, size_t len,
                           const SULayerRef layers[]);

/**
@brief  Retrieves the default layer object of a model object.
@param[in]  model The model object.
@param[out] layer The layer object retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT of model is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if layer is NULL
*/
SU_RESULT SUModelGetDefaultLayer(SUModelRef model, SULayerRef* layer);

/**
@brief  Retrieves the version of a model object.  The version consists of three
numbers: major version number, minor version number, and the build number.
@param[in]  model The model object.
@param[out] major The major version number retrieved.
@param[out] minor The minor version number retrieved.
@param[out] build The build version number retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT of model is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if major, minor, or build is NULL
*/
SU_RESULT SUModelGetVersion(SUModelRef model, int* major, int* minor,
                            int* build);

/**
@brief  Retrieves the number of attribute dictionaries of a model object.
@param[in]  model The model object.
@param[out] count The number of attribute dictionaries available.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if count is NULL
*/
SU_RESULT SUModelGetNumAttributeDictionaries(SUModelRef model,
                                             size_t* count);

/**
@brief  Retrieves the attribute dictionaries of a model object.
@param[in]  model        The model object.
@param[in]  len          The number of attribute dictionaries to retrieve.
@param[out] dictionaries The dictionaries retrieved.
@param[out] count        The number of attribute dictionaries retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if dictionaries or count is NULL
*/
SU_RESULT SUModelGetAttributeDictionaries(
    SUModelRef model,
    size_t len,
    SUAttributeDictionaryRef dictionaries[],
    size_t* count);

/**
@brief  Retrieves the attribute dictionary of a model object that has the given
        name. If a dictionary with the given name does not exist, one is added
        to the model object.
@param[in] model       The model object.
@param[in] name        The name of the attribute dictionary to retrieve. Assumed
                       to be UTF-8 encoded.
@param[out] dictionary The dictionary object retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if name is NULL
- \ref SU_ERROR_NULL_POINTER_OUTPUT if dictionary is NULL
*/
SU_RESULT SUModelGetAttributeDictionary(SUModelRef model, const char* name,
                                        SUAttributeDictionaryRef* dictionary);

/**
@brief  Retrieves the location information of a given model.
@param[in]  model    The model object.
@param[out] location The location retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if location is NULL
*/
SU_RESULT SUModelGetLocation(SUModelRef model,
                             SULocationRef* location);

/**
@brief  Calculates the sum of all entities by type in the model.
@param[in]  model      The model object.
@param[out] statistics The \ref SUModelStatistics struct that will be populated
                       with the number of each entity type in the model.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if statistics is NULL
*/
SU_RESULT SUModelGetStatistics(SUModelRef model,
                               struct SUModelStatistics* statistics);

/**
@brief  Georeferences the model.
@param[in] model               The model object.
@param[in] latitude            Latitude of the model.
@param[in] longitude           Longitude of the model.
@param[in] altitude            Altitude of the model.
@param[in] is_z_value_centered Indicates if z value should be centered.
@param[in] is_on_ocean_floor   Indicates whether the model is on the ocean
                               floor.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object or if latitude or
  longitude does not lie within a valid range
*/
SU_RESULT SUModelSetGeoReference(SUModelRef model, double latitude,
                                 double longitude, double altitude,
                                 bool is_z_value_centered,
                                 bool is_on_ocean_floor);

/**
@brief  Retrieves the rendering options of a model object.
@param[in]  model             The model object.
@param[out] rendering_options The rendering options object retrieved. This
                              object is owned by the model and must not be
                              explicitly released.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if rendering_options is NULL
- \ref SU_ERROR_NO_DATA if no rendering options is available
*/
SU_RESULT SUModelGetRenderingOptions(SUModelRef model,
                                     SURenderingOptionsRef* rendering_options);

/**
@brief  Retrieves the shadow info of a model object.
@since SketchUp 2015, API 3.0
@param[in]  model       The model object.
@param[out] shadow_info The shadow info object retrieved. This object is owned
                        by the model and must not be explicitly released.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if shadow_info is NULL
- \ref SU_ERROR_NO_DATA if no shadow info is available
*/
SU_RESULT SUModelGetShadowInfo(SUModelRef model,
                               SUShadowInfoRef* shadow_info);

/**
@brief  Retrieves options manager associated with the model.
@param[in]  model           The model object.
@param[out] options_manager The options manager object retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if options_manager is NULL
*/
SU_RESULT SUModelGetOptionsManager(SUModelRef model,
                                   SUOptionsManagerRef* options_manager);

/**
@brief  Retrieves the angle which will rotate the north direction to the y-axis
        for a given model.
@param[in]  model            The model object.
@param[out] north_correction The north correction angle retrieved (in degrees).
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if north_angle is NULL
*/
SU_RESULT SUModelGetNorthCorrection(SUModelRef model,
                                    double* north_correction);

/**
@brief  Merges all adjacent, coplanar faces in the model.
@param[in] model The model object.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid
*/
SU_RESULT SUModelMergeCoplanarFaces(SUModelRef model);

/**
@brief  Retrieves all the scenes associated with a model object.
@param[in]  model  The model object.
@param[in]  len    The number of scene objects to retrieve.
@param[out] scenes The scene objects retrieved.
@param[out] count  The number of scene objects retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if scenes or count is NULL
- \ref SU_ERROR_OVERWRITE_VALID if any element of scenes is already a valid
  object
- \ref SU_ERROR_NO_DATA if there are no scene objects to retrieve.
*/
SU_RESULT SUModelGetScenes(SUModelRef model, size_t len,
                           SUSceneRef scenes[], size_t* count);

/**
@brief  Adds scenes to a model object.
@param[in] model  The model object.
@param[in] len    The number of scene objects to add.
@param[in] scenes The array of scene objects to add.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if scenes is NULL
*/
SU_RESULT SUModelAddScenes(SUModelRef model, size_t len,
                           const SUSceneRef scenes[]);


/**
@brief  Adds a single matched photo scene to a model object.
@since SketchUp 2015, API 3.0
@param[in]  model      The model object.
@param[in]  image_file The full path of the image associated with this scene.
@param[in]  camera     The camera associated with this scene.
@param[in]  scene_name The name of the scene to add.
@param[out] scene      The scene object created.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model or camera is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if scene_name or image_file is NULL
- \ref SU_ERROR_INVALID_OUTPUT if scene is NULL
- \ref SU_ERROR_GENERIC if image_file is invalid or not found
*/
SU_RESULT SUModelAddMatchPhotoScene(SUModelRef model,
                                    const char* image_file,
                                    SUCameraRef camera,
                                    const char* scene_name,
                                    SUSceneRef *scene);

/**
@brief  Retrieves the name of a model object.
@param[in]  model The model object.
@param[out] name  The destination of the retrieved name object.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is an invalid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if name is NULL
- \ref SU_ERROR_INVALID_OUTPUT if name does not point to a valid \ref
  SUStringRef object
*/
SU_RESULT SUModelGetName(SUModelRef model, SUStringRef* name);

/**
@brief  Sets the name of a model object.
@param[in] model The model object.
@param[in] name  The name of the model object. Assumed to be UTF-8 encoded.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is an invalid object
- \ref SU_ERROR_NULL_POINTER_INPUT if model_name is NULL
*/
SU_RESULT SUModelSetName(SUModelRef model, const char* name);

/**
@brief  Returns the units associated with the given model.
@param[in]  model The model object.
@param[out] units The units retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if model is an invalid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if the units argument is invalid
*/
SU_RESULT SUModelGetUnits(SUModelRef model, enum SUModelUnits* units);

SU_RESULT SUModelGetClassifications(SUModelRef model,
                                    SUClassificationsRef* classifications);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif  // SLAPI_MODEL_MODEL_H_
