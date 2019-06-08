#include <exception>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_set>
#include <boost/test/included/unit_test.hpp>
#include <chrono>

#include "../src/algorithms/norvig.h"
#include "../src/algorithms/trie.h"
#include "../src/algorithms/trie_algorithm.h"
#include "../src/algorithms/symspell_adapter.h"
#include "../src/dictionary.h"


using namespace std;
using namespace boost;
using namespace std::chrono;
using namespace boost::unit_test;



void test_norvig_speed() {
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    Dictionary::getDictionary().loadDictionary( "resources/dictionary_example.txt" );
    unordered_set<string> wordset = Dictionary::getDictionary().getWordsSet();
    Norvig norvig(wordset);
    
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto setup_time = duration_cast<microseconds>( t2 - t1 ).count();
    
    ifstream file;
    file.open ("resources/text_with_mistakes.txt");
    string word;
    int number_of_matches = 0;
    
    high_resolution_clock::time_point t3 = high_resolution_clock::now();
    
    while (file >> word)
    {
        unordered_map<string,int> matches = norvig.get_matches(word);
        number_of_matches += matches.size();
    }
    
    high_resolution_clock::time_point t4 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( t4 - t3 ).count();
    
    cout << "NORVIG SEARCH TIME: " << duration  << " MICROSECONDS, MATCHES: " << number_of_matches << " SETUP TIME: " << setup_time << endl << endl;
}



void test_trie_algorithm_speed() {
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    Trie_Algorithm* trie_algorithm = new Trie_Algorithm("resources/dictionary_example.txt");
    
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto setup_time = duration_cast<microseconds>( t2 - t1 ).count();
    
    
    ifstream file;
    file.open ("resources/text_with_mistakes.txt");
    string word;
    
    int number_of_matches = 0;
    
    
    high_resolution_clock::time_point t3 = high_resolution_clock::now();

    while (file >> word)
    {
        unordered_map<string,int> matches = trie_algorithm->get_matches(word);
        number_of_matches += matches.size();
    }
    
    high_resolution_clock::time_point t4 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( t4 - t3 ).count();
    
    cout << "TRIE SEARCH TIME: " << duration  << " MICROSECONDS, MATCHES: " << number_of_matches << " SETUP TIME: " << setup_time << endl << endl;
    
}


void test_symspell_adapter_speed() {
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    Dictionary::getDictionary().loadDictionary( "resources/dictionary_example.txt" );
    unordered_set<string> dictionary = Dictionary::getDictionary().getWordsSet();
    
    symspell::Symspell_Adapter* symspell_adapter = new symspell::Symspell_Adapter(dictionary);
    
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto setup_time = duration_cast<microseconds>( t2 - t1 ).count();
    
    
    ifstream file;
    file.open ("resources/text_with_mistakes.txt");
    string word;
    int number_of_matches = 0;
    int number_of_words = 0;
    
    high_resolution_clock::time_point t3 = high_resolution_clock::now();

    while (file >> word)
    {
        unordered_map<string,int> matches = symspell_adapter->get_matches(word);
        number_of_matches += matches.size();
        number_of_words++;
        
    }
    
    high_resolution_clock::time_point t4 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( t4 - t3 ).count();
    
    cout << "SYMSPELL ADAPTER SEARCH TIME: " << duration  << " MICROSECONDS, MATCHES: " << number_of_matches << " SETUP TIME: " << setup_time << endl << endl;
    
    
}




test_suite* init_unit_test_suite( int, char* [] ) {
    
    
    test_suite* test_norvig = BOOST_TEST_SUITE( "TEST NORVIG"  );
    test_norvig->add(BOOST_TEST_CASE(&test_norvig_speed));
    
    
    test_suite* test_trie = BOOST_TEST_SUITE( "TEST TRIE" );
    test_trie->add(BOOST_TEST_CASE(&test_trie_algorithm_speed));
    
    
    test_suite* test_symspell_adapter = BOOST_TEST_SUITE( "TEST SYMSPELL ADAPTER" );
    test_symspell_adapter->add(BOOST_TEST_CASE(&test_symspell_adapter_speed));
    
    
    framework::master_test_suite().add( test_norvig );
    framework::master_test_suite().add( test_trie );
    framework::master_test_suite().add( test_symspell_adapter );
    
    
    
    
    return 0;
}
