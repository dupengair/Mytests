#include <iostream>

using std::cout;
using std::endl;

namespace template_test
{

    template <typename T>
    class AccumuationTraits;    

    template <>
    class AccumuationTraits<char> {
    public:
        typedef int AccT;   
        //static AccT const zero = 0;
        static AccT zero() {
            return 0;
        }
    };

    template <>
    class AccumuationTraits<short> {
    public:
        typedef int AccT;     
        //static AccT const zero = 0;
        static AccT zero() {
            return 0;
        }
    };

    template <>
    class AccumuationTraits<int> {
    public:
        typedef long AccT;     
        //static AccT const zero = 0;
        static AccT zero() {
            return 0;
        }
    };

    template <>
    class AccumuationTraits<unsigned int> {
    public:
        typedef unsigned long AccT;     
        //static AccT const zero = 0;
        static AccT zero() {
            return 0;
        }
    };

    template <>
    class AccumuationTraits<float> {
    public:
        typedef double AccT;
        //static AccT const zero = 0;
        static AccT zero() {
            return 0.0;
        }
    };

    template<typename T1, typename T2>
    class SumPolicy {
    public:        
        static void accumulate (T1& total, T2 const& value) {
            total += value;
        }
    };

    template<typename T1, typename T2>
    class MultiPolicy {
    public:
        static void accumulate (T1& total, T2 const& value) {
            total *= value;
        }
    };


    template <typename T, 
                      template<typename, typename> class Policy = SumPolicy,
                      typename Traits = AccumuationTraits<T> >
    class Accum {
    public:
        static typename Traits::AccT accum(T const* beg, T const* end) {
            typename Traits::AccT total = Traits::zero();
            while (beg != end) {
                Policy<typename Traits::AccT, T>::accumulate(total, *beg);
                ++beg;
            }

            return total;
        }    
    };

    /*
    template <typename T>
    typename AccumuationTraits<T>::AccT accum (T const* beg, T const* end)
    {       
        return Accum<T>::accum(beg, end);
    }

    template <typename T, template<typename, typename> class Policy>
    typename AccumuationTraits<T>::AccT accum (T const* beg, T const* end)
    {       
        return Accum<T, Policy<typename AccumuationTraits<T>::AccT, T> >::accum(beg, end);
    }

    template <typename T, template<typename, typename> class Policy, typename Traits>
    typename Traits::AccT accum (T const* beg, T const* end)
    {       
        return Accum<T, Policy<typename AccumuationTraits<T>::AccT, T>, Traits>::accum(beg, end);
    }
    */

    

};
