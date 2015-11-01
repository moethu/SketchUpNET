// Copyright 2013 Trimble Navigation Ltd.  All Rights Reserved
#ifndef SLAPI_MODEL_IMAGE_H_
#define SLAPI_MODEL_IMAGE_H_

#include <slapi/color.h>
#include <slapi/unicodestring.h>
#include <slapi/transformation.h>
#include <slapi/model/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
@struct SUImageRef
@brief References an image object.
*/

/**
@brief Converts from an \ref SUImageRef to an \ref SUEntityRef.
       This is essentially an upcast operation.
@param[in] image The given image reference.
@return
- The converted \ref SUEntityRef if image is a valid image.
- If not, the returned reference will be invalid.
*/
SU_EXPORT SUEntityRef SUImageToEntity(SUImageRef image);

/**
@brief Converts from an \ref SUEntityRef to an \ref SUImageRef.
       This is essentially a downcast operation so the given entity must be
       convertible to an \ref SUImageRef.
@param[in] entity The given entity reference.
@return
- The converted \ref SUImageRef if the downcast operation succeeds. If not, the
returned reference will be invalid
*/
SU_EXPORT SUImageRef SUImageFromEntity(SUEntityRef entity);

/**
@brief Converts from an \ref SUImageRef to an \ref SUDrawingElementRef.
       This is essentially an upcast operation.
@param[in] image The given image reference.
@return
- The converted \ref SUEntityRef if image is a valid image
- If not, the returned reference will be invalid
*/
SU_EXPORT SUDrawingElementRef SUImageToDrawingElement(SUImageRef image);

/**
@brief Converts from an \ref SUDrawingElementRef to an \ref SUImageRef.
       This is essentially a downcast operation so the given element must be
       convertible to an \ref SUImageRef.
@param[in] drawing_elem The given element reference.
@return
- The converted \ref SUImageRef if the downcast operation succeeds
- If not, the returned reference will be invalid
*/
SU_EXPORT SUImageRef SUImageFromDrawingElement(SUDrawingElementRef
                                               drawing_elem);

/**
@brief Creates a new image object from an image file specified by a path.
       The created image must be subsequently added to the Entities of a model,
       component definition or a group.
@param[out] image The image object created.
@param file_path  The file path of the source image file.
                  Assumed to be UTF-8 encoded.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if file_path is NULL
- \ref SU_ERROR_NULL_POINTER_OUTPUT if image is NULL
- \ref SU_ERROR_OVERWRITE_VALID if image already references a valid object.
*/
SU_RESULT SUImageCreateFromFile(SUImageRef* image, const char* file_path);

/**
@brief Retrieves the name of an image object.
@param[in]  image The image object.
@param[out] name  The name retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if image is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if name is NULL
- \ref SU_ERROR_INVALID_OUTPUT if name does not point to a valid \ref
  SUStringRef object
*/
SU_RESULT SUImageGetName(SUImageRef image, SUStringRef* name);

/**
@brief Sets the name of an image object.
@param[in] image The image object.
@param[in] name  The name to set. Assumed to be UTF-8 encoded.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if image is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if name is NULL
*/
SU_RESULT SUImageSetName(SUImageRef image, const char* name);

/**
@brief Retrieves the 3-dimensional homogeneous transform of an image object.
@param[in]  image     The image object.
@param[out] transform The transform retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if image is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if transform is NULL
*/
SU_RESULT SUImageGetTransform(SUImageRef image,
                              struct SUTransformation* transform);

/**
@brief Sets the 3-dimensional homogeneous transform of an image object.
@param[in] image     The image object.
@param[in] transform The affine transform to set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if image is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if transform is NULL
*/
SU_RESULT SUImageSetTransform(SUImageRef image,
                              const struct SUTransformation* transform);

/**
@brief Retrieves the image file name of an image object.
@param[in]  image     The image object.
@param[out] file_name The image file name retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if image is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if file_name is NULL
- \ref SU_ERROR_INVALID_OUTPUT if file_name does not point to a valid \ref
  SUStringRef object
*/
SU_RESULT SUImageGetFileName(SUImageRef image, SUStringRef* file_name);

/**
@brief Retrieves the world dimensions of an image object.
@param[in]  image  The image object.
@param[out] width  The width dimension retrieved.
@param[out] height The height dimension retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if image is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if width or height is NULL
*/
SU_RESULT SUImageGetDimensions(SUImageRef image, double* width, double* height);

/**
@brief Retrieves the width and height dimensions of an image object in pixels.
@param[in]  image  The image object.
@param[out] width  The width dimension retrieved.
@param[out] height The height dimension retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if image is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if width or height is NULL
*/
SU_RESULT SUImageGetPixelDimensions(SUImageRef image, size_t* width,
                                    size_t* height);

/**
@brief  Returns the total size and bits-per-pixel value of an image. This
        function is useful to determine the size of the buffer necessary to be
        passed into \ref SUImageGetData. The returned data can be used along
        with the returned bits-per-pixel value and the image dimensions to
        compute RGBA values at individual pixels of the image.
@param[in]  image          The image object.
@param[out] data_size      The total size of the image data in bytes.
@param[out] bits_per_pixel The number of bits per pixel of the image data.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if image is an invalid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if data_size or bits_per_pixel is NULL
*/
SU_RESULT SUImageGetDataSize(SUImageRef image, size_t* data_size,
                             size_t* bits_per_pixel);

/**
@brief  Returns the pixel data for an image. The given array must be large enough
        to hold the image's data. This size can be obtained by calling
        \ref SUImageGetDataSize.
@param[in]  image      The image object.
@param[in]  data_size  The size of the byte array.
@param[out] pixel_data The image data retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if image is an invalid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if pixel_data is NULL
- \ref SU_ERROR_INSUFFICIENT_SIZE if data_size is insufficient for the image
  data
*/
SU_RESULT SUImageGetData(SUImageRef image, size_t data_size, SUByte pixel_data[]);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // SLAPI_MODEL_IMAGE_H_
