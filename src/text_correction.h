
#ifndef text_correction_h
#define text_correction_h

#include <set>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <memory>
#include <boost/python.hpp>
#include "norvig.h"
#include "trie.h"
#include "trie_algorithm.h"
#include "word_popularity.h"
#include "word_rating.h"
#include "symspell6.h"


using namespace std;

class Text_Correction {
private:
    /* unordered_set used for O(1) look-up time */
    unordered_set<string> dictionary;
    vector <string> text;
    string dictionary_path;
    
    
public:
    Word_Popularity* word_popularity;
    
    Text_Correction();
    void loadDictionary(string path);
    //void loadWordPopularity(string path);
    boost::python::list correctData(boost::python::list ns);
    boost::python::list trieCorrection(boost::python::list ns);
    boost::python::list symSpellCorrection(boost::python::list ns);
    boost::python::list getDictionary();
    
    string info();
    
};


#endif /* norvig_h */
