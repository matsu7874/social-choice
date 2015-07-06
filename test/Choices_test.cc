#include <vector>

#include "../voter.h"
#include "gtest/gtest.h"

TEST(init_with_int, value_test){
    Voter voter(3);
    std::vector<int> utilities = {0,0,0};
    ASSERT_EQ(voter.utilities(), utilities);
}
TEST(init_with_vector, value_test){
    Voter voter(std::vector<int>{1,2,3});
    std::vector<int> utilities = {1,2,3};
    ASSERT_EQ(voter.utilities(), utilities);
}

TEST(utility_of, value_test){
    Voter voter(std::vector<int>{10,3,1,8,4});
    ASSERT_DOUBLE_EQ(10, voter.UtilityOf(std::vector<int>{0}));
    ASSERT_DOUBLE_EQ(6.5, voter.UtilityOf(std::vector<int>{0,1}));
    ASSERT_DOUBLE_EQ(9, voter.UtilityOf(std::vector<int>{0,3}));
    ASSERT_DOUBLE_EQ(5.2, voter.UtilityOf(std::vector<int>{0,1,2,3,4}));
}

TEST(update_utilities, value_test){
    Voter voter(3);
    std::vector<int> utilities = {1,2,3};
    ASSERT_NE(voter.utilities(), utilities);
    voter.UpdateUtilities(utilities);
    ASSERT_EQ(voter.utilities(), utilities);
}


TEST(has_insentive_lie, value_test){
    Voter voter(std::vector<int>{10,3,1,8,4});
    ASSERT_EQ(true, voter.HasInsentiveLie(std::vector<int>{1},std::vector<int>{0}));
    ASSERT_EQ(true, voter.HasInsentiveLie(std::vector<int>{2,4},std::vector<int>{0}));
    ASSERT_EQ(false, voter.HasInsentiveLie(std::vector<int>{0},std::vector<int>{3,1}));
}

TEST(preference, value_test){
    Voter voter(std::vector<int>{10,3,1,8,4});
    std::vector<int> order = {0,3,4,1,2};
    ASSERT_EQ(order, voter.Preference());
    voter.UpdateUtilities(std::vector<int>{4,3,3,4,4});
    order = std::vector<int>{0,3,4,1,2};
    ASSERT_EQ(order, voter.Preference());
}

TEST(difference, value_test){
    std::vector<Voter> voters;
    voters.push_back(Voter(std::vector<int>{10,3,1,8,4}));
    voters.push_back(Voter(std::vector<int>{0,3,11,8,4}));
    ASSERT_EQ(7, voters[0].PreferencesDifference(voters[1].utilities()));
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
