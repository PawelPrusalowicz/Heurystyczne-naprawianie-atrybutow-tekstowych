#ifndef dictionary_h
#define dictionary_h
/*!
*\file
*\brief Declaration of Dictionary class. 
*
* File includes definition of Dictionary used during data correction. It is implemented as
* a singleton. 
*/
#include <set>
#include <unordered_set>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
/*!
*\brief Defines dictionary structure and its available operations.
*/
class Dictionary{

public:
	/*!
	*\brief Returns current dictionary.
	*/
	static Dictionary& getDictionary();
	/*!
	*\brief Performs dictionary loading using a file path given as an argument.
	*
	*\param [in] path - Path to a file with words for a dictionary. 
	*/
	void loadDictionary(string path);
	/*!
	*\brief Returns an exact set of words sasved in a dictionary.
	*/
	unordered_set<string> getWordsSet();

private:
	Dictionary() = default;
	Dictionary(const Dictionary&) = delete;
	Dictionary& operator = (const Dictionary&) = delete;

    /*!
     * Stores the dictionary words
     */
	unordered_set<string> dictionary_set;
};

#endif /* dictionary_h */
