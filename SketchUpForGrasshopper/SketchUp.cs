/*

	SketchUpForGrasshopper - Trimble(R) SketchUp(R) interface for McNeel's(R) Grasshopper(R) 
	Copyright(C) 2020, Autor: Maximilian Thumfart

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
using System.Drawing;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;

using System.Net.Sockets;
using System.Net;
using System.Xml;
using System.Xml.Serialization;
using System.Runtime.Serialization;
using System.IO;
using System.Threading;
using SketchUpNET;

namespace SketchUpForGrasshopper
{
    /// <summary>
    /// SketchUp Model Component
    /// </summary>
    public class SketchUpModel : GH_Component
    {
        public SketchUpModel() : base("Load SketchUp Model", "Load SketchUp Model", "Loads a SketchUp Model from file", "GrassUp", "Model") { }

        protected override void RegisterInputParams(GH_Component.GH_InputParamManager pManager)
        {
            pManager.AddTextParameter("Path", "P", "Path to Sketchup File (skp)", GH_ParamAccess.item);
            int a = pManager.AddBooleanParameter("Mesh", "M", "Load Meshes (Default: True)", GH_ParamAccess.item);
            pManager[a].Optional = true;
        }

        protected override void RegisterOutputParams(GH_Component.GH_OutputParamManager pManager)
        {
            pManager.AddBrepParameter("Surfaces", "S", "Surfaces", GH_ParamAccess.list);
            pManager.AddTextParameter("Layers", "L", "Layers", GH_ParamAccess.list);
            pManager.AddGenericParameter("Instances", "I", "Instances", GH_ParamAccess.list);
            pManager.AddCurveParameter("Curves", "C", "Curves", GH_ParamAccess.list);
            pManager.AddMeshParameter("Meshes", "M", "Meshes", GH_ParamAccess.list);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            GH_String path = new GH_String();
            DA.GetData<GH_String>(0, ref path);

            GH_Boolean mesh = new GH_Boolean(true);
            if (!DA.GetData<GH_Boolean>(1, ref mesh))
            {
                mesh = new GH_Boolean(true);
            }

            List<GH_Brep> surfaces = new List<GH_Brep>();
            List<GH_String> layers = new List<GH_String>();
            List<Instance> Instances = new List<Instance>();
            List<GH_Curve> curves = new List<GH_Curve>();
            List<GH_Mesh> meshes = new List<GH_Mesh>();

            SketchUp skp = new SketchUp();
            if (skp.LoadModel(path.Value, mesh.Value))
            {
                foreach (Surface srf in skp.Surfaces)
                {
                    foreach (var brep in srf.ToRhinoGeo())
                        surfaces.Add(new GH_Brep(brep));

                    if (srf.FaceMesh != null)
                    {
                        meshes.Add(new GH_Mesh(srf.FaceMesh.ToRhinoGeo()));
                    }
                }

                foreach (Layer l in skp.Layers)
                    layers.Add(new GH_String(l.Name));

                foreach (Instance i in skp.Instances)
                    Instances.Add(i);

                foreach (Edge c in skp.Edges)
                    curves.Add(new GH_Curve(c.ToRhinoGeo().ToNurbsCurve()));
            }

            DA.SetDataList(0, surfaces);
            DA.SetDataList(1, layers);
            DA.SetDataList(2, Instances);
            DA.SetDataList(3, curves);
            DA.SetDataList(4, meshes);
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("{5ea8ce4d-d268-4d7f-a733-1583beeb4b5d}");
            }
        }
        protected override Bitmap Internal_Icon_24x24
        {
            get
            {
                return Properties.Resources.Skp;
            }
        }
    }

    /// <summary>
    /// Save SketchUp Model Component
    /// </summary>
    public class SaveSketchUpModel : GH_Component
    {
        public SaveSketchUpModel() : base("Save SketchUp Model", "Save SketchUp Model", "Save a SketchUp Model to file", "GrassUp", "Model") { }

        protected override void RegisterInputParams(GH_Component.GH_InputParamManager pManager)
        {
            pManager.AddTextParameter("Path", "P", "Path to Sketchup File (skp)", GH_ParamAccess.item);
            int a = pManager.AddCurveParameter("Curves", "C", "Curves", GH_ParamAccess.list);
            int b = pManager.AddSurfaceParameter("Surfaces", "S", "Surfaces", GH_ParamAccess.list);
            pManager[a].Optional = true;
            pManager[b].Optional = true;
        }

        protected override void RegisterOutputParams(GH_Component.GH_OutputParamManager pManager)
        {

        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            GH_String path = new GH_String();
            DA.GetData<GH_String>(0, ref path);

            List<GH_Surface> surfaces = new List<GH_Surface>();
            DA.GetDataList<GH_Surface>(1, surfaces);
            List<GH_Curve> curves = new List<GH_Curve>();
            DA.GetDataList<GH_Curve>(2, curves);

            Geometry.WriteModel(path.Value, surfaces, curves, false);
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("{5ea8ce3d-d262-4d7f-a733-1573beeb4b5d}");
            }
        }
        protected override Bitmap Internal_Icon_24x24
        {
            get
            {
                return Properties.Resources.Skp;
            }
        }
    }

    /// <summary>
    /// Decomposes a SketchUp Model Instance
    /// </summary>
    public class SketchUpInstance : GH_Component
    {
        public SketchUpInstance() : base("Decompose SketchUp Instance", "Decompose SketchUp Instance", "Decomposes a SketchUp Instance", "GrassUp", "Elements") { }

        protected override void RegisterInputParams(GH_Component.GH_InputParamManager pManager)
        {
            pManager.AddGenericParameter("Instance", "I", "Instance", GH_ParamAccess.item);
        }

        protected override void RegisterOutputParams(GH_Component.GH_OutputParamManager pManager)
        {
            pManager.AddPointParameter("Location", "L", "Location", GH_ParamAccess.item);
            pManager.AddTextParameter("Name", "N", "Name", GH_ParamAccess.item);
            pManager.AddNumberParameter("Scale", "S", "Scale", GH_ParamAccess.item);
            pManager.AddBrepParameter("Surfaces", "Sf", "Surfaces", GH_ParamAccess.list);
            pManager.AddTextParameter("Parent Name", "PN", "Parent Name", GH_ParamAccess.item);
            pManager.AddBrepParameter("Inner", "I", "Inner", GH_ParamAccess.list);
            pManager.AddCurveParameter("Curves", "C", "Curves", GH_ParamAccess.list);
            pManager.AddCurveParameter("Meshes", "M", "Meshes", GH_ParamAccess.list);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            Instance i = null;
            DA.GetData<Instance>(0, ref i);

            GH_Point location = new GH_Point(new Rhino.Geometry.Point3d(i.Transformation.X, i.Transformation.Y, i.Transformation.Z));
            GH_Number scale = new GH_Number(i.Transformation.Scale);
            GH_String name = new GH_String(i.Name);

            List<GH_Brep> surfaces = new List<GH_Brep>();
            List<GH_Brep> inner = new List<GH_Brep>();
            List<GH_Curve> curves = new List<GH_Curve>();
            List<GH_Mesh> meshes = new List<GH_Mesh>();

            GH_String parentName = new GH_String("");
            SketchUpNET.Component parentComponent = i.Parent as Component;
            if (parentComponent != null)
            {
                parentName = new GH_String(parentComponent.Name);
                foreach (Surface srf in parentComponent.Surfaces)
                {
                    foreach (var brep in srf.ToRhinoGeo(i.Transformation))
                    {
                        surfaces.Add(new GH_Brep(brep));
                    }

                    if (srf.FaceMesh != null)
                    {
                        meshes.Add(new GH_Mesh(srf.FaceMesh.ToRhinoGeo()));
                    }
                }

                foreach (Edge c in parentComponent.Edges)
                    curves.Add(new GH_Curve(c.ToRhinoGeo().ToNurbsCurve()));

               
            }

            DA.SetData(0, location);
            DA.SetData(1, name);
            DA.SetData(2, scale);
            DA.SetDataList(3, surfaces);
            DA.SetData(4, parentName);
            DA.SetDataList(5, inner);
            DA.SetDataList(6, curves);
            DA.SetDataList(7, meshes);
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("{5ea7ce4d-d266-4d7f-a733-1583beeb4b8d}");
            }
        }
        protected override Bitmap Internal_Icon_24x24
        {
            get
            {
                return Properties.Resources.Skp;
            }
        }
    }

    /// <summary>
    /// Geometry Translations
    /// </summary>
    public static class Geometry
    {
        public static string DefaultLayer = "Default";

        /// <summary>
        /// Converts a SketchUp Vertex to a Rhino Point
        /// </summary>
        public static Rhino.Geometry.Point3d ToRhinoGeo(this SketchUpNET.Vertex v, Transform t = null)
        {
            if (t == null)
                return new Rhino.Geometry.Point3d(v.X , v.Y , v.Z );
            else
            {
                Vertex transformed = t.GetTransformed(v);
                return new Rhino.Geometry.Point3d(transformed.X, transformed.Y, transformed.Z);
            }
        }

        /// <summary>
        /// Converts a Rhino Point to a SketchUp Point
        /// </summary>
        public static SketchUpNET.Vertex ToSkpGeo(this Rhino.Geometry.Point3d v)
        {
            return new SketchUpNET.Vertex(v.X, v.Y, v.Z);
        }

        /// <summary>
        /// Converts a Rhino Vector to a SketchUp Vector
        /// </summary>
        public static SketchUpNET.Vector ToSkpGeo(this Rhino.Geometry.Vector3d v)
        {
            return new SketchUpNET.Vector(v.X, v.Y, v.Z);
        }

        /// <summary>
        /// Converts a SketchUp Vector to a Rhino Vector
        /// </summary>
        public static Rhino.Geometry.Vector3d ToRhinoGeo(this SketchUpNET.Vector v)
        {
                return new Rhino.Geometry.Vector3d(v.X, v.Y, v.Z);
        }

        /// <summary>
        /// Converts a SketchUp Edge to a Rhino Line
        /// </summary>
        public static Rhino.Geometry.Line ToRhinoGeo(this SketchUpNET.Edge v, Transform t = null)
        {
            return new Rhino.Geometry.Line(v.Start.ToRhinoGeo(t), v.End.ToRhinoGeo(t));
        }

        /// <summary>
        /// Converts a Rhino Line to a SketchUp Edge
        /// </summary>
        public static SketchUpNET.Edge ToSkpGeo(this Rhino.Geometry.Line v)
        {
            return new SketchUpNET.Edge(v.PointAt(0).ToSkpGeo(), v.PointAt(1.0).ToSkpGeo(), DefaultLayer);
        }


        /// <summary>
        /// Converts a Rhino Curve to a SketchUp Curve
        /// </summary>
        public static SketchUpNET.Curve ToSkpGeo(this Rhino.Geometry.Curve v)
        {
            List<Edge> edges = new List<Edge>();
            if (v.IsLinear())
            {
                edges.Add(new Edge(v.PointAt(0).ToSkpGeo(), v.PointAt(1.0).ToSkpGeo(), DefaultLayer));
            }
            else
            {
                for (double i = 0; i < 1.0; i = i + 0.1)
                {
                    edges.Add(new Edge(v.PointAt(i).ToSkpGeo(), v.PointAt(i + 0.1).ToSkpGeo(), DefaultLayer));
                }
            }
            return new SketchUpNET.Curve(edges,v.IsArc());
        }

        /// <summary>
        /// Converts a Rhino Surface to a SketchUp Surface
        /// </summary>
        public static SketchUpNET.Surface ToSkpGeo(this Rhino.Geometry.Brep surface)
        {
            Surface srf = new Surface();
            srf.Vertices = new List<Vertex>();
            
            foreach (var curve in surface.Edges)
            {
                if (curve.IsLinear())
                {
                    srf.Vertices.Add(curve.PointAt(0.0).ToSkpGeo());
                }
                else
                {
                    for (double i = 0; i < 1.0; i = i + 0.1)
                    {
                        srf.Vertices.Add(curve.PointAt(i).ToSkpGeo());
                    }
                }
            }
            return srf;
        }

        /// <summary>
        /// Converts a SketchUp Surface to a Rhino Surface
        /// </summary>
        public static Rhino.Geometry.Brep[] ToRhinoGeo(this SketchUpNET.Surface v, Transform t = null)
        {
            List<Rhino.Geometry.Curve> curves = new List<Rhino.Geometry.Curve>();
            var tol = Rhino.RhinoDoc.ActiveDoc.ModelAbsoluteTolerance;
            foreach (SketchUpNET.Edge c in v.OuterEdges.Edges)
                curves.Add(c.ToRhinoGeo(t).ToNurbsCurve());

            Rhino.Geometry.Brep[] b = Rhino.Geometry.Brep.CreatePlanarBreps(curves,tol);
            if (b == null) return new Rhino.Geometry.Brep[] { };

            List<Rhino.Geometry.Brep> breps = v.InnerLoops(t);

            if (breps.Count > 0 && b.Length > 0)
            {
                  Rhino.Geometry.Brep[] tmp = Rhino.Geometry.Brep.CreateBooleanDifference(b, breps, 0);
                  if (tmp.Length > 0) return tmp;
            }
  
            return b;
        }

        /// <summary>
        /// Converts a SketchUp Surface InnerLoops to a Rhino Geometries
        /// </summary>
        public static List<Rhino.Geometry.Brep> InnerLoops(this SketchUpNET.Surface v, Transform t = null)
        {
            List<Rhino.Geometry.Brep> breps = new List<Rhino.Geometry.Brep>();
            var tol = Rhino.RhinoDoc.ActiveDoc.ModelAbsoluteTolerance;

            foreach (Loop loop in v.InnerEdges)
            {
                List<Rhino.Geometry.Curve> curves = new List<Rhino.Geometry.Curve>();
                foreach (SketchUpNET.Edge c in loop.Edges) curves.Add(c.ToRhinoGeo(t).ToNurbsCurve());
                Rhino.Geometry.Brep[] b = Rhino.Geometry.Brep.CreatePlanarBreps(curves,tol);
                if (b != null)
                {
                    foreach (var brep in b)
                        breps.Add(brep);
                }
            }
            return breps;
        }


        public static Rhino.Geometry.Mesh ToRhinoGeo(this SketchUpNET.Mesh mesh, Transform t = null)
        {
            Rhino.Geometry.Mesh m = new Rhino.Geometry.Mesh();

            foreach (var v in mesh.Vertices)
                m.Vertices.Add(v.ToRhinoGeo(t));

            foreach (var v in mesh.Faces)
                m.Faces.AddFace(v.A,v.B,v.C);

            m.Normals.ComputeNormals();
            m.Compact();
            return m;
        }

        public static void WriteModel(string path, List<GH_Surface> surfaces = null, List<GH_Curve> curves = null, bool append = false)
        {
            SketchUpNET.SketchUp skp = new SketchUpNET.SketchUp();
            skp.Surfaces = new List<Surface>();
            skp.Edges = new List<Edge>();
            skp.Curves = new List<Curve>();

            if (curves != null)
                foreach (var c in curves)
                {
                    var curve = c.Value;
                    if (curve.IsLinear())
                    {
                        var line = new SketchUpNET.Edge(curve.PointAt(0).ToSkpGeo(), curve.PointAt(1.0).ToSkpGeo(), DefaultLayer);
                        skp.Edges.Add(line);
                    }
                    else
                    {
                        skp.Curves.Add(curve.ToSkpGeo());
                    }
                }

            if (surfaces != null)
                foreach (var surface in surfaces)
                    skp.Surfaces.Add(surface.Value.ToSkpGeo());

            if (System.IO.File.Exists(path) && append)
                skp.AppendToModel(path);
            else
                skp.WriteNewModel(path);
        }

    }
}
