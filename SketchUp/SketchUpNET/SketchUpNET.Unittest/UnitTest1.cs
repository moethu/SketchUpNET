using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

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

        [TestMethod]
        public void GetMesh()
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

        [TestMethod]
        public void SaveAs()
        {
            SketchUpNET.SketchUp skp = new SketchUp();
            string dir = System.IO.Path.GetDirectoryName(TestFile);
            skp.SaveAs(TestFile, SKPVersion.V2016, dir + "/NewFile.skp");

            Assert.IsTrue(System.IO.File.Exists(dir + "/NewFile.skp"));
            
        }

        [TestMethod]
        public void SaveAsUTF8()
        {
            SketchUpNET.SketchUp skp = new SketchUp();
            string dir = System.IO.Path.GetDirectoryName(TestFile);
            skp.SaveAs(TestFile, SKPVersion.V2016, dir + "/Überß.skp");

            Assert.IsTrue(System.IO.File.Exists(dir + "/Überß.skp"));
            bool res = skp.LoadModel(dir + "/Überß.skp");
            Assert.IsTrue(res);
        }

        [TestMethod]
        public void DoNotGetMesh()
        {
            SketchUpNET.SketchUp skp = new SketchUp();
            skp.LoadModel(TestFile, false);
            foreach (var srf in skp.Surfaces)
            {
                Assert.IsNull(srf.FaceMesh);
            }
        }

        [TestMethod]
        public void GetMaterial()
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
    }
}
