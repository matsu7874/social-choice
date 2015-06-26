#include <vector>
#include <string>

#include "../util.h"
#include "gtest/gtest.h"

TEST(void_case, vec2str_test){
    std::vector<int> vec = {};
    ASSERT_EQ("[]", Vec2Str(vec));
}

TEST(single_case,vec2str_test){
    ASSERT_EQ("[1]", Vec2Str(std::vector<int>{1}));
    ASSERT_EQ("[0]", Vec2Str(std::vector<int>{0}));
    ASSERT_EQ("[-1]", Vec2Str(std::vector<int>{-1}));
}

TEST(multi_case,vec2str_test){
    ASSERT_EQ("[1, 2, 3, 4, 5]", Vec2Str(std::vector<int>{1, 2, 3, 4, 5}));
    ASSERT_EQ("[-1, 7, 22, 14, -25]", Vec2Str(std::vector<int>{-1, 7, 22, 14, -25}));
}

TEST(end,vec2str_test){
    ASSERT_EQ("[12345]", Vec2Str(std::vector<int>{1, 2, 3, 4, 5}, ""));
    ASSERT_EQ("[-1 7 22 14 -25]", Vec2Str(std::vector<int>{-1, 7, 22, 14, -25}, " "));
}


int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
