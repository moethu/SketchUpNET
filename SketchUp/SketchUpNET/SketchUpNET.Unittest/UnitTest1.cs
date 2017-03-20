using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace SketchUpNET.Unittest
{
    [TestClass]
    public class UnitTests
    {
        [TestMethod]
        public void GetMesh()
        {
            SketchUpNET.SketchUp skp = new SketchUp();
            skp.LoadModel(@"C:\Users\MThumfart\Documents\GitHub\SketchUpNET\SketchUp\SketchUpNET\Testfiles\Testmodel.skp", true);
            foreach (var srf in skp.Surfaces)
            {
                Assert.IsNotNull(srf.FaceMesh);
                Assert.IsTrue(srf.FaceMesh.Faces.Count > 0);
                Assert.IsTrue(srf.FaceMesh.Vertices.Count > 0);
            }
        }

        [TestMethod]
        public void DoNotGetMesh()
        {
            SketchUpNET.SketchUp skp = new SketchUp();
            skp.LoadModel(@"C:\Users\MThumfart\Documents\GitHub\SketchUpNET\SketchUp\SketchUpNET\Testfiles\Testmodel.skp", false);
            foreach (var srf in skp.Surfaces)
            {
                Assert.IsNull(srf.FaceMesh);
            }
        }

        [TestMethod]
        public void GetMaterial()
        {
            SketchUpNET.SketchUp skp = new SketchUp();
            skp.LoadModel(@"C:\Users\MThumfart\Documents\GitHub\SketchUpNET\SketchUp\SketchUpNET\Testfiles\Testmodel.skp", false);

            bool found = false;

            foreach (var srf in skp.Surfaces)
            {
                Assert.IsNotNull(srf.BackMaterial);
                Assert.IsNotNull(srf.FrontMaterial);
                Assert.IsNotNull(srf.BackMaterial.Colour);
                Assert.IsNotNull(srf.FrontMaterial.Colour);
                if (srf.BackMaterial.Name == "MyMat")
                    found = true;
            }

            Assert.IsTrue(found);
        }
    }
}
