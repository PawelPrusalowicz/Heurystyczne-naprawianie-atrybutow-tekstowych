
#ifndef norvig_h
#define norvig_h

#include <set>
#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

#include "corrector.h"

using namespace std;


class Norvig : public Corrector {
    
private:
    
    /* unordered_set used for O(1) look-up time */
    unordered_set<string> dictionary;
    set<string> edits;
    unordered_map<string,int> matches;
    
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    void create_deletes(const string& word);
    void create_transposes(const string& word);
    void create_replaces(const string& word);
    void create_inserts(const string& word);
    
    set<string> create_edits(const string& word);
    set<string> create_double_edits(const string& word);
    
    
public:
    
    Norvig();

    Norvig(unordered_set<string> dict);
    
    vector<string> get_single_edits(const string& word);
    vector<string> get_double_edits(const string& word);
    
    bool contains(const string& word);
    unordered_map<string,int> get_matches(string word);

    
};


#endif /* norvig_h */
