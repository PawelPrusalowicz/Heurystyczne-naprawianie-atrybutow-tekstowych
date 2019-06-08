#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//disable msvc warnings for Boost.Python (Boost 1.63)
#pragma warning(disable:4100)
#pragma warning(disable:4244)
#endif

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <unordered_map>

#include "trie.h"

using namespace std;


int Trie::insert(string added_word,  bool structure_beginning, string remaining_letters = ""){
    
    //For the first time we call insert
    if(structure_beginning == true) {
        remaining_letters = added_word;
    }
    
    int remaining_size = remaining_letters.size();
    
    if(children.count(remaining_letters[0]) == 0){
        children[remaining_letters[0]] = new Trie();
    }
    
    if (remaining_size == 0) {
        word = added_word;
        return 0;
        
    }
    else {
        
        children[remaining_letters[0]]->insert(added_word, false, remaining_letters.erase(0, 1));
        return 0;
    }
}

