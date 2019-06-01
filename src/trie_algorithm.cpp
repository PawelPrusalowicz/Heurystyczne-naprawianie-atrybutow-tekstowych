#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//disable msvc warnings for Boost.Python (Boost 1.63)
#pragma warning(disable:4100)
#pragma warning(disable:4244)
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "trie.h"
#include "trie_algorithm.h"


Trie_Algorithm::Trie_Algorithm(string path) {
    
    trie = new Trie();
    string word;
    //the dictionary with the words
    ifstream ifp(path);
    
    while(ifp >> word){
        trie->insert(word, 0, "");
    }
}

void Trie_Algorithm::search_recursive(Trie* p_tree, char ch, const string& word, vector<int>& previous_row, int max_cost, unordered_map <string, int>& results) {
    
    //const int max_cost = 1;
    const int too_big_distance = 10;
    
    int sz = previous_row.size();
    int min_row = 12;
    
    vector<int> current_row(sz, too_big_distance);
    current_row[0] = previous_row[0] + 1;
    
    // Calculate the min cost of insertion, deletion, match or substution
    int insert_or_del, replace;
    for (int i = 1; i < sz; i++) {
        insert_or_del = min(current_row[i-1] + 1, previous_row[i] + 1);
        replace = (word[i-1] == ch) ? previous_row[i-1] : (previous_row[i-1] + 1);
        
        current_row[i] = min(insert_or_del, replace);
    }
    
    if ((current_row[sz-1] <= max_cost) && (p_tree->word != "")) {
        results[p_tree->word] = current_row[sz-1];
    }
    
    for(auto& it: current_row){
        if(it < min_row)
        min_row = it;
    }
    if(min_row <= max_cost){
        for(auto& it: p_tree->children){
            search_recursive(it.second, it.first, word, current_row, max_cost, results);
        }
    }
    
}

unordered_map <string, int> Trie_Algorithm::searchMatches(string word, int max_cost) {
    
    
    const int too_big_distance = 10;
    unordered_map <string, int> results;
    
    int sz = word.size();
    
    vector<int> current_row(sz + 1);
    
    for (int i = 0; i <= sz; ++i){
        current_row[i] = i;
    }
    
    for(auto& it: trie->children){
        search_recursive(it.second, it.first, word, current_row, max_cost, results);
    }
    
    if(results.empty()){
        if (max_cost > too_big_distance){
            results.insert({word, 0});
        }
        else {
            return searchMatches(word, max_cost + 1);
        }
    }

    
    return results;
}
