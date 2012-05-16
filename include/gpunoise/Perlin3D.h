
#ifndef LIBGPUNOISE_PERLIN3D_H
#define LIBGPUNOISE_PERLIN3D_H

#include "gpunoise/Module3D.h"

namespace gpunoise
{




struct Perlin3D : Generator3D
{
  Perlin3D();
  
  virtual std::string generate() const;
  virtual std::string getName() const;
};

} // namespace gpunoise


#endif // LIBGPUNOISE_PERLIN3D_H
