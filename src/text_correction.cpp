#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//disable msvc warnings for Boost.Python (Boost 1.63)
#pragma warning(disable:4100)
#pragma warning(disable:4244)
#endif

#include <iostream>
#include <string>
#include "text_correction.h"


Text_Correction::Text_Correction() {
    loadDictionary("resources/wordlist.txt");
}

void Text_Correction::loadDictionary(string path){
    
    dictionary_path = path;
    
    ifstream input(path);
    
    if (input.is_open()) {
        string line;
        while ( getline(input,line) ) {
            dictionary.insert(line);
        }
        input.close();
    }
}


string Text_Correction::info(){
    return "Used dictionary:   " + dictionary_path;
}


boost::python::list Text_Correction::correctData(boost::python::list ns) {
    
    Norvig norvig(dictionary);
        
    vector <string> vec;
    
    for (int i = 0; i < len(ns); ++i)
    {
        vec.push_back(boost::python::extract<string>(ns[i]));
    }
    
    
    boost::python::list ret;
    for(unsigned int i=0; i< vec.size(); i++){
        
    
        if (dictionary.find(vec[i]) != dictionary.end()){
            ret.append(vec[i]);
        }
        else {
            string s = norvig.get_best_match(vec[i]);
            cout << "Word: " << vec[i] << " -> " << s << endl;
            
            ret.append(s);
        }
        
    }
    return ret;
    
}



boost::python::list Text_Correction::getDictionary() {
    
    boost::python::list dictionaryWords;
    
    for(auto f : dictionary) {
        dictionaryWords.append(f);
    }
    
    return dictionaryWords;
}


void initModule() {
	std::cout << "init module" << std::endl;
}





#include <boost/python.hpp>

using namespace boost;
using namespace boost::python;

BOOST_PYTHON_MODULE(text_correction)
{
    initModule();
    
    class_<Text_Correction>("Text_Correction")
    .def( "correctData", &Text_Correction::correctData)
    .def( "loadDictionary", &Text_Correction::loadDictionary)
    .def( "info", &Text_Correction::info)
    .def( "getDictionary", &Text_Correction::getDictionary)

    
    ;
    

}
