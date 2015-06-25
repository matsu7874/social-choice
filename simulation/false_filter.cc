#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "util.h"

int main(int argc, char const *argv[]) {
    std::ifstream ifs(argv[1]);
    std::string str;
    if(ifs.fail()){
        std::cerr << "fail" << std::endl;
        return -1;
    }
    while(getline(ifs, str)){
        if(str[0] == 'F'){
            std::vector<std::string> strings = Split(str, ' ');
            int length = strings.size();
            if(std::stod(strings[length-2]) > std::stod(strings[length-1])){
                std::cout << str << std::endl;
            }
        }else if(str[0] != 'T'){
            std::cout << str << std::endl;
        }
    }
    return 0;
}
