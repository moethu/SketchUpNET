/*

	SketchUpForDynamo - Trimble(R) SketchUp(R) interface for Autodesk's(R) Dynamo 
	Copyright(C) 2015, Autor: Maximilian Thumfart

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software
    and associated documentation files (the "Software"), to deal in the Software without restriction, 
    including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
    subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
    INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Autodesk.DesignScript.Runtime;
using Dynamo.Utilities;
using Dynamo.Models;
using SketchUpNET;

namespace SketchUpForDynamo
{

    public static class SketchUp
    {
        /// <summary>
        /// Reformats an existing SketchUp Model to another Version
        /// </summary>
        /// <param name="filepath">Original Model</param>
        /// <param name="version">Target Version like 2015 or 2018</param>
        /// <param name="newfilepath">Target Model Path</param>
        /// <returns></returns>
        public static bool ReformatModel(string filepath, string version, string newfilepath)
        {
            SketchUpNET.SketchUp skp = new SketchUpNET.SketchUp();
            SKPVersion v = SKPVersion.V2020;
            switch (version)
            {
                case "2014": v = SKPVersion.V2014; break;
                case "2015": v = SKPVersion.V2015; break;
                case "2016": v = SKPVersion.V2016; break;
                case "2017": v = SKPVersion.V2017; break;
                case "2018": v = SKPVersion.V2018; break;
                case "2019": v = SKPVersion.V2019; break;
                case "2020": v = SKPVersion.V2020; break;
            }
            return skp.SaveAs(filepath, v, newfilepath);
        }

        /// <summary>
        /// Load SketchUp Model by Path. 
        /// This node will load all SketchUp content into Dynamo. 
        /// By default it will include meshes.
        /// Turn meshes off if you are experiencing performance issues. 
        /// </summary>
        /// <param name="path">Path to SketchUp file</param>
        /// <param name="includeMeshes">Include Meshes (might be faster to turn it off)</param>
        [MultiReturn(new[] { "Surfaces", "Layers", "Instances", "Curves", "Edges", "Meshes", "Groups", "Materials" })]
        public static Dictionary<string, object> LoadModel(string path, bool includeMeshes = true)
        {
            List<Autodesk.DesignScript.Geometry.Surface> surfaces = new List<Autodesk.DesignScript.Geometry.Surface>();
            List<Autodesk.DesignScript.Geometry.Mesh> meshes = new List<Autodesk.DesignScript.Geometry.Mesh>();
            List<string> layers = new List<string>();
            List<Instance> Instances = new List<Instance>();
            List<List<Autodesk.DesignScript.Geometry.Line>> curves = new List<List<Autodesk.DesignScript.Geometry.Line>>();
            List<Autodesk.DesignScript.Geometry.Line> edges = new List<Autodesk.DesignScript.Geometry.Line>();
            List<Group> grp = new List<Group>();
            List<Material> mats = new List<Material>();

            SketchUpNET.SketchUp skp = new SketchUpNET.SketchUp();
            if (skp.LoadModel(path, includeMeshes))
            {

                foreach (Curve c in skp.Curves)
                    curves.Add(c.ToDSGeo());

                foreach (Surface srf in skp.Surfaces)
                {
                    surfaces.Add(srf.ToDSGeo());
                    if (srf.FaceMesh != null)
                        meshes.Add(srf.FaceMesh.ToDSGeo());
                }

                foreach (Layer l in skp.Layers)
                    layers.Add(l.Name);

                foreach (Instance i in skp.Instances)
                    Instances.Add(i);

                foreach (Edge e in skp.Edges)
                    edges.Add(e.ToDSGeo());

                foreach (Group gr in skp.Groups)
                    grp.Add(gr);

                foreach (var mat in skp.Materials)
                    mats.Add(new Material(mat.Value));

            }

            return new Dictionary<string, object>
            {
                { "Surfaces", surfaces },
                { "Layers", layers },
                { "Instances", Instances },
                { "Curves", curves },
                { "Edges", edges },
                { "Meshes", meshes},
                { "Groups", grp },
                { "Materials", mats }
            };
        }

        /// <summary>
        /// Load SketchUp Model by Path and Layername. 
        /// This node loads only contents of the specified layer into Dynamo.
        /// By default it will include meshes.
        /// Turn meshes off if you are experiencing performance issues. 
        /// </summary>
        /// <param name="path"></param>
        /// <param name="layername"></param>
        /// <param name="includeMeshes"></param>
        /// <returns></returns>
        [MultiReturn(new[] { "Surfaces", "Instances", "Edges", "Meshes", "Groups", "Materials" })]
        public static Dictionary<string, object> LoadModelByLayer(string path, string layername, bool includeMeshes = true)
        {
            List<Autodesk.DesignScript.Geometry.Surface> surfaces = new List<Autodesk.DesignScript.Geometry.Surface>();
            List<Autodesk.DesignScript.Geometry.Mesh> meshes = new List<Autodesk.DesignScript.Geometry.Mesh>();
            List<Instance> Instances = new List<Instance>();
            List<Autodesk.DesignScript.Geometry.Line> edges = new List<Autodesk.DesignScript.Geometry.Line>();
            List<Group> grp = new List<Group>();
            List<Material> mats = new List<Material>();

            SketchUpNET.SketchUp skp = new SketchUpNET.SketchUp();
            if (skp.LoadModel(path, includeMeshes))
            {

                foreach (Surface srf in skp.Surfaces.Where(s=>s.Layer == layername))
                {
                    surfaces.Add(srf.ToDSGeo());
                    if (srf.FaceMesh != null)
                        meshes.Add(srf.FaceMesh.ToDSGeo());
                }

                foreach (Instance i in skp.Instances.Where(s => s.Layer == layername))
                    Instances.Add(i);

                foreach (Edge e in skp.Edges.Where(s => s.Layer == layername))
                    edges.Add(e.ToDSGeo());

                foreach (Group gr in skp.Groups.Where(s => s.Layer == layername))
                    grp.Add(gr);

                foreach (var mat in skp.Materials)
                    mats.Add(new Material(mat.Value));

            }

            return new Dictionary<string, object>
            {
                { "Surfaces", surfaces },
                { "Instances", Instances },
                { "Edges", edges },
                { "Meshes", meshes},
                { "Groups", grp },
                { "Materials", mats }
            };
        }



        /// <summary>
        /// SketchUp Component Instance Data. 
        /// This node extracts all components from an instance. 
        /// </summary>
        /// <param name="instance">SketchUp Component Instance</param>
        [MultiReturn(new[] { "Surfaces","Curves","Instances","Meshes","Edges", "Position", "Scale", "Name", "Parent Name", "Groups", "MaterialsFront", "MaterialsBack" })]
        public static Dictionary<string, object> GetInstance(Instance instance)
        {
            List<Autodesk.DesignScript.Geometry.Surface> surfaces = new List<Autodesk.DesignScript.Geometry.Surface>();
            List<List<Autodesk.DesignScript.Geometry.Line>> curves = new List<List<Autodesk.DesignScript.Geometry.Line>>();
            List<Autodesk.DesignScript.Geometry.Line> edges = new List<Autodesk.DesignScript.Geometry.Line>();
            List<Autodesk.DesignScript.Geometry.Mesh> meshes = new List<Autodesk.DesignScript.Geometry.Mesh>();
            List<Material> matsBack = new List<Material>();
            List<Material> matsFront = new List<Material>();

            Autodesk.DesignScript.Geometry.Point p = Autodesk.DesignScript.Geometry.Point.ByCoordinates(instance.Transformation.X, instance.Transformation.Y, instance.Transformation.Z);

            Component parent = instance.Parent as Component;

            foreach (Surface srf in parent.Surfaces)
            {
                surfaces.Add(srf.ToDSGeo(instance.Transformation));
                if (srf.FaceMesh != null)
                    meshes.Add(srf.FaceMesh.ToDSGeo(instance.Transformation));
                matsBack.Add(new Material(srf.BackMaterial));
                matsFront.Add(new Material(srf.FrontMaterial));
            }
            foreach (Curve c in parent.Curves)
                curves.Add(c.ToDSGeo(instance.Transformation));
            foreach (Edge e in parent.Edges)
                edges.Add(e.ToDSGeo(instance.Transformation));

            foreach (Group grp in parent.Groups)
            {
                grp.Transformation = instance.Transformation;
            }

            return new Dictionary<string, object>
            {
                { "Surfaces", surfaces },
                { "Curves", curves },
                { "Instances", parent.Instances },
                { "Meshes", meshes },
                { "Edges", edges },
                { "Position", p },
                { "Scale", instance.Transformation.Scale },
                { "Name", instance.Name },
                { "Parent Name", parent.Name },
                { "Groups", parent.Groups },
                { "MaterialsFront", matsFront },
                { "MaterialsBack", matsBack }

            };
        }

        /// <summary>
        /// SketchUp Group Data. 
        /// This node extracts all contents from a group. 
        /// </summary>
        /// <param name="group">SketchUp Component Instance</param>
        [MultiReturn(new[] { "Surfaces", "Curves", "Instances", "Meshes", "Edges",  "Name", "Groups" })]
        public static Dictionary<string, object> GetGroup(Group group)
        {
            List<Autodesk.DesignScript.Geometry.Surface> surfaces = new List<Autodesk.DesignScript.Geometry.Surface>();
            List<List<Autodesk.DesignScript.Geometry.Line>> curves = new List<List<Autodesk.DesignScript.Geometry.Line>>();
            List<Autodesk.DesignScript.Geometry.Line> edges = new List<Autodesk.DesignScript.Geometry.Line>();
            List<Autodesk.DesignScript.Geometry.Mesh> meshes = new List<Autodesk.DesignScript.Geometry.Mesh>();
            List<Instance> insts = new List<Instance>();

            foreach (Surface srf in group.Surfaces)
            {
                surfaces.Add(srf.ToDSGeo(group.Transformation));
                if (srf.FaceMesh != null)
                    meshes.Add(srf.FaceMesh.ToDSGeo(group.Transformation));
            }
            foreach (Curve c in group.Curves)
                curves.Add(c.ToDSGeo(group.Transformation));
            foreach (Edge e in group.Edges)
                edges.Add(e.ToDSGeo(group.Transformation));
            foreach (Instance e in group.Instances)
                insts.Add(e);

            return new Dictionary<string, object>
            {
                { "Surfaces", surfaces },
                { "Curves", curves },
                { "Instances", insts },
                { "Meshes", meshes },
                { "Edges", edges },
                { "Name", group.Name },
                { "Groups", group.Groups },
            };
        }


        /// <summary>
        /// Flatten Instances.
        /// This node returns a list of all geometries from a list of instances. 
        /// </summary>
        /// <param name="instances"></param>
        /// <returns>All Geometries</returns>
        public static List<Autodesk.DesignScript.Geometry.Geometry> FlattenInstances(List<Instance> instances)
        {
            List<Autodesk.DesignScript.Geometry.Geometry> data = new List<Autodesk.DesignScript.Geometry.Geometry>();

            foreach (Instance instance in instances)
                FlattenInstance(instance, ref data);

            return data;
        }

        private static void FlattenInstance(Instance instance, ref List<Autodesk.DesignScript.Geometry.Geometry> data)
        {
            Autodesk.DesignScript.Geometry.Point p = Autodesk.DesignScript.Geometry.Point.ByCoordinates(instance.Transformation.X, instance.Transformation.Y, instance.Transformation.Z);

            Component parent = instance.Parent as Component;

            foreach (Surface srf in parent.Surfaces)
                data.Add(srf.ToDSGeo(instance.Transformation));

            foreach (Curve c in parent.Curves)
            {
                var curves = c.ToDSGeo(instance.Transformation);
                foreach (var curve in curves)
                    data.Add(curve);
            }      

            foreach (Edge e in parent.Edges)
                data.Add(e.ToDSGeo(instance.Transformation));
        }

        /// <summary>
        /// Write SketchUp Model.
        /// This node writes surfaces and cures into a SketchUp model. 
        /// </summary>
        /// <param name="path">Path to SketchUp file</param>
        /// <param name="surfaces">Surface Geometries</param>
        /// <param name="curves">Curve Geometries</param>
        public static void WriteModel(string path, List<Autodesk.DesignScript.Geometry.Surface> surfaces = null, List<Autodesk.DesignScript.Geometry.Curve> curves = null)
        {
            SketchUpNET.SketchUp skp = new SketchUpNET.SketchUp();
            skp.Surfaces = new List<Surface>();
            skp.Edges = new List<Edge>();
            skp.Curves = new List<Curve>();

            if (curves != null)
            foreach (Autodesk.DesignScript.Geometry.Curve curve in curves)
            {
                if (curve.GetType() == typeof(Autodesk.DesignScript.Geometry.Line))
                {
                    Autodesk.DesignScript.Geometry.Line line = (Autodesk.DesignScript.Geometry.Line)curve;
                    skp.Edges.Add(line.ToSKPGeo());
                }
                else
                {
                    Curve skpcurve = new Curve();
                    skpcurve.Edges = new List<Edge>();
                    foreach (Autodesk.DesignScript.Geometry.Curve tesselated in curve.ApproximateWithArcAndLineSegments())
                    {                      
                        Edge e = new Edge(tesselated.StartPoint.ToSKPGeo(), tesselated.EndPoint.ToSKPGeo(),"");
                        skpcurve.Edges.Add(e);
                    }
                    skp.Curves.Add(skpcurve);
                }
            }

            if (surfaces != null)
            foreach (Autodesk.DesignScript.Geometry.Surface surface in surfaces)
                skp.Surfaces.Add(surface.ToSKPGeo());

            if (System.IO.File.Exists(path))
                skp.AppendToModel(path);
            else 
                skp.WriteNewModel(path);

        }

    }

    [IsVisibleInDynamoLibrary(false)]
    public static class Geometry
    {
        [IsVisibleInDynamoLibrary(false)]
        public static SketchUpNET.Vertex ToSKPGeo(this Autodesk.DesignScript.Geometry.Point p)
        {
            return new Vertex(p.X, p.Y, p.Z);
        }

        [IsVisibleInDynamoLibrary(false)]
        public static SketchUpNET.Edge ToSKPGeo(this Autodesk.DesignScript.Geometry.Line p)
        {
            return new Edge(p.StartPoint.ToSKPGeo(), p.EndPoint.ToSKPGeo(),"");
        }

        [IsVisibleInDynamoLibrary(false)]
        public static SketchUpNET.Surface ToSKPGeo(this Autodesk.DesignScript.Geometry.Surface surface)
        {
            Surface srf = new Surface();
            srf.Vertices = new List<Vertex>();

            foreach (Autodesk.DesignScript.Geometry.Curve curve in surface.PerimeterCurves())
            {
                foreach (Autodesk.DesignScript.Geometry.Curve tesselated in curve.ApproximateWithArcAndLineSegments())
                {
                    srf.Vertices.Add(tesselated.StartPoint.ToSKPGeo());
                }
            }

            return srf;

        }




        [IsVisibleInDynamoLibrary(false)]
        public static Autodesk.DesignScript.Geometry.Point ToDSGeo(this SketchUpNET.Vertex v, Transform t)
        {

            if (t == null)
                return Autodesk.DesignScript.Geometry.Point.ByCoordinates(v.X, v.Y, v.Z);
            else
            {
                Vertex transformed = t.GetTransformed(v);
                return Autodesk.DesignScript.Geometry.Point.ByCoordinates(transformed.X, transformed.Y, transformed.Z);
            }
        }

        [IsVisibleInDynamoLibrary(false)]
        public static Autodesk.DesignScript.Geometry.Vector ToDSGeo(this SketchUpNET.Vector v)
        {
            return Autodesk.DesignScript.Geometry.Vector.ByCoordinates(v.X, v.Y, v.Z);
        }

        [IsVisibleInDynamoLibrary(false)]
        public static DSCore.Color ToDSColour(this SketchUpNET.Color c)
        {
            return DSCore.Color.ByARGB(c.A, c.R, c.G, c.B);
        }

        [IsVisibleInDynamoLibrary(false)]
        public static Autodesk.DesignScript.Geometry.Line ToDSGeo(this SketchUpNET.Edge v, Transform t = null)
        {
            return Autodesk.DesignScript.Geometry.Line.ByStartPointEndPoint(v.Start.ToDSGeo(t), v.End.ToDSGeo(t));
        }

        [IsVisibleInDynamoLibrary(false)]
        public static List<Autodesk.DesignScript.Geometry.Line> ToDSGeo(this SketchUpNET.Curve c, Transform t = null)
        {
            List<Autodesk.DesignScript.Geometry.Line> edges = new List<Autodesk.DesignScript.Geometry.Line>();
            foreach (Edge e in c.Edges)
                edges.Add(e.ToDSGeo(t));

            return edges;
        }

        [IsVisibleInDynamoLibrary(false)]
        public static Autodesk.DesignScript.Geometry.Mesh ToDSGeo(this SketchUpNET.Mesh mesh, Transform t = null)
        {
            List<Autodesk.DesignScript.Geometry.Point> points = new List<Autodesk.DesignScript.Geometry.Point>();
            foreach (var v in mesh.Vertices)
                points.Add(v.ToDSGeo(t));

            List<Autodesk.DesignScript.Geometry.IndexGroup> faces = new List<Autodesk.DesignScript.Geometry.IndexGroup>();
            foreach (var v in mesh.Faces)
                faces.Add(Autodesk.DesignScript.Geometry.IndexGroup.ByIndices(Convert.ToUInt32(v.A),Convert.ToUInt32(v.B),Convert.ToUInt32(v.C)));


            Autodesk.DesignScript.Geometry.Mesh m = Autodesk.DesignScript.Geometry.Mesh.ByPointsFaceIndices(points, faces);

            return m;
        }


        [IsVisibleInDynamoLibrary(false)]
        public static Autodesk.DesignScript.Geometry.Surface ToDSGeo(this SketchUpNET.Surface v, Transform t = null)
        {
            try
            {
                List<Autodesk.DesignScript.Geometry.Curve> curves = new List<Autodesk.DesignScript.Geometry.Curve>();
                foreach (Edge c in v.OuterEdges.Edges) curves.Add(c.ToDSGeo(t).ToNurbsCurve());
                int a = 0;
                Autodesk.DesignScript.Geometry.PolyCurve pc = Autodesk.DesignScript.Geometry.PolyCurve.ByJoinedCurves(curves);
                Autodesk.DesignScript.Geometry.Surface s = Autodesk.DesignScript.Geometry.Surface.ByPatch(pc);

                List<Autodesk.DesignScript.Geometry.Surface> inner = v.InnerLoops(t);

                foreach (Autodesk.DesignScript.Geometry.Surface srf in inner)
                {
                    Autodesk.DesignScript.Geometry.Geometry[] geo = s.Split(srf);
                    if (geo.Count() == 2) s = (Autodesk.DesignScript.Geometry.Surface)geo[0];

                }
                return s;
            }
            catch { return null; }
        }

        [IsVisibleInDynamoLibrary(false)]
        public static List<Autodesk.DesignScript.Geometry.Surface> InnerLoops(this SketchUpNET.Surface v, Transform t = null)
        {
            List<Autodesk.DesignScript.Geometry.Surface> surfaces = new List<Autodesk.DesignScript.Geometry.Surface>();

            foreach (Loop loop in v.InnerEdges)
            {
                List<Autodesk.DesignScript.Geometry.Curve> curves = new List<Autodesk.DesignScript.Geometry.Curve>();
                foreach (Edge c in loop.Edges) curves.Add(c.ToDSGeo(t).ToNurbsCurve());
                int a = 0;
                Autodesk.DesignScript.Geometry.PolyCurve pc = Autodesk.DesignScript.Geometry.PolyCurve.ByJoinedCurves(curves);
                Autodesk.DesignScript.Geometry.Surface s = Autodesk.DesignScript.Geometry.Surface.ByPatch(pc);
                surfaces.Add(s);
            }

            return surfaces;
        }
    }
}
