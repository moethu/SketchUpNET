// Copyright 2013 Trimble Navigation Ltd., All rights reserved.

#ifndef SKETCHUP_COLOR_H_
#define SKETCHUP_COLOR_H_

#pragma pack(push, 8)
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

/**
@typedef SUByte
@brief A type that stores a byte.
*/
typedef unsigned char SUByte;

/**
@struct SUColor
@brief Stores a RGBA color with 8 bit channels.
*/
typedef struct {
  SUByte red;
  SUByte green;
  SUByte blue;
  SUByte alpha;
} SUColor;

#ifdef __cplusplus
}  // end extern "C"
#endif  // __cplusplus
#pragma pack(pop)

#endif  // SKETCHUP_COLOR_H_
