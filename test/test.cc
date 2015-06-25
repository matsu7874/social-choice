#include <vector>
#include "../election.h"
#include "gtest/gtest.h"

TEST(prefTest,coordinate){
    std::vector<int> pref = {0,2,5,7,6,3,1};
    ASSERT_EQ(true, IsSinglePeakedness(pref));
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
