#ifndef corrector_h
#define corrector_h

#include <set>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <memory>
#include <boost/python.hpp>

//#include "dictionary.h"

using namespace std;
class Corrector {
    public:
    Corrector() = default;
    virtual unordered_map <string, int> get_matches(string word) = 0;
};

#endif
