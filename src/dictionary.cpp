#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//disable msvc warnings for Boost.Python (Boost 1.63)
#pragma warning(disable:4100)
#pragma warning(disable:4244)
#endif


#include <stdio.h>
#include "dictionary.h"

/*!
* \file
* \brief Definition of Dictionary class.
*
* Includes definitions of dictionary class members.
*/

/*!
* Provides access to the static Dictionary object.
* \return Returns a reference to the private Dictionary object.
*/
Dictionary& Dictionary::getDictionary() {
	static Dictionary dictionary;
	return dictionary;
}

/*!
* Reads from filepath given as an argument. Before reading the state of dictionary is checked.
* If it is not empty, it has to be cleared. Then, words may be read to dictionary_set.
*/
void Dictionary::loadDictionary(string path) {
	
	ifstream input(path);
	if (input.is_open()) {
		if(! dictionary_set.empty()){
            dictionary_set.clear();
		}
		string line;
		while (getline(input, line)) {
			dictionary_set.insert(line);
		}
		input.close();
	}
}
/*!
* Gets words from dictionary and return them as an unoredered_set.
* \return Returns an unordered_set of words from dictionary.
*/
unordered_set<string> Dictionary::getWordsSet(){
    
	return dictionary_set;
}
