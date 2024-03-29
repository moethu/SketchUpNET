# SketchUpNET

C++/CLI API Wrapper for the Trimble(R) SketchUp(R) C API.
http://www.sketchup.com/intl/en/developer/api-terms-of-service.pdf

This library adds .NET support to the existing SketchUp C-API. It makes most SketchUp C-API features available in .NET and therefore accessible in C# or VB applications. You can download a pre-built release of the library or build it yourself from scratch.

### Code-Examples

This Repo contains three sample projects using SketchUpNET in C#.NET:

- SketchUpForDynamo: An Autodesk's(R) Dynamo Node Package allowing you to read/write SketchUp files from Dynamo. 
- SketchUpForGrasshopper: A Set of Components for McNeel's(R) Grasshopper(R) allowing you to read/write SketchUp files from GH.
- SketchUpNETConsole: A sample C# console application using SketchUpNET.

If you want to build your own application using the SketchUp API take the following steps:

#### Loading a Model

```csharp
SketchUpNET.SketchUp skp = new SketchUp();
skp.LoadModel("myfile.skp", true);
foreach (var srf in skp.Surfaces) {
  // do something with your surfaces
}
```

#### Saving a Model

```csharp
skp.WriteNewModel("filename.skp");
```

#### Converting a Model

```csharp
SketchUpNET.SketchUp skp = new SketchUp();
skp.SaveAs("old-file.skp", SKPVersion.V2020, "new-file.skp");
```

#### Writing a Surface to a File

```csharp
SketchUpNET.SketchUp skp = new SketchUpNET.SketchUp();
skp.Layers = new List<Layer>() { new Layer("Layer0") };
skp.Surfaces = new List<Surface>();
skp.Curves = new List<Curve>();
skp.Edges = new List<Edge>();
List<SketchUpNET.Vertex> Verticies = new List<SketchUpNET.Vertex>();

SketchUpNET.Loop OuterEdges = new SketchUpNET.Loop();
OuterEdges.Edges = new List<Edge>();
{
  OuterEdges.Edges.Add(new SketchUpNET.Edge(new Vertex(0, 0, 0), new Vertex(500, 0, 0), "Layer0"));
  OuterEdges.Edges.Add(new SketchUpNET.Edge(new Vertex(500, 0, 0), new Vertex(500, 500, 0), "Layer0"));
  OuterEdges.Edges.Add(new SketchUpNET.Edge(new Vertex(500, 500, 0), new Vertex(0, 500, 0), "Layer0"));
  OuterEdges.Edges.Add(new SketchUpNET.Edge(new Vertex(0, 500, 0), new Vertex(0, 0, 0), "Layer0"));
}

List<Loop> InnerLoops = new List<Loop>();
{
  SketchUpNET.Loop InnerEdges = new SketchUpNET.Loop();
  InnerEdges.Edges = new List<Edge>();
  InnerEdges.Edges.Add(new SketchUpNET.Edge(new Vertex(100, 100, 0), new Vertex(400, 100, 0), "Layer0"));
  InnerEdges.Edges.Add(new SketchUpNET.Edge(new Vertex(400, 100, 0), new Vertex(400, 400, 0), "Layer0"));
  InnerEdges.Edges.Add(new SketchUpNET.Edge(new Vertex(400, 400, 0), new Vertex(100, 400, 0), "Layer0"));
  InnerEdges.Edges.Add(new SketchUpNET.Edge(new Vertex(100, 400, 0), new Vertex(100, 100, 0), "Layer0"));
  InnerLoops.Add(InnerEdges);
}

SketchUpNET.Surface s = new SketchUpNET.Surface(OuterEdges, InnerLoops);
skp.Surfaces.Add(s);

skp.WriteNewModel(@"TempModel.skp");
```

### Requirements

If not installed you might requires Visual C++ Redistributable Packages for Visual Studio 
https://www.microsoft.com/en-sg/download/details.aspx?id=40784

The library requires the SketchUp C API which is part of the package.


### nuget Binaries

SketchUpNET is available as a precompiled binary on nuget:
https://www.nuget.org/packages/SketchUpNET/
