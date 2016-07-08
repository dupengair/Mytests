#include <iostream>
#include <string.h>
#include "classdef.h"

using namespace std;

Enum::Enum()
{
    cout << " Enum class constructed" << endl;
}


Enum::~Enum()
{
    cout << " Enum class destructed" << endl;
}




ChildrenEnum::ChildrenEnum()
{
    cout << " ChildrenEnum class constructed" << endl;
}

ChildrenEnum::~ChildrenEnum()
{
    cout << " ChildrenEnum class destructed" << endl;
}



void ChildrenEnum::testbm(void)
{
      cout << "in ChildrenEnum class :" << __func__ << endl;
}

int ChildrenEnum::Enum(int i)
{
      cout << "in ChildrenEnum class : " << __func__ <<"(" << i << ")" << endl;
      return i;
}

TreeEnum::TreeEnum()
{
    cout << " TreeEnum class constructed" << endl;
}

TreeEnum::~TreeEnum()
{
    cout << " TreeEnum class destructed" << endl;
}



void TreeEnum::testbm(void)
{
      cout << "in TreeEnum class :" << __func__ << endl;
}

int TreeEnum::Enum(int i)
{
      cout << "in TreeEnum class : i" << __func__ <<"(" << i << ")" << endl;
      return i;
}


