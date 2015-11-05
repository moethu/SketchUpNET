/*

	SketchUpSharp Dynamo - SketchUp in Dynamo 
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
using DSCoreNodesUI;
using Dynamo.Utilities;
using Dynamo.Models;

namespace SketchUpSharp.Dynamo
{
    public class SketchUp
    {
        /// <summary>
        /// Cuda Info
        /// </summary>
        /// <param name="cuda">Cuda Instance</param>
        [MultiReturn(new[] { "Surfaces", "Layers", "Instances" })]
        public static Dictionary<string, object> LoadModel(string path)
        {
            List<Autodesk.DesignScript.Geometry.Surface> surfaces = new List<Autodesk.DesignScript.Geometry.Surface>();
            List<string> layers = new List<string>();
            List<Instance> Instances = new List<Instance>();

            SketchUpSharp.SketchUp skp = new SketchUpSharp.SketchUp();
            if (skp.LoadModel(path))
            {



                    foreach (Surface srf in skp.Surfaces)
                        surfaces.Add(srf.ToDSGeo());

                    foreach (Layer l in skp.Layers)
                        layers.Add(l.Name);

                    foreach (Instance i in skp.Instances)
                        Instances.Add(i);
                
                
            }

            return new Dictionary<string, object>
            {
                { "Surfaces", surfaces },
                { "Layers", layers },
                { "Instances", Instances }

            };
        }

        /// <summary>
        /// Cuda Info
        /// </summary>
        /// <param name="cuda">Cuda Instance</param>
        [MultiReturn(new[] { "Surfaces", "Position", "Scale", "Name", "Parent Name" })]
        public static Dictionary<string, object> GetInstance(Instance i)
        {
            List<Autodesk.DesignScript.Geometry.Surface> surfaces = new List<Autodesk.DesignScript.Geometry.Surface>();

            Autodesk.DesignScript.Geometry.Point p = Autodesk.DesignScript.Geometry.Point.ByCoordinates(i.Transformation.X, i.Transformation.Y, i.Transformation.Z);

            foreach (Surface srf in i.Parent.Surfaces)
                surfaces.Add(srf.ToDSGeo(i.Transformation));



            return new Dictionary<string, object>
            {
                { "Surfaces", surfaces },
                { "Position", p },
                { "Scale", i.Transformation.Scale },
                { "Name", i.Name },
                { "Parent Name", i.Parent.Name }

            };
        }

    }

    [IsVisibleInDynamoLibrary(false)]
    public static class Geometry
    {
        [IsVisibleInDynamoLibrary(false)]
        public static Autodesk.DesignScript.Geometry.Point ToDSGeo(this SketchUpSharp.Vertex v, Transform t)
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
        public static Autodesk.DesignScript.Geometry.Vector ToDSGeo(this SketchUpSharp.Vector v)
        {
            return Autodesk.DesignScript.Geometry.Vector.ByCoordinates(v.X, v.Y, v.Z);
        }

        [IsVisibleInDynamoLibrary(false)]
        public static Autodesk.DesignScript.Geometry.Line ToDSGeo(this SketchUpSharp.Corner v, Transform t)
        {
            return Autodesk.DesignScript.Geometry.Line.ByStartPointEndPoint(v.Start.ToDSGeo(t), v.End.ToDSGeo(t));
        }

        [IsVisibleInDynamoLibrary(false)]
        public static Autodesk.DesignScript.Geometry.Surface ToDSGeo(this SketchUpSharp.Surface v, Transform t = null)
        {
            List<Autodesk.DesignScript.Geometry.Curve> curves = new List<Autodesk.DesignScript.Geometry.Curve>();
            foreach (Corner c in v.OuterEdges.Corners) curves.Add(c.ToDSGeo(t).ToNurbsCurve());
            int a = 0;
            Autodesk.DesignScript.Geometry.PolyCurve pc = Autodesk.DesignScript.Geometry.PolyCurve.ByJoinedCurves(curves);
            Autodesk.DesignScript.Geometry.Surface s = Autodesk.DesignScript.Geometry.Surface.ByPatch(pc);
            
             List<Autodesk.DesignScript.Geometry.Surface> inner = v.InnerLoops(t);

            foreach(Autodesk.DesignScript.Geometry.Surface srf in inner)
            {
                Autodesk.DesignScript.Geometry.Geometry[] geo = s.Split(srf);
                if (geo.Count() == 2) s = (Autodesk.DesignScript.Geometry.Surface)geo[0];

            }
            return s;
        }

        [IsVisibleInDynamoLibrary(false)]
        public static List<Autodesk.DesignScript.Geometry.Surface> InnerLoops(this SketchUpSharp.Surface v, Transform t = null)
        {
            List<Autodesk.DesignScript.Geometry.Surface> surfaces = new List<Autodesk.DesignScript.Geometry.Surface>();

            foreach (Loop loop in v.InnerEdges)
            {
                List<Autodesk.DesignScript.Geometry.Curve> curves = new List<Autodesk.DesignScript.Geometry.Curve>();
                foreach (Corner c in loop.Corners) curves.Add(c.ToDSGeo(t).ToNurbsCurve());
                int a = 0;
                Autodesk.DesignScript.Geometry.PolyCurve pc = Autodesk.DesignScript.Geometry.PolyCurve.ByJoinedCurves(curves);
                Autodesk.DesignScript.Geometry.Surface s = Autodesk.DesignScript.Geometry.Surface.ByPatch(pc);
                surfaces.Add(s);
            }

            return surfaces;
        }
    }
}
