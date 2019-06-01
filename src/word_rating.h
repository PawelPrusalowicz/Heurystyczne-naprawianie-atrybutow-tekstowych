
#ifndef word_rating_h
#define word_rating_h

#include <set>
#include <string>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <boost/python.hpp>


using namespace std;

class Word_Rating {
    
public:
    
    string findMostProblableResult(unordered_map<string,int> word_popularity, unordered_map<string,int> results, string word_with_mistake);
    double countMistakeProbabilityCoefficient(string result, int correction_number, string word_with_mistake);
    
};


#endif /* word_rating_h */
