#ifndef LIBGPUNOISE_BINARYCGFUNCTION3D_H
#define LIBGPUNOISE_BINARYCGFUNCTION3D_H

#include "Module3D.h"
#include "BinaryCombiner3D.h"

namespace gpunoise
{         

  struct BinaryCGFunction3D : BinaryCombiner3D
  {
    BinaryCGFunction3D(const std::string& function_name, const std::string& function);
    BinaryCGFunction3D(const std::string& function_name, const std::string& function, Module3D* l, Module3D* r);
    virtual std::string generate() const;
    virtual std::string getName() const;
    
  private:
    const std::string function_name;
    const std::string function;
  };
  
} // namespace gpunoise

#endif // LIBGPUNOISE_BINARYCGFUNCTION3D_H
