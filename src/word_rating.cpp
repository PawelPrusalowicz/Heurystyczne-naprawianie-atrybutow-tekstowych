#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//disable msvc warnings for Boost.Python (Boost 1.63)
#pragma warning(disable:4100)
#pragma warning(disable:4244)
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <unordered_map>

#include "word_rating.h"

using namespace std;


string Word_Rating::findMostProblableResult(unordered_map<string,int> word_popularity, unordered_map<string,int> best_matches, string word_with_mistake) {
    
    unordered_map<string,double> matchProbabilities;
    
    
    for (auto& it_best_matches: best_matches) {
        

        if (it_best_matches.second == 0) {
            
            matchProbabilities.insert({it_best_matches.first, it_best_matches.second});
            break;
        }
        
        double mistake_probability_coefficient = Word_Rating::countMistakeProbabilityCoefficient(it_best_matches.first, it_best_matches.second, word_with_mistake);
        
        
        
        //finding result in popularity list
        unordered_map<string, int>::iterator it_word_popularity = word_popularity.find(it_best_matches.first);
        
        if (it_word_popularity != word_popularity.end()){
            
            mistake_probability_coefficient += it_word_popularity->second/100000;
            
            //cout << "cos  " << it_best_matches.first << " COEFFICIENT : " << mistake_probability_coefficient << endl;
            
            matchProbabilities.insert({it_best_matches.first, mistake_probability_coefficient });
        }
        else {
            
            
            // if word is not found in word_popularity, it's popularity is 1
            matchProbabilities.insert({it_best_matches.first, mistake_probability_coefficient});
        }
        
    }
    
    string best_match;
    double highest_probability = 0;
    
    for (auto& it: matchProbabilities) {
        
        if (it.second >= highest_probability){
            
            highest_probability = it.second;
            best_match = it.first;
        }
    }
    
    //return best_match->first;
    return best_match;

    
}

double Word_Rating::countMistakeProbabilityCoefficient(string match, int correction_number, string word_with_mistake){
    
    double mistake_probability_coefficient;
    
    if (match.length() == word_with_mistake.length() ){
        mistake_probability_coefficient = 0.18;
    }
    else if ( match.length() < word_with_mistake.length() ) {
        mistake_probability_coefficient = 0.45;
    }
    else {
        mistake_probability_coefficient = 0.12;
    }
    
    mistake_probability_coefficient /= (correction_number*correction_number*correction_number*correction_number*correction_number);
    
    return mistake_probability_coefficient;
    
}
