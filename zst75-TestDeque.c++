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
    % valgrind TestDeque.c++.app >& TestDeque.out
*/

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <deque>     // deque
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==
#include <memory>    // allocator
#include <stdio.h>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TestSuite.h"               // TestSuite
#include "cppunit/TextTestRunner.h"          // TestRunner

#include "Deque.h"

// ---------
// TestDeque
// ---------

using namespace std;

template <typename C>
struct TestDeque : CppUnit::TestFixture {
    // ----
    // size
    // ----

    void test_size () {
        C x;
        CPPUNIT_ASSERT(x.size() == 0);}

    void test_size_1() {
        C x(8, 1);
        CPPUNIT_ASSERT(x.size() == 8);
    }

    void test_size_2() {
        C x;
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.push_back(4);
        CPPUNIT_ASSERT(x.size() == 4);
    }

    void test_size_3() {
        C x;
        x.push_front(1);
        x.push_front(2);
        CPPUNIT_ASSERT(x.size() == 2);
    }

    void test_size_4() {
        C x;
        x.push_front(1);
        x.push_back(2);
        CPPUNIT_ASSERT(x.size() == 2);
    }

    void test_size_5() {
        C x;
        x.push_front(1);
        CPPUNIT_ASSERT(x.size() == 1);
        //cout << "Here" << endl;
        x.pop_front();
        CPPUNIT_ASSERT(x.size() == 0);
    }

    void test_size_6() {
        C x;
        x.push_back(1);
        CPPUNIT_ASSERT(x.size() == 1);
        x.pop_back();
        CPPUNIT_ASSERT(x.size() == 0);
    }

    void test_size_7() {
        C x;
        x.push_back(1);
        CPPUNIT_ASSERT(x.size() == 1);
        x.pop_front();
        CPPUNIT_ASSERT(x.size() == 0);
    }

    void test_size_8() {
        C x;
        x.push_front(1);
        CPPUNIT_ASSERT(x.size() == 1);
        x.pop_back();
        CPPUNIT_ASSERT(x.size() == 0);
    }

    // ------
    // resize
    // ------

    void test_resize_1() {
        C x(5);
        x.resize(10);
        CPPUNIT_ASSERT(x.size() == 10);
    }

    void test_resize_2() {
        C x(5);
        x.resize(2);
        CPPUNIT_ASSERT(x.size() == 2);
    }

    void test_resize_3() {
        C x(5);
        x.resize(10, 5);
        CPPUNIT_ASSERT(x.size() == 10);
        CPPUNIT_ASSERT(x.front() == 0);
        CPPUNIT_ASSERT(x.back() == 5);
    }

    void test_resize_4() {
        C x(5);
        x.resize(2, 5);
        CPPUNIT_ASSERT(x.size() == 2);
        CPPUNIT_ASSERT(x.front() == 0);
        CPPUNIT_ASSERT(x.back() == 0);
    }
 
    void test_resize_5() {
        C x(5,10);
        x.resize(35, 5);
        CPPUNIT_ASSERT(x.size() == 35);
        CPPUNIT_ASSERT(x.front() == 10);
        CPPUNIT_ASSERT(x.back() == 5);
    }
    
    void test_resize_6() {
        C x;
        x.resize(20);
        CPPUNIT_ASSERT(x.size() == 20);
    }

    // ----
    // swap
    // ----

    void test_swap_1() {
        C x(5);
        C y(10);
        x.swap(y);
        CPPUNIT_ASSERT(x.size() == 10);
        CPPUNIT_ASSERT(y.size() == 5);
    }

    void test_swap_2() {
        C x;
        x.push_back(1);
        x.push_back(2);
        C y;
        y.push_back(3);
        y.push_back(4);
        x.swap(y);
        CPPUNIT_ASSERT(x.front() == 3);
        CPPUNIT_ASSERT(x.back() == 4);
        CPPUNIT_ASSERT(y.front() == 1);
        CPPUNIT_ASSERT(y.back() == 2);
    }

    void test_swap_3() {
        C x;
        x.push_back(1);
        x.push_back(2);
        C y;
        y.push_back(3);
        y.push_back(4);
        x.swap(y);
        CPPUNIT_ASSERT(x.front() == 3);
        CPPUNIT_ASSERT(x.back() == 4);
        CPPUNIT_ASSERT(y.front() == 1);
        CPPUNIT_ASSERT(y.back() == 2);
        x.swap(y);
        CPPUNIT_ASSERT(x.front() == 1);
        CPPUNIT_ASSERT(x.back() == 2);
        CPPUNIT_ASSERT(y.front() == 3);
        CPPUNIT_ASSERT(y.back() == 4);
    }

    void test_swap_4() {
        C x(10);
        C y(5);
        x.swap(y);
        CPPUNIT_ASSERT(x.size() == 5);
        CPPUNIT_ASSERT(y.size() == 10); 
    }

    // -----
    // erase
    // -----

    void test_erase_1() {
        C x;
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.erase(x.begin() + 1);
        CPPUNIT_ASSERT(x.size() == 2);
        CPPUNIT_ASSERT(x.front() == 1);
        CPPUNIT_ASSERT(x.back() == 3);
    }

    void test_erase_2() {
        C x;
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.erase(x.begin());
        CPPUNIT_ASSERT(x.size() == 2);
        CPPUNIT_ASSERT(x.front() == 2);
        CPPUNIT_ASSERT(x.back() == 3);
    }

    void test_erase_3() {
        C x;
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.erase(x.end() - 1);
        CPPUNIT_ASSERT(x.size() == 2);
        CPPUNIT_ASSERT(x.front() == 1);
        CPPUNIT_ASSERT(x.back() == 2);
    }

    // -----
    // clear
    // -----

    void test_clear_1() {
        C x;
        x.clear();
        CPPUNIT_ASSERT(x.size() == 0);
    }

    void test_clear_2() {
        C x(5);
        x.clear();
        CPPUNIT_ASSERT(x.size() == 0);
    }

    void test_clear_3() {
        C x;
        x.push_back(1);
        x.clear();
        CPPUNIT_ASSERT(x.size() == 0);
    }

    void test_clear_4() {
        C x;
        x.push_front(1);
        x.clear();
        CPPUNIT_ASSERT(x.size() == 0);
    }

    // --
    // at
    // --

    void test_at_1() {
        C x;
        x.push_back(1);
        x.push_back(2);
        CPPUNIT_ASSERT(x.at(0) == 1);
        CPPUNIT_ASSERT(x.at(1) == 2);
    }

    void test_at_2() {
        C x;
        try{
            x.push_back(1);
            x.push_back(2);
            int i = x.at(2);
            ++i;
            CPPUNIT_ASSERT(false);
        }
        catch(out_of_range& o){
            CPPUNIT_ASSERT(true);
        }
    }

    void test_at_3() {
        C x;
        x.push_back(1);
        x.push_back(2);
        x.at(0) = 3;
        CPPUNIT_ASSERT(x.at(0) == 3);
    }

    // --
    // []
    // --

    void test_bracket_1() {
        C x;
        x.push_back(1);
        x.push_back(2);
        CPPUNIT_ASSERT(x[0] == 1);
        CPPUNIT_ASSERT(x[1] == 2);
    }

    void test_bracket_2() {
        C x(5);
        x.resize(10, 4);
        CPPUNIT_ASSERT(x[6] == 4);
    }

    void test_bracket_3() {
        C x;
        x.push_back(1);
        x.push_back(2);
        x[0] = 3;
        CPPUNIT_ASSERT(x[0] == 3);
    }

    // -
    // =
    // -

    void test_assignment_1() {
        C x;
        C y;
        x.push_back(1);
        x.push_back(2);
        y = x;
        CPPUNIT_ASSERT(y.size() == x.size());
        CPPUNIT_ASSERT(y[0] == x[0]);
        CPPUNIT_ASSERT(y[1] == x[1]);
    }

    void test_assignment_2() {
        C x(5);
        C y(10);
        x = y;
        CPPUNIT_ASSERT(x.size() == y.size());
    }

    void test_assignment_3() {
        C x;
        C y;
        x.push_back(1);
        x.push_back(2);
        y = x;
        y.push_back(3);
        CPPUNIT_ASSERT(x.size() != y.size());
    }

    // -------------------
    // default constructor
    // -------------------

    void test_default_1() {
        C x;
        CPPUNIT_ASSERT(x.size() == 0);
    }

    void test_default_2() {
        allocator<int> a;
        C x(a);
        CPPUNIT_ASSERT(x.size() == 0);
    }

    void test_default_3() {
        C x;
        x.push_back(1);
        CPPUNIT_ASSERT(x.size() == 1);
    }

    // ------------------------
    // initializing constructor
    // ------------------------

    void test_initialize_1() {
        C x(5);
        CPPUNIT_ASSERT(x.size() == 5);
    }

    void test_initialize_2() {
        C x(8, 5);
        CPPUNIT_ASSERT(x.size() == 8);
        CPPUNIT_ASSERT(x[3] == 5);
    }

    void test_initialize_3() {
        allocator<int> a;
        C x(5, 5, a);
        CPPUNIT_ASSERT(x.size() == 5);
        CPPUNIT_ASSERT(x[3] == 5);
    }
    
    void test_initialize_4() {
        C x(8000, 5);
        CPPUNIT_ASSERT(x.size() == 8000);
        CPPUNIT_ASSERT(x[3] == 5);
    }

    // ----------------
    // copy constructor
    // ----------------

    void test_copy_1() {
        C x(5);
        C y(x);
        CPPUNIT_ASSERT(y.size() == x.size());
    }

    void test_copy_2() {
        C x(5,5);
        C y(x);
        CPPUNIT_ASSERT(y.size() == x.size());
        CPPUNIT_ASSERT(y[3] == x[3]);
    }

    void test_copy_3() {
        C x;
        C y(x);
        CPPUNIT_ASSERT(y.size() == x.size());
    }
    
    
    void test_copy_4() {
        C x(8000,5);
        C y(x);
        CPPUNIT_ASSERT(y.size() == x.size());
        CPPUNIT_ASSERT(y[500] == x[500]);
    }

    // -----
    // begin and end
    // -----
    
    void test_begin_end_1() {
        C x;
        CPPUNIT_ASSERT(x.begin() == x.end());
    }

    void test_begin_end_2() {
        C x(5);
        CPPUNIT_ASSERT(x.begin() != x.end());
    }

    void test_begin_end_3() {
        C x;
        CPPUNIT_ASSERT(x.begin() == x.end());
        x.push_back(1);
        CPPUNIT_ASSERT(x.begin() != x.end());
    }

    // ----------
    // push_front
    // ----------

    void test_push_front_1() {
        C x;
        x.push_front(1);
        x.push_front(1);
        x.push_front(1);
        CPPUNIT_ASSERT(x.size() == 3);
        CPPUNIT_ASSERT(x[0] == 1);
    }

    void test_push_front_2() {
        C x;
        x.push_front(1);
        x.push_front(2);
        CPPUNIT_ASSERT(x.size() == 2);
        CPPUNIT_ASSERT(x[0] == 2);
    }

    void test_push_front_3() {
        C x(5,5);
        x.push_front(1);
        CPPUNIT_ASSERT(x.size() == 6);
        CPPUNIT_ASSERT(x[0] == 1);
        CPPUNIT_ASSERT(x[5] == 5);
    }

    // ---------
    // pop_front
    // ---------

    void test_pop_front_1() {
        C x(5);
        x.pop_front();
        CPPUNIT_ASSERT(x.size() == 4);
    }

    void test_pop_front_2() {
        C x(5);
        x.push_front(1);
        x.pop_front();
        CPPUNIT_ASSERT(x.size() == 5);
    }

    void test_pop_front_3() {
        C x(5,5);
        x.push_front(1);
        x.push_front(2);
        x.pop_front();
        CPPUNIT_ASSERT(x[0] = 1);
        CPPUNIT_ASSERT(x.size() == 6);
    }


    // ---------
    // push_back
    // ---------
    
    void test_push_back_1() {
        C x;
        x.push_back(1);
        CPPUNIT_ASSERT(x.size() == 1);
        CPPUNIT_ASSERT(x[0] == 1);
    }

    void test_push_back_2() {
        C x;
        x.push_back(1);
        x.push_back(2);
        CPPUNIT_ASSERT(x.size() == 2);
        CPPUNIT_ASSERT(x[0] == 1);
    }

    void test_push_back_3() {
        C x(5,5);
        x.push_back(1);
        CPPUNIT_ASSERT(x.size() == 6);
        CPPUNIT_ASSERT(x[0] == 5);
        CPPUNIT_ASSERT(x[5] == 1);
    }
    
    void test_push_back_4() {
        C x(5,5);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(20);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        x.push_back(1);
        
        
        CPPUNIT_ASSERT(x.size() == 50);
        CPPUNIT_ASSERT(x[0] == 5);
        CPPUNIT_ASSERT(x[6] == 1);
    }

    // --------
    // pop_back
    // --------

    void test_pop_back_1() {
        C x(5);
        x.pop_back();
        CPPUNIT_ASSERT(x.size() == 4);
    }

    void test_pop_back_2() {
        C x(5);
        x.push_back(1);
        x.pop_back();
        CPPUNIT_ASSERT(x.size() == 5);
    }

    void test_pop_back_3() {
        C x(5);
        x.push_front(1);
        x.pop_back();
        CPPUNIT_ASSERT(x.size() == 5);
    }
    
    void test_pop_back_4() {
        C x(5);
        for(int i = 0; i < 5; i++) {
            x.push_back(1);
        }
        
        for(int j = 0; j < 5; j++) {
            x.pop_back();
        }
        
        CPPUNIT_ASSERT(x.size() == 5);
    }

    // -----
    // front
    // -----

    void test_front_1() {
        C x(5);
        x.front();
        CPPUNIT_ASSERT(x.size() == 5);
    }

    void test_front_2() {
        C x;
        x.push_front(1);
        CPPUNIT_ASSERT(x.front() == 1);
    }

    void test_front_3() {
        C x;
        x.push_back(1);
        CPPUNIT_ASSERT(x.front() == 1);
    }
    
    void test_front_4() {
        C x;
        x.push_back(1);
        x.push_front(2);
        CPPUNIT_ASSERT(x.front() == 2);
    }

    // ----
    // back
    // ----

    void test_back_1() {
        C x(5, 5);
        CPPUNIT_ASSERT(x.size() == 5);
        CPPUNIT_ASSERT(x.back() == 5);
    }

    void test_back_2() {
        C x;
        x.push_back(1);
        CPPUNIT_ASSERT(x.back() == 1);
    }

    void test_back_3() {
        C x;
        x.push_front(1);
        CPPUNIT_ASSERT(x.back() == 1);
    }


    // ------
    // insert
    // ------

    void test_insert_1() {
        C x;
        x.insert(x.begin(), 1);
        CPPUNIT_ASSERT(x.size() == 1);
        CPPUNIT_ASSERT(x[0] == 1);
    }

    void test_insert_2() {
        C x(5,5);
        x.insert(x.begin(), 1);
        CPPUNIT_ASSERT(x.size() == 6);
        CPPUNIT_ASSERT(x[0] == 1);
    }

    void test_insert_3() {
        C x(5,5);
        x.insert(x.end(), 1);
        CPPUNIT_ASSERT(x.size() == 6);
        CPPUNIT_ASSERT(x[5] == 1);
    }
    void test_insert_4() {
        C x(5, 5);
        x.insert(x.begin() + 2, 1);
        CPPUNIT_ASSERT(x.size() == 6);
        CPPUNIT_ASSERT(x[2] == 1);
    }

    //  -----------------------------------
    //  iterator and const_iterator testing
    //  -----------------------------------

    // --
    // ==
    // --

    void test_iterator_equivalence_1() {
        C x;
        const C y;
        typename C::iterator it = x.begin();
        typename C::const_iterator cit = y.begin();

        CPPUNIT_ASSERT(it == x.begin());
        CPPUNIT_ASSERT(cit == y.begin());       
    }

    void test_iterator_equivalence_2() {
        C x;
        x.push_back(1);
        
        const C y(1, 1);
        
        typename C::iterator it = x.begin();
        typename C::const_iterator cit = y.begin();

        CPPUNIT_ASSERT(it == x.end() - 1);
        CPPUNIT_ASSERT(cit == y.end() - 1);
    }

    void test_iterator_equivalence_3() {
        C x(5,5);
        const C y (5,5);
        
        typename C::iterator it = x.end();
        typename C::const_iterator cit = y.end();

        CPPUNIT_ASSERT(it == x.begin() + 5);
        CPPUNIT_ASSERT(cit == y.begin() + 5);
    }
    
    
    // -
    // *
    // -
    
    void test_iterator_dereference_1() {
        C x(5,5);
        const C y(5,5);
        
        typename C::iterator it = x.begin();
        typename C::const_iterator cit = y.begin();
        
        CPPUNIT_ASSERT(*it == 5);
        CPPUNIT_ASSERT(*cit == 5);
    }

    void test_iterator_dereference_2() {
        C x;
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        
        const C y(3, 2);
        
        typename C::iterator it = x.begin();
        typename C::const_iterator cit = y.begin();
        
        CPPUNIT_ASSERT(*(it + 1) == 2);
        CPPUNIT_ASSERT(*(cit + 1) == 2);
    }

    void test_iterator_dereference_3() {
        C x;
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        
        const C y(3, 3);
        
        typename C::iterator it = x.end();
        typename C::const_iterator cit = y.end();
        
        CPPUNIT_ASSERT(*(it - 1) == 3);
        CPPUNIT_ASSERT(*(cit - 1) == 3);
    }
    
    
    // --
    // ++
    // --
    
    void test_increment_1(){
        C x(1);
        const C y(1);
        
        typename C::iterator it = x.begin();
        typename C::const_iterator cit = y.begin();
        
        ++it;
        ++cit;
        
        CPPUNIT_ASSERT(it == x.end());
        CPPUNIT_ASSERT(cit == y.end());        
    }
    
    void test_increment_2(){
        C x;
        x.push_back(1);
        x.push_back(2);
        
        const C y(2,2);
        
        typename C::iterator it = x.begin();
        typename C::const_iterator cit = y.begin();
        
        ++it;
        ++cit;
        
        CPPUNIT_ASSERT(*it == 2);
        CPPUNIT_ASSERT(*cit == 2);        
    }    

    void test_increment_3(){
        C x;
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        
        const C y(3,3);        
        
        typename C::iterator it = x.begin();
        typename C::const_iterator cit = y.begin();
        
        ++it;
        ++cit;
        ++it;
        ++cit;
        
        CPPUNIT_ASSERT(*it == 3);
        CPPUNIT_ASSERT(*cit == 3);        
    }    
    
    
    // ----
    // (--)
    // ----
    
    void test_decrement_1(){
        C x(1);
        const C y(1);
        
        typename C::iterator it = x.end();
        typename C::const_iterator cit = y.end();
        
        --it;
        --cit;
        
        CPPUNIT_ASSERT(it == x.begin());
        CPPUNIT_ASSERT(cit == y.begin());        
    }
    
    void test_decrement_2(){
        C x;
        x.push_back(1);
        x.push_back(2);
        
        const C y(2,2);
        
        typename C::iterator it = x.end();
        typename C::const_iterator cit = y.end();
        
        --it;
        --cit;
        
        CPPUNIT_ASSERT(*it == 2);
        CPPUNIT_ASSERT(*cit == 2);        
    }    

    void test_decrement_3(){
        C x(1);
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);        
        
        const C y(3, 2);
        
        typename C::iterator it = x.end();
        typename C::const_iterator cit = y.end();
        
        --it;
        --cit;
        --it;
        --cit;
        
        CPPUNIT_ASSERT(*it == 2);
        CPPUNIT_ASSERT(*cit == 2);        
    }    
    
    
    // --
    // +=
    // --
    
    void test_plus_equal_1(){
        C x(1);
        const C y(1);
        
        typename C::iterator it = x.begin();
        typename C::const_iterator cit = y.begin();
        
        it += 1;
        cit += 1;
        
        CPPUNIT_ASSERT(it == x.end());
        CPPUNIT_ASSERT(cit == y.end());        
    }
    
    void test_plus_equal_2(){
        C x;
        x.push_back(1);
        x.push_back(2);
        
        const C y(2,2);
        
        typename C::iterator it = x.begin();
        typename C::const_iterator cit = y.begin();
        
        it += 1;
        cit += 1;
        
        CPPUNIT_ASSERT(*it == 2);
        CPPUNIT_ASSERT(*cit == 2);        
    }    

    void test_plus_equal_3(){
        C x;
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        
        const C y(3,3);        
        
        typename C::iterator it = x.begin();
        typename C::const_iterator cit = y.begin();
        
        it += 2;
        cit += 2;

        
        CPPUNIT_ASSERT(*it == 3);
        CPPUNIT_ASSERT(*cit == 3);        
    }    
    
    
    // --
    // -=
    // --
    
    void test_minus_equal_1(){
        C x(1);
        
        const C y(1);
        
        typename C::iterator it = x.end();
        typename C::const_iterator cit = y.end();
        
        it -= 1;
        cit -= 1;
        
        CPPUNIT_ASSERT(it == x.begin());
        CPPUNIT_ASSERT(cit == y.begin());        
    }
    
    void test_minus_equal_2(){
        C x;
        x.push_back(1);
        x.push_back(2);
        
        const C y(2,2);
        
        typename C::iterator it = x.end();
        typename C::const_iterator cit = y.end();
        
        it -= 1;
        cit -= 1;
        
        CPPUNIT_ASSERT(*it == 2);
        CPPUNIT_ASSERT(*cit == 2);        
    }    

    void test_minus_equal_3(){
        C x(1);
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);        
        
        const C y(4,2);
        
        typename C::iterator it = x.end();
        typename C::const_iterator cit = y.end();
        
        it -= 2;
        cit -= 2;
        
        CPPUNIT_ASSERT(*it == 2);
        CPPUNIT_ASSERT(*cit == 2);        
    }    
    
    
    // -----
    // suite
    // -----


    CPPUNIT_TEST_SUITE(TestDeque);
    CPPUNIT_TEST(test_size);
    CPPUNIT_TEST(test_size_1);
    CPPUNIT_TEST(test_size_2);
    CPPUNIT_TEST(test_size_3);
    CPPUNIT_TEST(test_size_4);
    CPPUNIT_TEST(test_size_5);
    CPPUNIT_TEST(test_size_6);
    CPPUNIT_TEST(test_size_7);
    CPPUNIT_TEST(test_size_8);
    CPPUNIT_TEST(test_resize_1);
    CPPUNIT_TEST(test_resize_2);
    CPPUNIT_TEST(test_resize_3);
    CPPUNIT_TEST(test_resize_4);
    CPPUNIT_TEST(test_resize_5);
    CPPUNIT_TEST(test_resize_6);
    CPPUNIT_TEST(test_swap_1);
    CPPUNIT_TEST(test_swap_2);
    CPPUNIT_TEST(test_swap_3);
    CPPUNIT_TEST(test_swap_4);
    CPPUNIT_TEST(test_erase_1);
    CPPUNIT_TEST(test_erase_2);
    CPPUNIT_TEST(test_erase_3);
    CPPUNIT_TEST(test_clear_1);
    CPPUNIT_TEST(test_clear_2);
    CPPUNIT_TEST(test_clear_3);
    CPPUNIT_TEST(test_clear_4);
    CPPUNIT_TEST(test_at_1);
    CPPUNIT_TEST(test_at_2);
    CPPUNIT_TEST(test_at_3);
    CPPUNIT_TEST(test_bracket_1);
    CPPUNIT_TEST(test_bracket_2);
    CPPUNIT_TEST(test_bracket_3);
    CPPUNIT_TEST(test_assignment_1);
    CPPUNIT_TEST(test_assignment_2);
    CPPUNIT_TEST(test_assignment_3);
    CPPUNIT_TEST(test_default_1);
    CPPUNIT_TEST(test_default_2);
    CPPUNIT_TEST(test_default_3);
    CPPUNIT_TEST(test_initialize_1);
    CPPUNIT_TEST(test_initialize_2);
    CPPUNIT_TEST(test_initialize_3);
    CPPUNIT_TEST(test_initialize_4);
    CPPUNIT_TEST(test_copy_1);
    CPPUNIT_TEST(test_copy_2);
    CPPUNIT_TEST(test_copy_3);  
    CPPUNIT_TEST(test_copy_4);  
    CPPUNIT_TEST(test_begin_end_1);
    CPPUNIT_TEST(test_begin_end_2);
    CPPUNIT_TEST(test_begin_end_3);
    CPPUNIT_TEST(test_push_front_1);
    CPPUNIT_TEST(test_push_front_2);
    CPPUNIT_TEST(test_push_front_3);
    CPPUNIT_TEST(test_pop_front_1);
    CPPUNIT_TEST(test_pop_front_2);
    CPPUNIT_TEST(test_pop_front_3);
    CPPUNIT_TEST(test_push_back_1);
    CPPUNIT_TEST(test_push_back_2);
    CPPUNIT_TEST(test_push_back_3);
    CPPUNIT_TEST(test_push_back_4);
    CPPUNIT_TEST(test_pop_back_1);
    CPPUNIT_TEST(test_pop_back_2);
    CPPUNIT_TEST(test_pop_back_3);
    CPPUNIT_TEST(test_pop_back_4);
    CPPUNIT_TEST(test_front_1);
    CPPUNIT_TEST(test_front_2);
    CPPUNIT_TEST(test_front_3);
    CPPUNIT_TEST(test_front_4);
    CPPUNIT_TEST(test_back_1);
    CPPUNIT_TEST(test_back_2);
    CPPUNIT_TEST(test_back_3);
    CPPUNIT_TEST(test_insert_1);
    CPPUNIT_TEST(test_insert_2);
    CPPUNIT_TEST(test_insert_3);
    CPPUNIT_TEST(test_insert_4);
    CPPUNIT_TEST(test_iterator_equivalence_1);
    CPPUNIT_TEST(test_iterator_equivalence_2);
    CPPUNIT_TEST(test_iterator_equivalence_3);   
    CPPUNIT_TEST(test_iterator_dereference_1);
    CPPUNIT_TEST(test_iterator_dereference_2);
    CPPUNIT_TEST(test_iterator_dereference_3);       
    CPPUNIT_TEST(test_increment_1);    
    CPPUNIT_TEST(test_increment_2);
    CPPUNIT_TEST(test_increment_3);    
    CPPUNIT_TEST(test_decrement_1);    
    CPPUNIT_TEST(test_decrement_2);
    CPPUNIT_TEST(test_decrement_3);    
    CPPUNIT_TEST(test_plus_equal_1);   
    CPPUNIT_TEST(test_plus_equal_2);
    CPPUNIT_TEST(test_plus_equal_3);
    CPPUNIT_TEST(test_minus_equal_1);
    CPPUNIT_TEST(test_minus_equal_2);
    CPPUNIT_TEST(test_minus_equal_3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);        // turn off synchronization with C I/O
    cout << "TestDeque.c++" << endl << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDeque< MyDeque<int> >::suite());
    tr.addTest(TestDeque<   deque<int> >::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
