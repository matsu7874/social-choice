#ifndef ELECTION_H_
#define ELECTION_H_

double SocialWelfare(const std::vector<std::vector<int>>& individual_preferences, const std::vector<int>& social_choices);
std::vector<std::vector<int>> PairwiseComparison(const std::vector<std::vector<int>>& preferences);

std::vector<int> BordaScore(const std::vector<std::vector<int>>& preferences);
std::vector<int> BordaChoice(const std::vector<std::vector<int>>& preferences);

std::vector<int> PluralityChoice(const std::vector<std::vector<int>>& preferences);

std::vector<int> SchulzeChoice(const std::vector<std::vector<int>>& preferences);

#endif // ELECTION_H_
