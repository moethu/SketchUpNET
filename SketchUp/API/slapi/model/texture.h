// Copyright 2013 Trimble Navigation Ltd. All Rights Reserved.

#ifndef SLAPI_MODEL_TEXTURE_H_
#define SLAPI_MODEL_TEXTURE_H_

#include <stddef.h>
#include <slapi/color.h>
#include <slapi/unicodestring.h>
#include <slapi/model/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
@struct SUTextureRef
@brief  Used to manage image data that can be associated with any \ref
        SUEntityRef.
*/

/**
@brief  Converts from an \ref SUTextureRef to an \ref SUEntityRef. This is
        essentially an upcast operation.
@param[in] texture The texture reference.
@return
- The converted \ref SUEntityRef if texture is a valid object. If not, the
  returned reference will be invalid.
*/
SU_EXPORT SUEntityRef SUTextureToEntity(SUTextureRef texture);

/**
@brief  Converts from an \ref SUEntityRef to an \ref SUTextureRef. This is
        essentially a downcast operation so the given \ref SUEntityRef must be
        convertible to an \ref SUTextureRef.
@param[in] entity The entity reference.
@return
- The converted \ref SUTextureRef if the downcast operation succeeds. If
  not, the returned reference will be invalid.
*/
SU_EXPORT SUTextureRef SUTextureFromEntity(SUEntityRef entity);

/**
@brief  Creates a new texture object with the specified image data.  If the
        texture object is not subsequently associated with a parent object (e.g.
        material), then the texture object must be deallocated with \ref
        SUTextureRelease.
@param[out] texture        The texture object created.
@param[in]  width          The width in pixels of the texture data.
@param[in]  height         The height in pixels of the texture data.
@param[in]  bits_per_pixel The number of bits per pixel of the image data.
@param[in]  pixel_data     The source of the pixel data.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if pixels is NULL
- \ref SU_ERROR_NULL_POINTER_OUTPUT texture is NULL
- \ref SU_ERROR_OVERWRITE_VALID if texture already references a valid object
*/
SU_RESULT SUTextureCreateFromImageData(SUTextureRef* texture,
                                       size_t width, size_t height,
                                       size_t bits_per_pixel,
                                       const SUByte pixel_data[]);

/**
@brief  Creates a new texture object from an image file specified by a path.
        If the texture object is not subsequently associated with a parent
        object (e.g. material), then the texture object must be deallocated with
        SUTextureRelease.
@param[out] texture   The texture object created.
@param[in]  file_path The file path of the source image file. Assumed to be
                      UTF-8 encoded.
@param[in]  s_scale   The scale factor for s coordinate value.
@param[in]  t_scale   The scale factor for t coordinate value.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if file_path is NULL
- \ref SU_ERROR_SERIALIZATION if the image file could not be opened
- \ref SU_ERROR_GENERIC if a texture could not be created from the image file
- \ref SU_ERROR_NULL_POINTER_OUTPUT if texture is NULL
- \ref SU_ERROR_OVERWRITE_VALID is texture already references a valid object
*/
SU_RESULT SUTextureCreateFromFile(SUTextureRef* texture,
                                  const char* file_path,
                                  double s_scale, double t_scale);

/**
@brief  Deallocates a texture object and its resources. If the texture object
        is associated with a parent object (e.g. material) the parent object
        handles the deallocation of the resources of the texture object and the
        texture object must not be explicitly deallocated.
@param[in] texture The texture object to deallocate.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if texture is NULL
- \ref SU_ERROR_INVALID_INPUT if texture does not refer to a valid object
*/
SU_RESULT SUTextureRelease(SUTextureRef* texture);

/**
@brief  Retrieves the pixel width and height and scale factors of the texture.
@param[in] texture  The texture object whose dimensions are retrieved.
@param[out] width   The width dimension retrieved.
@param[out] height  The height dimension retrieved.
@param[out] s_scale The scale factor for s retrieved.
@param[out] t_scale The scale factor for t retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if texture is an invalid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if width, height, s_scale, or t_scale is
  NULL
*/
SU_RESULT SUTextureGetDimensions(SUTextureRef texture,
                                 size_t* width, size_t* height,
                                 double* s_scale, double* t_scale);

/**
@brief  Returns the total size and bits-per-pixel value of a texture's image
        data. This function is useful to determine the size of the buffer
        necessary to be passed into \ref SUTextureGetImageData. The returned
        data can be used along with the returned bits-per-pixel value and the
        texture dimensions to compute RGBA values at individual pixels of the
        texture image.
@param[in]  texture        The texture object.
@param[out] data_size      The total size of the image data in bytes.
@param[out] bits_per_pixel The number of bits per pixel of the image data.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if texture is an invalid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if data_size or bits_per_pixel is NULL
*/
SU_RESULT SUTextureGetImageDataSize(SUTextureRef texture,
                                    size_t* data_size,
                                    size_t* bits_per_pixel);

/**
@brief  Returns the texture's image data. The given array must be large enough
        to hold the texture's image data. This size can be obtained by calling
        \ref SUTextureGetImageDataSize.
@param[in] texture     The texture object.
@param[in] data_size   The size of the byte array.
@param[out] pixel_data The image data retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if texture is an invalid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if pixel_data is NULL
- \ref SU_ERROR_INSUFFICIENT_SIZE if data_size is insufficient for the image
  data
*/
SU_RESULT SUTextureGetImageData(SUTextureRef texture,
                                size_t data_size,
                                SUByte pixel_data[]);

/**
@brief  Writes a texture object as an image to disk.
@param[in] texture   The texture object.
@param[in] file_path The file path destination of the texture image. Assumed to
                     be UTF-8 encoded.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if texture is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if file_path is NULL
- \ref SU_ERROR_SERIALIZATION if image file could not be written to disk
*/
SU_RESULT SUTextureWriteToFile(SUTextureRef texture, const char* file_path);

/**
@brief  Retrieves the image file name of a texture object.
@param[in]  texture   The texture object.
@param[out] file_name The file name retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if texture is not a valid object
- \ref SU_ERROR_GENERIC if the texture is an unknown file type
- \ref SU_ERROR_NULL_POINTER_OUTPUT if file_name is NULL
- \ref SU_ERROR_INVALID_OUTPUT if file_name does not point to a valid \ref
  SUStringRef object
*/
SU_RESULT SUTextureGetFileName(SUTextureRef texture,
                               SUStringRef* file_name);

/**
@brief  Retrieves the value of the flag that indicates whether a texture object
        uses the alpha channel.
@param[in] texture             The texture object.
@param[out] alpha_channel_used The destination of the retrieved value.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if texture is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if alpha_channel_used is NULL
- \ref SU_ERROR_NO_DATA if the flag value could not be retrieved
*/
SU_RESULT SUTextureGetUseAlphaChannel(SUTextureRef texture,
                                      bool* alpha_channel_used);

#ifdef __cplusplus
}   // extern "C"
#endif

#endif  // SLAPI_MODEL_TEXTURE_H_
