#ifndef __CLASS_H__
#define __CLASS_H__


#include <iostream>


using std::cout;
using std::endl;

namespace template_test
{

     template <typename T>
     class MyChar {   
     T t;
     public:
        MyChar(T a);
        void get(void);
     };


};

#endif
