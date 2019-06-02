#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//disable msvc warnings for Boost.Python (Boost 1.63)
#pragma warning(disable:4100)
#pragma warning(disable:4244)
#endif

#include <iostream>
#include <string>
#include <memory>
#include "text_correction.h"


Text_Correction::Text_Correction() {
    loadDictionary("resources/wordlist.txt");
    word_popularity = new Word_Popularity("resources/popular_words.txt");
}

void Text_Correction::loadDictionary(string path){
    
    dictionary_path = path;
    
    ifstream input(path);
    
    if (input.is_open()) {
        string line;
        while ( getline(input,line) ) {
            dictionary.insert(line);
        }
        input.close();
    }
}


string Text_Correction::info(){
    return "Used dictionary:   " + dictionary_path;
}


boost::python::list Text_Correction::correctData(boost::python::list ns) {
    
    Norvig norvig(dictionary);
        
    vector <string> wordList;
    
    for (int i = 0; i < len(ns); ++i)
    {
        wordList.push_back(boost::python::extract<string>(ns[i]));
    }
    
    
    boost::python::list result;
    for(unsigned int i=0; i< wordList.size(); i++){
    
        if (dictionary.find(wordList[i]) != dictionary.end()){
            result.append(wordList[i]);
        }
        else {
            
            unordered_map <string, int> similar_results = norvig.get_matches(wordList[i]);
            Word_Rating word_rating;
            
            string most_probable_match = word_rating.findMostProblableResult(word_popularity->word_occurrences, similar_results, wordList[i]);
            
            cout << "Word: " << wordList[i] << " -> " << most_probable_match << endl;
            
            result.append (most_probable_match);
        }
        
    }
    return result;
    
}


// The cost and a distance for vector initialization



boost::python::list Text_Correction::trieCorrection(boost::python::list ns) {
    
    Trie_Algorithm* trie = new Trie_Algorithm("resources/wordlist.txt");
    
    vector <string> wordList;
    for (int i = 0; i < len(ns); ++i)
    {
        wordList.push_back(boost::python::extract<string>(ns[i]));
    }

    boost::python::list result;
    for(unsigned int i=0; i< wordList.size(); i++){
        

        if (dictionary.find(wordList[i]) != dictionary.end()){
            result.append(wordList[i]);
        }
        else {
            unordered_map <string, int> similar_results = trie->searchMatches(wordList[i]);
            Word_Rating word_rating;
            
            string most_probable_result = word_rating.findMostProblableResult(word_popularity->word_occurrences, similar_results, wordList[i]);
                        
            cout << "Word: " << wordList[i] << " -> " << most_probable_result << endl;

            result.append(most_probable_result);
        }
    
    }
    
    return result;

}



boost::python::list Text_Correction::symSpellCorrection(boost::python::list ns) {
    
    //Trie_Algorithm* trie = new Trie_Algorithm("resources/wordlist.txt");
    
    symspell::SymSpell symSpell(16, 2, 3);
    
    //std::unordered_set<T> mySet;
    for (const auto& elem: dictionary) {
        
        char cstr[elem.size() + 1];
        strcpy(cstr, elem.c_str());
        symSpell.CreateDictionaryEntry(cstr, 10);
        
    }
    
    
    
//    or (unsigned i=0; i < dictionary.size(); i++) {
//        sum += polygon[i];
//        symSpell.CreateDictionaryEntry("pips", 10);
//    }
    
    
    vector <string> wordList;
    for (int i = 0; i < len(ns); ++i)
    {
        wordList.push_back(boost::python::extract<string>(ns[i]));
    }
    
    boost::python::list result;
    for(unsigned int i=0; i< wordList.size(); i++){
        
        
        if (dictionary.find(wordList[i]) != dictionary.end()){
            
            result.append(wordList[i]);
        }
        else {
//            unordered_map <string, int> similar_results = trie->searchMatches(wordList[i]);
            vector<std::unique_ptr<symspell::SuggestItem>> result_vector;
            
            char cstr2[wordList[i].size() + 1];
            strcpy(cstr2, wordList[i].c_str());
            
            symSpell.Lookup(cstr2, symspell::Verbosity::All, 2, result_vector);
            
            unordered_map <string, int> similar_results;
            
            for (unsigned i=0; i < result_vector.size(); i++) {
                
                
                string str(result_vector[i]->term );
                similar_results.insert({ str, result_vector[i]->distance});
            }
            
            if (similar_results.empty()){
                similar_results.insert({ wordList[i], 0});
            }
            
            
            Word_Rating word_rating;
            
            string most_probable_result = word_rating.findMostProblableResult(word_popularity->word_occurrences, similar_results, wordList[i]);
            
            cout << "Word: " << wordList[i] << " -> " << most_probable_result << endl;
            
            result.append(most_probable_result);
        }
        
    }
    
    return result;
    
}



boost::python::list Text_Correction::getDictionary() {
    
    boost::python::list dictionaryWords;
    
    for(auto f : dictionary) {
        dictionaryWords.append(f);
    }
    
    return dictionaryWords;
}


void initModule() {
	std::cout << "init module" << std::endl;
}


#include <boost/python.hpp>

using namespace boost;
using namespace boost::python;

BOOST_PYTHON_MODULE(text_correction)
{
    initModule();
    
    class_<Text_Correction>("Text_Correction")
    .def( "correctData", &Text_Correction::correctData)
    .def( "loadDictionary", &Text_Correction::loadDictionary)
    .def( "trieCorrection", &Text_Correction::trieCorrection)
    .def( "symSpellCorrection", &Text_Correction::symSpellCorrection)
    .def( "info", &Text_Correction::info)
    .def( "getDictionary", &Text_Correction::getDictionary)

    ;
    
}
