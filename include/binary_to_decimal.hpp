
#include <cstdint>

/*
 * converts a binary number (specified as a uint64_t number with
 * only ones and zeros) to a nonnegative integer
 * Example:
 * binary_to_decimal<11010>::value is replaced by 26
 */
template <uint64_t input>
struct binary_to_decimal
{
  static uint64_t const value = (2 * binary_to_decimal<input / 10>::value) + 
    (input % 10);
};

/* recursion termination condition for binary_to_decimal */
template<>
struct binary_to_decimal<0>
{
  static uint64_t const value = 0;
};


