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

#include "gpunoise/Module3D.h"

#include <boost/format.hpp>
#include <boost/assert.hpp>

namespace gpunoise
{

Module3D::~Module3D()
{
  
}

UnaryModifier3D::UnaryModifier3D()
  : msource(NULL)
{}

UnaryModifier3D::UnaryModifier3D(Module3D* s)
  : msource(s)
{}

Module3D* UnaryModifier3D::source() const
{
  return msource;
}

void UnaryModifier3D::source(Module3D* s)
{
  msource = s;
}




UnaryCGFunction3D::UnaryCGFunction3D(const std::string& name, const std::string& function)
  : UnaryModifier3D()
  , name(name)
  , function(function)
{}

UnaryCGFunction3D::UnaryCGFunction3D(const std::string& name, const std::string& function, Module3D* s)
  : UnaryModifier3D(s)
  , name(name)
  , function(function)
{}

std::string UnaryCGFunction3D::getName() const
{
  BOOST_ASSERT(source());
  return
    boost::str(
      boost::format("%1%_%2%") % name % source()->getName());
}


std::string UnaryCGFunction3D::generate() const
{
  BOOST_ASSERT(source());
  
  return
    boost::str(
      boost::format(
        "inline float %1%(float3 xyz)\n"
        "{\n"
        "  return %2%(%3%(xyz));\n"
        "}\n") % getName() % function % source()->getName());
}


} // namespace gpunoise
