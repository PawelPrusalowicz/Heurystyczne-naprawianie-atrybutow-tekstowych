#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//disable msvc warnings for Boost.Python (Boost 1.63)
#pragma warning(disable:4100)
#pragma warning(disable:4244)
#endif

#include <iostream>
#include <string>
#include <memory>
#include "text_correction.h"
#include "algorithms/symspell_adapter.h"

#include <boost/python.hpp>

using namespace boost;
using namespace boost::python;




Text_Correction::Text_Correction(boost::python::str dictionary_path, boost::python::str pop_words_path) {
    
	Dictionary::getDictionary();
	this->dictionary_path = boost::python::extract<string>(dictionary_path);
	string p_path = boost::python::extract<string>(pop_words_path);
	Dictionary::getDictionary().loadDictionary( this->dictionary_path );
    word_popularity = new English_Word_Popularity(p_path);
    
}


string Text_Correction::info(){
    return "Used dictionary:   " + dictionary_path;
}



boost::python::list Text_Correction::correctData(boost::python::str str_algorithm, bool english_language, boost::python::list ns) {
    
	string type = boost::python::extract<string>(str_algorithm);
	vector <string> wordList;
    for (int i = 0; i < len(ns); ++i)
    {
        wordList.push_back(boost::python::extract<string>(ns[i]));
    }
    
    
    if (type == "norvig"){
        
        correction = new Norvig(Dictionary::getDictionary().getWordsSet());
    }
    else if (type == "trie") {
        
        correction = new Trie_Algorithm(dictionary_path);
    }
    
    else {
        
        correction = new symspell::Symspell_Adapter(Dictionary::getDictionary().getWordsSet());
        cout << "Symspell working" << endl;
    }
    
	
    Word_Rating word_rating;
    boost::python::list result;
    
    
    
    for(unsigned int i=0; i< wordList.size(); i++) {
		
        if (Dictionary::getDictionary().getWordsSet().find(wordList[i]) != Dictionary::getDictionary().getWordsSet().end()) {
            
            result.append(wordList[i]);
        }
        else {
            
            
            unordered_map <string, int> matches = correction->get_matches(wordList[i]);
            
            
            // WYŚWIETLANIE MATCHY DLA SŁOWA. MOŻE DODAĆ TAKĄ FUNCJĘ? FAJNA SPRAWA :D
//            for (std::pair<std::string, int> element : matches)
//            {
//                std::cout << element.first << " :: " << element.second << std::endl;
//            }
            
            string most_probable_match = word_rating.findMostProbableResult ( matches, wordList[i], english_language);
            
            cout << "Word: " << wordList[i] << " -> " << most_probable_match << endl;
            
            result.append (most_probable_match);
        }
        
    }
    return result;
    
}



boost::python::list Text_Correction::getDictionary() {
    
    boost::python::list dictionaryWords;
    
    for(auto f : Dictionary::getDictionary().getWordsSet()) {
        dictionaryWords.append(f);
    }
    
    return dictionaryWords;
}


void initModule() {
	std::cout << "init module" << std::endl;
}




BOOST_PYTHON_MODULE(text_correction)
{
    initModule();
    
    class_<Text_Correction>("Text_Correction", init<boost::python::str, boost::python::str>())
    .def( "correctData", &Text_Correction::correctData)
 	.def( "info", &Text_Correction::info)
    .def( "getDictionary", &Text_Correction::getDictionary)

    ;
    
}



