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

#include "MPPerlin3D.h"

#include <boost/format.hpp>

namespace gpunoise
{

	MPPerlin3D::MPPerlin3D()
	{
	}

	std::string MPPerlin3D::getName() const
	{
		return boost::str(boost::format("MPPerlin3D"));
	}

	std::string MPPerlin3D::generate() const
	{
		return boost::str(
			boost::format(
					"float %1%(float3 _p, uniform sampler1D _perm, uniform sampler1D _grad) { " \
					"float3 Pos = fmod(floor( _p ), 256.0 ); " \
					"_p -= floor( _p ); " \
					"float3 f = fade( _p ); " \
	       
					"float A = permutation(Pos.x, _perm) + Pos.y; " \
					"float AA = permutation(A, _perm) + Pos.z; " \
					"float AB = permutation(A + 1, _perm) + Pos.z; " \
					"float B = permutation(Pos.x + 1, _perm) + Pos.y; " \
					"float BA = permutation(B, _perm) + Pos.z; " \
					"float BB = permutation(B + 1, _perm) + Pos.z; " \
	       
					"return lerp( " \
						"lerp( lerp( gradient( permutation(AA, _perm), _grad, _p), " \
											"gradient( permutation(BA, _permp), _grad, _p + float3(-1, 0, 0)), f.x), " \
						  "lerp( gradient( permutation(AB, _perm), _grad, _p + float3( 0,-1, 0)), " \
											"gradient( permutation(BB, _perm), _grad, _p + float3(-1,-1, 0)), f.x), f.y), " \
					"lerp( lerp( gradient( permutation(AA + 1, _perm), _grad, _p + float3( 0, 0,-1)), " \
											"gradient( permutation(BA + 1, _perm), _grad, _p + float3(-1, 0,-1)), f.x), " \
							  "lerp( gradient( permutation(AB + 1, _perm), _grad, _p + float3( 0,-1,-1)), " \
											"gradient( permutation(BB + 1, _perm), _grad, _p + float3(-1,-1,-1)), f.x), f.y), " \
					"f.z).x;" \
					"}") % getName());
	}


} // namespace gpunoise
