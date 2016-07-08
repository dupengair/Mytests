
#include "BearCorner.h"
#include "traits.h"
#include "test.h"
#include "gtest/gtest.h"








int main(int argc, char **argv) {

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  
#if 0
    Boy cr;
    BearCorner<Boy, Feed> pc1(cr);
    pc1.entertain();
    Bear pb;
    BearCorner<Bear, Stuff> pc2(pb);
    pc2.entertain();
    BearCorner<Bear, Sleep, MixedUpTraits> pc3(pb);
    pc3.entertain();
#endif
}








