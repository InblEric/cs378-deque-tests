// ----------------------------
// projects/deque/TestDeque.c++
// Copyright (C) 2012
// Glenn P. Downing
// ----------------------------

/*
To test the program:
% ls /usr/include/cppunit/
...
HelperMacros.h
...
% locate libcppunit.a
/usr/lib/libcppunit.a
% g++ -ansi -pedantic -lcppunit -ldl -Wall TestDeque.c++ -o TestDeque.c++.app
% valgrind ./TestDeque.c++.app >& TestDeque.out
*/

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring> // strcmp
#include <deque> // deque
#include <sstream> // ostringstream
#include <stdexcept> // invalid_argument
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TestSuite.h" // TestSuite
#include "cppunit/TextTestRunner.h" // TestRunner

#include "Deque.h"

// ---------
// TestDeque
// ---------

template <typename C>
struct TestDeque : CppUnit::TestFixture {

    // --
    // Operator ==
    // --

    void test_equal_equal_1 () {
        C x(21, 2);
        C y(21, 2);
        CPPUNIT_ASSERT(x == y); }
        
    void test_equal_equal_2 () {
        C x(10,1);
        C y(0,1);
        CPPUNIT_ASSERT(x!=y); }

    void test_equal_equal_3 () {
        C x(1,1);
        C y(x);
        CPPUNIT_ASSERT(x == y); }
        
    // ----------
    // Operator =
    // ----------

    void test_assignment_constructor_1() {
       C x(4);
       C y(2);
       y = x;
       CPPUNIT_ASSERT(y.size() == 4);}

    void test_assignment_constructor_2() {
       C x(2, 5);
       C y(2);
       y = x;
       CPPUNIT_ASSERT(y.at(1) == 5);}

    void test_assignment_constructor_3() {
       C x(2, 5);
       C y(3, 6);
       y = x;
       CPPUNIT_ASSERT(y.at(0) == 5);}

    // -
    // Operator <
    // -

    void test_less_1 () {
        C x(21, 2);
        C y(21, 2);
        y[11] = 1;
        CPPUNIT_ASSERT(y<x); }

    void test_less_2 () {
        C x(1, 0);
        C y(1, 1);
        CPPUNIT_ASSERT(y>x); }

    void test_less_3 () {
        C x(100,99);
        C y(x);
        CPPUNIT_ASSERT(x <= y); }

    // ----------
    // contructor
    // ----------

    void test_constructor_1 () {
        try {
            const C x();}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
            
    void test_constructor_2 () {
        try {
            const C x(1, 0); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_constructor_3 () {
        try {
            const C x(1);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    
    // ----------------
    // copy constructor
    // ----------------

    void test_copy_constructor_1 () {
        try{
            C x(99, 99);
            C y(x);
            CPPUNIT_ASSERT(x.size() == y.size());
            CPPUNIT_ASSERT(y[0] == 99); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
            
    void test_copy_constructor_2 () {
        try{
            C x(100,1);
            C y(x);
            x.resize(0);
            CPPUNIT_ASSERT(x.size() != y.size());
            CPPUNIT_ASSERT(y[99] == 1); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_copy_constructor_3 () {
        try{
            C x(10, 5);
            x[5]=10;
            C y(x);
            CPPUNIT_ASSERT(x.size() == y.size());
            CPPUNIT_ASSERT(y[5] == 10); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // --
    // at
    // --

    void test_at_1 () {
        const C x(10, 5);
        CPPUNIT_ASSERT(x.at(5) == 5);}

    void test_at_2 () {
        const C x(100, 5);
        CPPUNIT_ASSERT(x.at(5) == 5);}

    void test_at_3 () {
        const C x(10, 6);
        CPPUNIT_ASSERT(x.at(5) != 5);}
        
    // -----------
    // Operator []
    // -----------

    void test_index_1 () {
        const C x(10, 100);
        CPPUNIT_ASSERT(x[5] == 100);}

    void test_index_2 () {
        const C x(100, 10);
        CPPUNIT_ASSERT(x[50] == 10);}

    void test_index_3 () {
        const C x(1, 1);
        CPPUNIT_ASSERT(x[0] != 0);}

    // ----------
    // front/back
    // ----------

    void test_front_back_1 () {
        C x(5,9999);
        x[0] = 1;
        int z = x.front();
        CPPUNIT_ASSERT(z == 1); }
        
    void test_front_back_2 () {
        C x(10,10);
        x[0] = 2;
        x[4] = 9;
        int y = x.back();
        int z = x.front();
        CPPUNIT_ASSERT(y != z); }

    void test_front_back_3 () {
        C x(11,5);
        x[10] = 77;
        int z = x.back();
        CPPUNIT_ASSERT(z == 77); }

    // ----
    // size
    // ----

    void test_size () {
        const C x;
        CPPUNIT_ASSERT(x.empty());}

    void test_size_1 () {
        const C x(1);
        CPPUNIT_ASSERT(x.size() == 1);}

    void test_size_2 () {
        const C x(100);
        CPPUNIT_ASSERT(x.size() == 100);}

    void test_size_3 () {
        const C x(1000);
        CPPUNIT_ASSERT(x.size() == 1000);}

    // ------
    // resize
    // ------

    void test_resize_1 () {
        try {
            C x(10, 0);
            x.resize(0);
            CPPUNIT_ASSERT(x.empty());}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
    
    void test_resize_2 () {
        try {
            using namespace std;
            C x(10, 1);
            x.resize(20, 6);
            CPPUNIT_ASSERT(x[0]==1);
            CPPUNIT_ASSERT(x[15]==6);
            CPPUNIT_ASSERT(x.size() == 20);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_resize_3 () {
        try {
            C x(10, 0);
            x.resize(10, 1);
            CPPUNIT_ASSERT(x[0]==0);
            CPPUNIT_ASSERT(x[9]==0);
            CPPUNIT_ASSERT(x.size() == 10);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---------
    // push_back
    // ---------

    void test_push_back_1 () {
        try {
            C x(10, 5);
            x.push_back(0); 
            CPPUNIT_ASSERT( x[10] == 0 ); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
            
    void test_push_back_2 () {
        using namespace std;
        try {
            C x(222,111);
            x.push_back(1); 
            x.push_back(2); 
            CPPUNIT_ASSERT( x[222] == 1 ); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_push_back_3 () {
        try {
            C x(0);
            x.push_back(1); 
            CPPUNIT_ASSERT( x[0] == 1 ); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    

    // ---------
    // push_front
    // ---------

    void test_push_front_1 () {
        try {
            C x(10, 1);
            x.push_front(100); 
            CPPUNIT_ASSERT( x[0] == 100 ); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_push_front_2 () {
        try {
            C x(0);
            x.push_front(9999); 
            CPPUNIT_ASSERT( x[0] == 9999 ); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_push_front_3 () {
        using namespace std;
        try {
            C x(99,99);
            x.push_front(88); 
            x.push_front(77); 
            CPPUNIT_ASSERT( x[0] == 77 ); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---------
    // pop_back
    // ---------
    
    void test_pop_back_1 () {
        using namespace std;
        try {
            C x(3,2);
            x[0] = 1;
            x.pop_back(); 
            x.pop_back(); 
            CPPUNIT_ASSERT( x[0] == 1 ); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_pop_back_2 () {
        try {
            C x(2, 0);
            x.pop_back(); 
            CPPUNIT_ASSERT( x.size() == 1 ); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_pop_back_3 () {
        try {
            C x(1);
            x.pop_back(); 
            CPPUNIT_ASSERT( x.empty() ); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    

    // ---------
    // pop_front
    // ---------

    void test_pop_front_1 () {
        try {
            C x(10, 1);
            x.pop_front(); 
            CPPUNIT_ASSERT( x.size() == 9 ); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_pop_front_2 () {
        try {
            C x(9999,10);
            x.pop_front(); 
            x.pop_front(); 
            CPPUNIT_ASSERT( x[0] == 10 ); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
            
    void test_pop_front_3 () {
        try {
            C x(1);
            x.pop_front(); 
            CPPUNIT_ASSERT( x.empty() ); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ------------
    // insert/erase
    // ------------
    
     void test_insert_erase_1 () {
        try {
            C x(1,999);
            C y(2,999);
            x.insert(x.begin(),999);
            CPPUNIT_ASSERT(x == y); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_insert_erase_2 () {
        try {
            C x(1,0);
            typename C::iterator z = x.insert(x.begin(),1);
            CPPUNIT_ASSERT(*z == 1); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_insert_erase_3 () {
        try {
            C x(10,10);
            C y(11,10);
            x.insert(x.begin(),10);
            CPPUNIT_ASSERT(x == y); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}
            
    // --------
    // iterator
    // --------

    void test_iterator_1 () {
        C x(1, 1);
        typename C::iterator b = x.begin();
        CPPUNIT_ASSERT(*b == 1 ); }

    void test_iterator_2 () {
        C x(10, 0);
        x[2] = 1;
        typename C::iterator b = x.begin();
        ++b;
        ++b;
        CPPUNIT_ASSERT(*b == 1 ); }
    
    void test_iterator_3 () {
        C x(0);
        typename C::iterator b = x.begin();
        typename C::iterator c = x.end();
        CPPUNIT_ASSERT(b == c); }

    // --------
    // const_iterator
    // --------

    void test_const_iterator_1 () {
        const C x(1, 1);
        typename C::const_iterator b = x.begin();
        CPPUNIT_ASSERT(*b == 1 ); }
        
    void test_const_iterator_2 () {
        const C x(0);
        typename C::const_iterator b = x.begin();
        typename C::const_iterator c = x.end();
        CPPUNIT_ASSERT(b == c); }

    void test_const_iterator_3 () {
        const C x(100, 900);
        typename C::const_iterator b = x.begin();
        ++b;
        CPPUNIT_ASSERT(*b == 900 ); }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDeque);
    CPPUNIT_TEST(test_equal_equal_1);
    CPPUNIT_TEST(test_equal_equal_2);
    CPPUNIT_TEST(test_equal_equal_3);
    CPPUNIT_TEST(test_less_1);
    CPPUNIT_TEST(test_less_2);
    CPPUNIT_TEST(test_less_3);
    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_copy_constructor_1);
    CPPUNIT_TEST(test_copy_constructor_2);
    CPPUNIT_TEST(test_copy_constructor_3);
    CPPUNIT_TEST(test_assignment_constructor_1);
    CPPUNIT_TEST(test_assignment_constructor_2);
    CPPUNIT_TEST(test_assignment_constructor_3);
    CPPUNIT_TEST(test_index_1);
    CPPUNIT_TEST(test_index_2);
    CPPUNIT_TEST(test_index_3);
    CPPUNIT_TEST(test_at_1);
    CPPUNIT_TEST(test_at_2);
    CPPUNIT_TEST(test_at_3);
    CPPUNIT_TEST(test_front_back_1);
    CPPUNIT_TEST(test_front_back_2);
    CPPUNIT_TEST(test_front_back_3);
    CPPUNIT_TEST(test_iterator_1);
    CPPUNIT_TEST(test_iterator_2);
    CPPUNIT_TEST(test_iterator_3);
    CPPUNIT_TEST(test_const_iterator_1);
    CPPUNIT_TEST(test_const_iterator_2);
    CPPUNIT_TEST(test_const_iterator_3);
    CPPUNIT_TEST(test_size);
    CPPUNIT_TEST(test_size_1);
    CPPUNIT_TEST(test_size_2);
    CPPUNIT_TEST(test_size_3);
    CPPUNIT_TEST(test_resize_1);
    CPPUNIT_TEST(test_resize_2);
    CPPUNIT_TEST(test_resize_3);
    CPPUNIT_TEST(test_push_front_1);
    CPPUNIT_TEST(test_push_front_2);
    CPPUNIT_TEST(test_push_front_3);
    CPPUNIT_TEST(test_push_back_1);
    CPPUNIT_TEST(test_push_back_2);
    CPPUNIT_TEST(test_push_back_3);
    CPPUNIT_TEST(test_pop_front_1);
    CPPUNIT_TEST(test_pop_front_2);
    CPPUNIT_TEST(test_pop_front_3);
    CPPUNIT_TEST(test_pop_back_1);
    CPPUNIT_TEST(test_pop_back_2);
    CPPUNIT_TEST(test_pop_back_3);
    CPPUNIT_TEST(test_insert_erase_1);
    CPPUNIT_TEST(test_insert_erase_2);
    CPPUNIT_TEST(test_insert_erase_3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestDeque.c++" << endl << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDeque< MyDeque<int> >::suite());
    tr.addTest(TestDeque< deque<int> >::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}