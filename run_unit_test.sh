#!/bin/bash

if [ "$1" = "clean" ];
then
rm *.gcov *.gcno *.gcda *.os *.txt *.o
else
g++ src/dictionary.cpp src/word_rating.cpp src/english_word_popularity.cpp src/algorithms/norvig.cpp src/algorithms/trie.cpp src/algorithms/symspell_adapter.cpp src/algorithms/trie_algorithm.cpp test/unit_test.cpp -o build/unit_test -std=c++14 -fPIC -Wall -pedantic -pthread -fprofile-arcs -ftest-coverage -lgcov



./build/unit_test --log_level=test_suite > build/unit_test_result.txt

gcov norvig.cpp > build/norvigPercentage.txt
gcov trie_algorithm.cpp > build/trie_algorithmPercentage.txt
gcov word_rating.cpp > build/word_ratingPercentage.txt
gcov english_word_popularity.cpp > build/english_word_popularityPercentage.txt
gcov trie.cpp > build/triePercentage.txt
gcov symspell_adapter.cpp > build/symspell_adapterPercentage.txt
gcov dictionary.cpp > build/dictionaryPercentage.txt


fi

