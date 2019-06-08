#ifndef symspell_adapter_h
#define symspell_adapter_h
/*!
*\file
*\brief Declaration of SymSpell_Adapter class. 
*
*/
#include <set>
#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <memory>


#include "corrector.h"

using namespace std;

namespace symspell {
    

    class SymSpell;
	
	/*!
	* \brief Interface to SymSpell class. 
	* Adaptation includes dictionary loading and passing word for correction proccess.
	*/
    class Symspell_Adapter : public Corrector {

    private:
        /*!
         * Obect of the imported class Symspell
         */
        symspell::SymSpell* symspell;
        
        /*!
         * Loads the current dictionary to the Symspell object
         */
        void load_symspell_dictionary(unordered_set<string> dictionary);
        
    public:
		/*!
		* Construct new object of Symspell_Adapter using given dictionary
		*/
        Symspell_Adapter (unordered_set<string> dictionary);
		/*!
		* Finds most similar words to the word given as an argument
		*/
        unordered_map <string, int> get_matches(string word);

    };
    
}
#endif /*symspell_adapter_h*/
