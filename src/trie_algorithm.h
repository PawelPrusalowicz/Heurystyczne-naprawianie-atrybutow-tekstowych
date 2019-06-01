
#ifndef trie_algorithm_h
#define trie_algorithm_h

#include <set>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <boost/python.hpp>


using namespace std;

class Trie_Algorithm {
    
    Trie* trie;

public:
    
    Trie_Algorithm(string path);
    
    void search_recursive(Trie* p_tree, char ch, const string& word, vector<int>& previous_row, int max_cost, unordered_map <string, int>& results);
    
    unordered_map <string, int> searchMatches(string word, int max_cost = 1);
    
};


#endif /* trie_algorithm_h */
