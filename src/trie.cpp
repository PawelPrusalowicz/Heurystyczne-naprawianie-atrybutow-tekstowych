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


// this function works
// with the argument flag set to zero
int Trie::insert(string w, int flag, string remaining_w = ""){
    //the first time we call insert
    if(flag == 0)
    remaining_w = w;
    int the_size = remaining_w.size();
    
    if(children.count(remaining_w[0]) == 0){
        children[remaining_w[0]] = new Trie();
    }
    if(the_size == 0){
        word = w;
        return 0;
    }else{
        //the recursive calls with flag one
        children[remaining_w[0]]->insert(w, 1, remaining_w.erase(0, 1));
        return 0;
    }
}

