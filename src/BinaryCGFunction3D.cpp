

#include "gpunoise/BinaryCGFunction3D.h"

#include <boost/assert.hpp>
#include <boost/format.hpp>

namespace gpunoise
{
  BinaryCGFunction3D::BinaryCGFunction3D(const std::string& function_name, const std::string& function)
    : BinaryCombiner3D()
    , function_name(function_name)
    , function(function)
  {}
  
  BinaryCGFunction3D::BinaryCGFunction3D(const std::string& function_name, const std::string& function, Module3D* l, Module3D* r)
    : BinaryCombiner3D(l, r)
    , function_name(function_name)
    , function(function)
  {}
  
  std::string BinaryCGFunction3D::getName() const
  {
    BOOST_ASSERT(lhs());
    BOOST_ASSERT(rhs());
    return boost::str(boost::format("cg_%1%_%2%_%3%") % function_name % lhs()->getName() % rhs()->getName());
  }
  
  std::string BinaryCGFunction3D::generate() const
  {
    BOOST_ASSERT(lhs());
    BOOST_ASSERT(rhs());
    
    return
      boost::str(
        boost::format(
          "float %1%(float3 xyz){ return %2%( %3%(xyz), %4%(xyz) ); }"
               ) % getName() % function % lhs()->getName() % rhs()->getName());
  }
  
} // namespace gpunoise
