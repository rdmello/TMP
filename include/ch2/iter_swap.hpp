
#include <iostream>

namespace rd
{
  namespace ch2
  {
    /* 
     * Imagine that we are implementing the std library. A std::iter_swap
     * needs to be added to <algorithm>.
     *
     * see: http://en.cppreference.com/w/cpp/algorithm/iter_swap
     */

    /* we start with a naive implementation */
    template <class ForwardIterator1, class ForwardIterator2>
      void iter_swap0(ForwardIterator1 i1, ForwardIterator2 i2)
      {
        typename ForwardIterator1::value_type x = *i1;
        *i1 = *i2;
        *i2 = x;
      }

    // here's a ForwardIterator type which can be used with the above fcn
    // I'm going to make a weird kind of iterator which owns the T
    template <class T> 
      class ForwardIterator
      {
        T* ref;

        public:
        using value_type = T;            // typedef for consistency
        ForwardIterator(T* t): ref(t) {} // ctor
        T& operator*()                   // deref operator
        {
          // std::cout << "ref is: " << ref << std::endl;
          return *ref;
        }
      };

    /* the above implementation has a problem:  */





  }
}

