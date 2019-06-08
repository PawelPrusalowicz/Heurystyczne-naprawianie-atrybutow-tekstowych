
#ifndef word_popularity_h
#define word_popularity_h
/*!
*\file
*\brief Declaration of English_Word_Popularity class. 
*/
#include <set>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>


using namespace std;

/*!
*\brief Declaration of methos used for language-based word rating 
*/
class English_Word_Popularity {
    
private:
    
    //map contains a word and its percentage in english language
    unordered_map<string,double> word_percentage; /*!< Dictionary of most popular words in English */
    
    
    
public:
    
    /*!
     * Class constructoe with path to the data about word popularoty
     */
    English_Word_Popularity (string path);
	/*!
	* Loads dictionary of most popular words in English to a map
	*/
    void loadWordPopularity (string path);
	/*!
	* Returns popularity of a word according to a dictionary of popular words as a fraction from 0 to 1
	*/
	double getWordPercentageInLanguage (string word);
    
    
};


#endif /* word_popularity_h */
