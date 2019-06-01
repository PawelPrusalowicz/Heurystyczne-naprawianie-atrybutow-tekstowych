
#ifndef norvig_h
#define norvig_h

#include <set>
#include <string>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <boost/python.hpp>
using namespace std;

namespace {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
}


class Norvig {
private:
    /* unordered_set used for O(1) look-up time */
    unordered_set<string> dictionary;
    set<string> edits;
    
    void create_deletes(const string& word);
    void create_transposes(const string& word);
    void create_replaces(const string& word);
    void create_inserts(const string& word);
    
    set<string> create_edits(const string& word);
    set<string> create_double_edits(const string& word);
    
    unordered_map<string,int> matches;
    
public:
    /*
     * Takes a filename of dictionary and inserts all words from it in
     * the unordered set which is practically a hash set.
     */

    Norvig(unordered_set<string> dict);
    

    /*
     * Checks if the word passed as argument exists in the word set.
     */
    bool contains(const string& word);
    
    
    vector<string> get_single_edits(const string& word);
    vector<string> get_double_edits(const string& word);
    
    vector<string> get_top_matches(const string& word, unsigned int limit);
    void findMatches(string word);
    
    unordered_map<string,int> get_matches(string word);

    
};


#endif /* norvig_h */
