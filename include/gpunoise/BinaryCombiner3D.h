#ifndef LIBGPUNOISE_BINARYCOMBINER3D_H
#define LIBGPUNOISE_BINARYCOMBINER3D_H

#include "Module3D.h"


namespace gpunoise
{
  struct BinaryCombiner3D : Combiner3D
  {
    BinaryCombiner3D();
    BinaryCombiner3D(Module3D* lhs, Module3D* rhs);
    
    Module3D* lhs() const;
    Module3D* rhs() const;
    void lhs(Module3D* l);
    void rhs(Module3D* r);
  private:
    Module3D* mlhs;
    Module3D* mrhs;
  };
} // namespace gpunoise

#endif // LIBGPUNOISE_BINARYCOMBINER3D_H
