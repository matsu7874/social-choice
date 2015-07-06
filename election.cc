#include <iostream>
#include <vector>
#include <algorithm>

#include "election.h"
#include "util.h"

std::vector<std::vector<int>> PairwiseComparison(const std::vector<std::vector<int>>& individual_preferences){
    const int kVoters = individual_preferences.size();
    const int kChoices = individual_preferences[0].size();
    std::vector<std::vector<int>> pairwise_preferences(kChoices, std::vector<int>(kChoices));
    for(int i=0; i<kChoices; ++i){
        pairwise_preferences[i][i] = kVoters;
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
    const int kVoters = individual_preferences.size();
    const int kChoices = individual_preferences[0].size();
    std::vector<int> score(kChoices, (kChoices-1)*kChoices/2*(kVoters-1));
    for(int i=0; i<kVoters; ++i){
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

int PreferencesDistance(const std::vector<std::vector<int>>& preferences){
    int distance = 0;
    const int kVoters = preferences.size();
    const int kChoices = preferences[0].size();
    std::vector<std::vector<int>> rank(kVoters, std::vector<int>(kChoices, 0));
    for(int i=0; i<kVoters; ++i){
        for(int j=0; j<kChoices; j++){
            rank[i][j] = std::distance(preferences[i].begin(), std::find(preferences[i].begin(), preferences[i].end(), j));
        }
    }
    for(int i=0; i<kVoters-1; ++i){
        for(int j=i+1; j<kVoters; ++j){
            for(int k=0; k<kChoices-1; ++k){
                for(int l=k+1; l<kChoices; ++l){
                    if((rank[i][k]-rank[i][l])*(rank[j][k]-rank[j][l]) < 0){
                        distance += 1;
                    }
                }
            }
        }
    }
    return distance;
}

int PreferencesDistance(const std::vector<std::vector<int>>& preferences, const std::vector<int>& root_preference){
    const int kVoters = preferences.size();
    const int kChoices = preferences[0].size();
    std::vector<std::vector<int>> rank(kVoters, std::vector<int>(kChoices, 0));
    for(int i=0; i<kVoters; ++i){
        for(int j=0; j<kChoices; j++){
            rank[i][j] = std::distance(preferences[i].begin(), std::find(preferences[i].begin(), preferences[i].end(), j));
        }
    }
    std::vector<int> root_rank(kChoices, 0);
    for(int i=0; i<kChoices; i++){
        root_rank[i] = std::distance(root_preference.begin(), std::find(root_preference.begin(), root_preference.end(), i));
    }
    int distance = 0;
    for(int i=0; i<kVoters; ++i){
        for(int k=0; k<kChoices-1; ++k){
            for(int l=k+1; l<kChoices; ++l){
                if((rank[i][k]-rank[i][l])*(root_rank[k]-root_rank[l]) < 0){
                    distance += 1;
                }
            }
        }
    }
    return distance;
}
