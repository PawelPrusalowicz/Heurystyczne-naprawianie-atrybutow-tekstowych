
#ifndef text_correction_h
#define text_correction_h

#include <set>
#include <string>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <boost/python.hpp>
#include "norvig.h"


using namespace std;

class Text_Correction {
private:
    /* unordered_set used for O(1) look-up time */
    unordered_set<string> dictionary;
    vector <string> text;
    string dictionary_path;
    
    
public:
    
    Text_Correction();
    void loadDictionary(string path);
    boost::python::list correctData(boost::python::list ns);
    boost::python::list getDictionary();
    
    string info();
    
    
};


#endif /* norvig_h */