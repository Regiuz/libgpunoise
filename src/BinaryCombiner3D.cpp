
#include "gpunoise/BinaryCombiner3D.h"

namespace gpunoise {
  
  BinaryCombiner3D::BinaryCombiner3D()
    : mlhs(NULL)
    , mrhs(NULL)
  {}

  BinaryCombiner3D::BinaryCombiner3D(Module3D* l, Module3D* r)
    : mlhs(l)
    , mrhs(r)
 {}

  Module3D* BinaryCombiner3D::lhs() const
  {
    return mlhs;
  }

  Module3D* BinaryCombiner3D::rhs() const
  {
    return mrhs;
  }

  void BinaryCombiner3D::lhs(Module3D* l)
  {
    mlhs = l;
  }

  void BinaryCombiner3D::rhs(Module3D* r)
  {
    mrhs = r;
  }

} // namespace gpunoise
