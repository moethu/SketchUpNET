// Copyright 2013 Trimble Navigation Ltd., All rights reserved.
// This file is intended for public distribution.

#ifndef SLAPI_SLAPI_H_
#define SLAPI_SLAPI_H_

/*! \mainpage SketchUp SDK

# SketchUp SDK Contents

Welcome to the SketchUp SDK, which includes the SketchUp C API,
the SketchUp Importer/Exporter Interface, full documentation, example
projects, as well as the deprecated SDK.

## SketchUp C API

The SketchUp C API is an interface for reading and writing data to and
from SketchUp models. This API interacts directly with SketchUp files
(.skp). It can create new ones as well as read or modify existing ones.

## SketchUp Importer/Exporter Interface

The SketchUp Importer/Exporter Interface allows you to create native
SketchUp importer and exporter modules that are available directly
within SketchUp as an import or export option.

## SketchUp SDK Documentation

The documentation contains reference material for all functions, data
structures, and enumerations in both the SketchUp C API and the
SketchUp Importer/Exporter interface.

The online SDK documentation can be found here: 
[SketchUp C API Online Documentation](http://www.sketchup.com/intl/en/developer/su-api)

## Build and Release Considerations

### Windows
The C API library for Windows is built using Microsoft Visual Studio 2010 SP1. It
includes both 32-bit and 64-bit binaries. Building and releasing an application
using the SketchUp C API for Windows requires including slapi.dll, which can be
found in the SketchUp C SDK for Windows. Also, the following C runtime DLLs must
be included: msvcp100.dll and msvcr100.dll. These must all be the appropriate
32-bit or 64-bit versions. Alternatively the Microsoft Visual C++ 2010 SP1
Redistributable Packages can used, which can be found here:

[32-bit redistributable package](http://www.microsoft.com/download/en/details.aspx?id=8328)

[64-bit redistributable package](http://www.microsoft.com/download/en/details.aspx?id=13523)

### OS X
The C API library for Mac is built using Xcode 5.1.1. Building and releasing an
application using the SketchUp C API for OS X requires including slapi.framework.
The framework is 64-bit, and can be found in the SketchUp C SDK for OS X.

## Example Projects

Included in the SDK package are two C++ sample projects: skp_to_xml and
xml_to_skp. These projects demonstrate how the SketchUp C API can be
used within the SketchUp plugin architecture to create importers and
exporters meant to be hosted directly by SketchUp. The XML schema used
by the samples is only for demonstration purposes.

# Quick Start

Below are some simple code examples of how to use the SketchUp C API in a
standalone C++ program.

## Reading from a .skp file

This example demonstrates how to load a SketchUp model from a .SKP file and read
some data from it.

\code{.cpp}
#include <slapi/slapi.h>
#include <slapi/geometry.h>
#include <slapi/initialize.h>
#include <slapi/unicodestring.h>
#include <slapi/model/model.h>
#include <slapi/model/entities.h>
#include <slapi/model/face.h>
#include <slapi/model/edge.h>
#include <slapi/model/vertex.h>
#include <vector>

int main() {
  // Always initialize the API before using it
  SUInitialize();

  // Load the model from a file
  SUModelRef model = SU_INVALID;
  SUResult res = SUModelCreateFromFile(&model, "model.skp");

  // It's best to always check the return code from each SU function call.
  // Only showing this check once to keep this example short.
  if (res != SU_ERROR_NONE)
    return 1;

  // Get the entity container of the model.
  SUEntitiesRef entities = SU_INVALID;
  SUModelGetEntities(model, &entities);

  // Get all the faces from the entities object
  size_t faceCount = 0;
  SUEntitiesGetNumFaces(entities, &faceCount);
  if (faceCount > 0) {
    std::vector<SUFaceRef> faces(faceCount);
    SUEntitiesGetFaces(entities, faceCount, &faces[0], &faceCount);

    // Get all the edges in this face
    for (size_t i = 0; i < faceCount; i++) {
      size_t edgeCount = 0;
      SUFaceGetNumEdges(faces[i], &edgeCount);
      if (edgeCount > 0) {
        std::vector<SUEdgeRef> edges(edgeCount);
        SUFaceGetEdges(faces[i], edgeCount, &edges[0], &edgeCount);

        // Get the vertex positions for each edge
        for (size_t j = 0; j < edgeCount; j++) {
          SUVertexRef startVertex = SU_INVALID;
          SUVertexRef endVertex = SU_INVALID;
          SUEdgeGetStartVertex(edges[j], &startVertex);
          SUEdgeGetEndVertex(edges[j], &endVertex);
          SUPoint3D start;
          SUPoint3D end;
          SUVertexGetPosition(startVertex, &start);
          SUVertexGetPosition(endVertex, &end);
          // Now do something with the point data
        }
      }
    }
  }

  // Get model name
  SUStringRef name = SU_INVALID;
  SUStringCreate(&name);
  SUModelGetName(model, &name);
  size_t name_length = 0;
  SUStringGetUTF8Length(name, &name_length);
  char* name_utf8 = new char[name_length + 1];
  SUStringGetUTF8(name, name_length + 1, name_utf8, &name_length);
  // Now we have the name in a form we can use
  SUStringRelease(&name);
  delete []name_utf8;

  // Must release the model or there will be memory leaks
  SUModelRelease(&model);

  // Always terminate the API when done using it
  SUTerminate();
  return 0;
}
\endcode

## Writing to a .skp file

This example demonstrates how to create a SketchUp model, add some data to it,
and then save the model to a .SKP file.

\code{.cpp}
#include <slapi/slapi.h>
#include <slapi/geometry.h>
#include <slapi/initialize.h>
#include <slapi/model/model.h>
#include <slapi/model/entities.h>
#include <slapi/model/face.h>
#include <slapi/model/edge.h>
#include <slapi/model/vertex.h>
#include <vector>

int main() {
  // Always initialize the API before using it
  SUInitialize();

  // Create an empty model
  SUModelRef model = SU_INVALID;
  SUResult res = SUModelCreate(&model);

  // It's best to always check the return code from each SU function call.
  // Only showing this check once to keep this example short.
  if (res != SU_ERROR_NONE)
    return 1;

  // Get the entity container of the model
  SUEntitiesRef entities = SU_INVALID;
  SUModelGetEntities(model, &entities);

  // Create a loop input describing the vertex ordering for a face's outer loop
  SULoopInputRef outer_loop = SU_INVALID;
  SULoopInputCreate(&outer_loop);
  for (size_t i = 0; i < 4; ++i) {
    SULoopInputAddVertexIndex(outer_loop, i);
  }

  // Create the face
  SUFaceRef face = SU_INVALID;
  SUPoint3D vertices[4] = { { 0,   0,   0 },
                            { 100, 100, 0 },
                            { 100, 100, 100 },
                            { 0,   0,   100 } };
  SUFaceCreate(&face, vertices, &outer_loop);

  // Add the face to the entities
  SUEntitiesAddFaces(entities, 1, &face);

  // Save the in-memory model to a file
  SUModelSaveToFile(model, "new_model.skp");

  // Must release the model or there will be memory leaks
  SUModelRelease(&model);

  // Always terminate the API when done using it
  SUTerminate();

  return 0;
}
\endcode

# Memory Management in the SketchUp C API
The SketchUp C API does not automatically track and dispose of objects that are
created. The API is a C interface, and therefore there are technical limitations
to memory management.

The general rule is that after an object is created using one of the
SU*Create*() functions, the object should in some way be attached to the model
data hierarchy.

Some object types can be retrieved directly from an existing object without
explicitly calling a create function. In this case, you should not explicitly
call the matching release function, as it is already attached to an object.

## Rules for explicitly created objects

### Add the object to an entities collection

An entities collection can be retrieved from a model, a component definition, or
a group. Entities collections are never created explicitly--they are
automatically created as part of another object. Objects that can be added to an
entities collection are faces, edges, curves, groups, images and component
instances, using one of the SUEntitiesAdd*() functions. These objects will be
released automatically when the model is released.

The types of objects that can be added to an Entities collection are:
-SUFaceRef
-SUEdgeRef
-SUCurveRef
-SUGroupRef
-SUImageRef
-SUComponentInstanceRef

Example:
If you create an edge using SUEdgeCreate(), the most common pattern is to then
add the edge to the model or to an object's entities collection. Example code
(return values ignored for brevity):

\code{.cpp}
// Create the model object
SUModelRef model = SU_INVALID;
SUModelCreate(&model);
// Get the model's entities collection
SUEntitiesRef entities = SU_INVALID;
SUModelGetEntities(model, &entities);
// Create an edge
SUEdgeRef edge = SU_INVALID;
SUPoint3D point1 = {0.0, 0.0, 0.0};
SUPoint3D point2 = {10.0, 20.0, 30.0};
SUEdgeCreate(&edge, &point1, &point2);
SUEntitiesAddEdges(entities, 1, &edge);
// Now release the model, which automatically releases the edge
SUModelRelease(&model);
\endcode

### Attach the object directly to the model
Objects that can be added to a model are materials, component definitions,
layers or scenes, using one of the SUModelAdd*() functions. These objects will
be released automatically when the model is released. Example code:

\code{.cpp}
// Create the model object
SUModelRef model = SU_INVALID;
SUModelCreate(&model);
// Create a layer
SULayerRef layer = SU_INVALID;
SULayerCreate(&layer);
SUModelAddLayers(model, 1, &layer);
// Now release the model, which automatically releases the layer
SUModelRelease(&model);
\endcode

### Attach the object directly to another object
In this case, the created object is then owned by an existing object. For
instance, a loop input can be added to a face as an inner loop. A material or
layer can be added to any drawing element. These objects will be released
automatically when the model is released.

\code{.cpp}
// Assume you already have a model with a face in it
// Get the model's entities collection
SUEntitiesRef entities = SU_INVALID;
SUModelGetEntities(model, &entities);
size_t count;
SUEntitiesGetNumFaces(entities, &count);
SUFaceRef face = SU_INVALID;
// Just get one face
SUEntitiesGetFaces(entities, 1, &face, &count);
// Create a material from a texture from a file
SUMaterialRef material = SU_INVALID;
SUMaterialCreate(&material);
SUTextureRef texture = SU_INVALID;
SUTextureCreateFromFile(&texture, "c:\\texture.jpg", 1.0, 1.0);
SUMaterialSetTexture(material, texture);
// Add the material to the face
SUFaceSetFrontMaterial(face, material);
// Now release the model, which automatically releases the
// face, the material, and the texture
SUModelRelease(&model);
\endcode

### Release the object manually
This is done by calling the corresponding SU*Release() function. This is not the
typical use case for an object, except for the model itself as well as
SUStringRef objects. However, it is possible to create and release many
different types of objects explicitly. This is not advised however, because in
most cases an active model is necessary for a function to operate properly.

\code{.cpp}
SUEdgeRef edge = SU_INVALID;
SUPoint3D point1 = {0.0, 0.0, 0.0};
SUPoint3D point2 = {10.0, 20.0, 30.0};
SUEdgeCreate(&edge, &point1, &point2);
// Now release the edge explicitly
SUEdgeRelease(&edge);
\endcode

### Transient Objects
A transient object is one that is not actually added to the model, but helps in
the process. They are always explicitly created, are then used in some operation
with the active model, and then are explicitly released. Examples of transient
objects are: SUGeometryInputRef, SULoopInputRef, SUMeshHelperRef and
SUUVHelperRef.

## Exceptions to the general case rules

SUComponentInstanceRef - Component instances are actually created from an
existing component definition using SUComponentDefinitionCreateInstance().
Though it can be released using SUComponentInstanceRelease(), the common pattern
is to add the component instance to an entities collection using
SUEntitiesAddInstance().

SUGeometryInputRef - Geometry input is a special type designed specifically
allow you to input a large amount of geometry data to the model. The lifecycle
of a geometry input object is that it is created, has vertex and loop data added
to it, is added to an entities collection (using SUEntitiesFill()), and then is
explicitly destroyed.

SUImageRef - An image can be created from a file using SUImageCreateFromFile(),
however there is no corresponding release function. An image must be added to
the entities collection of a model, component definition, or group. When the
parent object is released, the image will be released automatically.

SUMeshHelperRef - A mesh helper is never added to another object, so it must
always be explicitly released.

SUModelRef - Since a model is a top-level object, it must always be explicitly
released.

SUStringRef - A string object is always created with one of the
SUStringCreate*() functions. It is used to retrieve string data, like a name or
a description, from an existing object (e.g., SUComponentInstanceGetName()). It
must always be released using SUStringRelease() or you will leak memory. There
is no memory management concern with the API regarding string data passed to an
object (e.g., SUComponentInstanceSetName()), because a const char * is passed,
not a SUStringRef.

*/

/**
@enum SUResult
@brief Defines return values used by most API functions.
*/
enum SUResult {
  SU_ERROR_NONE = 0, ///< Indicates success.

  SU_ERROR_NULL_POINTER_INPUT, ///< A pointer for a required input was NULL.

  SU_ERROR_INVALID_INPUT, ///< An API object input to the function was not
                          ///< created properly.

  SU_ERROR_NULL_POINTER_OUTPUT, ///< A pointer for a required output was NULL.

  SU_ERROR_INVALID_OUTPUT, ///< An API object to be written with output from the
                           ///< function was not created properly.

  SU_ERROR_OVERWRITE_VALID, ///< Indicates that an input object reference
                            ///< already references an object where it was
                            ///< expected to be \ref SU_INVALID.

  SU_ERROR_GENERIC, ///< Indicates an unspecified error.

  SU_ERROR_SERIALIZATION, ///< Indicate an error occurred during loading or
                          ///< saving of a file.

  SU_ERROR_OUT_OF_RANGE, ///< An input contained a value that was outside the
                         ///< range of allowed values.

  SU_ERROR_NO_DATA, ///< The requested operation has no data to return to the
                    ///< user. This usually occurs when a request is made for
                    ///< data that is only available conditionally.

  SU_ERROR_INSUFFICIENT_SIZE, ///< Indicates that the size of an output
                              ///< parameter is insufficient.

  SU_ERROR_UNKNOWN_EXCEPTION, ///< An unknown exception occurred.

  SU_ERROR_MODEL_INVALID, ///< The model requested is invalid and cannot be loaded.

  SU_ERROR_MODEL_VERSION, ///< The model cannot be loaded or saved due to an
                          ///< invalid version
};

// Define a platform-independent UTF16 type.
#if defined(__APPLE__) || defined(__LINUX__)
#ifndef FOUNDATION_IMPORT
typedef unsigned short unichar;
#endif  // FOUNDATION_IMPORT
#else  // WIN32
#include <wtypes.h>
typedef wchar_t unichar; ///< A platform-independent UTF16 type.
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#define SU_EXPORT
#if defined WIN32 && !defined GSLAPI_NO_EXPORTS
#undef SU_EXPORT
#ifdef GSLAPI_API_EXPORTS
#define SU_EXPORT __declspec(dllexport)
#else
#define SU_EXPORT __declspec(dllimport)
#endif  // GSLAPI_API_EXPORTS
#endif  // WINDOWS

#if defined __APPLE__
#undef SU_EXPORT
#ifdef GSLAPI_API_EXPORTS
#define SU_EXPORT __attribute__ ((visibility("default")))
#else
#define SU_EXPORT __attribute__ ((visibility("hidden")))
#endif
#endif  // #if defined __APPLE__

#define DEFINE_SU_TYPE(TYPENAME) \
  typedef struct { \
    void *ptr; \
  } TYPENAME; 

#define SU_RESULT SU_EXPORT enum SUResult

#endif // DOXYGEN_SHOULD_SKIP_THIS

/**
@brief Use this macro to initialize new reference variables.
       e.g. \ref SUStringRef str = SU_INVALID;
*/
#define SU_INVALID { 0 }

/**
@brief Use this macro to test for valid SU variables.
       e.g. if (SUIsValid(result)) return true;
*/
#define SUIsValid(VARIABLE) ((VARIABLE).ptr != 0)

/**
@brief Use this macro to test for invalid SU variables.
       e.g. if (SUIsInvalid(result)) return false;
*/
#define SUIsInvalid(VARIABLE) ((VARIABLE).ptr == 0)

/**
@brief Use this macro to set a reference invalid.
*/
#define SUSetInvalid(VARIABLE) (VARIABLE).ptr = 0

/**
@brief Use this macro to check if two references are equal.
*/
#define SUAreEqual(VARIABLE1, VARIABLE2) ((VARIABLE1).ptr == (VARIABLE2).ptr)

#include <stddef.h> // for size_t

#if !defined(__STDC_HOSTED__) || (__STDC_HOSTED__ == 0)
// The host compiler does not implement C99
#ifdef WIN32
typedef __int64 int64_t;
typedef __int32 int32_t;
typedef __int16 int16_t;
#else
#error Unsupported compiler!
#endif
#else
#include <stdint.h>
#endif  // #if !defined(__STDC_HOSTED__) || (__STDC_HOSTED__ == 0)

#endif  // SLAPI_SLAPI_H_
