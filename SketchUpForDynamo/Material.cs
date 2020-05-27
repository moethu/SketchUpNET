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

        /// <summary>
        /// Get Textrue Height
        /// </summary>
        /// <returns></returns>
        public int GetTextureHeight()
        {
            return Internal.MaterialTexture.Height;
        }

        /// <summary>
        /// Get Texture Width
        /// </summary>
        /// <returns></returns>
        public int GetTextureWidth()
        {
            return Internal.MaterialTexture.Width;
        }

        /// <summary>
        /// Get Texture Scale in Height
        /// </summary>
        /// <returns></returns>
        public double GetTextureScaleH()
        {
            return Internal.MaterialTexture.ScaleH;
        }

        /// <summary>
        /// Get Textute Scale in Width
        /// </summary>
        /// <returns></returns>
        public double GetTextureScaleW()
        {
            return Internal.MaterialTexture.ScaleW;
        }

        /// <summary>
        /// Does the material texture use alpha?
        /// </summary>
        /// <returns></returns>
        public bool GetTextureUsesAlpha()
        {
            return Internal.MaterialTexture.useAlpha;
        }

        /// <summary>
        /// Get Colour
        /// </summary>
        /// <returns></returns>
        public DSCore.Color GetColour()
        {
            return Internal.Colour.ToDSColour();
        }

        /// <summary>
        /// Get Texture Colour
        /// </summary>
        /// <returns></returns>
        public DSCore.Color GetTextureColour()
        {
            return Internal.MaterialTexture.Colour.ToDSColour();
        }

        /// <summary>
        /// Get Opacity
        /// </summary>
        /// <returns></returns>
        public double GetOpacity()
        {
            return Internal.Opacity;
        }

        /// <summary>
        /// Does the material use opacity?
        /// </summary>
        /// <returns></returns>
        public bool GetUseOpacity()
        {
            return Internal.UseOpacity;
        }

        /// <summary>
        /// Does the material use colour?
        /// </summary>
        /// <returns></returns>
        public bool GetUsesColor()
        {
            return Internal.UsesColor;
        }

        /// <summary>
        /// Does the material use texture?
        /// </summary>
        /// <returns></returns>
        public bool GetUsesTexture()
        {
            return Internal.UsesTexture;
        }
    }
}
