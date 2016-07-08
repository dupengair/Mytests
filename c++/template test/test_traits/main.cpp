#include <iostream>

#include "BearCorner.h"
#include "traits.h"

using namespace std;







int main() {
    Boy cr;
    BearCorner<Boy, Feed> pc1(cr);
    pc1.entertain();
    Bear pb;
    BearCorner<Bear, Stuff> pc2(pb);
    pc2.entertain();
    BearCorner<Bear, Sleep, MixedUpTraits> pc3(pb);
    pc3.entertain();
}








