#include <exception>
#include <iostream>
#include <sstream>

#include <vector>
#include <map>

//#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>
//#include <boost/function.hpp>
//#include <boost/bind.hpp>
//#include <boost/ref.hpp>
//#include <boost/variant.hpp>

#include "../src/algorithms/norvig.h"
#include <unordered_set>


using namespace std;
using namespace boost;
using namespace boost::unit_test;



void setup() {
    
}

void zad1() {
    
    unordered_set<string> dictionary;
    //dictionary.reserve(7000);
    string word = "word";
    dictionary.insert(word);
    Norvig norvig();
    
    if (norvig.contains("word")){
        cout << "tak" << endl;
    }
    
    cout << "lala" << endl;
//    typedef SmartPtr<int,NoCheck> PNoCheck;
//    typedef SmartPtr<int,CheckInit> PInitCheck;
//    typedef SmartPtr<int,CheckDeref> PDerefCheck;
//    typedef SmartPtr<int,CheckAll> PAllCheck;
//
//    BOOST_CHECK_NO_THROW( PNoCheck(0L) );
//    BOOST_CHECK_THROW( PInitCheck(0L), NullPointerException );
//    BOOST_CHECK_NO_THROW( PDerefCheck(0L) );
//    BOOST_CHECK_THROW( PAllCheck(0L), NullPointerException );
//
//    PNoCheck p1(0L);
//    PDerefCheck p2(0L);
//    BOOST_CHECK_NO_THROW( p1.get() );
//    BOOST_CHECK_THROW( p2.get(), NullPointerException );
}



test_suite*
init_unit_test_suite( int, char* [] ) {
    test_suite* test= BOOST_TEST_SUITE( "Test Norvig" );
    test->add(BOOST_TEST_CASE(&zad1));
//    test->add(BOOST_TEST_CASE(&zad2));
//    test->add(BOOST_TEST_CASE(&zad3));
//    test->add(BOOST_TEST_CASE(&zad4));
    return test;
}
