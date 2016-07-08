#pragma once

#include <iostream>

using std::cout;
using std::endl;

namespace template_test
{

    class DefaultPolicy1 {
        public:
            static void print(void) {
                cout << "DefaultPolicy1" << endl;
            }
    };

    class DefaultPolicy2 {
        public:
            static void print(void) {
                cout << "DefaultPolicy2" << endl;
            }
    };

    class DefaultPolicy3 {
        public:
            static void print(void) {
                cout << "DefaultPolicy3" << endl;
            }
    };


    class DefaultPolicy4 {
        public:
            static void print(void) {
                cout << "DefaultPolicy4" << endl;
            }
    };

    
    class DefaultPolicies {
        public:
            typedef DefaultPolicy1 P1;
            typedef DefaultPolicy2 P2;
            typedef DefaultPolicy3 P3;
            typedef DefaultPolicy4 P4;
    };

    class DefaultPolicyArgs: virtual public DefaultPolicies {
    };

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


    template <typename Base, int D>
    class Discriminator : public Base {
    };

    template <typename Setter1, typename Setter2, typename Setter3,  typename Setter4>
    class PolicySelector: public Discriminator<Setter1, 1>,  
                                    public Discriminator<Setter2, 2>,  
                                    public Discriminator<Setter3, 3>,  
                                    public Discriminator<Setter4, 4> {
    };
                                            










};
