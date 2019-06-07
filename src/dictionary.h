#ifndef dictionary_h
#define dictionary_h

#include <set>
#include <unordered_set>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Dictionary{

public:
	static Dictionary& getDictionary();
	void loadDictionary(string path);
	unordered_set<string> getWordsSet();

private:
	Dictionary() = default;
	Dictionary(const Dictionary&) = delete;
	Dictionary& operator = (const Dictionary&) = delete;

	unordered_set<string> dictionary_set;
};

#endif /* dictionary_h */
