
#ifndef trie_algorithm_h
#define trie_algorithm_h

#include <set>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <boost/python.hpp>
#include "corrector.h"


using namespace std;

class Trie_Algorithm : public Corrector {
    
    Trie* trie;

public:
    
    Trie_Algorithm(string path);
    
    void search_recursive(Trie* p_tree, char ch, const string& word, vector<int>& previous_row, int max_cost, unordered_map <string, int>& results);
    
    unordered_map <string, int> get_matches(string word);
    unordered_map <string, int> get_matches(string word, int max_cost);
    
};


#endif /* trie_algorithm_h */
