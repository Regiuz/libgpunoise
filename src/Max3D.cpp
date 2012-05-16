
#include "gpunoise/Max3D.h"


namespace gpunoise
{
  
  Max3D::Max3D()
    : BinaryCGFunction3D("Max3D", "max")
  {}
  
  Max3D::Max3D(Module3D* l, Module3D* r)
    : BinaryCGFunction3D("Max3D", "max", l, r)
  {}

} // namespace gpunoise
