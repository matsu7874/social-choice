#ifndef ELECTION_H_
#define ELECTION_H_

bool IsSinglePeakedness(const std::vector<int>& individual_preference);
bool HasInsentiveLie(const std::vector<int>& individual_preference, const std::vector<int>& true_social_choices, const std::vector<int>& false_social_choices);
double SocialWelfare(const std::vector<std::vector<int>>& individual_preferences, const std::vector<int>& social_choices);
std::vector<std::vector<int>> PairwiseComparison(const std::vector<std::vector<int>>& preferences);

std::vector<int> BordaScore(const std::vector<std::vector<int>>& preferences);
std::vector<int> BordaChoice(const std::vector<std::vector<int>>& preferences);

std::vector<int> PluralityChoice(const std::vector<std::vector<int>>& preferences);

//std::vector<int> ApprovalChoice(const std::vector<std::vector<int>>& preferences);

std::vector<int> SchulzeChoice(const std::vector<std::vector<int>>& preferences);

#endif // ELECTION_H_
