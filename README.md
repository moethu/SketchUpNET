# SketchUpNET

C++/CLI API Wrapper for the Trimble(R) SketchUp(R) C API.
http://www.sketchup.com/intl/en/developer/api-terms-of-service.pdf

This library adds .NET support to the existing SketchUp C-API. It makes most SketchUp C-API features available in .NET and therefore accessible in C# or VB applications. You can download a pre-built release of the library or build it yourself from scratch.

### Code-Examples

This Repo contains two projects using SketchUpNET in C#.NET:

- An Autodesk's(R) Dynamo Node Package allowing you to read/write SketchUp files from Dynamo.
- A Set of Components for McNeel's(R) Grasshopper(R) allowing you to read/write SketchUp files from GH.

If you want to build your own application using the SketchUp API take the following steps:

### Loading a Model

```
SketchUpNET.SketchUp skp = new SketchUp();
skp.LoadModel("myfile.skp", true);
foreach (var srf in skp.Surfaces) {
  // do something with your surfaces
}
```

### Saving a Model

```
skp.WriteNewModel("filename.skp");
```

### Converting a Model

```
SketchUpNET.SketchUp skp = new SketchUp();
skp.SaveAs("old-file.skp", SKPVersion.V2020, "new-file.skp");
```



### Requirements

If not installed you might requires Visual C++ Redistributable Packages for Visual Studio 
https://www.microsoft.com/en-sg/download/details.aspx?id=40784

The library requires the SketchUp C API which is part of the package.
