// Copyright 2013 Trimble Navigation Ltd., All rights reserved.

#ifndef SKETCHUP_TRANSFORMATION_H_
#define SKETCHUP_TRANSFORMATION_H_

#pragma pack(push, 8)

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

/**
@struct SUTransformation
@brief Represents a 3D (4x4) geometric transformation matrix.

Matrix values are in column-major order.
The transformation is stored as:
@code
     -     -
     | R T |
 M = | 0 w |
     -     -
@endcode
where:
<ul>
<li> M is a 4x4 matrix
<li> R is a 3x3 sub-matrix. It is the rotation part
<li> T is a 3x1 sub-matrix. It is the translation part
<li> w is a scalar.         It is 1/scale.
</ul>
*/
struct SUTransformation {
  double values[16]; ///< Matrix values in column-major order.
};

#ifdef __cplusplus
}  // end extern "C"
#endif  // __cplusplus

#pragma pack(pop)

#endif  // SKETCHUP_TRANSFORMATION_H_
