
#ifndef word_rating_h
#define word_rating_h

#include <set>
#include <string>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <boost/python.hpp>

#include "english_word_popularity.h"


using namespace std;

class Word_Rating {
    
    
    English_Word_Popularity* english_word_popularity;
    
    double countMistakeProbabilityCoefficient(string result, int edit_distance, string word_with_mistake, bool english_language);
    
    bool consistsOfTheSameLetters(string a, string b);
    
    
public:
    
    string findMostProbableResult( unordered_map<string,int> best_matches, string word_with_mistake, bool english_language );

    
};


#endif /* word_rating_h */
