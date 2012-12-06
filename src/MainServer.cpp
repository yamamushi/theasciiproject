/*

  The ASCII Project - Server

  0.0.1f - December 5th, 2012 

  http://www.theasciiproject.com
  Jonathan Rumion - yamamushi@gmail.com

 */

#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

int main()
{
    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    std::for_each(
        in(std::cin), in(), std::cout << (_1 * 3) << " " );
}
