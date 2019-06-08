
#ifndef trie_algorithm_h
#define trie_algorithm_h
/*!
*\file
*\brief Declaration of Trie_Algorithm class. 
*
*File includes definition of search algorithm based on Trie structure.
*The algorithm gets best matches for a single word.
*/
#include <set>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "corrector.h"


using namespace std;

/*!
*\brief Defines an algorithm for searching best matches for a word using Trie structure. 
*/
class Trie_Algorithm : public Corrector {
    
    /*!
     * The data structure
     */
    Trie* trie;
    
    /*!
     * Search recursively down the trie
     */
    void search_recursive(Trie* p_tree, char ch, const string& word, vector<int>& previous_row, int max_cost, unordered_map <string, int>& results);

public:
    /*!
	* Creates an object of Trie_algorithm class and a trie structure for a given dictionary.
	*/
    Trie_Algorithm(string path);
    
    /*!
	* Returns a map of best matches for the word passed as an argument.
	*/
    unordered_map <string, int> get_matches(string word);
	/*!
	* Returns a map of best matches for the word passed as an argument, allows to regulate maximum cost.
	*/
    unordered_map <string, int> get_matches(string word, int max_cost);
    
};


#endif /* trie_algorithm_h */
