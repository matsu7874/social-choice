#include <vector>
#include <algorithm>

#include "voter.h"
#include "util.h"

Voter::Voter(int kChoices){
    preference_ = std::vector<int>(kChoices, 0);
    std::iota(preference_.begin(), preference_.end(), 0);
    utility_ = std::vector<double>(kChoices, 0.0);
}
Voter::Voter(const std::vector<int> preference){
    preference_ = preference;
    utility_ = std::vector<double>(preference_.size(), 0.0);
}
Voter::Voter(const std::vector<int> preference, const std::vector<double> utility){
    preference_ = preference;
    utility_ = utility;
}

std::vector<double> Voter::utility(){
    return utility_;
}

std::vector<double> Voter::UpdateUtility(const std::vector<double>& utility){
    return utility_ = utility;
}

std::vector<int> Voter::preference(){
    return preference_;
}

std::vector<int> Voter::UpdatePreference(const std::vector<int>& preference){
    return preference_ = preference;
}

bool Voter::NextPermutationalPreference(){
    return std::next_permutation(preference_.begin(), preference_.end());
};


double Voter::UtilityOf(const std::vector<int>& choices){
    double utility = 0.0;
    for(auto choice: choices){
        for(unsigned int i=0; i<preference_.size(); ++i){
            if(preference_[i] == choice){
                utility += utility_[i];
                break;
            }
        }
    }
    utility /= choices.size();
    return utility;
}

bool Voter::HasInsentiveLie(const std::vector<int>& choices_if_say_true, const std::vector<int>& choices_if_say_false){
    if(UtilityOf(choices_if_say_true) < UtilityOf(choices_if_say_false)){
        return true;
    }
    return false;
}
