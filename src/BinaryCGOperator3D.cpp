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


#include "gpunoise/BinaryCGOperator3D.h"

#include <boost/assert.hpp>
#include <boost/format.hpp>

namespace gpunoise
{

  BinaryCGOperator3D::BinaryCGOperator3D(const std::string& name, const std::string& op)
    : BinaryCombiner3D()
    , name(name)
    , op(op)
  {

  }

  BinaryCGOperator3D::BinaryCGOperator3D(const std::string& name, const std::string& op, gpunoise::Module3D* l, gpunoise::Module3D* r)
    : BinaryCombiner3D(l,r)
    , name(name)
    , op(op)
  {

  }

  std::string BinaryCGOperator3D::getName() const
  {
    BOOST_ASSERT(!!lhs());
    BOOST_ASSERT(!!rhs());
    return boost::str(boost::format("_%2%_cg_op_%1%_%3%_") % name % lhs()->getName() % rhs()->getName());
  }


  std::string BinaryCGOperator3D::generate() const
  {
      BOOST_ASSERT(!!lhs());
      BOOST_ASSERT(!!rhs());

      return boost::str(
              boost::format(
                "float %1%(float3 xyz){ return %2%(xyz) %3% %4%(xyz); }"
                ) % getName() % lhs()->getName() % op % rhs()->getName());
  }


} // namespace gpunoise

