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

#include "gpunoise/encode.h"

#include <sstream>
#include <boost/algorithm/string/replace.hpp>
#include <boost/integer.hpp>

namespace gpunoise
{
  
  std::string encode_as_integer(real_t v)
  {
    std::ostringstream os;
    
    typedef boost::uint_t<sizeof(real_t) * 8>::exact integer_t;
    
    BOOST_STATIC_ASSERT(sizeof(integer_t) == sizeof(real_t));
    
    os << *reinterpret_cast<integer_t*>(&v);
    
    return os.str();
  }
  
} // namespace gpunoise
