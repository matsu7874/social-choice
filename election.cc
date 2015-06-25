#include <iostream>
#include <vector>
#include <algorithm>

#include "election.h"
#include "util.h"


bool IsSinglePeakedness(const std::vector<int>& individual_preference){
    bool peak_appeared = false;
    int pre_choice = individual_preference[0];
    for(auto choice: individual_preference){
        if(pre_choice < choice){
            if(peak_appeared){
                return false;
            }else{
                pre_choice = choice;
            }
        }else if(pre_choice > choice){
            if(peak_appeared){
                pre_choice = choice;
            }else{
                peak_appeared = true;
            }
        }
    }
    return true;
}

bool HasInsentiveLie(const std::vector<int>& individual_preference, const std::vector<int>& true_social_choices, const std::vector<int>& false_social_choices){
    double utility_true=0.0, utility_false = 0.0;
    for(auto true_social_choice: true_social_choices){
        utility_true -= std::distance(individual_preference.begin(), find(individual_preference.begin(), individual_preference.end(), true_social_choice));
    }
    for(auto false_social_choice: false_social_choices){
        utility_false -= std::distance(individual_preference.begin(), find(individual_preference.begin(), individual_preference.end(), false_social_choice));
    }
    utility_true /= true_social_choices.size();
    utility_false /= false_social_choices.size();
    if(utility_true < utility_false){
        return true;
    }
    return false;
}

double SocialWelfare(const std::vector<std::vector<int>>& individual_preferences, const std::vector<int>& social_choices){
    double social_welfare = 0.0;
    for(auto social_choice: social_choices){
        for(auto preference: individual_preferences){
            social_welfare -= std::distance(preference.begin(), std::find(preference.begin(), preference.end(), social_choice));
        }
    }
    return social_welfare/social_choices.size();
}

std::vector<std::vector<int>> PairwiseComparison(const std::vector<std::vector<int>>& individual_preferences){
    const int kVoter = individual_preferences.size();
    const int kChoices = individual_preferences[0].size();
    std::vector<std::vector<int>> pairwise_preferences(kChoices, std::vector<int>(kChoices));
    for(int i=0; i<kChoices; ++i){
        pairwise_preferences[i][i] = kVoter;
    }
    for(auto preference: individual_preferences){
        for(int i=0; i<kChoices-1; ++i){
            int rank_i = std::distance(preference.begin(), find(preference.begin(), preference.end(), i));
            for(int j=i+1; j<kChoices; ++j){
                int rank_j = std::distance(preference.begin(), find(preference.begin(), preference.end(), j));
                if(rank_i < rank_j){
                    pairwise_preferences[i][j] += 1;
                }else{
                    pairwise_preferences[j][i] += 1;
                }
            }
        }
    }
    return pairwise_preferences;
}

std::vector<int> BordaScore(const std::vector<std::vector<int>>& individual_preferences){
    const int kVoter = individual_preferences.size();
    const int kChoices = individual_preferences[0].size();
    std::vector<int> score(kChoices, (kChoices-1)*kChoices/2*(kVoter-1));
    for(int i=0; i<kVoter; ++i){
        for(int j=0; j<kChoices; ++j){
            score[individual_preferences[i][j]] -= j;
        }
    }
    return score;
}

std::vector<int> BordaChoice(const std::vector<std::vector<int>>& individual_preferences){
    const int kChoices = individual_preferences[0].size();
    std::vector<int> score = BordaScore(individual_preferences);
    int max_score = score[0];
    std::vector<int> choices{0};
    for(int i=1; i<kChoices; ++i){
        if(max_score < score[i]){
            choices = {i};
            max_score = score[i];
        }else if(max_score == score[i]){
            choices.push_back(i);
        }
    }
    return choices;
}

std::vector<int> PluralityChoice(const std::vector<std::vector<int>>& individual_preferences){
    const int kChoices = individual_preferences[0].size();
    std::vector<int> score(kChoices, 0);
    for(auto preference: individual_preferences){
        score[preference[0]] += 1;
    }
    int max_score = score[0];
    std::vector<int> choices{0};
    for(int i=1; i<kChoices; ++i){
        if(max_score < score[i]){
            choices = {i};
            max_score = score[i];
        }else if(max_score == score[i]){
            choices.push_back(i);
        }
    }
    return choices;
}

std::vector<int> SchulzeChoice(const std::vector<std::vector<int>>& individual_preferences){
    const int kChoices = individual_preferences[0].size();
    std::vector<std::vector<int>> pairwise_preferences = PairwiseComparison(individual_preferences);
    std::vector<std::vector<int>> path_strengths(kChoices, std::vector<int>(kChoices, 0));
    for(int i=0; i<kChoices; ++i){
        for(int j=0; j<kChoices; ++j){
            if(i != j){
                if(pairwise_preferences[i][j] > pairwise_preferences[j][i]){
                    path_strengths[i][j] = pairwise_preferences[i][j];
                }else{
                    path_strengths[i][j] = 0;
                }
            }
        }
    }
    for(int i=0; i<kChoices; ++i){
        for(int j=0; j<kChoices; ++j){
            if(i == j){
                continue;
            }
            for(int k=0; k<kChoices; ++k){
                if(i == k || j == k){
                    continue;
                }
                path_strengths[j][k] = std::max(path_strengths[j][k], std::min(path_strengths[j][i], path_strengths[i][k]));
            }
        }
    }
    std::vector<bool> is_lost(kChoices, false);
    for(int i=0; i<kChoices; ++i){
        if(is_lost[i]){
            continue;
        }
        for(int j=0; j<kChoices; ++j){
            if(i == j){
                continue;
            }
            if(path_strengths[i][j] < path_strengths[j][i]){
                is_lost[i] = true;
            }
        }
    }
    std::vector<int> choices;
    for(int i=0; i<kChoices; ++i){
        if(is_lost[i] == false){
            choices.push_back(i);
        }
    }
    return choices;
}
