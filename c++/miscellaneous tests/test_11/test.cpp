#include <iostream>
#include "classdef.h"

using namespace sio_test;


int main(void)
{
    ExecutionContext sio_test_context;
    TCPListenSocket Obj1(sio_test_context);
    
    Obj1.Listen();
    sio_test_context.Run();
    
    Obj1.Connect();
    sio_test_context.Run();

    sio_test_context.TestFriend();


    std::cout << "1 : " << (sizeof(void *) != sizeof(int)) << std::endl;
    std::cout << "2 : " << (sizeof(void *))  << std::endl;
    std::cout << "3 : " << (sizeof(int)) << std::endl;  
    
    return 0;
}
