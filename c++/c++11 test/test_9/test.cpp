#include <iostream>
#include <vector>
#include <algorithm>

#include "test.h"

#define TEST2

using namespace cpp11test;

using std::cout;
using std::endl;


std::vector<int> nums;
std::vector<int> largenums;
int bound = 10;




void IsLarge(int i) {
    if(i > bound) 
        largenums.push_back(i);
}

class IsLNums {
public:
    IsLNums(int u): bound(u) {}
    void operator() (int i) const {
        if(i > bound)
            largenums.push_back(i);
    }
private:
    int bound;
};

#ifdef TEST2
void GetLargeNums(int bound) {
    IsLNums Isl(bound);
    
    for_each(nums.begin(), nums.end(), Isl);
    for_each(nums.begin(), nums.end(), [=](int i){
        if(i > bound)
            largenums.push_back(i);
    });
}

int main() 
{
    GetLargeNums(bound);
}

#else

int main() 
{
    IsLNums Isl(bound);			
    
    std::for_each(nums.begin(), nums.end(), IsLarge);
    std::for_each(nums.begin(), nums.end(), Isl);
    std::for_each(nums.begin(), nums.end(), [=](int i){
        if(i > bound)
            largenums.push_back(i);
    });
}
#endif



