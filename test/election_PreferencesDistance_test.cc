#include <vector>

#include "../election.h"
#include "gtest/gtest.h"

TEST(same_preferences, value_test){
    ASSERT_EQ(0, PreferencesDistance(std::vector<std::vector<int>>{{1, 2, 3, 0}, {1, 2, 3, 0}}));
    ASSERT_EQ(0, PreferencesDistance(std::vector<std::vector<int>>{{1, 0}, {1, 0}, {1, 0}, {1, 0}}));
    ASSERT_EQ(0, PreferencesDistance(std::vector<std::vector<int>>{{1, 2, 3, 0, 5, 4}, {1, 2, 3, 0, 5, 4}}));
}

TEST(different_preferences, value_test){
    ASSERT_EQ(1, PreferencesDistance(std::vector<std::vector<int>>{{2, 1, 3, 0, 5, 4}, {1, 2, 3, 0, 5, 4}}));
    ASSERT_EQ(4, PreferencesDistance(std::vector<std::vector<int>>{{2, 1, 3, 0}, {1, 2, 3, 0}, {1, 2, 0, 3}}));
    ASSERT_EQ(15, PreferencesDistance(std::vector<std::vector<int>>{{0, 1, 2, 3, 4, 5}, {5, 4, 3, 2, 1, 0}}));
}

TEST(root_preference, value_test){
    ASSERT_EQ(1, PreferencesDistance(std::vector<std::vector<int>>{{1, 2, 3, 0, 5, 4}}, std::vector<int>{2, 1, 3, 0, 5, 4}));
    ASSERT_EQ(5, PreferencesDistance(std::vector<std::vector<int>>{{1, 2, 3, 0}, {0, 1, 2, 3}}, std::vector<int>{2, 1, 3, 0}));
}


int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
