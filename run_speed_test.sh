#!/bin/bash


g++ src/dictionary.cpp src/algorithms/norvig.cpp src/algorithms/trie.cpp src/algorithms/symspell_adapter.cpp src/algorithms/trie_algorithm.cpp test/speed_test.cpp -o build/speed_test -std=c++14 -fPIC -Wall -pedantic -pthread -fprofile-arcs -ftest-coverage -lgcov 

./build/speed_test --log_level=test_suite > build/speed_test_result.txt

rm -f *.o *.gcov *.gcno *.gcda *.os

