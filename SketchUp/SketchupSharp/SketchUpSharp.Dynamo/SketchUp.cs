/*

	SketchUpSharp Dynamo - SketchUp in Dynamo 
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
                return Autodesk.DesignScript.Geometry.Point.ByCoordinates(v.X + t.X, v.Y + t.Y, v.Z + t.Z);
        }

        [IsVisibleInDynamoLibrary(false)]
        public static Autodesk.DesignScript.Geometry.Vector ToDSGeo(this SketchUpSharp.Vector v, Transform t)
        {
            if (t == null)
                return Autodesk.DesignScript.Geometry.Vector.ByCoordinates(v.X, v.Y, v.Z);
            else
                return Autodesk.DesignScript.Geometry.Vector.ByCoordinates(v.X + t.X, v.Y + t.Y, v.Z + t.Z);
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
            foreach (Corner c in v.Corners) curves.Add(c.ToDSGeo(t).ToNurbsCurve());
            int a = 0;
            Autodesk.DesignScript.Geometry.PolyCurve pc = Autodesk.DesignScript.Geometry.PolyCurve.ByJoinedCurves(curves);
            Autodesk.DesignScript.Geometry.Surface s = Autodesk.DesignScript.Geometry.Surface.ByPatch(pc);
            return s;
        }
    }
}
