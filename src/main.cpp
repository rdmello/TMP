
#include <iostream>
#include <cstdint>

#include "ch1/binary_to_decimal.hpp"
#include "ch1/decimal_to_binary.hpp"

#include "ch2/iter_swap.hpp"


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
  std::cout << std::endl;
  std::cout << "    ==== Chapter1 ====    " << std::endl;

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
   *    "We can solve any problem by introducing an extra level of indirection"
   *
   *                                                                  - Butler Lampson
   *
   */
  std::cout << std::endl;
  std::cout << "    ==== Chapter2 ====    " << std::endl;

  /* test iter_swap version 0 */
  // uint64_t *i1 = new uint64_t{32}, *i2 = new uint64_t{45};
  uint64_t i1 = 32, i2 = 45;
  rd::ch2::ForwardIterator<uint64_t> f1(&i1);  // construct ForwardIterator
  rd::ch2::ForwardIterator<uint64_t> f2(&i2);  // construct ForwardIterator
  assert(i1 == *f1);               // verify correct deref behavior
  assert(i2 == *f2);               // verify correct deref behavior

  rd::ch2::iter_swap0(f1, f2);
  assert(i1 == 45);                // verify value swapped
  assert(i2 == 32);                // verify value swapped
  assert(i1 == *f1);               // verify correct deref behavior after swap
  assert(i2 == *f2);               // verify correct deref behavior after swap
  std::cout << "uint64_t values swapped succesfully" << std::endl;

  // try swapping a pointer with an iterator
  uint64_t* p1 = &i1;
  // rd::ch2::iter_swap0(p1, f2);     // Compile-time error, no member value_type
  
  rd::ch2::iter_swap1(p1, f2);
  assert(i1 == 32);                // verify value swapped
  assert(i2 == 45);                // verify value swapped
  assert(i1 == *f1);               // verify correct deref behavior after swap
  assert(i2 == *f2);               // verify correct deref behavior after swap
  std::cout << "uint64_t values swapped succesfully (again)" << std::endl;

  rd::ch2::iter_swap0(f1, f2);
  assert(i1 == 45);                // verify value swapped
  assert(i2 == 32);                // verify value swapped
  assert(i1 == *f1);               // verify correct deref behavior after swap
  assert(i2 == *f2);               // verify correct deref behavior after swap
  std::cout << "uint64_t values swapped succesfully (yet again)" << std::endl;




  return 0;
}
  
