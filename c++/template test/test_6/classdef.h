#include <iostream>
#include <stddef.h>
#include <cassert>
#include <cstring>
#include <typeinfo>


namespace template_test
{

    using std::cout;
    using std::endl;


    class DefaultPolicy1 {
    public:
        static void doPrint() {
            cout << "this is DefaultPolicy1" << endl;
            }
     };

    class DefaultPolicy2 {
    public:
        static void doPrint() {
            cout << "this is DefaultPolicy2" << endl;
            }
     };
    
    class DefaultPolicy3 {
    public:
        static void doPrint() {
            cout << "this is DefaultPolicy3" << endl;
            }
     };
    
    class DefaultPolicy4 {
    public:
        static void doPrint() {
            cout << "this is DefaultPolicy4" << endl;
            }
     };

    class CustomPolicy {
    public:
        static void doPrint() {
            cout << "this is CustomPolicy" << endl;
            }
     };

    

    class DefaultPolicies {
    public:
        typedef DefaultPolicy1 P1;
        typedef DefaultPolicy2 P2;
        typedef DefaultPolicy3 P3;
        typedef DefaultPolicy4 P4;
    };

    class DefaultPolicyArgs: virtual public DefaultPolicies {};

    template <typename Policy>
    class Policy1_is: virtual public DefaultPolicies {
    public:
        typedef Policy P1;
    };

    template <typename Policy>
    class Policy2_is: virtual public DefaultPolicies {
    public:
        typedef Policy P2;
    };
    
    template <typename Policy>
    class Policy3_is: virtual public DefaultPolicies {
    public:
        typedef Policy P3;
    };
    
    template <typename Policy>
    class Policy4_is: virtual public DefaultPolicies {
    public:
        typedef Policy P4;
    };
    

    template<typename Base, int D>
    class Discriminator: public Base {};

    template<typename Setter1, typename Setter2, typename Setter3, typename Setter4>
    class PolicySelector: public Discriminator<Setter1, 1>,
                                    public Discriminator<Setter2, 2>,
                                    public Discriminator<Setter3, 3>,
                                    public Discriminator<Setter4, 4> {
     };


    template <typename PolicySetter1 = DefaultPolicyArgs,
                      typename PolicySetter2 = DefaultPolicyArgs,
                      typename PolicySetter3 = DefaultPolicyArgs,
                      typename PolicySetter4 = DefaultPolicyArgs>
    class BreadSlicer {
    private:
        typedef PolicySelector<PolicySetter1, PolicySetter2, PolicySetter3, PolicySetter4> Policies;
    public:
        void print(int i) {
            switch (i) {
                case 1:
                    Policies::P1::doPrint();
                    break;
                case 2:
                    Policies::P2::doPrint();
                    break;
                case 3:
                    Policies::P3::doPrint();
                    break;
                case 4:
                    Policies::P4::doPrint();
                    break;
                default:
                    cout << "no such choice(1~4)!" << endl;
                }
            }
    };

    

};
