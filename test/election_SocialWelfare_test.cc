#include <vector>

#include "../election.h"
#include "gtest/gtest.h"

TEST(same_preferences, value_test){
    std::vector<std::vector<int>> preferences = {{0, 1, 2, 3}, {0, 1, 2, 3}, {0, 1, 2, 3}};
    ASSERT_DOUBLE_EQ(0.0, SocialWelfare(preferences, std::vector<int>{0}));
    ASSERT_DOUBLE_EQ(-3.0, SocialWelfare(preferences, std::vector<int>{1}));
    ASSERT_DOUBLE_EQ(-3.0, SocialWelfare(preferences, std::vector<int>{0, 2}));
}

TEST(deferent_preferences, value_test){
    std::vector<std::vector<int>> preferences = {{0, 1, 2, 3}, {1, 2, 3, 0}, {0, 3, 2, 1}};
    ASSERT_DOUBLE_EQ(-3.0, SocialWelfare(preferences, std::vector<int>{0}));
    ASSERT_DOUBLE_EQ(-4.0, SocialWelfare(preferences, std::vector<int>{1}));
    ASSERT_DOUBLE_EQ(-4.0, SocialWelfare(preferences, std::vector<int>{0, 2}));
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
