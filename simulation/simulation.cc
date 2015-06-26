#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>

#include "../election.h"
#include "../util.h"

void Simulation(const int kVoter, const int kChoices, std::vector<int> (*choice_method)(const std::vector<std::vector<int>>&));
void AllSimulation();
int main(int argc, char* argv[]){
    const int kVoter = atoi(argv[1]);
    const int kChoices = atoi(argv[2]);
    const std::string kMethod = std::string(argv[3]);

    std::cout << "choice method : " << kMethod << std::endl;
    std::cout << "number of voter : " << kVoter << std::endl;
    std::cout << "number of choices : " << kChoices << std::endl;

    const auto startTime = std::chrono::system_clock::now();
    if(kMethod == "Borda"){
        Simulation(kVoter, kChoices, BordaChoice);
    }else if(kMethod == "Schulze"){
        Simulation(kVoter, kChoices, SchulzeChoice);
    }else if(kMethod == "Plurality"){
        Simulation(kVoter, kChoices, PluralityChoice);
    }
    const auto endTime = std::chrono::system_clock::now();
    const auto timeSpan = endTime - startTime;
    std::cout << "elapsed_time : " << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]" << std::endl;
    return 0;
}


void Simulation(const int kVoter, const int kChoices, std::vector<int> (*choice_method)(const std::vector<std::vector<int>>&)){
    std::vector<std::vector<int>> preferences(kVoter+1);
    for(int i=0; i<=kVoter; ++i){
        preferences[i] = std::vector<int>(kChoices);
        iota(preferences[i].begin(), preferences[i].end(), 0);
    }
    long long true_cnt = 0, false_cnt = 0;
    bool move_up = false;
    int voter = kVoter;
    bool HasInsentiveLie_ = false;
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
            std::vector<std::vector<int>> true_preferences(preferences.begin(), preferences.end()-1);
            std::vector<std::vector<int>> false_preferences(preferences.begin()+1, preferences.end());
            std::vector<int> true_social_choices = choice_method(true_preferences);
            std::vector<int> false_social_choices = choice_method(false_preferences);

            if(HasInsentiveLie(preferences[0], true_social_choices, false_social_choices)){
                HasInsentiveLie_ = true;
                std::cout << "F ";
            }else{
                std::cout << "T ";
            }
            for(int i=0; i<=kVoter; ++i){
                std::cout << Vec2Str(preferences[i]) << " ";
            }
            std::cout << Vec2Str(true_social_choices) << " " << Vec2Str(false_social_choices) << " ";
            std::cout << PreferencesDistance(true_preferences) << " ";
            std::cout << PreferencesDistance(true_preferences, true_preferences[0]) << " ";
            std::cout << SocialWelfare(true_preferences, true_social_choices) << " ";
            std::cout << SocialWelfare(true_preferences, false_social_choices) << std::endl;
            if(std::next_permutation(preferences[voter].begin(), preferences[voter].end()) == false){
                voter -= 1;
                move_up = true;
                if(HasInsentiveLie_){
                    HasInsentiveLie_ = false;
                    false_cnt += 1;
                }else{
                    true_cnt += 1;
                }
            }
        }
    }while(voter!=0 || move_up!=true);

    std::cout << "true count: " << true_cnt << std::endl;
    std::cout << "false count: " << false_cnt << std::endl;
    std::cout << "total count: " << false_cnt+true_cnt << std::endl;
    std::cout << "false rate: " << (double)false_cnt/(false_cnt+true_cnt) << std::endl;
}
