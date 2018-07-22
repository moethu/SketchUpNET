using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SketchUpForDynamo
{
    public class Material
    {
        private SketchUpNET.Material Internal;

        internal Material(SketchUpNET.Material mat)
        {
            Internal = mat;
        }

        /// <summary>
        /// Get Material Name
        /// </summary>
        /// <returns></returns>
        public string GetName()
        {
            return Internal.Name;
        }

        /// <summary>
        /// Get Texture Filename
        /// </summary>
        /// <returns></returns>
        public string GetTextureFileName()
        {
            return Internal.MaterialTexture.Name;
        }

        public int GetTextureHeight()
        {
            return Internal.MaterialTexture.Height;
        }

        public int GetTextureWidth()
        {
            return Internal.MaterialTexture.Width;
        }

        public double GetTextureScaleH()
        {
            return Internal.MaterialTexture.ScaleH;
        }

        public double GetTextureScaleW()
        {
            return Internal.MaterialTexture.ScaleW;
        }

        public bool GetTextureUsesAlpha()
        {
            return Internal.MaterialTexture.useAlpha;
        }

        public DSCore.Color GetColour()
        {
            return Internal.Colour.ToDSColour();
        }

        public DSCore.Color GetTextureColour()
        {
            return Internal.MaterialTexture.Colour.ToDSColour();
        }

        public double GetOpacity()
        {
            return Internal.Opacity;
        }

        public bool GetUseOpacity()
        {
            return Internal.UseOpacity;
        }

        public bool GetUsesColor()
        {
            return Internal.UsesColor;
        }

        public bool GetUsesTexture()
        {
            return Internal.UsesTexture;
        }
    }
}
