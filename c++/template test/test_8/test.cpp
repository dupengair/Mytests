#include <iostream>
#include <vector>

#include "classdef.h"

using namespace template_test;

void test1();
void test2();

int main()
{
    test1();
    test2();
}

void test1()
{
    std::cout << "\ntest1():\n";
    CountingPtr<int> p0;
    { 
       CountingPtr<int> p1(new int(42));
       std::cout << "*p1: " << *p1 << std::endl;

       *p1 = 17;
       std::cout << "*p1: " << *p1 << std::endl;

       CountingPtr<int> p2 = p1;
       std::cout << "*p2: " << *p2 << std::endl;

       *p1 = 33;
       std::cout << "*p2: " << *p2 << std::endl;

       p0 = p2;
       std::cout << "*p0: " << *p0 << std::endl;

       ++*p0;
       ++*p1;
       ++*p2;
       std::cout << "*p0: " << *p0 << std::endl;
       std::cout << "*p1: " << *p1 << std::endl;
       std::cout << "*p2: " << *p2 << std::endl;
    }
    std::cout << "after block: *p0: " << *p0 << std::endl;
}

void test2()
{
    std::cout << "\ntest2():\n";
    { CountingPtr<int> p0(new int(42));
       CountingPtr<int> p2 = p0;
    }
    CountingPtr<int> p1(new int(42));
    
    std::cout << "qqq" << std::endl;

    std::vector<CountingPtr<int> > coll;
    std::cout << "qqq" << std::endl;
    coll.push_back(p1);
    std::cout << "qqq" << std::endl;
    coll.push_back(p1);
    std::cout << "qqq" << std::endl;

    std::cout << "qqq" << std::endl;

    ++*p1;
    ++*coll[0];
    std::cout << *coll[1] << std::endl;
}

