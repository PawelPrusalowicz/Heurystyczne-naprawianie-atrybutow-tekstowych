#if defined(_MSC_VER) && (_MSC_VER >= 1400)
//disable msvc warnings for Boost.Python (Boost 1.63)
#pragma warning(disable:4100)
#pragma warning(disable:4244)
#endif


#include <stdio.h>
#include "dictionary.h"

Dictionary& Dictionary::getDictionary() {
	static Dictionary dictionary;
	return dictionary;
}

void Dictionary::loadDictionary(string path) {

	ifstream input(path);

	if (input.is_open()) {
		string line;
		while (getline(input, line)) {
			dictionary_set.insert(line);
		}
		input.close();
	}
}

unordered_set<string> Dictionary::getWordsSet(){
	return dictionary_set;
}
