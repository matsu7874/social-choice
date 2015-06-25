#include <vector>
#include <string>

#include "../util.h"
#include "gtest/gtest.h"

TEST(void_case, vecvec2str_test){
    std::vector<std::vector<int>> vecvec = {{}};
    ASSERT_EQ("[[]]", VecVec2Str(vecvec));
}

TEST(single_case,vecvec2str_test){
    ASSERT_EQ("[[]]", VecVec2Str(std::vector<std::vector<int>>{{}}));
    ASSERT_EQ("[[1]]", VecVec2Str(std::vector<std::vector<int>>{{1}}));
    ASSERT_EQ("[[-11]]", VecVec2Str(std::vector<std::vector<int>>{{-11}}));
}

TEST(multi_case,vecvec2str_test){
    ASSERT_EQ("[[1], [1]]", VecVec2Str(std::vector<std::vector<int>>{{1}, {1}}));
    ASSERT_EQ("[[1], [], [1, 2, 3]]", VecVec2Str(std::vector<std::vector<int>>{{1}, {}, {1, 2, 3}}));
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
