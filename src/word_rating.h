
#ifndef word_rating_h
#define word_rating_h
/*!
*\file
*\brief Declaration of Word_Rating class.
*/
#include <set>
#include <string>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <algorithm>

#include "english_word_popularity.h"


using namespace std;

/*!
*\brief Declaration of Word_Rating class.
*
* Provides method for finding most probable matches depending on language and
* probability of each mistake.
*/
class Word_Rating {
    
    
    English_Word_Popularity* english_word_popularity;
	/*!
	*\brief Counts probability correction using probabilities of made operations and language.  
	*/
    double countMistakeProbabilityCoefficient(string result, int edit_distance, string word_with_mistake, bool english_language);
    
    /*!
     *\brief Checks if a word and a match consist of the same letters.
     */
    
    bool consistsOfTheSameLetters(string a, string b);
    
    
public:
	/*!
	*\brief Rating function.
	*/
    string findMostProbableResult( unordered_map<string,int> best_matches, string word_with_mistake, bool english_language );

    
};


#endif /* word_rating_h */
