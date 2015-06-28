#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

#include "../util.h"

int main(int argc, char const *argv[]) {
    std::ifstream ifs(argv[1]);
    if(ifs.fail()){
        std::cerr << "fail" << std::endl;
        return -1;
    }
    long long case_count = 0;
    std::vector<long long> welfare_down_count(3,0);
    std::vector<std::set<long long>> welfare_down_case(3, std::set<long long>());
    std::vector<std::set<long long>> false_case(3, std::set<long long>());
    std::vector<double> welfare_sum(3, 0.0);
    std::vector<double> welfare_difference_sum(3, 0.0);
    std::vector<std::string> methods={"PluralityChoice", "BordaChoice", "SchulzeChoice"};
    std::string str;
    long long case_number = 0;
    while(getline(ifs, str)){
        std::vector<std::string> s = Split(str, ',');
        int len = s.size();
        if(len<10){
            continue;
        }
        ++case_count;
        if(s[len-13]=="F" || s[len-8]=="F" || s[len-3]=="F"){
            std::cout << str << std::endl;
        }
        for(int i=0; i<3; ++i){
            welfare_sum[i] += std::stod(s[len-2-5*(2-i)]);
            if(s[len-3-5*(2-i)] == "F"){
                false_case[i].insert(std::stoll(s[0]));
                if(std::stod(s[len-2-5*(2-i)])-std::stod(s[len-1-5*(2-i)]) > 0){
                    if(welfare_down_case[i].count(std::stoll(s[0])) == 0){
                        welfare_down_case[i].insert(std::stoll(s[0]));
                    }
                    welfare_difference_sum[i] += std::stod(s[len-1-5*(2-i)])-std::stod(s[len-2-5*(2-i)]);
                    welfare_down_count[i] += 1;

                }
            }
        }
        case_number = std::stoll(s[0]);
    }
    for(int i=0; i<3; ++i){
        std::cout << methods[i] << ": ";
        std::cout << false_case[i].size() << ", " << (double)false_case[i].size()/case_number << ", ";
        std::cout << welfare_down_case[i].size() << ", " << (double)welfare_down_case[i].size()/case_number << ", ";
        std::cout << (double)welfare_sum[i]/case_count << ", ";
        std::cout << (double)welfare_difference_sum[i]/welfare_down_count[i] << std::endl;
    }
    return 0;
}
