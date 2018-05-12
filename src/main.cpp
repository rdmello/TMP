
#include <iostream>

#include "binary_to_decimal.hpp"
#include "decimal_to_binary.hpp"


int main(int argc, char** argv)
{
  std::cout << "Hello!" << std::endl;

  /* test binary_to_decimal */
  const uint64_t input = 11010;
  const uint64_t output = 26;
  static_assert(output == binary_to_decimal<input>::value, "binary_to_decimal");
  std::cout << "Convert " << input << " to decimal: " 
    << binary_to_decimal<input>::value << std::endl;

  /* test decimal_to_binary */
  static_assert(input == decimal_to_binary<output>::value, "decimal_to_binary");
  std::cout << "Convert " << output << " to binary: " 
    << decimal_to_binary<output>::value << std::endl;
  

  return 0;
}
  
