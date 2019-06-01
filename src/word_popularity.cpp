#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//disable msvc warnings for Boost.Python (Boost 1.63)
#pragma warning(disable:4100)
#pragma warning(disable:4244)
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <unordered_map>

#include "word_popularity.h"

using namespace std;

template <class Container>
void split(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
              istream_iterator<string>(),
              back_inserter(cont));
}


Word_Popularity::Word_Popularity(string path) {
    loadWordPopularity(path);
}


void Word_Popularity::loadWordPopularity(string path){
    
    ifstream input(path);
    
    if (input.is_open()) {
        string line;
    
        getline(input,line);
        //input >> line;
        vector<string> title_words;
        split(line, title_words);

        int total_number;
        std::istringstream iss (title_words[0]);
        iss >> total_number;

        number_of_words = total_number;

        while ( getline(input,line) ) {
        //while(input >> line){
        
            vector<string> words;
            split(line, words);

            
            int number;
            std::istringstream iss (words[0]);
            iss >> number;

            unordered_map<string, int>::iterator it = word_occurrences.find(words[1]);
            
            if (it == word_occurrences.end()){
                word_occurrences.insert({words[1], number});
            }
            else {
                //in case some words are repeated in file
                it->second += number;
            }
        }
        
        input.close();
    }
}
