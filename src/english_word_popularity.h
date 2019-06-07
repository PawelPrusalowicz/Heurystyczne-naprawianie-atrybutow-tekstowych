
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

class English_Word_Popularity {
    
private:
    
    //map contains a word and its percentage in english language
    unordered_map<string,double> word_percentage;
    
    
    string dictionary_path;
    int number_of_words;
    
    
public:
    
    English_Word_Popularity (string path);
    void loadWordPopularity (string path);
    double getWordPercentageInLanguage (string word);
    
    //unordered_map<string,double> getWordPercentage();
    
    
};


#endif /* word_popularity_h */
