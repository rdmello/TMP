
#include <iostream>

#include "ch1/binary_to_decimal.hpp"
#include "ch1/decimal_to_binary.hpp"


int main(int argc, char** argv)
{
  std::cout << "Hello!" << std::endl;

  /*
   * ch1: Introduction
   *
   * This is mainly a quick introduction to the template metaprogramming facilities
   * in C++. We go through some compile-time decimal to binary conversion functions 
   * which are also implemented and tested below.
   *
   */

  /* test binary_to_decimal */
  const uint64_t input = 11010;
  const uint64_t output = 26;
  static_assert(output == rd::ch1::binary_to_decimal<input>::value, "binary_to_decimal");
  std::cout << "Convert " << input << " to decimal: " 
    << rd::ch1::binary_to_decimal<input>::value << std::endl;

  /* test decimal_to_binary */
  static_assert(input == rd::ch1::decimal_to_binary<output>::value, "decimal_to_binary");
  std::cout << "Convert " << output << " to binary: " 
    << rd::ch1::decimal_to_binary<output>::value << std::endl;

  /*
   * ch2: Traits and Type Manipulation
   *
   * Start with type-based computation using metafunctions and metadata. We implement
   * several iterations of an iter_swap function which swaps std container iterators.
   * Finally the chapter ends with an overview of the type traits faciltites in boost::mpl
   *
   */

  /* test iter_swap */

  return 0;
}
  
