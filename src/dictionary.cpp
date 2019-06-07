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
	
	//try{
	ifstream input(path);
	//input.exceptions (ifstream::failbit);
	if (input.is_open()) {
		if(! dictionary_set.empty()){
		dictionary_set.clear();
		}
		string line;
		while (getline(input, line)) {
			dictionary_set.insert(line);
		}
		input.close();
	}
	//}catch(exception const &e){
	//cout << "Error in dictionary loading: " << e.what() << endl;
	//}
}

unordered_set<string> Dictionary::getWordsSet(){
	return dictionary_set;
}
