#include <string>
#include <vector>

#include "util.h"

std::string Vec2Str(std::vector<int> vec){
    int kLength = vec.size();
    std::string str="[";
    if(kLength > 0){
        for(int i=0; i<kLength-1; ++i){
            str += std::to_string(vec[i]) + ", ";
        }
        str += std::to_string(vec[kLength-1]);
    }
    str += "]";
    return str;
}

std::string VecVec2Str(std::vector<std::vector<int>> vecvec){
    int kLength = vecvec.size();
    std::string str="[";
    if(kLength > 0){
        for(int i=0; i<kLength-1; ++i){
            str += Vec2Str(vecvec[i]) + ", ";
        }
        str += Vec2Str(vecvec[kLength-1]);
    }
    str += "]";
    return str;
}

std::vector<std::string> Split(const std::string& str, const char delimiter){
    std::vector<std::string> elements;
    std::string element = "";
    for(char c: str){
        if(c == delimiter){
            if(element != ""){
                elements.push_back(element);
            }
            element = "";
        }else{
            element += c;
        }
    }
    if(element != ""){
        elements.push_back(element);
    }
    return elements;
}
