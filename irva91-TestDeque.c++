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
To Test on my laptop:
    % g++ -ansi -pedantic -ldl TestDeque.c++ -lcppunit -o TestDeque.c++.app
    % valgrind ./TestDeque.c++.app
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

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TestSuite.h"               // TestSuite
#include "cppunit/TextTestRunner.h"          // TestRunner

#include "Deque.h"

// ---------
// TestDeque
// ---------

template <typename C>
struct TestDeque : CppUnit::TestFixture {
    /***ITERATOR TESTS***/

    // ----
    // it equals
    // ----
    void test_it_equal_1 () {
        C x;
        x.push_back(9);
        x.push_back(11);
        x.push_back(13);
        typename C::iterator itx = x.begin();
        typename C::iterator itx_2 = x.begin();
        CPPUNIT_ASSERT(itx == itx_2);
        }

    void test_it_equal_2 () {
        C x(11, 77);
        typename C::iterator itx = x.begin();
        typename C::iterator itx_2 = x.begin();
        CPPUNIT_ASSERT(itx == itx_2);
        itx++;
        itx_2++;
        CPPUNIT_ASSERT(itx == itx_2);
        itx++;
        itx_2++;
        CPPUNIT_ASSERT(itx == itx_2);}

    void test_it_equal_3 () {
        C x(20, 13);
        typename C::iterator itxB = x.begin();
        typename C::iterator itx2B = x.begin();
        typename C::iterator itxE = x.end();
        typename C::iterator itx2E = x.end();

        while (itxB != itxE){
            CPPUNIT_ASSERT(itxB == itx2B);
            itxB++;
            itx2B++;
        }}

    // ----
    // it operator *
    // ----
    void test_it_opSTAR_1 () {
        C x;
        x.push_back(9);
        x.push_back(11);
        x.push_back(13);
        typename C::iterator it = x.begin();
        int num = 9;
        while (it != x.end()){
            CPPUNIT_ASSERT(*it == num); 
            it++;
            num+=2;
        }}

    void test_it_opSTAR_2 () {
        C x(10, 99);
        typename C::iterator it = x.begin();
        while (it != x.end()){
            CPPUNIT_ASSERT(*it == 99); 
            it++;
        }}

    void test_it_opSTAR_3 () {
        C x(201, 5);
        typename C::iterator it = x.begin();
        while (it != x.end()){
            CPPUNIT_ASSERT(*it == 5); 
            it++;
        }}

    // ----
    // it operator ++
    // ----
    void test_it_plusPlus_1 () {
        C x(10, 5);
        typename C::iterator it = x.begin();
        typename C::iterator it2 = x.begin();
        CPPUNIT_ASSERT(it == it2++);
        CPPUNIT_ASSERT(++it == it2);}

    void test_it_plusPlus_2 () {
        C x(100, 5);
        typename C::iterator it = x.begin();
        typename C::iterator it2 = x.begin();
        while (it != x.end()){
            CPPUNIT_ASSERT(it == it2);
            it++;
            ++it2;}}

    void test_it_plusPlus_3 () {
        C x(200, 7);
        typename C::iterator it = x.begin();
        typename C::iterator it2 = x.begin();
        while (it != x.end()){
            CPPUNIT_ASSERT(it == it2);
            it++;
            ++it2;}}

    // ----
    // it operator --
    // ----
    void test_it_minusMinus_1 () {
        C x(10, 5);
        typename C::iterator end = x.end();
        typename C::iterator end2 = x.end();
        CPPUNIT_ASSERT(end == end2--);
        CPPUNIT_ASSERT(--end == end2);}

    void test_it_minusMinus_2 () {
        C x(100, 5);
        typename C::iterator end = x.end();
        typename C::iterator end2 = x.end();
        while (end != x.begin()){
            end == end2;
            end--;
            --end;}}

    void test_it_minusMinus_3 () {
        C x(200, 7);
        typename C::iterator end = x.end();
        typename C::iterator end2 = x.end();
        while (end != x.begin()){
            end == end2;
            end--;
            --end;}}

    // ----
    // it operator -
    // ----
    void test_it_minus_1 () {
        C x(10, 5);
        typename C::iterator it = x.begin();
        CPPUNIT_ASSERT((x.end() - 10) == it);}

    void test_it_minus_2 () {
        C x;
        x.push_back(10);
        x.push_back(5);
        x.push_back(2);
        typename C::iterator it = x.begin();
        CPPUNIT_ASSERT(*(x.end() - 1) == 2);
        CPPUNIT_ASSERT(*(x.end() - 2) == 5);
        CPPUNIT_ASSERT(*(x.end() - 3) == 10);}

    void test_it_minus_3 () {
        C x(200, 5);
        typename C::iterator it = x.begin();
        CPPUNIT_ASSERT((x.end() - 200) == it);}

    // ----
    // it operator +
    // ----
    void test_it_plus_1 () {
        C x(10, 5);
        typename C::iterator it = x.begin();
        CPPUNIT_ASSERT((it + 10) == x.end());}

    void test_it_plus_2 () {
        C x;
        x.push_back(5);
        x.push_back(3);
        x.push_back(2);
        typename C::iterator it = x.begin();
        CPPUNIT_ASSERT(*(it) == 5);
        CPPUNIT_ASSERT(*(it + 1) == 3);
        CPPUNIT_ASSERT(*(it + 2) == 2);}

    void test_it_plus_3 () {
        C x(190, 5);
        typename C::iterator it = x.begin();
        CPPUNIT_ASSERT((it + 190) == x.end());}

    /***Deque Tests***/  
    // ----
    // size
    // ----

    void test_size_1 () {
        const C x;
        CPPUNIT_ASSERT(x.size() == 0);
        }

    void test_size_2 () {
        const C x(11, 1);
        CPPUNIT_ASSERT(x.size() == 11);
        }

    void test_size_3 () {
        const C x(222, 1);
        CPPUNIT_ASSERT(x.size() == 222);
        }

    void test_size_4 () {
        const C x(333, 1);
	    CPPUNIT_ASSERT(x.size() == 333);
	    }

    void test_size_5 () {
        const C x(4444, 1);
        CPPUNIT_ASSERT(x.size() == 4444);
        }

    // ----------
    // Constructors
    // ----------
    void test_constructors_1 () {
        const C x;
        CPPUNIT_ASSERT(x.size() == 0);}

    void test_constructors_2 () {
        const C x(120, 1);
        CPPUNIT_ASSERT(x.getOuterSize() == 2);
        CPPUNIT_ASSERT(x.getOuterCapacity() == 2);
        CPPUNIT_ASSERT(x.getBeginOffset() == 40);
        CPPUNIT_ASSERT(x.getEndOffset()  == 40);}

    void test_constructors_3 () {
        const C y(120, 3);
        const C x(y);
        CPPUNIT_ASSERT(x.getOuterSize() == 2);
        CPPUNIT_ASSERT(x.getOuterCapacity() == 2);
        CPPUNIT_ASSERT(x.getBeginOffset() == 40);
        CPPUNIT_ASSERT(x.getEndOffset()  == 40);}
        
    void test_constructors_4 () {
        const C x(61235, 100);
        CPPUNIT_ASSERT(x.getOuterSize() == 613);
        CPPUNIT_ASSERT(x.getOuterCapacity() == 613);
        CPPUNIT_ASSERT(x.getBeginOffset() == 32);
        CPPUNIT_ASSERT(x.getEndOffset()  == 33);}
        
    void test_constructors_5 () {
        const C y(120, 3);
        const C x(y);
        CPPUNIT_ASSERT(x.getOuterSize() == 2);
        CPPUNIT_ASSERT(x.getOuterCapacity() == 2);
        CPPUNIT_ASSERT(x.getBeginOffset() == 40);
        CPPUNIT_ASSERT(x.getEndOffset()  == 40);
        CPPUNIT_ASSERT(x.size()  == 120);}

    // ----------
    // Destructors
    // ----------
    void test_deconstructors_1 () {
        C x(100);
        CPPUNIT_ASSERT(true);}

    // ----------
    // =
    // ----------
    void test_assign_1 () {
        C x(10, 5);
	    C y;
        CPPUNIT_ASSERT(x != y);
	    y = x;	
        CPPUNIT_ASSERT(x == y);}

    void test_assign_2 () {
        C x;
        x.push_back(10);
        x.push_back(1);
	    C y;
        CPPUNIT_ASSERT(x != y);
        CPPUNIT_ASSERT(&x != &y);
	    y = x;
        CPPUNIT_ASSERT(x == y);
        CPPUNIT_ASSERT(&x != &y);
	    x.push_back(5);	
        CPPUNIT_ASSERT(x != y);}

    void test_assign_3 () {
        C x(10, 5);
	    C y(x);
	    C z = y;
        CPPUNIT_ASSERT(x == y);
        CPPUNIT_ASSERT(x == z);
        CPPUNIT_ASSERT(y == z);
	    x.push_back(-1);
        CPPUNIT_ASSERT(x != y);
        CPPUNIT_ASSERT(x != z);
        CPPUNIT_ASSERT(y == z);}

    // ----------
    // ==
    // ----------
    void test_equals_1 () {
        const C x(10, 5);
	    const C y(10, 5);
        CPPUNIT_ASSERT(x == y);}

    void test_equals_2 () {
        C x(5);
	    for (int i = 0; i < 5; i++)
	         x.push_back(i);
	    C y(5);
	    for (int i = 0; i < 5; i++)
	        y.push_back(i);
        CPPUNIT_ASSERT(x == y);}

    void test_equals_3 () {
        C x(5);
        for (int i = 0; i < 5; i++)
             x.push_front(i);
        C y(5);
        for (int i = 0; i < 5; i++)
             y.push_front(i);
        CPPUNIT_ASSERT(x == y);}

    void test_equals_4 () {
        const C x(10, 5);
	    const C y(x);
        CPPUNIT_ASSERT(x == y);}

    // ----------
    // push_front
    // ----------
    void test_push_front_1 () {
        C x;
	    x.push_front(5);
        CPPUNIT_ASSERT(x.front() == 5);
	    x.push_front(9);
        CPPUNIT_ASSERT(x.front() == 9);
	    x.push_front(12);
        CPPUNIT_ASSERT(x.front() == 12);}

    void test_push_front_2 () {
        C x(5);
	    x.push_front(5);
        CPPUNIT_ASSERT(x.front() == 5);
	    x.push_front(9);
        CPPUNIT_ASSERT(x.front() == 9);
	    x.push_front(12);
        CPPUNIT_ASSERT(x.front() == 12);}

    void test_push_front_3 () {
        C x(100, 5);
	    x.push_front(5);
        CPPUNIT_ASSERT(x.front() == 5);
	    x.push_front(9);
        CPPUNIT_ASSERT(x.front() == 9);
	    x.push_front(12);
        CPPUNIT_ASSERT(x.front() == 12);}

    // ---------
    // push_back
    // ---------
    void test_push_back_1 () {
        C x;
	    x.push_back(5);
        CPPUNIT_ASSERT(x.back() == 5);
	    x.push_back(9);
        CPPUNIT_ASSERT(x.back() == 9);
	    x.push_back(12);
        CPPUNIT_ASSERT(x.back() == 12);}

    void test_push_back_2 () {
        C x(5);
	    x.push_back(5);
        CPPUNIT_ASSERT(x.back() == 5);
	    x.push_back(9);
        CPPUNIT_ASSERT(x.back() == 9);
	    x.push_back(12);
        CPPUNIT_ASSERT(x.back() == 12);}

    void test_push_back_3 () {
        C x(100, 5);
	    x.push_back(5);
        CPPUNIT_ASSERT(x.back() == 5);
	    x.push_back(9);
        CPPUNIT_ASSERT(x.back() == 9);
	    x.push_back(12);
        CPPUNIT_ASSERT(x.back() == 12);}

    // ---------
    // pop_front
    // ---------
    void test_pop_front_1 () {
        C x;
	    x.push_front(5);
	    x.push_front(9);
	    x.push_front(12);
	    x.pop_front();
        CPPUNIT_ASSERT(x.front() == 9);}

    void test_pop_front_2 () {
        C x(5);
	    x.push_front(5);
	    x.push_front(9);
	    x.push_front(12);
	    x.pop_front();
        CPPUNIT_ASSERT(x.front() == 9);}

    void test_pop_front_3 () {
        C x(100, 5);
	    x.push_front(5);
	    x.push_front(9);
	    x.push_front(12);
	    x.pop_front();
        CPPUNIT_ASSERT(x.front() == 9);}

    // --------
    // pop_back
    // --------
    void test_pop_back_1 () {
        C x;
	    x.push_back(5);
	    x.push_back(9);
	    x.push_back(12);
	    x.pop_back();
        CPPUNIT_ASSERT(x.back() == 9);}

    void test_pop_back_2 () {
        C x(11);
	    x.push_back(5);
	    x.push_back(9);
	    x.push_back(12);
	    x.pop_back();
        CPPUNIT_ASSERT(x.back() == 9);}

    void test_pop_back_3 () {
        C x(123, 5);
	    x.push_back(5);
	    x.push_back(9);
	    x.push_back(12);
	    x.pop_back();
        CPPUNIT_ASSERT(x.back() == 9);}

    // -----
    // front
    // -----
    void test_front_1 () {
        C x;
        x.push_back(-1);
        x.push_back(9);
        x.push_back(8);
        CPPUNIT_ASSERT(x.front() == -1);
        x.push_front(10);
        CPPUNIT_ASSERT(x.front() == 10);
        x.pop_front();
        CPPUNIT_ASSERT(x.front() == -1);}

    void test_front_2 () {
        C x(10);
        x.push_back(99);
        x.push_front(50);
        x.push_back(-9);
        x.push_back(-88);
        CPPUNIT_ASSERT(x.front() == 50);
        x.push_front(190);
        CPPUNIT_ASSERT(x.front() == 190);
	    x.push_front(-7);
        CPPUNIT_ASSERT(x.front() == -7);}

    void test_front_3 () {
        C x(100);
        x.push_front(87);
        x.push_front(-1);
        x.push_front(23);
        CPPUNIT_ASSERT(x.front() == 23);
        x.pop_front();
        CPPUNIT_ASSERT(x.front() == -1);
	    x.pop_front();
        CPPUNIT_ASSERT(x.front() == 87);}

    // -----
    // back
    // -----
    void test_back_1 () {
        C x;
        x.push_back(-1);
        x.push_back(9);
        x.push_back(8);
        CPPUNIT_ASSERT(x.back() == 8);
        x.push_back(10);
        CPPUNIT_ASSERT(x.back() == 10);
	    x.pop_back();
        CPPUNIT_ASSERT(x.back() == 8);}

    void test_back_2 () {
        C x(10);
        x.push_back(99);
        x.push_front(50);
        x.push_back(-9);
        x.push_back(-88);
        CPPUNIT_ASSERT(x.back() == -88);
        x.push_back(190);
        CPPUNIT_ASSERT(x.back() == 190);
	    x.push_back(-7);
        CPPUNIT_ASSERT(x.back() == -7);}

    void test_back_3 () {
        C x(100);
        x.push_back(87);
        x.push_back(-1);
        x.push_back(23);
        CPPUNIT_ASSERT(x.back() == 23);
        x.pop_back();
        CPPUNIT_ASSERT(x.back() == -1);
	    x.pop_back();
        CPPUNIT_ASSERT(x.back() == 87);}

    // -----------
    // insert
    // -----------
    void test_insert_1 () {
        C x(100, 10);
        CPPUNIT_ASSERT(x[50] == 10);	
	x.insert(x.begin() + 50, -1); //insert at 50 5
        CPPUNIT_ASSERT(x[50] == -1);

        CPPUNIT_ASSERT(x.size() == 101);}

    void test_insert_2 () {
        C x;
	x.push_back(1);
	x.push_back(2);
	x.push_back(3);
        CPPUNIT_ASSERT(x[0] == 1);
        x.insert(x.begin(), -1);
        CPPUNIT_ASSERT(x[0] == -1);
        CPPUNIT_ASSERT(x[3] == 3);
	x.insert(x.begin() + 4, -1);
        CPPUNIT_ASSERT(x[4] == -1);
        CPPUNIT_ASSERT(x.size() == 5);}

    void test_insert_3 () {
        C x;
	x.push_back(1);
	x.push_back(2);
	x.push_back(3);
	x.insert(x.begin() + 1, -1); // insert -1 as the second element
        CPPUNIT_ASSERT(x[0] == 1);
        CPPUNIT_ASSERT(x[1] == -1);
        CPPUNIT_ASSERT(x[2] == 2);
        CPPUNIT_ASSERT(x[3] == 3);
        CPPUNIT_ASSERT(x.size() == 4);}

    // -----------
    // erase
    // -----------
    void test_erase_1 () {
        C x;
	for (int i = 0; i < 10; i++)
	    x.push_back(i);
        CPPUNIT_ASSERT(x[5] == 5);
        CPPUNIT_ASSERT(x.size() == 10);
	x.erase(x.begin() + 5); //erases 6th element
        CPPUNIT_ASSERT(x[5] == 6);
        CPPUNIT_ASSERT(x.size() == 9);}

    void test_erase_2 () {
        C x;
	for (int i = 0; i < 10; i++)
	    x.push_back(i);
        CPPUNIT_ASSERT(x[9] == 9);
        CPPUNIT_ASSERT(x.size() == 10);
	x.erase(x.begin() + 9); //erases 9th element
        CPPUNIT_ASSERT(x[8] == 8);
        CPPUNIT_ASSERT(x.size() == 9);}

    void test_erase_3 () {
        C x;
	for (int i = 0; i < 10; i++)
	    x.push_back(i);
        CPPUNIT_ASSERT(x[0] == 0);
        CPPUNIT_ASSERT(x.size() == 10);
	x.erase(x.begin()); //erases 9th element
        CPPUNIT_ASSERT(x[0] == 1);
        CPPUNIT_ASSERT(x.size() == 9);}

    // -----------
    // [] operator
    // -----------
    void test_operator_index_1 () {
        C x;
	    for (int i = 0; i < 10; i++)
	        x.push_back(i);
	    for (int i = 0; i < 10; i++)
            CPPUNIT_ASSERT(x[i] == i);
        CPPUNIT_ASSERT(x.size() == 10);}

    void test_operator_index_2 () {
        C x(20, 1);
        CPPUNIT_ASSERT(x[19] == 1);
        CPPUNIT_ASSERT(x[0] == 1);
        CPPUNIT_ASSERT(x.size() == 20);}


    void test_operator_index_3 () {
        C x;
	    x.push_back(10);
	    x.push_back(1);
	    x.push_back(-23);
        CPPUNIT_ASSERT(x[0] == 10);
        CPPUNIT_ASSERT(x[1] == 1);
        CPPUNIT_ASSERT(x[2] == -23);
        CPPUNIT_ASSERT(x.size() == 3);}

    // -----------
    // at
    // -----------
    void test_at_1 () {
        C x;
        for (int i = 0; i < 10; i++)
            x.push_back(i);
        for (int i = 0; i < 10; i++)
            CPPUNIT_ASSERT(x.at(i) == i);
        CPPUNIT_ASSERT(x.size() == 10);}

    void test_at_2 () {
        C x(20, 1);
        CPPUNIT_ASSERT(x.at(19) == 1);
        CPPUNIT_ASSERT(x.at(0) == 1);
        CPPUNIT_ASSERT(x.size() == 20);}


    void test_at_3 () {
        C x;
	    x.push_back(10);
	    x.push_back(1);
	    x.push_back(-23);
        CPPUNIT_ASSERT(x.at(0) == 10);
        CPPUNIT_ASSERT(x.at(1) == 1);
        CPPUNIT_ASSERT(x.at(2) == -23);
        CPPUNIT_ASSERT(x.size() == 3);}

    // -----------
    // clear
    // -----------
    void test_clear_1 () {
        C x;
	    for (int i = 0; i < 10; i++)
	    x.push_back(i);
        CPPUNIT_ASSERT(x.size() == 10);
	    x.clear();
        CPPUNIT_ASSERT(x.size() == 0);}

    void test_clear_2 () {
        C x(199);
        CPPUNIT_ASSERT(x.size() == 199);
	    x.clear();
        CPPUNIT_ASSERT(x.size() == 0);}

    void test_clear_3 () {
        C x(20, 33);
        CPPUNIT_ASSERT(x.size() == 20);
	    x.clear();
        CPPUNIT_ASSERT(x.size() == 0);}

    // -----
    // empty
    // -----
    void test_empty_1 () {
        C x;
        CPPUNIT_ASSERT(x.empty() == true);
        x.push_back(1);
        CPPUNIT_ASSERT(x.empty() == false);
        //x.erase(x.begin());
        //CPPUNIT_ASSERT(x.empty() == true);
        x.push_front(9);
        CPPUNIT_ASSERT(x.empty() == false);
        CPPUNIT_ASSERT(x.size() == 2);}

    void test_empty_2 () {
        C x(10);
        CPPUNIT_ASSERT(x.empty() == false);
        x.clear();
        CPPUNIT_ASSERT(x.empty() == true);
        CPPUNIT_ASSERT(x.size() == 0);}

    void test_empty_3 () {
        const C x(100);
	    CPPUNIT_ASSERT(x.empty() == false);
        CPPUNIT_ASSERT(x.size() == 100);
	    const C y(x);
	    CPPUNIT_ASSERT(y.empty() == false);
        CPPUNIT_ASSERT(y.size() == 100);}

    // ------
    // resize
    // ------
    void test_resize_1 (){
        C x(200);
        CPPUNIT_ASSERT(x.size() == 200);
        x.resize(100);
        CPPUNIT_ASSERT(x.size() == 100);}

    void test_resize_2 (){
        C x(200);
        CPPUNIT_ASSERT(x.size() == 200);
        x.resize(300);
        CPPUNIT_ASSERT(x.size() == 300);}

    void test_resize_3 (){
        C x;
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.push_back(4);
        x.push_back(5);
        CPPUNIT_ASSERT(x.size() == 5);
        x.resize(3);
        CPPUNIT_ASSERT(x[0] == 1);
        CPPUNIT_ASSERT(x[1] == 2);
        CPPUNIT_ASSERT(x[2] == 3);
        CPPUNIT_ASSERT(x.size() == 3);}

    void test_resize_4 (){
        C x;
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.push_back(4);
        x.push_back(5);
        CPPUNIT_ASSERT(x.size() == 5);
        x.resize(7);
        CPPUNIT_ASSERT(x[4] == 5);
        CPPUNIT_ASSERT(x[5] == 0);
        CPPUNIT_ASSERT(x[6] == 0);
        CPPUNIT_ASSERT(x.size() == 7);}

    void test_resize_5 (){
        C x;
        CPPUNIT_ASSERT(x.size() == 0);
        x.resize(50);
        CPPUNIT_ASSERT(x.size() == 50);}

    // ----
    // swap
    // ----

    void test_swap_1 (){
        C x(3, 100);
        C y(5, 200);
        unsigned old_xSize = x.size();
        unsigned old_ySize = y.size();
        for (unsigned i = 0; i < x.size(); i++)
            CPPUNIT_ASSERT(x[i] == 100);
        for (unsigned i = 0; i < y.size(); i++)
            CPPUNIT_ASSERT(y[i] == 200);
        x.swap(y);
        for (unsigned i = 0; i < x.size(); i++)
            CPPUNIT_ASSERT(x[i] == 200);
        for (unsigned i = 0; i < y.size(); i++)
            CPPUNIT_ASSERT(y[i] == 100);
        CPPUNIT_ASSERT(x.size() == old_ySize);
        CPPUNIT_ASSERT(y.size() == old_xSize);}

    void test_swap_2 (){
        C x(100, 2);
        C y(9, 17);
        unsigned old_xSize = x.size();
        unsigned old_ySize = y.size();
        for (unsigned i = 0; i < x.size(); i++)
            CPPUNIT_ASSERT(x[i] == 2);
        for (unsigned i = 0; i < y.size(); i++)
            CPPUNIT_ASSERT(y[i] == 17);
        x.swap(y);
        for (unsigned i = 0; i < x.size(); i++)
            CPPUNIT_ASSERT(x[i] == 17);
        for (unsigned i = 0; i < y.size(); i++)
            CPPUNIT_ASSERT(y[i] == 2);
        CPPUNIT_ASSERT(x.size() == old_ySize);
        CPPUNIT_ASSERT(y.size() == old_xSize);}

    void test_swap_3 (){
        C x(66, 0);
        C y(72, 9);
        unsigned old_xSize = x.size();
        unsigned old_ySize = y.size();
        for (unsigned i = 0; i < x.size(); i++)
            CPPUNIT_ASSERT(x[i] == 0);
        for (unsigned i = 0; i < y.size(); i++)
            CPPUNIT_ASSERT(y[i] == 9);
        x.swap(y);
        for (unsigned i = 0; i < x.size(); i++)
            CPPUNIT_ASSERT(x[i] == 9);
        for (unsigned i = 0; i < y.size(); i++)
            CPPUNIT_ASSERT(y[i] == 0);
        CPPUNIT_ASSERT(x.size() == old_ySize);
        CPPUNIT_ASSERT(y.size() == old_xSize);}

    void test_swap_4 (){
        C x(88, -23);
        C y(10, 17);
        unsigned old_xSize = x.size();
        unsigned old_ySize = y.size();
        for (unsigned i = 0; i < x.size(); i++)
            CPPUNIT_ASSERT(x[i] == -23);
        for (unsigned i = 0; i < y.size(); i++)
            CPPUNIT_ASSERT(y[i] == 17);
        x.swap(y);
        for (unsigned i = 0; i < x.size(); i++)
            CPPUNIT_ASSERT(x[i] == 17);
        for (unsigned i = 0; i < y.size(); i++)
            CPPUNIT_ASSERT(y[i] == -23);
        CPPUNIT_ASSERT(x.size() == old_ySize);
        CPPUNIT_ASSERT(y.size() == old_xSize);}

    //begin
    void test_begin_1 (){
        C x;
        x.push_back(20);
        x.push_back(15);
        x.push_back(32);
        CPPUNIT_ASSERT(*x.begin() == 20);
        x.pop_front();
        CPPUNIT_ASSERT(*x.begin() == 15);}

    void test_begin_2 (){
        C x;
        x.push_back(-10);
        x.push_back(-5);
        x.push_back(8);
        CPPUNIT_ASSERT(*x.begin() == -10);
        x.pop_front();
        CPPUNIT_ASSERT(*x.begin() != -10);
        CPPUNIT_ASSERT(*x.begin() == -5);
        x.pop_front();
        CPPUNIT_ASSERT(*x.begin() == 8);}

    void test_begin_3 (){
        C x;
        x.push_front(20);
        x.push_front(15);
        x.push_front(32);
        CPPUNIT_ASSERT(*x.begin() == 32);
        x.pop_front();
        x.pop_back();
        CPPUNIT_ASSERT(x.begin() + 1 == x.end());}

    //end
    void test_end_1 (){
        C x;
        x.push_back(20);
        x.push_back(15);
        x.push_back(32);
        CPPUNIT_ASSERT(x.begin() + x.size() == x.end());
        x.pop_front();
        CPPUNIT_ASSERT(x.begin() + x.size() == x.end());}

    void test_end_2 (){
        C x;
        x.push_back(-19);
        x.push_back(21);
        CPPUNIT_ASSERT(x.begin() + x.size() == x.end());
        x.pop_front();
        CPPUNIT_ASSERT(x.begin() + x.size() == x.end());
        x.pop_front();
        CPPUNIT_ASSERT(x.begin() == x.end());}

    void test_end_3 (){
        C x;
        x.push_back(20);
        x.push_back(15);
        x.push_back(32);
        CPPUNIT_ASSERT(x.begin() + x.size() == x.end());
        x.pop_front();
        x.pop_back();
        CPPUNIT_ASSERT(x.begin() + x.size() == x.end());
        CPPUNIT_ASSERT(x.size() == 1);	}


    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDeque);

    //it equal
    CPPUNIT_TEST(test_it_equal_1);
    CPPUNIT_TEST(test_it_equal_2);
    CPPUNIT_TEST(test_it_equal_3);

    //it *
    CPPUNIT_TEST(test_it_opSTAR_1);
    CPPUNIT_TEST(test_it_opSTAR_2);
    CPPUNIT_TEST(test_it_opSTAR_3);

    //it++ and ++it
    CPPUNIT_TEST(test_it_plusPlus_1);
    CPPUNIT_TEST(test_it_plusPlus_2);
    CPPUNIT_TEST(test_it_plusPlus_3);

    //it-- and --it
    CPPUNIT_TEST(test_it_minusMinus_1);
    CPPUNIT_TEST(test_it_minusMinus_2);
    CPPUNIT_TEST(test_it_minusMinus_3);

    //it -
    CPPUNIT_TEST(test_it_minus_1);
    CPPUNIT_TEST(test_it_minus_2);
    CPPUNIT_TEST(test_it_minus_3);

    //it +
    CPPUNIT_TEST(test_it_plus_1);
    CPPUNIT_TEST(test_it_plus_2);
    CPPUNIT_TEST(test_it_plus_3);

    //size
    CPPUNIT_TEST(test_size_1);
    CPPUNIT_TEST(test_size_2);
    CPPUNIT_TEST(test_size_3);
    CPPUNIT_TEST(test_size_4);
    CPPUNIT_TEST(test_size_5);

    //constructors
    CPPUNIT_TEST(test_constructors_1);
    CPPUNIT_TEST(test_constructors_2);
    CPPUNIT_TEST(test_constructors_3);
    CPPUNIT_TEST(test_constructors_4);
    CPPUNIT_TEST(test_constructors_5);
    
    //destructor
    CPPUNIT_TEST(test_deconstructors_1);

    //assign
    CPPUNIT_TEST(test_assign_1);
    CPPUNIT_TEST(test_assign_2);
    CPPUNIT_TEST(test_assign_3);
 
    //==
    CPPUNIT_TEST(test_equals_1);
    CPPUNIT_TEST(test_equals_2);
    CPPUNIT_TEST(test_equals_3);
    CPPUNIT_TEST(test_equals_4);

    //push_front
    CPPUNIT_TEST(test_push_front_1);
    CPPUNIT_TEST(test_push_front_2);
    CPPUNIT_TEST(test_push_front_3);

    //push_back
    CPPUNIT_TEST(test_push_back_1);
    CPPUNIT_TEST(test_push_back_2);
    CPPUNIT_TEST(test_push_back_3);

    //pop_front
    CPPUNIT_TEST(test_pop_front_1);
    CPPUNIT_TEST(test_pop_front_2);
    CPPUNIT_TEST(test_pop_front_3);

    //pop_back
    CPPUNIT_TEST(test_pop_back_1);
    CPPUNIT_TEST(test_pop_back_2);
    CPPUNIT_TEST(test_pop_back_3);

    //front
    CPPUNIT_TEST(test_front_1);
    CPPUNIT_TEST(test_front_2);
    CPPUNIT_TEST(test_front_3);

    //back
    CPPUNIT_TEST(test_back_1);
    CPPUNIT_TEST(test_back_2);
    CPPUNIT_TEST(test_back_3);
/*
    //insert
    CPPUNIT_TEST(test_insert_1);
    CPPUNIT_TEST(test_insert_2);
    CPPUNIT_TEST(test_insert_3);

    //erase
    CPPUNIT_TEST(test_erase_1);
    CPPUNIT_TEST(test_erase_2);
    CPPUNIT_TEST(test_erase_3);
*/
    //operator[]
    CPPUNIT_TEST(test_operator_index_1);
    CPPUNIT_TEST(test_operator_index_2);
    CPPUNIT_TEST(test_operator_index_3);

    //at
    CPPUNIT_TEST(test_at_1);
    CPPUNIT_TEST(test_at_2);
    CPPUNIT_TEST(test_at_3);

    //clear
    CPPUNIT_TEST(test_clear_1);
    CPPUNIT_TEST(test_clear_2);
    CPPUNIT_TEST(test_clear_3);

    //empty
    CPPUNIT_TEST(test_empty_1);
    CPPUNIT_TEST(test_empty_2);
    CPPUNIT_TEST(test_empty_3);

    //resize
    CPPUNIT_TEST(test_resize_1);
    CPPUNIT_TEST(test_resize_2);
    CPPUNIT_TEST(test_resize_3);
    CPPUNIT_TEST(test_resize_4);
    CPPUNIT_TEST(test_resize_5);

    //swap
    CPPUNIT_TEST(test_swap_1);
    CPPUNIT_TEST(test_swap_2);
    CPPUNIT_TEST(test_swap_3);
    CPPUNIT_TEST(test_swap_4);

    //begin
    CPPUNIT_TEST(test_begin_1);
    CPPUNIT_TEST(test_begin_2);
    CPPUNIT_TEST(test_begin_3);

    //end
    CPPUNIT_TEST(test_end_1);
    CPPUNIT_TEST(test_end_2);
    CPPUNIT_TEST(test_end_3);

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
    //tr.addTest(TestDeque<   deque<int> >::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
