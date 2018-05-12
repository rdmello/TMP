
#include <cstdint>

/*
 * converts a nonnegative integral number (specified as a uint64_t)
 *  to its nonnegative binary representation
 *
 * Example:
 * decimal_to_binary<26>::value is replaced by 11010
 */
template <uint64_t input>
struct decimal_to_binary
{
  static uint64_t const value = (10 * decimal_to_binary<input / 2>::value) + 
    (input % 2);
};

/* recursion termination condition for binary_to_decimal */
template<>
struct decimal_to_binary<0>
{
  static uint64_t const value = 0;
};


