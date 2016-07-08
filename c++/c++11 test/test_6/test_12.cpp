#include <iostream>
#include <string>

#include "test.h"

#include <stdio.h>


using std::cout;
using std::endl;


void func(Size& s, Type& t) {
   // if(s.General >= Type::General) 		//error, ¿‡–Õ≤ª∆•≈‰
   //     cout << "1" << endl;
    if(s.General >= Size::General) 		//ok
        cout << "2" << endl;
}


int main() {


    Size s = Size::General;
    Type t = Type::General;

    func(s, t);
    
       
}
