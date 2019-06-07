#include <exception>
#include <iostream>
#include <sstream>

#include <vector>
#include <map>

//#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/variant.hpp>


using namespace std;
using namespace boost;
using namespace boost::unit_test;

//--------ZAD1--------------------------------------------------------------------------

struct NullPointerException : public std::exception {};
/*
 template<typename T,typename Checking = NoCheck >
 class SmartPtr {
 public:
 SmartPtr(T* p) : p_(p) {
 if( Checking == CheckInit || Checking == CheckAll )
 check();
 }
 T& get() {
 if( Checking == CheckDeref || Checking == CheckAll )
 check();
 return *p_;
 };
 private:
 void check() const { (!p_) throw NullPointerException(); }
 T* p_;
 };
 
 */
//--------ZAD1--rozw--------------------------------------------------------------------

struct NoCheck { };
struct CheckInit : public NoCheck {};
struct CheckDeref : public NoCheck { };
struct CheckAll : public CheckInit, public CheckDeref { };

template<typename T,typename Checking = NoCheck >
class SmartPtr {
public:
    SmartPtr(T* p) : p_(p) {
        init(Checking());
    }
    T& get() {
        deref(Checking());
        return *p_;
    };
private:
    void init(CheckInit){ check();}
    void init(NoCheck){ }
    void deref(CheckDeref){ check();}
    void deref(NoCheck){  }
    void check() const { if(!p_) throw NullPointerException(); }
    T* p_;
};

void zad1() {
    typedef SmartPtr<int,NoCheck> PNoCheck;
    typedef SmartPtr<int,CheckInit> PInitCheck;
    typedef SmartPtr<int,CheckDeref> PDerefCheck;
    typedef SmartPtr<int,CheckAll> PAllCheck;
    
    BOOST_CHECK_NO_THROW( PNoCheck(0L) );
    BOOST_CHECK_THROW( PInitCheck(0L), NullPointerException );
    BOOST_CHECK_NO_THROW( PDerefCheck(0L) );
    BOOST_CHECK_THROW( PAllCheck(0L), NullPointerException );
    
    PNoCheck p1(0L);
    PDerefCheck p2(0L);
    BOOST_CHECK_NO_THROW( p1.get() );
    BOOST_CHECK_THROW( p2.get(), NullPointerException );
}


//--------ZAD2--------------------------------------------------------------------------
typedef boost::function<int (int)> PF;

struct SumFunctor {
    SumFunctor() : s_(1) {}
    int addDiffInt(int x, int y) const { return s_ + x - y; }
    void addFun(const PF& pf){  s_ += pf(s_); }
    int s_;
};
void zad2() {
    vector<PF> vpf;
    SumFunctor sum_functor;
    vpf.push_back( boost::bind(&SumFunctor::addDiffInt, boost::ref(sum_functor), _1, 1) );
    vpf.push_back( boost::bind(&SumFunctor::addDiffInt, boost::ref(sum_functor), _1, 2) );
    
    std::for_each( vpf.begin(), vpf.end(), boost::bind(&SumFunctor::addFun, boost::ref(sum_functor), _1) );
    cout << "zad 2: " << sum_functor.s_ << endl;
}

//--------ZAD3--------------------------------------------------------------------------

typedef variant<int,string> Var;

struct Visitor : public static_visitor<void> {
    Visitor() : count_(0) {}
    void operator()(const int& i){ count_ += i; }
    void operator()(const string& s) { count_ += s.size(); }
    int count_;
};

struct ApplyFunctor {
    ApplyFunctor(Visitor& v) : visitor_(v) {}
    void operator()(const Var& var) {
        apply_visitor(visitor_, var);
    }
    Visitor& visitor_;
};

void zad3() {
    vector<Var> vv;
    vv.push_back("zad");
    vv.push_back(3);
    vv.push_back("zest");
    vv.push_back(2);
    Visitor vis;
    ApplyFunctor functor(vis);
    
    std::for_each(vv.begin(), vv.end(),functor );
    cout << "zad 3: " << vis.count_ << endl;
}

//--------ZAD4--------------------------------------------------------------------------
//blad - iterator do wektora

struct Foo {
    Foo(int i) : i_(i) {}
    int i_;
};

void zad4() {
    
    vector<Foo> kolekcja;
    typedef vector<Foo>::const_iterator Id;
    map<int,Id> index;
    
    static const int N = 5;
    
    for(int i=0; i < N; ++i ) {
        Id id = kolekcja.insert( kolekcja.end(), Foo(i) );
        index.insert( make_pair(i,id) );
    }
    Id id_0 = (*index.find(0)).second;
    const Foo& f = *id_0;
    cout << "zad 4 : " <<  f.i_ << endl;
}

test_suite*
init_unit_test_suite( int, char* [] ) {
    test_suite* test= BOOST_TEST_SUITE( "ZPR Kol 2 zest B" );
    test->add(BOOST_TEST_CASE(&zad1));
    test->add(BOOST_TEST_CASE(&zad2));
    test->add(BOOST_TEST_CASE(&zad3));
    test->add(BOOST_TEST_CASE(&zad4));
    return test;
}
