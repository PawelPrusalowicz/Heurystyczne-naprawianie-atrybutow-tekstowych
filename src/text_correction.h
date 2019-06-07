
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
#include "algorithms/corrector.h"
#include "algorithms/norvig.h"
#include "algorithms/trie.h"
#include "algorithms/trie_algorithm.h"
#include "english_word_popularity.h"
#include "word_rating.h"
#include "dictionary.h"


using namespace std;

class Text_Correction {
private:

    vector <string> text;
    string dictionary_path;
    Corrector* correction;
    
public:
    English_Word_Popularity* word_popularity;
    
    Text_Correction(boost::python::str dictionary_path, boost::python::str pop_words_path);
    void loadDictionary(boost::python::str dictionary_path);
    boost::python::list correctData(boost::python::str str_algorithm, bool english_language, boost::python::list ns);
    boost::python::list getDictionary();
    
    string info();
    
};


#endif /* text_correction_h */
