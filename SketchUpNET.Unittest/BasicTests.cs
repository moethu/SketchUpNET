using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;

namespace SketchUpNET.Unittest
{
    [TestClass]
    public class UnitTests
    {
        [TestInitialize()]
        public void Initialize()
        {
            Type t = typeof(UnitTests);
            TestFile = System.IO.Path.GetDirectoryName(t.Assembly.Location) + @"\..\..\..\..\Testfiles\TestModel.skp";
        }

        public static string TestFile;

        /// <summary>
        /// Test loading surfaces and meshes from testfile
        /// </summary>
        [TestMethod]
        public void TestGetMesh()
        {
            SketchUpNET.SketchUp skp = new SketchUp();
            skp.LoadModel(TestFile, true);
            foreach (var srf in skp.Surfaces)
            {
                Assert.IsNotNull(srf.FaceMesh);
                Assert.IsTrue(srf.FaceMesh.Faces.Count > 0);
                Assert.IsTrue(srf.FaceMesh.Vertices.Count > 0);
            }
        }

        /// <summary>
        /// Test loading options
        /// </summary>
        [TestMethod]
        public void TestOptions()
        {
            SketchUpNET.SketchUp skp = new SketchUp();
            skp.LoadModel(TestFile, true);
            Assert.IsNotNull(skp.Options);
        }

        /// <summary>
        /// Test saving file as
        /// </summary>
        [TestMethod]
        public void TestSaveAs()
        {
            SketchUpNET.SketchUp skp = new SketchUp();
            string dir = System.IO.Path.GetDirectoryName(TestFile);
            skp.SaveAs(TestFile, SKPVersion.V2016, dir + "/NewFile.skp");
            Assert.IsTrue(System.IO.File.Exists(dir + "/NewFile.skp"));
        }

        /// <summary>
        /// Test saving UTF8 Filenames
        /// </summary>
        [TestMethod]
        public void TestSaveAsUTF8()
        {
            SketchUpNET.SketchUp skp = new SketchUp();
            string dir = System.IO.Path.GetDirectoryName(TestFile);
            skp.SaveAs(TestFile, SKPVersion.V2016, dir + "/Überß.skp");

            Assert.IsTrue(System.IO.File.Exists(dir + "/Überß.skp"));
            bool res = skp.LoadModel(dir + "/Überß.skp");
            Assert.IsTrue(res);
        }

        /// <summary>
        /// Test loading model without meshes
        /// </summary>
        [TestMethod]
        public void TestDoNotGetMesh()
        {
            SketchUpNET.SketchUp skp = new SketchUp();
            skp.LoadModel(TestFile, false);
            foreach (var srf in skp.Surfaces)
            {
                Assert.IsNull(srf.FaceMesh);
            }
        }

        /// <summary>
        /// Test getting Materials from model
        /// </summary>
        [TestMethod]
        public void TestGetMaterial()
        {
            SketchUpNET.SketchUp skp = new SketchUp();
            skp.LoadModel(TestFile, false);

            bool found = false;

            foreach (var srf in skp.Surfaces)
            {
                Assert.IsNotNull(srf.BackMaterial);
                Assert.IsNotNull(srf.FrontMaterial);
                Assert.IsNotNull(srf.BackMaterial.Colour);
                Assert.IsNotNull(srf.FrontMaterial.Colour);
                if (srf.BackMaterial.Name == "MyMat" || srf.FrontMaterial.Name == "MyMat")
                    found = true;
            }

            Assert.IsTrue(found);
        }

        [TestMethod]
        public void TestInnerLoop()
        {

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

            SketchUpNET.Surface s = new SketchUpNET.Surface(OuterEdges, InnerLoops, null, 0, Verticies, null, "Layer0", null, null);
            skp.Surfaces.Add(s);
            
            
            skp.WriteNewModel(@"TempModel.skp");
            skp.LoadModel(@"TempModel.skp");

            Assert.IsTrue(skp.Surfaces.Count == 1);
            Assert.IsTrue(skp.Surfaces[0].InnerEdges.Count == 1);
            Assert.IsTrue(skp.Surfaces[0].InnerEdges[0].Edges.Count == 4);
            Assert.IsTrue(skp.Surfaces[0].OuterEdges.Edges.Count == 4);
        }
    }
}
