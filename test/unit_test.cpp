#include <exception>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_set>
#include <boost/test/included/unit_test.hpp>

#include "../src/algorithms/norvig.h"
#include "../src/algorithms/trie.h"
#include "../src/algorithms/trie_algorithm.h"
#include "../src/algorithms/symspell_adapter.h"
#include "../src/dictionary.h"
#include "../src/word_rating.h"
#include "../src/english_word_popularity.h"


using namespace boost::unit_test;

using namespace std;
using namespace boost;
using namespace boost::unit_test;



void test_norvig_constructor() {
    
    unordered_set<string> dictionary;
    dictionary.insert("word");
    dictionary.insert("one");
    Norvig norvig(dictionary);
    
    BOOST_CHECK_EQUAL(norvig.contains("word"), true);
}


void test_norvig_create_edits() {
    
    unordered_set<string> dictionary;
    dictionary.insert("word");
    dictionary.insert("one");
    Norvig norvig(dictionary);
    
    
    vector<string> single_edits = norvig.get_single_edits("ons");
    BOOST_CHECK_EQUAL(single_edits[0], "one");
    
    vector<string> single_edits2 = norvig.get_single_edits("difference");
    BOOST_CHECK_EQUAL(single_edits2.empty(), true);
    
}


void test_norvig_create_double_edits() {
    
    unordered_set<string> dictionary;
    dictionary.insert("word");
    dictionary.insert("one");
    Norvig norvig(dictionary);
    
    vector<string> double_edits = norvig.get_double_edits("onde");
    BOOST_CHECK_EQUAL(double_edits[0], "one");
    
    vector<string> empty_edits = norvig.get_single_edits("differnce");
    BOOST_CHECK_EQUAL(empty_edits.empty(), true);
    
}

void test_norvig_getmatches() {
    
    unordered_set<string> dictionary;
    dictionary.insert("word");
    dictionary.insert("one");
    Norvig norvig(dictionary);
    
    unordered_map<string,int> matches = norvig.get_matches("worn");
    BOOST_CHECK_EQUAL(matches.size() > 0, true);
    
}

void test_trie_constructor () {
    
    Trie* trie = new Trie();
    
    BOOST_CHECK_EQUAL( trie == nullptr, false);
    
}

void test_trie_insert () {
    
    Trie* trie = new Trie();
    trie->insert("like", true, "");
    trie->insert("lemon", true, "");

    BOOST_CHECK_EQUAL( trie->children.empty(), false);
    
}

void test_trie_algorithm_constructor () {
    
    Trie_Algorithm* trie_algorithm = new Trie_Algorithm("resources/test_dictionary_example.txt");
    
    BOOST_CHECK_EQUAL( trie_algorithm == nullptr, false);
}

void test_trie_algorithm_get_matches() {
    
    Trie_Algorithm* trie_algorithm = new Trie_Algorithm("../resources/test_dictionary_example.txt");
    unordered_map <string, int> matches = trie_algorithm->get_matches("abdicater");
    
    BOOST_CHECK_EQUAL( matches.count("abdicate") , 1);
    
}

void test_symspell_adapter_constructor() {
    
    unordered_set<string> dictionary;
    dictionary.insert("word");
    dictionary.insert("one");
    symspell::Symspell_Adapter* symspell_adapter = new symspell::Symspell_Adapter(dictionary);
    
    BOOST_CHECK_EQUAL( symspell_adapter == nullptr, false);
    
}


void test_symspell_get_matches() {
    
    unordered_set<string> dictionary;
    dictionary.insert("word");
    dictionary.insert("one");
    symspell::Symspell_Adapter* symspell_adapter = new symspell::Symspell_Adapter(dictionary);
    
    unordered_map <string, int> matches = symspell_adapter->get_matches("kord");

    BOOST_CHECK_EQUAL( matches.at("word"), 1);
    
}

void test_get_words_set() {
    
    Dictionary::getDictionary().loadDictionary( "../resources/test_dictionary_example.txt" );
    unordered_set<string> wordset = Dictionary::getDictionary().getWordsSet();
    
    BOOST_CHECK_EQUAL( wordset.size() > 0, true);
}

void test_find_most_probable_result() {
    
    Word_Rating word_rating;
    Trie_Algorithm* trie_algorithm = new Trie_Algorithm("../resources/dictionary_example2.txt");
    unordered_map <string, int> matches = trie_algorithm->get_matches("abdicater");
    
    
    string result = word_rating.findMostProbableResult ( matches, "abdicate", false);
    
    BOOST_CHECK_EQUAL( result, "abdicate");
    
}

void test_english_word_popularity_constructor() {
    
    English_Word_Popularity* english_word_popularity = new English_Word_Popularity("resources/test_english_words_popularity.txt");
    
    BOOST_CHECK_EQUAL( english_word_popularity == nullptr, false);
}

void test_get_word_percentage_in_language() {
    
    English_Word_Popularity* english_word_popularity = new English_Word_Popularity("../resources/test_english_words_popularity.txt");
    double percentage = english_word_popularity->getWordPercentageInLanguage("the");
    
    BOOST_CHECK_EQUAL( percentage > 0.005 , true);
    
}




test_suite* init_unit_test_suite( int, char* [] ) {
    
    
    test_suite* test_norvig = BOOST_TEST_SUITE( "TEST NORVIG"  );
    test_norvig->add(BOOST_TEST_CASE(&test_norvig_constructor));
    test_norvig->add(BOOST_TEST_CASE(&test_norvig_create_edits));
    test_norvig->add(BOOST_TEST_CASE(&test_norvig_create_double_edits));
    test_norvig->add(BOOST_TEST_CASE(&test_norvig_getmatches));
    
    
    test_suite* test_trie = BOOST_TEST_SUITE( "TEST TRIE" );
    test_trie->add(BOOST_TEST_CASE(&test_trie_constructor));
    test_trie->add(BOOST_TEST_CASE(&test_trie_insert));
    test_trie->add(BOOST_TEST_CASE(&test_trie_algorithm_constructor));
    test_trie->add(BOOST_TEST_CASE(&test_trie_algorithm_get_matches));
    
    
    test_suite* test_symspell_adapter = BOOST_TEST_SUITE( "TEST SYMSPELL ADAPTER" );
    test_symspell_adapter->add(BOOST_TEST_CASE(&test_symspell_adapter_constructor));
    test_symspell_adapter->add(BOOST_TEST_CASE(&test_symspell_get_matches));
    
    
    test_suite* test_dictionary = BOOST_TEST_SUITE( "TEST DICTIONARY" );
    test_dictionary->add(BOOST_TEST_CASE(&test_get_words_set));
    
    
    test_suite* test_word_rating = BOOST_TEST_SUITE( "TEST WORD RATING" );
    test_word_rating->add(BOOST_TEST_CASE(&test_find_most_probable_result));
    
    test_suite* test_english_word_popularity = BOOST_TEST_SUITE( "TEST ENGLISH WORD POPULARITY" );
    test_english_word_popularity->add(BOOST_TEST_CASE(&test_english_word_popularity_constructor));
    test_english_word_popularity->add(BOOST_TEST_CASE(&test_get_word_percentage_in_language));

    
    
    framework::master_test_suite().add( test_norvig );
    framework::master_test_suite().add( test_trie );
    framework::master_test_suite().add( test_symspell_adapter );
    framework::master_test_suite().add( test_dictionary );
    framework::master_test_suite().add( test_word_rating );
    framework::master_test_suite().add( test_english_word_popularity );
    
    
    
    return 0;
}
