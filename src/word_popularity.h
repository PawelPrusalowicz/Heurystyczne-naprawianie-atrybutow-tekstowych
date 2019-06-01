
#ifndef word_popularity_h
#define word_popularity_h

#include <set>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <boost/python.hpp>


using namespace std;

class Word_Popularity {
    
private:
    
    string dictionary_path;
    int number_of_words;
    
    
public:
    
    unordered_map<string,int> word_occurrences;
    
    Word_Popularity(string path);
    void loadWordPopularity(string path);
    
};


#endif /* word_popularity_h */
