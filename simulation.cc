#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

#include "election.h"
#include "voter.h"
#include "util.h"

double SocialWelfare(const std::vector<Voter>& voters, std::vector<int> social_choices){
    double welfare = 0;
    for(auto voter: voters){
        welfare += voter.UtilityOf(social_choices);
    }
    return welfare;
}

void Simulation(const int kVoter, const int kChoice, const std::vector<double>& utility_model){
    std::vector<Voter> voters(kVoter+1, Voter(kChoice));
    bool up = false;
    int idx = kVoter;
    long long case_number = 0;
    // long long case_group = factorial(kChoice);
    std::vector<std::vector<int>> preferences;
    for(int i=0; i<=kVoter; ++i){
        preferences.push_back(voters[i].preference());
        voters[i].UpdateUtility(utility_model);
    }
    do{
        if(up){
            if(voters[idx].NextPermutationalPreference() == false){
                idx -= 1;
                up = true;
            }else{
                up = false;
                idx = kVoter;
                ++case_number;
            }
        }else{
            std::cout << case_number << ",";
            for(int i=0; i<=kVoter; ++i){
                std::cout << Vec2Str(voters[i].preference(), "") << ",";
                preferences[i] = voters[i].preference();
            }
            std::vector<std::vector<int>> true_preferences(preferences.begin(), preferences.end()-1);
            for(auto choice_method: {PluralityChoice, BordaChoice, SchulzeChoice}){
                std::vector<int> true_social_choices = choice_method(true_preferences);
                std::vector<int> false_social_choices = choice_method(std::vector<std::vector<int>>(preferences.begin()+1, preferences.end()));
                std::cout << Vec2Str(true_social_choices, "") << "," << Vec2Str(false_social_choices,"") << ",";
                if(voters[0].HasInsentiveLie(true_social_choices, false_social_choices)){
                    std::cout <<  "F,";
                }else{
                    std::cout << "T,";
                }
                std::cout << voters[0].UtilityOf(true_social_choices) << ",";
                std::cout << voters[0].UtilityOf(false_social_choices) << ",";
                std::vector<Voter> true_voters(voters.begin(), voters.end()-1);
                std::cout << SocialWelfare(true_voters, true_social_choices) << ",";
                std::cout << SocialWelfare(true_voters, false_social_choices) << ",";
            }
            std::cout << "\n";
            if(voters[kVoter].NextPermutationalPreference() == false){
                idx -= 1;
                up = true;
            }
        }
    }while(idx!=0 || up!=true);
}

int main(int argc, char const *argv[]){
    const int kVoter = std::atoi(argv[1]);
    const int kChoice = std::atoi(argv[2]);
    std::vector<double> utility_model;
    for(int i=3; i<argc; ++i){
        utility_model.push_back(std::atof(argv[i]));
    }
    const auto startTime = std::chrono::system_clock::now();
    Simulation(kVoter, kChoice, utility_model);
    const auto endTime = std::chrono::system_clock::now();
    const auto timeSpan = endTime - startTime;
    std::cout << "elapsed_time : " << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]" << std::endl;

    return 0;
}
