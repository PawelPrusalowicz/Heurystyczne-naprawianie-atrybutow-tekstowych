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
/*!
*\file
*\brief Definition of Word_Rating class.
*
* File includes implementation of Word_Rating class.
*/
#define substitution_mistake_probability 1.65
#define insertion_mistake_probability 0.67
#define omission_mistake_probability 0.8

using namespace std;

/*!
* \param [in] best_matches Similar words to the one to be corrected, extracted during spelling correction algorithm
* \param [in] word_with_mistake Word to be corrected
* \param [in] english_language Logiacal value that indicates if language of rating is english
* \return best_match Most probable word
*/
string Word_Rating::findMostProbableResult( unordered_map<string,int> best_matches, string word_with_mistake, bool english_language ) {
    
    // if no matches were found, the word stays the same
    if (best_matches.empty()) {
        
        return word_with_mistake;
    }

    
    unordered_map<string,double> matchProbabilities;
    
    if ( english_language ) {
        
        english_word_popularity = new English_Word_Popularity("resources/english_words_popularity.txt");
    }
        
        
    for (auto& it_best_matches: best_matches) {
        
        double mistake_probability_coefficient = countMistakeProbabilityCoefficient(it_best_matches.first, it_best_matches.second, word_with_mistake, english_language);
        
        matchProbabilities.insert( {it_best_matches.first, mistake_probability_coefficient } );
        
    }
    
    
    string best_match;
    double highest_probability = 0;
    
    for (auto& it: matchProbabilities) {
        
        if (it.second >= highest_probability){
            
            //cout << "WORD: " << it.first << " PROBAB: " << it.second << endl;
            
            highest_probability = it.second;
            best_match = it.first;
        }
    }
    
    return best_match;
    
}



double Word_Rating::countMistakeProbabilityCoefficient(string match, int edit_distance, string word_with_mistake, bool english_language){
    
    double mistake_probability_coefficient = 0;
    
    
    mistake_probability_coefficient += 4/edit_distance;
    
    //substitutions
    if ( match.length() == word_with_mistake.length() ){
        mistake_probability_coefficient *= substitution_mistake_probability;
    }
    //insertion
    else if ( word_with_mistake.length() > match.length() ) {
        mistake_probability_coefficient *= insertion_mistake_probability;
    }
    //omission
    else {
        mistake_probability_coefficient += omission_mistake_probability;
    }
    
    
    if ( consistsOfTheSameLetters(word_with_mistake, match)){
        //cout << word_with_mistake << " " << match   << endl;
        mistake_probability_coefficient += 5;
    }
    
    
    if (english_language){
        
        mistake_probability_coefficient += english_word_popularity->getWordPercentageInLanguage(match) ;
    }
    
    return mistake_probability_coefficient;
}


bool Word_Rating::consistsOfTheSameLetters(string word1, string word2) {
    set<char> set1, set2;
    
    for_each(word1.begin(), word1.end(),
             [&set1] (char c) -> void {
                 set1.insert(c);
             });
    
    for_each(word2.begin(), word2.end(),
             [&set2] (char c) -> void {
                 set2.insert(c);
             });
    
    return set1 == set2;
}
