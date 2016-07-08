#include <iostream>
#include <string.h>
#include "classdef.h"

using namespace std;

void func(std::initializer_list<int> l) { 
            for(auto i=l.begin(); i!=l.end(); ++i) 
                std::cout << (*i) << std::endl;
        
}

