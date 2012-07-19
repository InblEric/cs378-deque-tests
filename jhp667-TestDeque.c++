// ----------------------------
// Joe Peacock
// UT EID: jhp667
// CS 378 Project 4 - Deque
// 7/16/2012
//
// BASED ON:
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
    // ----
    // Size
    // ----

    void test_size1 () {
        const C x;
        CPPUNIT_ASSERT(x.size() == 0);}
        
	void test_size2 () {
        const C x(73, 0);
        CPPUNIT_ASSERT(x.size() == 73);}
	
	void test_size3 () {
        C x(76, 12);
        x.push_front(13);
        CPPUNIT_ASSERT(x.size() == 77);}
        
        
	void test_size4 () {
        C x(76, 12);
        x.push_back(13);
        CPPUNIT_ASSERT(x.size() == 77);}
        
        
        
    // ----
    // Equality
    // ----

    void test_equal1 () {
        const C x;
        const C y;
        CPPUNIT_ASSERT(x == y);}
	
	void test_equal2 () {
        const C x;
        const C y(x);
        CPPUNIT_ASSERT(x == y);}
        
	void test_equal3 () {
        C x;
        C y;
        x.push_front(5);
        y.push_back(5);
        CPPUNIT_ASSERT(x == y);}
        
        
	// ----
    // Less Than
    // ----

    void test_less1 () {
        const C x;
        const C y(11,2);
        CPPUNIT_ASSERT(x < y);}
	
	void test_less2 () {
        const C x;
        C y(x);
        x.push_back(5);
        CPPUNIT_ASSERT(y < x);}
        
	void test_less3 () {
        C x;
        C y;
        x.push_front(5);
        y.push_back(5);
        x.push_back(4);
        CPPUNIT_ASSERT(x == y);}
            
        
	// ----
    // Constructors
    // ----

    void test_cons1 () {
        const C x;
        CPPUNIT_ASSERT(x.size() == 0);}
        
        
    void test_cons2 () {
        const C x(56,5);
        CPPUNIT_ASSERT(x.size() ==56);
        CPPUNIT_ASSERT(x.at(52) ==5);
	}
        
        
    void test_cons3 () {
        C x(56,5);
        C y(x);
        
        CPPUNIT_ASSERT(x == y);
        CPPUNIT_ASSERT(x.at(40) == y.at(40));
        y.pop_front();
        CPPUNIT_ASSERT(x != y);
        CPPUNIT_ASSERT(y.size() == 55);
        CPPUNIT_ASSERT(x.size() == 56);
	}
	
	// ----
    // Assignment
    // ----

    void test_assign1 () {
        const C x(26,44);
        const C y = x;
        CPPUNIT_ASSERT(x == y);
        CPPUNIT_ASSERT(x.at(13) == y.at(13));
        CPPUNIT_ASSERT(x.size() == y.size());
        
	}
        
	void test_assign2 () {
        C x(26,44);
        C y = x;
        CPPUNIT_ASSERT(x == y);
        x.push_front(5);
        CPPUNIT_ASSERT(x.at(0) == 5);
        CPPUNIT_ASSERT(y.at(0) == 44);
        CPPUNIT_ASSERT(x.size() == 27);
        CPPUNIT_ASSERT(y.size() == 26);
        
	}
	
	void test_assign3 () {
			
		C y;
		
		{
			C x(26,44);
			y = x;
		}
		
        CPPUNIT_ASSERT(y.size()==26);
        
	}
    
        
    
    //------------
    // Iterators + begin and end 
    //------------    
        
    void test_iter1(){
		C x(56,5);
		typename C:: iterator i = x.begin();
		
		CPPUNIT_ASSERT(x.begin() == i);
		CPPUNIT_ASSERT(i+1 == x.begin()+1);
		CPPUNIT_ASSERT(++i == x.begin()+1);
		CPPUNIT_ASSERT(i-1 == x.begin());
		CPPUNIT_ASSERT(--i == x.begin());
		CPPUNIT_ASSERT(i++ == x.begin());
		CPPUNIT_ASSERT(i-- == x.begin()+1);
		CPPUNIT_ASSERT(i == x.begin());
	}
	
	void test_iter2(){
		C x(56,5);
		typename C:: iterator i = x.begin();
		typename C:: iterator j = i+40;
		
		CPPUNIT_ASSERT(i+40 == j);
		CPPUNIT_ASSERT(i == j-40);
	}
	
	void test_iter3(){
		C x(56,5);
		typename C:: iterator i = x.begin();
		typename C:: iterator j = i+40;
		typename C:: iterator e = x.end();
		
		CPPUNIT_ASSERT(e-56 == i);
		CPPUNIT_ASSERT(i+56 == e);
		CPPUNIT_ASSERT(j+16 == e);
		CPPUNIT_ASSERT(j == e-16);
	}
	
	void test_iter4(){
		C x(56,5);
		C y(56,5);
		C z(x);
		typename C:: iterator i = x.begin();
		typename C:: iterator j = y.begin();
		typename C:: iterator k = z.begin();
		
		CPPUNIT_ASSERT(i != j);
		CPPUNIT_ASSERT(i != k);
		CPPUNIT_ASSERT(j != k);
		
	}    
        
        
    //----------------
    // Const Iterators + const begin and end
    //-----------------    
        
	void test_const_iter1(){
		const C x(56,5);
		typename C:: const_iterator i = x.begin();
		
		CPPUNIT_ASSERT(x.begin() == i);
		CPPUNIT_ASSERT(i+1 == x.begin()+1);
		CPPUNIT_ASSERT(++i == x.begin()+1);
		CPPUNIT_ASSERT(i-1 == x.begin());
		CPPUNIT_ASSERT(--i == x.begin());
		CPPUNIT_ASSERT(i++ == x.begin());
		CPPUNIT_ASSERT(i-- == x.begin()+1);
		CPPUNIT_ASSERT(i == x.begin());
		
	}
	
	void test_const_iter2(){
		const C x(56,5);
		typename C:: const_iterator i = x.begin();
		typename C:: const_iterator j = i+40;
		
		CPPUNIT_ASSERT(i+40 == j);
		CPPUNIT_ASSERT(i == j-40);
	}
	
	void test_const_iter3(){
		const C x(56,5);
		typename C:: const_iterator i = x.begin();
		typename C:: const_iterator j = i+40;
		typename C:: const_iterator e = x.end();
		
		CPPUNIT_ASSERT(e-56 == i);
		CPPUNIT_ASSERT(i+56 == e);
		CPPUNIT_ASSERT(j+16 == e);
		CPPUNIT_ASSERT(j == e-16);
	}
	
	void test_const_iter4(){
		const C x(56,5);
		const C y(56,5);
		const C z(x);
		typename C:: const_iterator i = x.begin();
		typename C:: const_iterator j = y.begin();
		typename C:: const_iterator k = z.begin();
		
		CPPUNIT_ASSERT(i != j);
		CPPUNIT_ASSERT(i != k);
		CPPUNIT_ASSERT(j != k);
		
	}
	
	// ----
    // At
    // ----

    void test_at1 () {
        const C x(26,44);
        CPPUNIT_ASSERT(x.at(13) == 44);
	}
	
	void test_at2 () {
        C x(26,44);
        x.push_front(14);
        CPPUNIT_ASSERT(x.at(0) == 14);
        CPPUNIT_ASSERT(x.at(1) == 44);
	}
	
	void test_at3 () {
        C x(26,44);
        x.push_back(16);
        CPPUNIT_ASSERT(x.at(26) == 16);
        CPPUNIT_ASSERT(x.at(25) == 44);
	}


	// ----
    // Index []
    // ----

    void test_index1 () {
        const C x(26,44);
        CPPUNIT_ASSERT(x.at(13) == 44);
	}
	
	void test_index2 () {
        C x(26,44);
        x.push_front(14);
        CPPUNIT_ASSERT(x.at(0) == 14);
        CPPUNIT_ASSERT(x.at(1) == 44);
	}
	
	void test_index3 () {
        C x(26,44);
        x.push_back(16);
        CPPUNIT_ASSERT(x.at(26) == 16);
        CPPUNIT_ASSERT(x.at(25) == 44);
	}
	
	// ----
    // Front
    // ----

    void test_front1 () {
        const C x(26,44);
        CPPUNIT_ASSERT(x.front() == 44);
	}
	
	void test_front2 () {
        C x(26,44);
        x.push_front(14);
        CPPUNIT_ASSERT(x.front() == 14);
        x.pop_front();
        CPPUNIT_ASSERT(x.front() == 44);
	}
	
	void test_front3 () {
        C x(26,44);
        x.front() = 3;
        CPPUNIT_ASSERT(x[0] == 3);
	}


	// ----
    // Back
    // ----

    void test_back1 () {
        const C x(26,44);
        CPPUNIT_ASSERT(x.back() == 44);
	}
	
	void test_back2 () {
        C x(26,44);
        x.push_back(14);
        CPPUNIT_ASSERT(x.back() == 14);
        x.pop_back();
        CPPUNIT_ASSERT(x.back() == 44);
	}
	
	void test_back3 () {
        C x(26,44);
        x.back() = 3;
        CPPUNIT_ASSERT(x[25] == 3);
	}
	
	
	// ----
    // Push_Front and Pop_front
    // ----

    void test_push_front1 () {
        C x(26,44);
        x.push_front(14);
        CPPUNIT_ASSERT(x.front() == 14);
        x.pop_front();
        CPPUNIT_ASSERT(x.front() == 44);
	}
	
	void test_push_front2 () {
        C x(26,44);
        x.push_front(14);
        x.push_front(12);
        CPPUNIT_ASSERT(x.front() == 12);
        x.pop_front();
        CPPUNIT_ASSERT(x.front() == 14);
	}
	
	void test_push_front3 () {
        C x(26,44);
        for (int i = 0; i <125; ++i){
			x.push_front(7);
		}
		CPPUNIT_ASSERT(x.size() == 151);
        for (int i = 0; i <125; ++i){
			CPPUNIT_ASSERT(x.front() == 7);
			x.pop_front();
		}
		CPPUNIT_ASSERT(x.size() == 26);
		CPPUNIT_ASSERT(x.front() == 44);
	}
	
	void test_push_front4 () {
        C x;
        for (int i = 0; i <125; ++i){
			x.push_front(7);
		}
		CPPUNIT_ASSERT(x.size() == 125);
        for (int i = 0; i <125; ++i){
			CPPUNIT_ASSERT(x.front() == 7);
			x.pop_front();
		}
		CPPUNIT_ASSERT(x.size() == 0);
	}
	
	
	// ----
    // Push_Back and Pop_Back
    // ----

    void test_push_back1 () {
        C x(26,44);
        x.push_back(14);
        CPPUNIT_ASSERT(x.back() == 14);
        x.pop_back();
        CPPUNIT_ASSERT(x.back() == 44);
	}
	
	void test_push_back2 () {
        C x(26,44);
        x.push_back(14);
        x.push_back(12);
        CPPUNIT_ASSERT(x.back() == 12);
        x.pop_back();
        CPPUNIT_ASSERT(x.back() == 14);
	}
	
	void test_push_back3 () {
        C x(26,44);
        for (int i = 0; i <125; ++i){
			x.push_back(7);
		}
		CPPUNIT_ASSERT(x.size() == 151);
        for (int i = 0; i <125; ++i){
			CPPUNIT_ASSERT(x.back() == 7);
			x.pop_back();
		}
		CPPUNIT_ASSERT(x.size() == 26);
		CPPUNIT_ASSERT(x.back() == 44);
	}
	
	void test_push_back4 () {
        C x;
        for (int i = 0; i <125; ++i){
			x.push_back(7);
		}
		CPPUNIT_ASSERT(x.size() == 125);
        for (int i = 0; i <125; ++i){
			CPPUNIT_ASSERT(x.back() == 7);
			x.pop_back();
		}
		CPPUNIT_ASSERT(x.size() == 0);
	}
	
	
	// ----
    // Insert
    // ----

    void test_insert1 () {
        C x(26,44);
        x.insert(x.begin()+5, 13);
        
        CPPUNIT_ASSERT(x[5] == 13);
        
        CPPUNIT_ASSERT(x.front() == 44);
        CPPUNIT_ASSERT(x.back() == 44);
        CPPUNIT_ASSERT(x.size() == 27);
	}
	
	void test_insert2 () {
        C x(26,44);
        typename C:: iterator i =  x.insert(x.begin(), 12);
        
        CPPUNIT_ASSERT(x.begin() == i);
        CPPUNIT_ASSERT(x.size() == 27);
        CPPUNIT_ASSERT(x.front() == 12);
        CPPUNIT_ASSERT(x.back() == 44);
	}
	
	void test_insert3 () {
        C x(26,44);
        typename C:: iterator i = x.insert(x.end(), 12);
        
        CPPUNIT_ASSERT(x.end()-1 == i);
        CPPUNIT_ASSERT(x.size() == 27);
        CPPUNIT_ASSERT(x.front() == 44);
        CPPUNIT_ASSERT(x.back() == 12);
	}
	
	
	// ----
    // Erase
    // ----

    void test_erase1 () {
        C x(26,44);
        x.insert(x.begin()+5, 13);
        
        CPPUNIT_ASSERT(x[5] == 13);
        CPPUNIT_ASSERT(x.size() == 27);
        
        x.erase(x.begin()+5);
        
        CPPUNIT_ASSERT(x[5] == 44);
        CPPUNIT_ASSERT(x.size() == 26);
        CPPUNIT_ASSERT(x.front() == 44);
        CPPUNIT_ASSERT(x.back() == 44);
	}
	
	void test_erase2 () {
        C x(26,44);
        x.insert(x.begin(), 13);
        typename C:: iterator i =  x.erase(x.begin());
        
        CPPUNIT_ASSERT(x.begin() == i);
        CPPUNIT_ASSERT(x.size() == 26);
        CPPUNIT_ASSERT(x.front() == 44);
        CPPUNIT_ASSERT(x.back() == 44);
	}
	
	void test_erase3 () {
        C x(26,44);
        x.insert(x.end(), 13);
        typename C:: iterator i = x.erase(x.end()-1);
        
        CPPUNIT_ASSERT(x.end() == i);
        CPPUNIT_ASSERT(x.size() == 26);
        CPPUNIT_ASSERT(x.front() == 44);
        CPPUNIT_ASSERT(x.back() == 44);
	}
	
	
	
	// ----
    // Resize
    // ----

    void test_resize1 () {
        C x(26,44);
        x.push_back(13);
        
        CPPUNIT_ASSERT(x.back() == 13);
        CPPUNIT_ASSERT(x.size() == 27);
        
        x.resize(26, 12);
        
        CPPUNIT_ASSERT(x[5] == 44);
        CPPUNIT_ASSERT(x.size() == 26);
        CPPUNIT_ASSERT(x.front() == 44);
        CPPUNIT_ASSERT(x.back() == 44);
	}
	
	void test_resize2 () {
        C x(26,44);
        x.resize(28, 11);
        
        CPPUNIT_ASSERT(x.front() == 44);
        CPPUNIT_ASSERT(x[25] == 44);
        CPPUNIT_ASSERT(x[26] == 11);
        CPPUNIT_ASSERT(x[27] == 11);
        CPPUNIT_ASSERT(x.size() == 28);
	}
	
	void test_resize3 () {
        C x(26,44);
        x.resize(26, 11);
        
        CPPUNIT_ASSERT(x.front() == 44);
        CPPUNIT_ASSERT(x.back() == 44);
        CPPUNIT_ASSERT(x.size() == 26);
	}
	
	
	
	// ----
    // Swap
    // ----

    void test_swap1 () {
        C x(26,44);
        C y(13, 57);
        
        x.swap(y);
        
        CPPUNIT_ASSERT(x.size() == 13);
        CPPUNIT_ASSERT(y.size() == 26);
	}
	
	void test_swap2 () {
        C x(26,44);
        C y;
        
        x.swap(y);
        
        CPPUNIT_ASSERT(x.size() == 0);
        CPPUNIT_ASSERT(y.size() == 26);
	}
	
	void test_swap3 () {
        C x(26,44);
        C y(13, 57);
        
        x.resize(37, 52);
        
        x.swap(y);
        
        CPPUNIT_ASSERT(x.size() == 13);
        CPPUNIT_ASSERT(y.size() == 37);
        
        CPPUNIT_ASSERT(x.front() == 57);
        CPPUNIT_ASSERT(x.back() == 57);
        
        CPPUNIT_ASSERT(y.front() == 44);
        CPPUNIT_ASSERT(y[25] == 44);
        CPPUNIT_ASSERT(y[26] == 52);
        CPPUNIT_ASSERT(y.back() == 52);
        
	}
	
	
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDeque);
    
    CPPUNIT_TEST(test_equal1);
    CPPUNIT_TEST(test_equal2);
    CPPUNIT_TEST(test_equal3);
    
    CPPUNIT_TEST(test_size1);
    CPPUNIT_TEST(test_size2);
    CPPUNIT_TEST(test_size3);
    CPPUNIT_TEST(test_size4);
    
    CPPUNIT_TEST(test_cons1);
    CPPUNIT_TEST(test_cons2);
    CPPUNIT_TEST(test_cons3);
    
    CPPUNIT_TEST(test_assign1);
    CPPUNIT_TEST(test_assign2);
    CPPUNIT_TEST(test_assign3);
    
    CPPUNIT_TEST(test_iter1);
    CPPUNIT_TEST(test_iter2);
    CPPUNIT_TEST(test_iter3);
    CPPUNIT_TEST(test_iter4);
    
    CPPUNIT_TEST(test_const_iter1);
    CPPUNIT_TEST(test_const_iter2);
    CPPUNIT_TEST(test_const_iter3);
    CPPUNIT_TEST(test_const_iter4);
    
    CPPUNIT_TEST(test_at1);
    CPPUNIT_TEST(test_at2);
    CPPUNIT_TEST(test_at3);
    
    CPPUNIT_TEST(test_index1);
    CPPUNIT_TEST(test_index2);
    CPPUNIT_TEST(test_index3);
    
    CPPUNIT_TEST(test_front1);
    CPPUNIT_TEST(test_front2);
    CPPUNIT_TEST(test_front3);
	
	CPPUNIT_TEST(test_back1);
	CPPUNIT_TEST(test_back2);
	CPPUNIT_TEST(test_back3);
	
	CPPUNIT_TEST(test_push_front1);
	CPPUNIT_TEST(test_push_front2);
	CPPUNIT_TEST(test_push_front3);
	CPPUNIT_TEST(test_push_front4);
	
	CPPUNIT_TEST(test_push_back1);
	CPPUNIT_TEST(test_push_back2);
	CPPUNIT_TEST(test_push_back3);
	CPPUNIT_TEST(test_push_back4);
	
	CPPUNIT_TEST(test_insert1);
	CPPUNIT_TEST(test_insert2);
	CPPUNIT_TEST(test_insert3);
	
	
	CPPUNIT_TEST(test_erase1);
	CPPUNIT_TEST(test_erase2);
	CPPUNIT_TEST(test_erase3);
	
	CPPUNIT_TEST(test_resize1);
	CPPUNIT_TEST(test_resize2);
	CPPUNIT_TEST(test_resize3);
	
	CPPUNIT_TEST(test_swap1);
	CPPUNIT_TEST(test_swap2);
	CPPUNIT_TEST(test_swap3);
	
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
