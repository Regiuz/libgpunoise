/*
 * 
 * This file contains code from noisepp, which is licensed under the BSD 2-Clause License. noisepp can be
 * obtained here: http://sourceforge.net/projects/noisepp/, and is authored by Urs C. Hanselmann.
 * 
 */


#include "gpunoise/Perlin3D.h"
#include <boost/format.hpp>

namespace gpunoise
{
  
  
  
  
  Perlin3D::Perlin3D()
  {
    
  }
  
  std::string Perlin3D::getName() const
  {
    return "Perlin3D";
  }
  
  std::string Perlin3D::generate() const
  {
    
    std::string CubicCurve3Def =
      "float noisepp_Math_CubicCurve3(float a)\n"
      "{\n"
        "return (a * a * (Real(3) - Real(2) * a));\n"
      "}\n";
    
    std::string calcGradientNoise =
      "const int NOISE_X_FACTOR = 1619;\n"
      "const int NOISE_Y_FACTOR = 31337;\n"
      "const int NOISE_Z_FACTOR = 6971;\n"
      "const int NOISE_SEED_FACTOR = 1013;\n"
      "const int NOISE_SHIFT = 8;\n"
      "\n"
      "float calcGradientNoise (float fx, int ix, int seed)\n"
      "{\n"
        "int vIndex = (NOISE_X_FACTOR * ix + NOISE_SEED_FACTOR * seed) & 0xffffffff;\n"
        "vIndex ^= (vIndex >> NOISE_SHIFT);\n"
        "vIndex &= 0xff;\n"

        "const float xGradient = tex2D(randomVectors3D, vIndex << 2);\n"

        "const float xDelta = fx - float(ix);\n"
        "return xDelta * xGradient;\n"
      "}\n";
    
    
    std::string interpGradientCoherentNoise =
      "float noisepp_Gradient3D_interpGradientCoherentNoise(float xyz,\n"
                                                           "int x0, int x1, int y0, int y1, int z0, int z1,\n"
                                                           "float3 s, int seed, float scale)\n"
      "\n"
      "{\n"
        "float n0, n1, ix0, ix1, iy0, iy1;\n"
        "n0 = calcGradientNoise(xyz, x0, y0, z0, seed);\n"
        "n1 = calcGradientNoise(x, y, z, x1, y0, z0, seed);\n"
        "ix0 = lerp(n0, n1, xs);\n"
        "n0 = calcGradientNoise(x, y, z, x0, y1, z0, seed);\n"
        "n1 = calcGradientNoise(x, y, z, x1, y1, z0, seed);\n"
        "ix1 = lerp(n0, n1, xs);\n"
        "iy0 = lerp(ix0, ix1, ys);\n"
        "n0 = calcGradientNoise(x, y, z, x0, y0, z1, seed);\n"
        "n1 = calcGradientNoise(x, y, z, x1, y0, z1, seed);\n"
        "ix0 = lerp(n0, n1, xs);\n"
        "n0 = calcGradientNoise(x, y, z, x0, y1, z1, seed);\n"
        "n1 = calcGradientNoise(x, y, z, x1, y1, z1, seed);\n"
        "ix1 = lerp(n0, n1, xs);\n"
        "iy1 = lerp(ix0, ix1, ys);\n"

        "return lerp(iy0, iy1, zs) * scale;\n"
      "}\n";
                        
    std::string calcGradientCoherentNoiseStdDef =
      "float noisepp_Generator3D_calcGradientCoherentNoiseStd(float3 xyz int seed, float scale)\n"
      "{\n"
        "int x0 = floor(xyz.x); int y0 = floor(xyz.y) int z0 = floor(xyz.z);\n"
        "int x1 = x0 + 1; int y1 = y0 + 1; int z1 = z0 + 1;\n"
        
        "float3 s;\n"
        "s.x = noisepp_Math_CubicCurve3(xyz.x - float(x0));\n"
        "s.y = noisepp_Math_CubicCurve3(xyz.y - float(y0));\n"
        "s.z = noisepp_Math_CubicCurve3(xyz.z - float(z0));\n"

        "return noisepp_Generator3D_interpGradientCoherentNoise(xyz, x0, x1, y0, y1, z0, z1, s, seed, scale)\n;"
      "}\n";
    
    std::string MakeInt32Range =
      "float noisepp_Math_MakeInt32Range(float n)\n"
      "{\n"
        //FIXME
        "return n;\n"
      "}\n";
    
    
    
    return
      boost::str(
        boost::format(
          "float %1%(float3 xyz){\n"
            
            "float value = 0.0;\n"
            "float signal = 1.0;\n"
            
            "int octaves = %2%\n"
            
            "for (int octave = 0; octave < octaves; ++octave)\n"
            "{\n"
                "float nx = noisepp_Math_MakeInt32Range (xyz.x * mOctaves[o].scale);\n"
                "float ny = noisepp_Math_MakeInt32Range (xyz.y * mOctaves[o].scale);\n"
                "float nz = noisepp_Math_MakeInt32Range (xyz.z * mOctaves[o].scale);\n"
                "signal = noisepp_Math_calcGradientCoherentNoiseStd(nx, ny, nz, mOctaves[o].seed);\n"

                "value += signal * mOctaves[o].persistence;\n"
            "}\n"
        ) % getName()); 
  }
  
} // namespace gpunoise


