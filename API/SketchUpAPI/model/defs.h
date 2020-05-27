// Copyright 2013 Trimble Inc. All Rights Reserved.

#ifndef SKETCHUP_MODEL_DEFS_H_
#define SKETCHUP_MODEL_DEFS_H_

#include <SketchUpAPI/defs.h>

#pragma pack(push, 8)

DEFINE_SU_TYPE(SUArcCurveRef)
DEFINE_SU_TYPE(SUAttributeDictionaryRef)
DEFINE_SU_TYPE(SUAxesRef)
DEFINE_SU_TYPE(SUCameraRef)
DEFINE_SU_TYPE(SUClassificationsRef)
DEFINE_SU_TYPE(SUClassificationAttributeRef)
DEFINE_SU_TYPE(SUClassificationInfoRef)
DEFINE_SU_TYPE(SUComponentDefinitionRef)
DEFINE_SU_TYPE(SUComponentInstanceRef)
DEFINE_SU_TYPE(SUCurveRef)
DEFINE_SU_TYPE(SUDimensionRef)
DEFINE_SU_TYPE(SUDimensionLinearRef)
DEFINE_SU_TYPE(SUDimensionRadialRef)
DEFINE_SU_TYPE(SUDimensionStyleRef)
DEFINE_SU_TYPE(SUDrawingElementRef)
DEFINE_SU_TYPE(SUDynamicComponentInfoRef)
DEFINE_SU_TYPE(SUDynamicComponentAttributeRef)
DEFINE_SU_TYPE(SUEdgeRef)
DEFINE_SU_TYPE(SUEdgeUseRef)
DEFINE_SU_TYPE(SUEntitiesRef)
DEFINE_SU_TYPE(SUEntityListRef)
DEFINE_SU_TYPE(SUEntityListIteratorRef)
DEFINE_SU_TYPE(SUEntityRef)
DEFINE_SU_TYPE(SUFaceRef)
DEFINE_SU_TYPE(SUFontRef)
DEFINE_SU_TYPE(SUGeometryInputRef)
DEFINE_SU_TYPE(SUGroupRef)
DEFINE_SU_TYPE(SUGuideLineRef)
DEFINE_SU_TYPE(SUGuidePointRef)
DEFINE_SU_TYPE(SUImageRef)
DEFINE_SU_TYPE(SUImageRepRef)
DEFINE_SU_TYPE(SUInstancePathRef)
DEFINE_SU_TYPE(SULayerRef)
DEFINE_SU_TYPE(SULineStyleRef)
DEFINE_SU_TYPE(SULineStylesRef)
DEFINE_SU_TYPE(SULocationRef)
DEFINE_SU_TYPE(SULoopInputRef)
DEFINE_SU_TYPE(SULoopRef)
DEFINE_SU_TYPE(SUMaterialRef)
DEFINE_SU_TYPE(SUMeshHelperRef)
DEFINE_SU_TYPE(SUModelRef)
DEFINE_SU_TYPE(SUOpeningRef)
DEFINE_SU_TYPE(SUOptionsManagerRef)
DEFINE_SU_TYPE(SUOptionsProviderRef)
DEFINE_SU_TYPE(SUPolyline3dRef)
DEFINE_SU_TYPE(SURenderingOptionsRef)
DEFINE_SU_TYPE(SUSceneRef)
DEFINE_SU_TYPE(SUSchemaRef)
DEFINE_SU_TYPE(SUSchemaTypeRef)
DEFINE_SU_TYPE(SUSectionPlaneRef)
DEFINE_SU_TYPE(SUShadowInfoRef)
DEFINE_SU_TYPE(SUStyleRef)
DEFINE_SU_TYPE(SUStylesRef)
DEFINE_SU_TYPE(SUTextRef)
DEFINE_SU_TYPE(SUTextureRef)
DEFINE_SU_TYPE(SUTextureWriterRef)
DEFINE_SU_TYPE(SUTypedValueRef)
DEFINE_SU_TYPE(SUUVHelperRef)
DEFINE_SU_TYPE(SUVertexRef)

/**
@enum SURefType
@brief Types of concrete object references.
*/
enum SURefType {
  SURefType_Unknown = 0,
  SURefType_AttributeDictionary,
  SURefType_Camera,
  SURefType_ComponentDefinition,
  SURefType_ComponentInstance,
  SURefType_Curve,
  SURefType_Edge,
  SURefType_EdgeUse,
  SURefType_Entities,
  SURefType_Face,
  SURefType_Group,
  SURefType_Image,
  SURefType_Layer,
  SURefType_Location,
  SURefType_Loop,
  SURefType_MeshHelper,
  SURefType_Material,
  SURefType_Model,
  SURefType_Polyline3D,
  SURefType_Scene,
  SURefType_Texture,
  SURefType_TextureWriter,
  SURefType_TypedValue,
  SURefType_UVHelper,
  SURefType_Vertex,
  SURefType_RenderingOptions,
  SURefType_GuidePoint,
  SURefType_GuideLine,
  SURefType_Schema,
  SURefType_SchemaType,
  SURefType_ShadowInfo,
  SURefType_Axes,
  SURefType_ArcCurve,
  SURefType_SectionPlane,
  SURefType_DynamicComponentInfo,
  SURefType_DynamicComponentAttribute,
  SURefType_Style,
  SURefType_Styles,
  SURefType_ImageRep,
  SURefType_InstancePath,
  SURefType_Font,
  SURefType_Dimension,
  SURefType_DimensionLinear,
  SURefType_DimensionRadial,
  SURefType_DimensionStyle,
  SURefType_Text,
  SURefType_EntityList,
  SURefType_EntityListIterator,
  SURefType_DrawingElement,
  SURefType_Entity,
  SURefType_LengthFormatter,
  SURefType_LineStyle,
  SURefType_LineStyleManager
};

#pragma pack(pop)

#endif  // SKETCHUP_MODEL_DEFS_H_
