
#ifndef norvig_h
#define norvig_h
/*!
*\file
*\brief Definition of Norvig class. 
* 
*/
#include <set>
#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

#include "corrector.h"

using namespace std;

/*!
*\brief Declaration of methods and structures needed to perform word correction using Norvig algorithm
*
* To perform data correction with Norvig algorithm there are implemented functions for operations of 
* delation, transposition, insertion and replacing in incorrect word. Best matches are found using a dictionary
* given as an argument of class constructor.
*/
class Norvig : public Corrector {
    
private:
    
    
    /** \brief Stores the dictionary */
    unordered_set<string> dictionary;
    
    
    /** \brief Stores the generated edits - words that may be matches */
    set<string> edits;
    
    
    /** \brief Stores the matches - possible correction results */
    unordered_map<string,int> matches;
    
    
    /** \brief Stores all the letters needed to generate new edits */
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    
    /*!
     *\ Creates edits with deletions.
     */
    void create_deletes(const string& word);
    
    /*!
     *\ Creates edits with transpositions.
     */
    void create_transposes(const string& word);
    
    /*!
     *\ Creates edits with replaces.
     */
    void create_replaces(const string& word);
    
    /*!
     *\ Creates edits with insertions.
     */
    void create_inserts(const string& word);
    
    /*!
     *\ Creates possible edits - words that can become matches, when they exist in dictionary
     */
    set<string> create_edits(const string& word);
    
    /*!
     *\ Creates double edits - words that differ in at least 2 edit distance from the initial word
     */
    set<string> create_double_edits(const string& word);
    
    
public:
    
    Norvig();

    Norvig(unordered_set<string> dict);
    
    /*!
     *\ Gets words with 1 edit line distance from the searched
     */
    vector<string> get_single_edits(const string& word);
    
    /*!
     *\ Gets words with w edit line distance from the searched
     */
    vector<string> get_double_edits(const string& word);
    
    /*!
     *\ Checks if the dictionary contains a word
     */
    bool contains(const string& word);
    
    /*!
     *\ Returns a map of matches with their edit distance
     */
    unordered_map<string,int> get_matches(string word);

    
};


#endif /* norvig_h */
