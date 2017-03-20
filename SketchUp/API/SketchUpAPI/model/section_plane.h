// Copyright 2015 Trimble Navigation Ltd. All Rights Reserved.

#ifndef SKETCHUP_MODEL_SECTION_PLANE_H_
#define SKETCHUP_MODEL_SECTION_PLANE_H_

#include <SketchUpAPI/common.h>
#include <SketchUpAPI/geometry.h>
#include <SketchUpAPI/model/defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
@struct SUSectionPlaneRef
@brief  An sectionPlane entity reference.
@since SketchUp 2016, API 4.0
*/

/**
@brief Converts from an \ref SUSectionPlaneRef to an \ref SUEntityRef. This is
       essentially an upcast operation.
@since SketchUp 2016, API 4.0
@param[in] sectionPlane The sectionPlane object.
@return
- The converted \ref SUEntityRef if sectionPlane is a valid object
- If not, the returned reference will be invalid
*/
SU_EXPORT SUEntityRef SUSectionPlaneToEntity(SUSectionPlaneRef sectionPlane);

/**
@brief Converts from an \ref SUEntityRef to an \ref SUSectionPlaneRef.
       This is essentially a downcast operation so the given \ref SUEntityRef
       must be convertible to an \ref SUSectionPlaneRef.
@since SketchUp 2016, API 4.0
@param[in] entity The entity object.
@return
- The converted \ref SUSectionPlaneRef if the downcast operation succeeds
- If the downcast operation fails, the returned reference will be invalid
*/
SU_EXPORT SUSectionPlaneRef SUSectionPlaneFromEntity(SUEntityRef entity);

/**
@brief Converts from an \ref SUSectionPlaneRef to an \ref SUDrawingElementRef.
       This is essentially an upcast operation.
@since SketchUp 2016, API 4.0
@param[in] sectionPlane The given sectionPlane reference.
@return
- The converted \ref SUEntityRef if sectionPlane is a valid sectionPlane
- If not, the returned reference will be invalid
*/
SU_EXPORT SUDrawingElementRef SUSectionPlaneToDrawingElement(
    SUSectionPlaneRef sectionPlane);

/**
@brief Converts from an \ref SUDrawingElementRef to an \ref SUSectionPlaneRef.
       This is essentially a downcast operation so the given element must be
       convertible to an \ref SUSectionPlaneRef.
@since SketchUp 2016, API 4.0
@param[in] drawing_elem The given element reference.
@return
- The converted \ref SUSectionPlaneRef if the downcast operation succeeds
- If not, the returned reference will be invalid.
*/
SU_EXPORT SUSectionPlaneRef SUSectionPlaneFromDrawingElement(
    SUDrawingElementRef
    drawing_elem);

/**
@brief Creates an sectionPlane object. The sectionPlane object must be
       subsequently deallocated with \ref SUSectionPlaneRelease unless it is
       associated with a parent object.  The plane is initialized as an xy
       plane and can be changed with the \ref SUSectionPlaneSetPlane.
@since SketchUp 2016, API 4.0
@param[in] sectionPlane The sectionPlane object.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if sectionPlane is NULL
- \ref SU_ERROR_OVERWRITE_VALID if sectionPlane references a valid object
*/
SU_RESULT SUSectionPlaneCreate(SUSectionPlaneRef* sectionPlane);

/**
@brief Releases a sectionPlane object. The sectionPlane object must have been 
       created with \ref SUSectionPlaneCreate and not subsequently associated
       with a parent object (e.g. \ref SUEntitiesRef).
@since SketchUp 2016, API 4.0
@param[in] sectionPlane The sectionPlane object.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_NULL_POINTER_INPUT if sectionPlane is NULL
- \ref SU_ERROR_INVALID_INPUT if sectionPlane does not reference a valid object
*/
SU_RESULT SUSectionPlaneRelease(SUSectionPlaneRef* sectionPlane);

/**
@brief Sets the plane of the section plane.
@param[in] sectionPlane The sectionPlane object.
@param[in] plane        The 3d plane to be set.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if sectionPlane is not a valid object
- \ref SU_ERROR_NULL_POINTER_INPUT if plane is NULL
*/
SU_RESULT SUSectionPlaneSetPlane(SUSectionPlaneRef sectionPlane,
                                 const struct SUPlane3D* plane);

/**
@brief Retrieves the plane of the section plane.
@param[in]  sectionPlane  The sectionPlane object.
@param[out] plane         The 3d plane retrieved.
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if sectionPlane is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if plane is NULL
*/
SU_RESULT SUSectionPlaneGetPlane(SUSectionPlaneRef sectionPlane,
                                 struct SUPlane3D* plane);

/**
@brief Retrieves the a boolean indicating whether or not the section plane is
       active.
@param[in]  sectionPlane  The sectionPlane object.
@param[out] is_active     Returns true if the section plane is active. 
@return
- \ref SU_ERROR_NONE on success
- \ref SU_ERROR_INVALID_INPUT if sectionPlane is not a valid object
- \ref SU_ERROR_NULL_POINTER_OUTPUT if is_active is NULL
*/
SU_RESULT SUSectionPlaneIsActive(SUSectionPlaneRef sectionPlane,
                                 bool* is_active);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // SKETCHUP_MODEL_SECTION_PLANE_H_