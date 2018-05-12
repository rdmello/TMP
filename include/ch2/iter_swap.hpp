
#include <iostream>
#include <type_traits>

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
        using reference  = T&;           // typedef for consistency
        ForwardIterator(T* t): ref(t) {} // ctor
        T& operator*()                   // deref operator
        {
          // std::cout << "ref is: " << ref << std::endl;
          return *ref;
        }
      };

    /* the above implementation has a problem: if iter_swap0 is given a pointer
     * instead of an iterator type, a compile-time error is generated since the 
     * pointer type does not have a value_type member type
     */

    /* we try to resolve this by introducing a traits class for iterators */
    template <class Iterator> struct iterator_traits;

    template <class ForwardIterator1, class ForwardIterator2>
      void iter_swap1(ForwardIterator1 f1, ForwardIterator2 f2)
      {
        typename iterator_traits<ForwardIterator1>::value_type x = *f1;
        *f1 = *f2;
        *f2 = x;
      }

    /* non-intrusively define an iterator_traits specialization */
    // template<class T>
    //   struct iterator_traits<ForwardIterator<T>>
    //   {
    //     using value_type = typename ForwardIterator<T>::value_type;
    //   };

    /* another iterator_traits specialization for raw pointers */
    template<class T>
      struct iterator_traits<T*>
      {
        using value_type = T;
        using reference  = T&;
      };

    /* a shortcut: using the template definition to auto-connect the value_type
     * in any iterator base types to the value_type in the traits class 
     */
    template <class Iterator>
      struct iterator_traits
      {
        using value_type = typename Iterator::value_type;
        using reference  = typename Iterator::reference;
      };

    // The type-traits class defined above is used like a function, but at 
    // compile-time. We call these things "metafunctions".
    // However, type-traits models the "Blob" pattern where a set of vaguely
    // related types are grouped into a single class, impeding composability.
    //
    // It would be nicer to use separate metafunctions for this instead.
    // Boost-based metafunctions will have a single "foo::type" member type 
    // which is considered to be the "return value" of the metafunction.
    //
    // Additionally, if we want to get the numerical value of a integer constant
    // wrapper, we can use the "foo::type::value" member. Sometimes however, a 
    // "foo::value" member can give you the right numerical value (true for all
    // boost numerical metafunctions).


    /* 2.4 making choices at compile-time
     * iter_swap is slow since it doesn't call std::swap(T, T), which needs two
     * parameters of the same type as input. 
     */

    // add specialization of iter_swap1 which calls std::swap
    template <class ForwardIterator>
      void iter_swap1(ForwardIterator f1, ForwardIterator f2)
      {
        std::swap(*f1, *f2);
      }

    // the problem with the above is that it doesn't work with different types
    // that have the same value::type (and should therefore be std::swap()-able)

    template <bool use_std_swap> struct iter_swap2_impl;   // fwd-define swap's impl

    template <class ForwardIterator1, class ForwardIterator2>
      void iter_swap2(ForwardIterator1 f1, ForwardIterator2 f2)
      {
        using value_type1 = typename iterator_traits<ForwardIterator1>::value_type;
        using value_type2 = typename iterator_traits<ForwardIterator2>::value_type;

        using reference1  = typename iterator_traits<ForwardIterator1>::reference;
        using reference2  = typename iterator_traits<ForwardIterator2>::reference;

        // select impl based on equality of value_types and if reference types are
        // real reference types (rather than proxies)
        bool const use_std_swap = std::is_same<value_type1, value_type2>::value
          && std::is_reference<reference1>::value
          && std::is_reference<reference2>::value;

        // try using a type computation instead??
        // using use_std_swap = std::is_same<value_type1, value_type2>::type;

        // shell out to the impl, use specialization to select the correct one
        iter_swap2_impl<use_std_swap>::do_swap(f1, f2);
      }

    template <>
      struct iter_swap2_impl<false>
      {
        template <class ForwardIterator1, class ForwardIterator2>
          static void do_swap(ForwardIterator1 f1, ForwardIterator2 f2)
          {
            typename iterator_traits<ForwardIterator1>::value_type x = *f1;
            *f1 = *f2;
            *f2 = x;
          }
      };

    template <>
      struct iter_swap2_impl<true>
      {
        template <class ForwardIterator1, class ForwardIterator2>
          static void do_swap(ForwardIterator1 f1, ForwardIterator2 f2)
          {
            std::swap(*f1, *f2);
          }
      };
  }
}

