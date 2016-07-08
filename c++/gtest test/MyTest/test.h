#ifndef TEST_H
#define TEST_H


#include "traits.h"
#include "gtest/gtest.h"


template <typename T>
class ToBeTested {
public:
    ToBeTested(): t(t) { cout << "ctor : ToBeTested" << endl; }
    ~ToBeTested() { cout << "dtor : ToBeTested" << endl; }
    //void setVal(T tt) {  t = tt;  return 0; } 
    int getVal() {  cout << "the type : " << typeid(t).name() << endl;  return 0; } 

private:
    T t;
    
};

template <typename T>
ToBeTested<T>* CreateToBeTested() {
    return new ToBeTested<T>();    
}


template <class T>
class MyTest:public testing::Test {    
protected:        
    MyTest(): tbtd(CreateToBeTested<T>()) {}        
    virtual ~MyTest(){delete tbtd;}        
    ToBeTested<T>* const tbtd;
};

TYPED_TEST_CASE_P(MyTest);


TYPED_TEST_P(MyTest, TestType) {   
    
    EXPECT_EQ(0u, this->tbtd->getVal());
}



REGISTER_TYPED_TEST_CASE_P(MyTest, TestType);

using testing::Types;// The list of types we want to test.
typedef Types<int, char> Implementations;
INSTANTIATE_TYPED_TEST_CASE_P(TestTypes_INT_CHAR, MyTest, Implementations);



#endif
