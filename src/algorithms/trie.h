
#ifndef trie_h
#define trie_h

#include <set>
#include <string>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <boost/python.hpp>

#include <iostream>
#include <cctype>
#include <unordered_map>

using namespace std;

class Trie {
    
public:
    
    string word;
    unordered_map <char, Trie*> children;
    
    int insert(string added_word, bool structure_beginning, string remaining_letters );
    
};


#endif /* word_popularity_h */
