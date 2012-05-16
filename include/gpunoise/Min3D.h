#ifndef LIBGPUNOISE_MIN3D_H
#define LIBGPUNOISE_MIN3D_H

#include "gpunoise/Module3D.h"
#include "gpunoise/BinaryCGFunction3D.h"

namespace gpunoise
{         

  struct Min3D : BinaryCGFunction3D
  {
  public:
    Min3D();
    Min3D(Module3D* l, Module3D* r);
  };

} // namespace gpunoise

#endif // LIBGPUNOISE_MIN3D_H
