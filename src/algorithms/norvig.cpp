#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//disable msvc warnings for Boost.Python (Boost 1.63)
#pragma warning(disable:4100)
#pragma warning(disable:4244)
#endif

#include <queue>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stdio.h>

#include "norvig.h"
/*!
*\file
*\brief Definition of Norvig class.
*
* File includes implementation of Norvig class.
*/

using namespace std;


Norvig::Norvig(unordered_set<string> dict) {
    dictionary = dict;
}

Norvig::Norvig() {
    unordered_set<string> dict;
    //dictionary.reserve(7000);
    string word = "word";
    dict.insert(word);
    dictionary = dict;
}


bool Norvig::contains(const string &word) {
    
    return dictionary.count(word) > 0;
}

void Norvig::create_deletes(const string &word) {
    
    for (unsigned int i = 0; i < word.length(); ++i) {
        
        string temp = word;
        temp.erase(temp.begin()+i);
        edits.insert(temp);
    }
}


void Norvig::create_transposes(const string &word) {
    
    for (unsigned int i = 0; i < word.length()-1; ++i) {
        
        string temp = word;
        swap(temp[i], temp[i+1]);
        edits.insert(temp);
        
    }
}

void Norvig::create_replaces(const string &word) {
    
    for (unsigned int i = 0; i < word.length(); ++i) {
        
        for (char c : alphabet) {
            
            string temp = word;
            swap(temp[i], c);
            edits.insert(temp);
        }
        
    }
    
}


void Norvig::create_inserts(const string &word) {
    
    for (unsigned int i = 0; i < word.length(); ++i) {
        
        for (char c : alphabet) {
            
            string temp = word;
            temp.insert(temp.begin()+i, c);
            edits.insert(temp);
            
        }
        
    }
    
}


set<string> Norvig::create_double_edits(const string &word) {
    
    set<string> double_edits;
    
    for(string edit1 : create_edits(word)) {
        
        for (string edit2 : create_edits(edit1)) {
            
            double_edits.insert(edit2);
        }
    }
    
    return double_edits;
}


set<string> Norvig::create_edits(const string &word) {
    
    edits.clear();
    
    if ( contains(word) ){
        edits.insert(word);
    }
    
    create_deletes(word);
    create_transposes(word);
    create_replaces(word);
    create_inserts(word);
    
    return edits;
}


vector<string> Norvig::get_single_edits(const string &word){
    
    vector<string> single_edits;
    
    for(string str : create_edits(word)) {
        
        if(contains(str)) single_edits.push_back(str);
    }
    
    return single_edits;
}


vector<string> Norvig::get_double_edits(const string &word){
    
    vector<string> double_edits;
    
    for(string str : create_double_edits(word)) {
        
        if(contains(str)) double_edits.push_back(str);
    }
    
    return double_edits;
}



std::unordered_map<string,int> Norvig::get_matches(string word) {
    
    matches.clear();
    vector<string> single_edits = get_single_edits(word);
    
    for(auto match: single_edits) {
        
        matches.insert ({match, 1});
    }
    
    if (matches.empty()){
        
        vector<string> double_edits = get_double_edits(word);
    
        for(auto match: double_edits) {
            
            matches.insert ({match, 2});
        }
        
    }
    
    return matches;
}

