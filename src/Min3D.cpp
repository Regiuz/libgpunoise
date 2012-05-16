
#include "gpunoise/Min3D.h"


namespace gpunoise
{
  
  Min3D::Min3D()
    : BinaryCGFunction3D("Min3D", "min")
  {}
  
  Min3D::Min3D(Module3D* l, Module3D* r)
    : BinaryCGFunction3D("Min3D", "min", l, r)
  {}

} // namespace gpunoise
