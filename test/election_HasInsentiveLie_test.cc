#include <vector>

#include "../election.h"
#include "gtest/gtest.h"

TEST(single_choice, value_test){
    std::vector<int> pref = {0, 1, 2, 3};
    ASSERT_EQ(true, HasInsentiveLie(pref, std::vector<int>{3}, std::vector<int>{0}));
    ASSERT_EQ(true, HasInsentiveLie(pref, std::vector<int>{2}, std::vector<int>{0}));
    ASSERT_EQ(true, HasInsentiveLie(pref, std::vector<int>{1}, std::vector<int>{0}));
    ASSERT_EQ(true, HasInsentiveLie(pref, std::vector<int>{3}, std::vector<int>{2}));
    ASSERT_EQ(false, HasInsentiveLie(pref, std::vector<int>{0}, std::vector<int>{3}));
    ASSERT_EQ(false, HasInsentiveLie(pref, std::vector<int>{0}, std::vector<int>{2}));
    ASSERT_EQ(false, HasInsentiveLie(pref, std::vector<int>{0}, std::vector<int>{1}));
    ASSERT_EQ(false, HasInsentiveLie(pref, std::vector<int>{2}, std::vector<int>{3}));
    pref = std::vector<int>{1, 0, 2, 3};
    ASSERT_EQ(true, HasInsentiveLie(pref, std::vector<int>{3}, std::vector<int>{0}));
    ASSERT_EQ(true, HasInsentiveLie(pref, std::vector<int>{2}, std::vector<int>{0}));
    ASSERT_EQ(false, HasInsentiveLie(pref, std::vector<int>{1}, std::vector<int>{0}));
    ASSERT_EQ(false, HasInsentiveLie(pref, std::vector<int>{3}, std::vector<int>{3}));
}

TEST(multi_choices, value_test){
    std::vector<int> pref = {0, 1, 2, 3};
    ASSERT_EQ(true, HasInsentiveLie(pref, std::vector<int>{3}, std::vector<int>{0, 3}));
    ASSERT_EQ(true, HasInsentiveLie(pref, std::vector<int>{2, 0}, std::vector<int>{0}));
    ASSERT_EQ(true, HasInsentiveLie(pref, std::vector<int>{1, 2}, std::vector<int>{0}));
    ASSERT_EQ(true, HasInsentiveLie(pref, std::vector<int>{3, 2, 1}, std::vector<int>{2, 1}));
    ASSERT_EQ(false, HasInsentiveLie(pref, std::vector<int>{1}, std::vector<int>{0, 2}));
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
