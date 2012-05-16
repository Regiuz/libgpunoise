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
#ifndef LIBGPUNOISE_CLAMP3D_H
#define LIBGPUNOISE_CLAMP3D_H

#include "Module3D.h"
#include "types.h"

namespace gpunoise
{         
  class Clamp3D : public UnaryModifier3D
  {
  public:
    Clamp3D();
    Clamp3D(Module3D* s, real_t lower_bound = -1, real_t upper_bound = 1);
    
    virtual std::string generate() const;
    virtual std::string getName() const;
    
    real_t GetLowerBound() const;
    real_t GetUpperBound() const;
    void SetBounds (real_t lowerBound, real_t upperBound);

  private:
    real_t lower_bound;
    real_t upper_bound;
  };

} // namespace gpunoise

#endif // LIBGPUNOISE_CLAMP3D_H
