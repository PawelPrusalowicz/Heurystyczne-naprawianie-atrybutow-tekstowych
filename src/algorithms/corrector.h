#ifndef corrector_h
#define corrector_h
/*!
*\file
*\brief Definition of Corrector class. 
*
* Corrector is a base class for classes implementing spelling corrections: Norvig,
* Trie_Algorithm and Symspell_Adapter (as an adapter for symspell algorithm).
*/
#include <set>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

/*!
*\brief Provides a base for correction algorithms.
*
* Includes virtual method get_matches which must be implemented in derived classes.
*/
class Corrector {
    public:
    Corrector() = default;
	/*!
	*\brief Allows to perform data correction with algorithm depending of Corrector's type.
	*/
    virtual unordered_map <string, int> get_matches(string word) = 0;
};

#endif
