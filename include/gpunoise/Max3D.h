#ifndef LIBGPUNOISE_MAX3D_H
#define LIBGPUNOISE_MAX3D_H

#include "gpunoise/Module3D.h"
#include "gpunoise/BinaryCGFunction3D.h"

namespace gpunoise
{         

  struct Max3D : BinaryCGFunction3D
  {
  public:
    Max3D();
    Max3D(Module3D* l, Module3D* r);
  };

} // namespace gpunoise

#endif // LIBGPUNOISE_MAX3D_H
