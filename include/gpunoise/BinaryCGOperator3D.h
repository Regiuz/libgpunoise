#ifndef LIBGPUNOISE_BINARYCGOPERATOR3D_H
#define LIBGPUNOISE_BINARYCGOPERATOR3D_H

#include "BinaryCombiner3D.h"


namespace gpunoise
{

  struct BinaryCGOperator3D : BinaryCombiner3D
  {
    BinaryCGOperator3D(const std::string& name, const std::string& op);
    BinaryCGOperator3D(const std::string& name, const std::string& op, Module3D* l, Module3D* r);
    virtual std::string generate() const;
    virtual std::string getName() const;
    
  private:
    const std::string name;
    const std::string op;
  };
  
} // namespace gpunoise

#endif // LIBGPUNOISE_BINARYCGOPERATOR3D_H
