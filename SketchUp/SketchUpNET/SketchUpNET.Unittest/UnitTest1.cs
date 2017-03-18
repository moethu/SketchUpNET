using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace SketchUpNET.Unittest
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestMethod1()
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
    }
}
