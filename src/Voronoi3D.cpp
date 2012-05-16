/*
 * Warning: 
 * 
 * This file contains code from http://briansharpe.wordpress.com/2011/10/01/gpu-texture-free-noise/,
 * under an unknown license.
 * 
 * This file contains code from noisepp, which is licensed under the BSD 2-Clause License. noisepp can be
 * obtained here: http://sourceforge.net/projects/noisepp/, and is authored by Urs C. Hanselmann.
 * 
 */



#include "gpunoise/Voronoi3D.h"

#include <boost/format.hpp>
#include <boost/format/group.hpp>
#include <gpunoise/encode.h>

namespace gpunoise
{
  
  std::string Voronoi3DHelperModule::getName() const
  {
    return "Voronoi3DHelperModule";
  }
  
  std::string Voronoi3DHelperModule::generate() const
  {
    
    /*
    std::string intNoise =
      
      "const int NOISE_X_FACTOR = 1619;\n"
      "const int NOISE_Y_FACTOR = 31337;\n"
      "const int NOISE_Z_FACTOR = 6971;\n"
      "const int NOISE_SEED_FACTOR = 1013;\n"
      "const int NOISE_SHIFT = 8;\n"
      "\n"
      
      "\n"
      "int intNoise (int x, int y, int z, int seed)\n"
      "{\n"
      //"  int n = (NOISE_X_FACTOR * x + NOISE_Y_FACTOR * y + NOISE_Z_FACTOR * z + NOISE_SEED_FACTOR * seed) & 0x7fffffff;\n"
      "  int n = mod((NOISE_X_FACTOR * x + NOISE_Y_FACTOR * y + NOISE_Z_FACTOR * z + NOISE_SEED_FACTOR * seed), 2147483647);\n"
      "  //n = shift_right(n, 13) ^ n;\n"
      "  return mod((n * (n * n * 60493 + 19990303) + 1376312589), 2147483647);\n"
      "}\n";
    */  
    
    
    /**
     * This code is from http://briansharpe.wordpress.com/2011/10/01/gpu-texture-free-noise/,
     * under an unknown license.
     */
    
    std::string noise =
      "float4 SGPP_coord_prepare(float4 x) {\n"
      "// return mod( x, 289.0 );  // unoptimized reference\n"
      "  return x - floor(x * ( 1.0 / 289.0 )) * 289.0;\n"
      "}\n"
      "float4 SGPP_permute(float4 x) {\n"
      "  // return mod( ( 34.0 * x + 1.0 ) * x , 289.0 );  // unoptimized reference\n"
      "  return fract( x * ( ( 34.0 / 289.0 ) * x + ( 1.0 / 289.0 ) ) ) * 289.0;  // LQ mod\n"
      "}\n"
      "float4 SGPP_resolve(float4 x) {\n"
      "  const float K = 7.0 / 288.0;\n"
      "  return fract(x * K);\n"
      "}\n"
      "float4 SGPP_hash( float2 gridcell ) {\n"
      "//    gridcell is assumed to be an integer coordinate\n"
      "  float4 hash_coord = SGPP_coord_prepare( float4( gridcell.xy, gridcell.xy + 1.0.xx ) );\n"
      "  return SGPP_resolve( SGPP_permute( SGPP_permute( hash_coord.xzxz ) + hash_coord.yyww ) );\n"
      "}\n"
      "\n";
      
    std::string calcNoise = noise +
      "inline float calcNoise (int x, int y, int z, int seed=0)\n"
      "{\n"
      //"  float3 xyz(x,y,z);\n"
      //"  xyz += xyz * seed;\n"
      //"  return noise(xyz);\n"
      "  return SGPP_hash(float2( x * seed + y * seed, x * seed + z * seed)).x;\n"
      //"  return noise(float3(x,y,z));\n"
      //"  return float(1.0) - ((float)intNoise(x, y, z, seed) / float(1073741824.0));\n"
      "}\n";

    return calcNoise;
  }
  
  
  
  Voronoi3D::Voronoi3D(Voronoi3DHelperModule* voronoi_math_module)
    : voronoi_math_module(voronoi_math_module)
    , mfrequency(1)
    , mdisplacement(1)
    , mseed(0)
    , mdistanceenabled(true)
  {
    BOOST_ASSERT(voronoi_math_module);
  }
  
  void Voronoi3D::EnableDistance(bool enabled)
  {
    mdistanceenabled = enabled;
  }
  
  real_t Voronoi3D::GetDisplacement() const
  {
    return mdisplacement;
  }
  
  real_t Voronoi3D::GetFrequency() const
  {
    return mfrequency;
  }
  
  int Voronoi3D::GetSeed() const
  {
    return mseed;
  }
  
  void Voronoi3D::SetDisplacement(real_t displacement)
  {
    mdisplacement = displacement;
  }
  
  void Voronoi3D::SetFrequency(real_t frequency)
  {
    mfrequency = frequency;
  }
  
  void Voronoi3D::SetSeed(int seed)
  {
    mseed = seed;
  }


  std::string Voronoi3D::getName() const
  {
    using boost::format;
    using boost::io::group;
    using boost::str;
    
    return str(format("Voronoi3D_f%1%_d%2%_s%3%_e_%4%")
      % encode_as_integer(mfrequency)
      % encode_as_integer(mdisplacement)
      % mseed
      % (mdistanceenabled ? "true" : "false"));
  }
  
  std::string Voronoi3D::generate() const
  {
  
    
    std::string value_def;
    if (mdistanceenabled)
    {
      value_def =
        "  const float SQRT_THREE = 1.7320508075688772;\n"
        "  float3 dist = min - xyz;\n"
        "  float value = (sqrt(dist.x * dist.x + dist.y * dist.y + dist.z * dist.z)) * SQRT_THREE - float(1.0);\n";
    } else {
      value_def =
        "  float value = 0;\n";
    }
    
    return
      boost::str(
        boost::format(
          "inline float %1%(float3 xyz)\n"
          "{\n"
          "  float frequency = %2%;\n"
          "  int seed = %3%;\n"
          "  float displacement = %4%;\n"
          "  xyz *= frequency;\n"
          
          "  int xi = (xyz.x > float(0.0) ? (int)xyz.x : (int)xyz.x - 1);\n"
          "  int yi = (xyz.y > float(0.0) ? (int)xyz.y : (int)xyz.y - 1);\n"
          "  int zi = (xyz.z > float(0.0) ? (int)xyz.z : (int)xyz.z - 1);\n"

          "  float minDist = float(2147483647.0);\n"
          "  float3 min = float3(0.0, 0.0, 0.0);\n"

          "  for (int xc=xi-2;xc<=xi+2;++xc) {\n"
          "    for (int yc=yi-2;yc<=yi+2;++yc) {\n"
          "      for (int zc=zi-2;zc<=zi+2;++zc) {\n"
          "        float3 p;\n"
          "        p.x = xc + calcNoise(xc, yc, zc, seed);\n"
          "        p.y = yc + calcNoise(xc, yc, zc, seed+1);\n"
          "        p.z = zc + calcNoise(xc, yc, zc, seed+2);\n"
          "        float3 d = p - xyz;\n"
          "        float dist = d.x * d.x + d.y * d.y + d.z * d.z;\n"
          "        if (dist < minDist)\n"
          "        {\n"
          "          minDist = dist;\n"
          "          min = p;\n"
          "        }\n"
          "      }\n"
          "    }\n"
          "  }\n"
          "\n"
          + value_def +
          ///FIXME: check source
          "  return value + (displacement * (float)calcNoise((int)floor(min.x), (int)floor(min.y), (int)floor(min.z)));\n"
          "}\n"
          ) % getName() % mfrequency % mseed % mdisplacement);
    
  }
  
} // namespace gpunoise
