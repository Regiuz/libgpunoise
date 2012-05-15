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


#ifndef LIBGPUNOISE_ADD3D_H
#define LIBGPUNOISE_ADD3D_H

#include "Module3D.h"

namespace gpunoise
{	  
	class Add3D : Combiner3D
	{
	public:
		Add3D();
		Add3D(Module3D* l, Module3D* r);

		Module3D* lhs() const;
		Module3D* rhs() const;
		void lhs(Module3D* l);
		void rhs(Module3D* r);

		virtual std::string generate() const;
		virtual std::string getName() const;
	  
	private:
		Module3D* mlhs;
		Module3D* mrhs;
	};

} // namespace gpunoise

#endif // LIBGPUNOISE_ADD3D_H