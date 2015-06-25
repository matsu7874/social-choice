#include <vector>

#include "../election.h"
#include "gtest/gtest.h"

TEST(one_voter, value_test){
    std::vector<std::vector<int>> preferences = {{0, 1, 2, 3}};
    std::vector<std::vector<int>> cross = {{1, 1, 1, 1}, {0, 1, 1, 1}, {0, 0, 1, 1}, {0, 0, 0, 1}};
    ASSERT_EQ(cross, PairwiseComparison(preferences));
}
TEST(same_preferences, value_test){
    std::vector<std::vector<int>> preferences = {{0, 1, 2, 3}, {0, 1, 2, 3}, {0, 1, 2, 3}};
    std::vector<std::vector<int>> cross = {{3, 3, 3, 3}, {0, 3, 3, 3}, {0, 0, 3, 3}, {0, 0, 0, 3}};
    ASSERT_EQ(cross, PairwiseComparison(preferences));
}
TEST(different_preferences, value_test){
    std::vector<std::vector<int>> preferences = {{0, 1, 2, 3}, {1, 3, 2, 0}, {3, 1, 2, 0}};
    std::vector<std::vector<int>> cross = {{3, 1, 1, 1}, {2, 3, 3, 2}, {2, 0, 3, 1}, {2, 1, 2, 3}};
    ASSERT_EQ(cross, PairwiseComparison(preferences));
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
