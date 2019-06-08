
#ifndef trie_h
#define trie_h
/*!
*\file
*\brief Definition of class Trie.
*
*/
#include <set>
#include <string>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <algorithm>

#include <iostream>
#include <cctype>
#include <unordered_map>

using namespace std;

/*!
*\brief Defines a Trie structure. 
* 
* Each node in that structure is a single letter. Each node has a branch with letters which may follow it.
*/
class Trie {
    
public:
    
    /*!
     * Stores the word
     */
    string word;
    
    /*!
     * Stores the children - map of depending objects
     */
    unordered_map <char, Trie*> children;
    /*!
	*Add new word to the actual trie structure.
	*/
    int insert(string added_word, bool structure_beginning, string remaining_letters );
    
};


#endif /* word_popularity_h */
