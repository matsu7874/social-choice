#include <vector>

#include "../election.h"
#include "gtest/gtest.h"

TEST(one_voter, value_test){
    std::vector<std::vector<int>> preferences = {{0, 1, 2, 3}};
    std::vector<int> choices = {0};
    ASSERT_EQ(choices, PureCondorcetChoice(preferences));
}

TEST(same_preferences, value_test){
    std::vector<std::vector<int>> preferences = {{1, 2, 3, 0}, {1, 2, 3, 0}, {1, 2, 3, 0}};
    std::vector<int> choices = {1};
    ASSERT_EQ(choices, PureCondorcetChoice(preferences));
}

TEST(different_preferences, value_test){
    std::vector<std::vector<int>> preferences = {{0, 1, 2, 3}, {3, 1, 2, 0}, {2, 3, 0, 1}};
    std::vector<int> choices = {2, 3};
    ASSERT_EQ(choices, PureCondorcetChoice(preferences));
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
