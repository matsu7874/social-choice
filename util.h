#ifndef UTIL_HPP_
#define UTIL_HPP_

std::string Vec2Str(std::vector<int> vec, std::string end=", ");
std::string VecVec2Str(std::vector<std::vector<int>> vecvec);
std::vector<std::string> Split(const std::string& str, const char delimiter);
long long factorial(int n);
#endif // UTIL_HPP_
