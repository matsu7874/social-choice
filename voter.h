#ifndef VOTER_H_
#define VOTER_H_


class Voter{
    std::vector<double> utility_;
    std::vector<int> preference_;
public:
    Voter(const int kChoices);
    Voter(const std::vector<int> preference);
    Voter(const std::vector<int> preference, const std::vector<double> utility);

    std::vector<double> utility();
    std::vector<double> UpdateUtility(const std::vector<double>& utility);

    std::vector<int> preference();
    std::vector<int> UpdatePreference(const std::vector<int>& preference);
    bool NextPermutationalPreference();

    double UtilityOf(const std::vector<int>& choices);

    bool HasInsentiveLie(const std::vector<int>& choices_if_say_true, const std::vector<int>& choices_if_say_false);

};
#endif // VOTER_H_
