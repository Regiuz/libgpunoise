/*
Copyright (c) 2012 <copyright holder> <email>

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/


#include "gpunoise/Clamp3D.h"

#include <boost/format.hpp>
#include <boost/assert.hpp>
#include <gpunoise/encode.h>


namespace gpunoise
{

  Clamp3D::Clamp3D()
    : UnaryModifier3D()
    , lower_bound(-1)
    , upper_bound(1)
  {

  }

  Clamp3D::Clamp3D(Module3D* s, real_t lower_bound, real_t upper_bound)
    : UnaryModifier3D(s)
    , lower_bound(lower_bound)
    , upper_bound(upper_bound)
  {

  }


  real_t Clamp3D::GetLowerBound() const
  {
    return lower_bound;
  }
  
  real_t Clamp3D::GetUpperBound() const
  {
    return upper_bound;
  }
  
  void Clamp3D::SetBounds(real_t lowerBound, real_t upperBound)
  {
    lower_bound = lowerBound;
    upper_bound = upperBound;
  }
  
  std::string Clamp3D::getName() const
  {
    BOOST_ASSERT(source());
    return
      boost::str(
        boost::format(
          "Clamp3D_l%1%_u%2%__%3%") % encode_as_integer(lower_bound) % encode_as_integer(upper_bound) % source()->getName());
  }
  
  
  std::string Clamp3D::generate() const
  {
    BOOST_ASSERT(source());
    
    return
      boost::str(
        boost::format(
          "float %1%(float3 xyz)\n"
          "{\n"
          "  return clamp(%2%(xyz), %3%, %4%);\n"
          "}\n") % getName() % source()->getName() % lower_bound % upper_bound);
  }

} // namespace gpunoise

