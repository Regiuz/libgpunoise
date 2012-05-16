
#ifndef LIBGPUNOISE_VORONOI3D_H
#define LIBGPUNOISE_VORONOI3D_H

#include "gpunoise/Module3D.h"
#include "gpunoise/types.h"


namespace gpunoise
{

struct Voronoi3DHelperModule : public HelperModule
{
  virtual std::string generate() const;
  virtual std::string getName() const;
};

struct Voronoi3D : public Generator3D
{
  Voronoi3D(Voronoi3DHelperModule* voronoi_math_module);
  
  virtual std::string generate() const;
  virtual std::string getName() const;
  
  void EnableDistance(bool enable=true);
  real_t GetDisplacement() const;
  real_t GetFrequency() const;
  int GetSeed() const;
  
  void SetDisplacement(real_t displacement);
  void SetFrequency(real_t frequency);
  void SetSeed(int seed);
  
private:
  Voronoi3DHelperModule* voronoi_math_module;
  real_t mfrequency;
  real_t mdisplacement;
  int mseed;
  bool mdistanceenabled;
};

} // namespace gpunoise


#endif
