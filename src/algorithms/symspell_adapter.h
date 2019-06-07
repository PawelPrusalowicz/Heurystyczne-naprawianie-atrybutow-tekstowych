#ifndef symspell_adapter_h
#define symspell_adapter_h

#include <set>
#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <memory>
#include <boost/python.hpp>
#include "corrector.h"

using namespace std;

namespace symspell {
    

    class SymSpell;

    class Symspell_Adapter : public Corrector {

    private:
        
        symspell::SymSpell* symspell;
        void load_symspell_dictionary(unordered_set<string> dictionary);
        
    public:
        
        Symspell_Adapter (unordered_set<string> dictionary);
        unordered_map <string, int> get_matches(string word);

    };
    
}
#endif// symspell_adapter_h
