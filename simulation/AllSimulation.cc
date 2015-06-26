#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>

#include "../election.h"
#include "../util.h"

void AllSimulation(const int kVoter, const int kChoices);

int main(int argc, char* argv[]){
    const int kVoter = atoi(argv[1]);
    const int kChoices = atoi(argv[2]);

    std::cout << "number of voter : " << kVoter << std::endl;
    std::cout << "number of choices : " << kChoices << std::endl;

    const auto startTime = std::chrono::system_clock::now();
    AllSimulation(kVoter, kChoices);
    const auto endTime = std::chrono::system_clock::now();
    const auto timeSpan = endTime - startTime;
    std::cout << "elapsed_time : " << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]" << std::endl;
    return 0;
}


void AllSimulation(const int kVoter, const int kChoices){
    std::vector<std::vector<int>> preferences(kVoter+1);
    for(int i=0; i<=kVoter; ++i){
        preferences[i] = std::vector<int>(kChoices);
        iota(preferences[i].begin(), preferences[i].end(), 0);
    }
    bool move_up = false;
    int voter = kVoter;
    do{
        if(move_up){
            if(std::next_permutation(preferences[voter].begin(), preferences[voter].end()) == false){
                voter -= 1;
                move_up = true;
            }else{
                move_up = false;
                voter = kVoter;
            }
        }else{
            for(int i=0; i<=kVoter; ++i){
                std::cout << Vec2Str(preferences[i], "") << ",";
            }
            std::vector<std::vector<int>> true_preferences(preferences.begin(), preferences.end()-1);
            std::vector<std::vector<int>> false_preferences(preferences.begin()+1, preferences.end());
            std::cout << PreferencesDistance(true_preferences) << ",";
            std::cout << PreferencesDistance(true_preferences, true_preferences[0]) << ",";
            for(auto choice_method: {PluralityChoice, BordaChoice, SchulzeChoice}){
                std::vector<int> true_social_choices = choice_method(true_preferences);
                std::vector<int> false_social_choices = choice_method(false_preferences);
                std::cout << Vec2Str(true_social_choices, "") << "," << Vec2Str(false_social_choices,"") << ",";
                if(HasInsentiveLie(preferences[0],true_social_choices, false_social_choices)){
                    std::cout <<  "F,";
                }else{
                    std::cout << "T,";
                }
                std::cout << SocialWelfare(true_preferences, true_social_choices) << ",";
                std::cout << SocialWelfare(true_preferences, false_social_choices) << ",";
            }
            std::cout << std::endl;
            if(std::next_permutation(preferences[voter].begin(), preferences[voter].end()) == false){
                voter -= 1;
                move_up = true;
            }
        }
    }while(voter!=0 || move_up!=true);
}
