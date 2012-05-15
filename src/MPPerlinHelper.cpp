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

#include "MPPerlinHelper.h"

#include <boost/format.hpp>

namespace gpunoise
{

	MPPerlinHelper::MPPerlinHelper()
	{
	}

	std::string MPPerlinHelper::getName() const
	{
		return boost::str(boost::format("MPPerlinHelper"));
	}

	std::string MPPerlinHelper::generate() const
	{
		return 		"float3 fade( float3 _t ) " \
					"{ " \
					"	return _t * _t * _t * (_t * (_t * 6 - 15) + 10); " \
					"} " \
	
					"float permutation(float _x, sampler1D _perm) " \
					"{ " \
					"	return tex1D(_perm, _x / 256.0).x * 256;" \
					"} " \

					"float gradient(float _x, sampler1D _grad, float3 _p) " \
					"{ " \
					"	return dot(2.0 * tex1D(_grad, _x).xyz - 1.0, _p); " \
					"}";
	}


} // namespace gpunoise
