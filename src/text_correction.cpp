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
/*!
*\file
*\brief Definition of Text_Correction class.
*
* File includes implementation of Text_Correction class.
*/
using namespace boost;
using namespace boost::python;



/*!
* Creates an instance of Text_Correction class. Creates new singleton-dictionary and instance of 
* English_Word_Popularity with given arguments.
* \param [in] dictionary_path Path to the file with words to be loaded to the dictionary
* \param [in] pop_words_path Path to the file with words to be loaded to the dictionary of popular words
*/
Text_Correction::Text_Correction(boost::python::str dictionary_path, boost::python::str pop_words_path) {
    
	Dictionary::getDictionary();
	this->dictionary_path = boost::python::extract<string>(dictionary_path);
	string p_path = boost::python::extract<string>(pop_words_path);
	Dictionary::getDictionary().loadDictionary( this->dictionary_path );
    word_popularity = new English_Word_Popularity(p_path);
    
}
/*!
* Loads new dictionary from user level using function from Dictionary class. 
*/
void Text_Correction::loadDictionary(boost::python::str dictionary_path){
    
	this->dictionary_path = boost::python::extract<string>(dictionary_path);	
	Dictionary::getDictionary().loadDictionary( this->dictionary_path );

}
/*!
* \return Returns name of a current dictionary file.
*/
string Text_Correction::info(){
    return "Used dictionary:   " + dictionary_path;
}


/*!
* \param[in] str_algorithm Name of the algorithm, three options are available: "norvig", "trie" and "symspell".
* \param[in] english_language Logical value if the language of 
*\ param[in] ns List of words to be corrected.
* If str_algorithm is incorrect, default algorithm is SymSpell. 
* Text correction consists from: 
* 1. Loading a list of words and choosing proper correction algorithm
* 2. Finding most probable matches with chosen algorithm
* 3. Finding best match using word rating
* \return List of words after correction
*/
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
    }
    
	
    Word_Rating word_rating;
    boost::python::list result;
    
    
    
    for(unsigned int i=0; i< wordList.size(); i++) {
		
        if (Dictionary::getDictionary().getWordsSet().find(wordList[i]) != Dictionary::getDictionary().getWordsSet().end()) {
            
            result.append(wordList[i]);
        }
        else {
            
            
            unordered_map <string, int> matches = correction->get_matches(wordList[i]);
            

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

/*!
* Informs about python module initialization.
*/
void initModule() {
	std::cout << "init module" << std::endl;
}


/*!
* \brief Definition of boost python module.
*/
BOOST_PYTHON_MODULE(text_correction)
{
    initModule();
    
    class_<Text_Correction>("Text_Correction", init<boost::python::str, boost::python::str>())
    .def( "correctData", &Text_Correction::correctData)
	.def( "loadDictionary", &Text_Correction::loadDictionary)
 	.def( "info", &Text_Correction::info)
    .def( "getDictionary", &Text_Correction::getDictionary)

    ;
    
}



