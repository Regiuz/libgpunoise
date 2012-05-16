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
#ifndef LIBGPUNOISE_MODULE3D_H
#define LIBGPUNOISE_MODULE3D_H

#include <boost/noncopyable.hpp>
#include <string>
#include "Module.h"

namespace gpunoise
{
  
  ///This is a module that represents a function that takes a 3D value, and returns a 1D value.
  class Module3D : public Module
  {
  public:
    virtual std::string getName() const = 0;
    virtual std::string generate() const = 0;
    virtual ~Module3D();
  };

  class Generator3D : public Module3D
  {};

  class Combiner3D : public Module3D
  {};

  class Modifier3D : public Module3D
  {};

  class Selector3D : public Module3D
  {};

  class Transformer3D : public Module3D
  {};

  //FIXME: move this to own file
  struct UnaryModifier3D : Modifier3D
  {
    UnaryModifier3D();
    UnaryModifier3D(Module3D* s);
    
    Module3D* source() const;
    void source(Module3D* s) const;
  private:
    Module3D* msource;
  };
  
  //FIXME: move this to own file
  struct UnaryCGFunction3D : UnaryModifier3D
  {
    UnaryCGFunction3D(const std::string& name, const std::string& function);
    UnaryCGFunction3D(const std::string& name, const std::string& function, Module3D* s);
    
  private:
    const std::string name;
    const std::string function;
  };
  
} // namespace gpunoise

#endif // LIBGPUNOISE_MODULE3D_H
