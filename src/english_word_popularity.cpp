#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//disable msvc warnings for Boost.Python (Boost 1.63)
#pragma warning(disable:4100)
#pragma warning(disable:4244)
#endif
/*!
*\file
*\brief Definition of English_Word_Popularity class.
*/
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <unordered_map>

#include "english_word_popularity.h"

using namespace std;

template <class Container>
void split(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
              istream_iterator<string>(),
              back_inserter(cont));
}


English_Word_Popularity::English_Word_Popularity(string path) {
    loadWordPopularity(path);
}

/*!
*\param[in] path Path to the file with most popular words in a language
* Loads dictionary of most popular words to a map which consists from pairs word-probability
*/
void English_Word_Popularity::loadWordPopularity(string path){
    
    ifstream input(path);
    
    if (input.is_open()) {
        string line;
    
        getline(input,line);
        
        vector<string> title_words;
        split(line, title_words);

        double total_number_of_words;
        std::istringstream iss (title_words[0]);
        iss >> total_number_of_words;


        while ( getline(input,line) ) {
        
            vector<string> words;
            split(line, words);

            
            double number_of_occurrences;
            // words[0] represents the number of occurrences of a word
            std::istringstream iss (words[0]);
            iss >> number_of_occurrences;
            

            // words[1] represents a word in file
            unordered_map<string, double>::iterator it = word_percentage.find(words[1]);
            
            if (it == word_percentage.end()){
                word_percentage.insert( {words[1], (number_of_occurrences/total_number_of_words) } );
            }
            else {
                //in case some words are repeated in file
                it->second += (number_of_occurrences/total_number_of_words);
            }
            
        }
        
        input.close();
    }
}

/*!
*\return Popularity of a word according to a popular-words-dictionary as a number from 0 to 1
*/
double English_Word_Popularity::getWordPercentageInLanguage (string word) {
    
    
    unordered_map<string, double>::iterator it_word_percentage = word_percentage.find(word);
    
    if (it_word_percentage != word_percentage.end()){
        
        return it_word_percentage->second;
    }
    else {
        // if word is not found in english_word_popularity, it's popularity is 0
        return 0;
    }
    
    
}


