#ifndef LIBGPUNOISE_POWER3D_H
#define LIBGPUNOISE_POWER3D_H

#include "gpunoise/Module3D.h"
#include "gpunoise/BinaryCGFunction3D.h"

namespace gpunoise
{         

  struct Power3D : BinaryCGFunction3D
  {
  public:
    Power3D();
    Power3D(Module3D* l, Module3D* r);
  };

} // namespace gpunoise

#endif // LIBGPUNOISE_POWER3D_H
