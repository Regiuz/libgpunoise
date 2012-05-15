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


#include "Add3D.h"

#include <boost/assert.hpp>
#include <boost/format.hpp>

namespace gpunoise
{

	Add3D::Add3D()
		: mlhs(NULL)
		, mrhs(NULL)
	{

	}

	Add3D::Add3D(gpunoise::Module3D* l, gpunoise::Module3D* r)
		: mlhs(l)
		, mrhs(r)
	{

	}

	Module3D* Add3D::lhs() const
	{
		return mlhs;
	}

	Module3D* Add3D::rhs() const
	{
		return mrhs;
	}

	void Add3D::lhs(Module3D* l)
	{
		mlhs = l;
	}

	void Add3D::rhs(Module3D* r)
	{
		mrhs = r;
	}

	std::string Add3D::getName() const
	{
		BOOST_ASSERT(!!mlhs);
		BOOST_ASSERT(!!mrhs);
		return boost::str(boost::format("_%1%_Add3D_%2%_") % mlhs->getName() % mrhs->getName());
	}


	std::string Add3D::generate() const
	{
		BOOST_ASSERT(!!mlhs);
		BOOST_ASSERT(!!mrhs);

		return boost::str(
			boost::format(
				"float %1%(float3 xyz){ return %2%(xyz) + %3%(xyz); }"
				) % getName() % mlhs->getName() % mrhs->getName());
	}


} // namespace gpunoise

