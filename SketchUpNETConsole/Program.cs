using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SketchUpNETConsole
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length > 0)
            {
                SketchUpNET.SketchUp skp = new SketchUpNET.SketchUp();
                if (skp.LoadModel(args[0]))
                {
                    // do something
                }
            }
        }
    }
}
