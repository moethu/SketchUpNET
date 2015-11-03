/*

	SketchUpSharp Grasshopper - SketchUp in Grasshopper 
	Copyright(C) 2015, Autor: Maximilian Thumfart

	This program is free software : you can redistribute it and / or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.If not, see <http://www.gnu.org/licenses/>.

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

namespace SketchUpSharp.Grasshopper
{
    /// <summary>
    /// Grevit Revit Family Component
    /// </summary>
    public class SketchUpModel : GH_Component
    {
        public SketchUpModel() : base("Sketch Up Model", "Sketch Up Model", "Sketch Up Model", "SketchUpSharp", "Model") { }


        protected override void RegisterInputParams(GH_Component.GH_InputParamManager pManager)
        {
            pManager.AddTextParameter("Path", "P", "Path to SKP File", GH_ParamAccess.item);
        }

        protected override void RegisterOutputParams(GH_Component.GH_OutputParamManager pManager)
        {
            pManager.AddBrepParameter("Surfaces", "S", "Surfaces", GH_ParamAccess.list);
            pManager.AddTextParameter("Layers", "L", "Layers", GH_ParamAccess.list);
            pManager.AddGenericParameter("Instances", "I", "Instances", GH_ParamAccess.list);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            GH_String path = new GH_String();
            DA.GetData<GH_String>(0, ref path);

            List<GH_Brep> surfaces = new List<GH_Brep>();
            List<GH_String> layers = new List<GH_String>();
            List<Instance> Instances = new List<Instance>();

            SketchUp skp = new SketchUp();
            if (skp.LoadModel(path.Value))
            { 
                foreach (Surface srf in skp.Surfaces)
                    surfaces.Add(new GH_Brep(srf.ToRhinoGeo().ToBrep()));

                foreach (Layer l in skp.Layers)
                    layers.Add(new GH_String(l.Name));

                foreach (Instance i in skp.Instances)
                    Instances.Add(i);
            }



            DA.SetDataList(0, surfaces);
            DA.SetDataList(1, layers);
            DA.SetDataList(2, Instances);
        }

        // Properties
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
    /// Grevit Revit Family Component
    /// </summary>
    public class SketchUpInstance : GH_Component
    {
        public SketchUpInstance() : base("Sketch Up Instance", "Sketch Up Instance", "Sketch Up Instance", "SketchUpSharp", "Elements") { }


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
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {

            Instance i = null;
            DA.GetData<Instance>(0, ref i);

            GH_Point p = new GH_Point(new Rhino.Geometry.Point3d(i.Transformation.X, i.Transformation.Y, i.Transformation.Z));
            GH_Number scale = new GH_Number(i.Transformation.Scale);
            GH_String name = new GH_String(i.Name);
            GH_String parent = new GH_String(i.Parent.Name);

            List<GH_Brep> surfaces = new List<GH_Brep>();

                foreach (Surface srf in i.Parent.Surfaces)
                    surfaces.Add(new GH_Brep(srf.ToRhinoGeo(i.Transformation).ToBrep()));
          

            DA.SetData(0, p);
            DA.SetData(1, name);
            DA.SetData(2, scale);
            DA.SetDataList(3, surfaces);
            DA.SetData(4, parent);
        }

        // Properties
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

    public static class Geometry
    {
        public static Rhino.Geometry.Point3d ToRhinoGeo(this SketchUpSharp.Vertex v, Transform t)
        {
            if (t == null)
                return new Rhino.Geometry.Point3d(v.X , v.Y , v.Z );
            else
                return new Rhino.Geometry.Point3d(v.X + t.X, v.Y+ t.Y, v.Z+t.Z);
        }

        public static Rhino.Geometry.Vector3d ToRhinoGeo(this SketchUpSharp.Vector v, Transform t)
        {
            if (t == null)
                return new Rhino.Geometry.Vector3d(v.X, v.Y, v.Z);
            else
                return new Rhino.Geometry.Vector3d(v.X + t.X, v.Y + t.Y, v.Z + t.Z);
        }

        public static Rhino.Geometry.Line ToRhinoGeo(this SketchUpSharp.Corner v, Transform t)
        {
            return new Rhino.Geometry.Line(v.Start.ToRhinoGeo(t), v.End.ToRhinoGeo(t));
        }

        public static Rhino.Geometry.NurbsSurface ToRhinoGeo(this SketchUpSharp.Surface v, Transform t = null)
        {
            List<Rhino.Geometry.Curve> curves = new List<Rhino.Geometry.Curve>();
            foreach (Corner c in v.Corners) curves.Add(c.ToRhinoGeo(t).ToNurbsCurve());
            int a = 0;
            Rhino.Geometry.NurbsSurface s =  Rhino.Geometry.NurbsSurface.CreateNetworkSurface(curves, 3, 0, 0, 0,out a);
            return s;
        }
    }
}
