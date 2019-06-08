
#ifndef text_correction_h
#define text_correction_h
/*!
*\file
*\brief Declaration of Text_Correction class.
*
* File includes structure of Text_Correction class. It provides methods needed to
* perform data correction, dictionary loading and get information about current dictionary.
*/
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

/*!
*\brief Defines a an interface needed to perform data correction and dictionary loading.
*/
class Text_Correction {
private:

    string dictionary_path; /*!< Stores data about the used dictionary */
    Corrector* correction; /*!< Algorithm of data correction */
    
public:
	
    English_Word_Popularity* word_popularity;
    /*!
	* Creates an instance of Text_Correction using paths for dictionary and most-popular-words files.
	*/
    Text_Correction(boost::python::str dictionary_path, boost::python::str pop_words_path);
	/*!
	* Loads a dictionary, regarding its current state.
	*/
    void loadDictionary(boost::python::str dictionary_path);
	/*!
	* Performs data correction.
	*/
    boost::python::list correctData(boost::python::str str_algorithm, bool english_language, boost::python::list ns);
	/*!
	* Returns a python list with current dictionary.
	*/
    boost::python::list getDictionary();
    /*!
	* Returns information about object.
	*/
    string info();
    
};


#endif /* text_correction_h */
