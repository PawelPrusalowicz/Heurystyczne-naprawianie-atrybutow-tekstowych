#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//disable msvc warnings for Boost.Python (Boost 1.63)
#pragma warning(disable:4100)
#pragma warning(disable:4244)
#endif



#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "symspell6.h"
#include "symspell_adapter.h"
/*!
*\file
*\brief Definition of Symspell_Adapter class.
*
*/
using namespace symspell;



Symspell_Adapter::Symspell_Adapter(unordered_set<string> dictionary){
    
    symspell = new SymSpell();
    
	load_symspell_dictionary(dictionary);
}
/*!
*\param[in] word Word to be corrected
*\return Most similar words according to SymSpell algorithm
* Uses SymSpell \link symspell:: SymSpell Lookup\endlink
*/
unordered_map <string, int> Symspell_Adapter::get_matches(string word) {
    
    
    vector<std::unique_ptr<symspell::SuggestItem>> result_vector;
            
        char cstr2[word.size() + 1];
        strcpy(cstr2, word.c_str());
            
        symspell->Lookup(cstr2, symspell::Verbosity::All, 2, result_vector);
    
        unordered_map <string, int> matches;
            
        for (unsigned i=0; i < result_vector.size(); i++) {
                
            string str(result_vector[i]->term );
            matches.insert({ str, result_vector[i]->distance});
        }
    
    
    return matches;
}
/*!
*\param[in] dictionary Words to be corrected as a set
* Uses SymSpell \link symspell:: CreateDictionaryEntry\endlink to load dictionary.
*/
void Symspell_Adapter::load_symspell_dictionary(unordered_set<string> dictionary){
    
    for (const auto& elem: dictionary) {
        
        char cstr[elem.size() + 1];
        strcpy(cstr, elem.c_str());
        symspell->CreateDictionaryEntry(cstr, 10);
        
    }
}
