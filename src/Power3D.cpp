
#include "gpunoise/Power3D.h"


namespace gpunoise
{
  
  Power3D::Power3D()
    : BinaryCGFunction3D("Power3D", "pow")
  {}
  
  Power3D::Power3D(Module3D* l, Module3D* r)
    : BinaryCGFunction3D("Power3D", "pow", l, r)
  {}

} // namespace gpunoise
