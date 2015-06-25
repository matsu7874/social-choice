CFLAGS=-I./

simulation: choice.cc election.cc util.cc
	g++ -Wall -std=c++11 -O2 -o simulation choice.cc election.cc util.cc

filter: false_filter.cc util.cc
	g++ -Wall -std=c++11 -O2 -o filter false_filter.cc util.cc

test_util_Vec2Str: test/util_vec2str_test.cc util.cc
	g++ -std=c++11 -I../include -L../  -o test/util_vec2str_test util.cc test/util_vec2str_test.cc -lgtest -lpthread

test_util_VecVec2Str: test/util_vecvec2str_test.cc util.cc
	g++ -std=c++11 -I../include -L../  -o test/util_vecvec2str_test util.cc test/util_vecvec2str_test.cc -lgtest -lpthread

test_election_IsSinglePeakedness: test/election_IsSinglePeakedness_test.cc election.cc
	g++ -std=c++11 -I../include -L../  -o test/election_IsSinglePeakedness_test election.cc test/election_IsSinglePeakedness_test.cc -lgtest -lpthread

test_election_HasInsentiveLie: test/election_HasInsentiveLie_test.cc election.cc
	g++ -std=c++11 -I../include -L../  -o test/election_HasInsentiveLie_test election.cc test/election_HasInsentiveLie_test.cc -lgtest -lpthread

test_election_SocialWelfare: test/election_SocialWelfare_test.cc election.cc
	g++ -std=c++11 -I../include -L../  -o test/election_SocialWelfare_test election.cc test/election_SocialWelfare_test.cc -lgtest -lpthread

test_election_PairwiseComparison: test/election_PairwiseComparison_test.cc election.cc
	g++ -std=c++11 -I../include -L../  -o test/election_PairwiseComparison_test election.cc test/election_PairwiseComparison_test.cc -lgtest -lpthread

test_election_BordaChoice: test/election_BordaChoice_test.cc election.cc
	g++ -std=c++11 -I../include -L../  -o test/election_BordaChoice_test election.cc test/election_BordaChoice_test.cc -lgtest -lpthread

test_election_PluralityChoice: test/election_PluralityChoice_test.cc election.cc
	g++ -std=c++11 -I../include -L../  -o test/election_PluralityChoice_test election.cc test/election_PluralityChoice_test.cc -lgtest -lpthread

test_election_SchulzeChoice: test/election_SchulzeChoice_test.cc election.cc
	g++ -std=c++11 -I../include -L../  -o test/election_SchulzeChoice_test election.cc test/election_SchulzeChoice_test.cc -lgtest -lpthread

test_election_PreferencesDistance: test/election_PreferencesDistance_test.cc election.cc
	g++ -std=c++11 -I../include -L../  -o test/election_PreferencesDistance_test election.cc test/election_PreferencesDistance_test.cc -lgtest -lpthread
