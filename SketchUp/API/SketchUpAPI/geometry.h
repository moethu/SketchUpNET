// Copyright 2013 Trimble Navigation Ltd., All rights reserved.

#ifndef SKETCHUP_GEOMETRY_H_
#define SKETCHUP_GEOMETRY_H_

// includes
#include <SketchUpAPI/common.h>


#pragma pack(push, 8)

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

/**
@struct SUPoint2D
@brief Represents a point in 2-dimensional space.
*/
struct SUPoint2D {
  double x;
  double y;
};
  
/**
@struct SUVector2D
@brief Represents a vector in 2-dimensional space.
*/
struct SUVector2D {
  double x;
  double y;
};

/**
@struct SUPoint3D
@brief Represents a point in 3-dimensional space.
*/
struct SUPoint3D {
  double x;
  double y;
  double z;
};

/**
@struct SUVector3D
@brief Represents a vector in 3-dimensional space.
*/
struct SUVector3D {
  double x;
  double y;
  double z;
};

/**
@struct SUPlane3D
@brief Represents a 3D plane by the parameters a, b, c, d.
       For any point on the plane, ax + by + cz + d = 0.
       The coeficients are normalized so that a*a + b*b + c*c = 1.
*/
struct SUPlane3D {
  double a;
  double b;
  double c;
  double d;
};

/**
@struct SUBoundingBox3D
@brief Represents a 3D axis-aligned bounding box represented by the extreme
       diagonal corner points with minimum and maximum x,y,z coordinates.
*/
struct SUBoundingBox3D {
  struct SUPoint3D min_point;
  struct SUPoint3D max_point;
};

/**
@struct SUAxisAlignedRect2D
@brief Represents a 2D rectangle that is aligned with the X and Y axis of the
       coordinate system.
*/
struct SUAxisAlignedRect2D {
  struct SUPoint2D upper_left;
  struct SUPoint2D lower_right;
};

#ifdef __cplusplus
}  // end extern "C"
#endif  // __cplusplus

#pragma pack(pop)

#endif  // SKETCHUP_GEOMETRY_H_
