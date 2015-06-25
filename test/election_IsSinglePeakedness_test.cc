#include <vector>

#include "../election.h"
#include "gtest/gtest.h"

TEST(single_peaked, value_test){
    ASSERT_EQ(true, IsSinglePeakedness(std::vector<int>{0, 1, 2, 3}));
    ASSERT_EQ(true, IsSinglePeakedness(std::vector<int>{0, 2, 3, 4, 1}));
    ASSERT_EQ(true, IsSinglePeakedness(std::vector<int>{1, 4, 0}));
    ASSERT_EQ(true, IsSinglePeakedness(std::vector<int>{5, 4, 3, 2, 1, 0}));
}

TEST(multi_peaked, value_test){
    ASSERT_EQ(false, IsSinglePeakedness(std::vector<int>{1, 0, 2}));
    ASSERT_EQ(false, IsSinglePeakedness(std::vector<int>{0, 3, 1, 4, 2}));
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
