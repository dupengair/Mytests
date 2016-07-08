#pragma once

#include <iostream>

using std::cout;
using std::endl;

namespace template_test
{


    template <typename Base, typename Member>
    class BaseMemberPair: private Base {
    private:
        Member member;
    public:
        BaseMemberPair(const Base& b, const Member& m): Base(b), member(m) {}
        
        const Base& first() const { return (const Base&)*this; }
        Base& first() { return (Base&)*this; }
        
        const Member& second() const { return this->member; }
        Member& second() { return this->member; }
    };

    template <typename CustomClass>
    class Optimizable {
    private:
        BaseMemberPair<CustomClass, int> custom_and_count;
    };



    template <typename CustomClass>
    class NoOptimizable {
    private:
        CustomClass a;
        int b;
    };





};
