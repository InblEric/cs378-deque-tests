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
#include <ostream>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TestSuite.h"               // TestSuite
#include "cppunit/TextTestRunner.h"          // TestRunner

#include "Deque.h"

using namespace std;

// ---------
// TestDeque
// ---------

template <typename C>
struct TestDeque : CppUnit::TestFixture {
    // ----
    // size
    // ----

    void test_size () {
        const C x;
        CPPUNIT_ASSERT(x.size() == 0);}

    void test_size2 () {
        const C x(9,5);
        CPPUNIT_ASSERT(x.size() == 9);}

    void test_size3 () {
        const C x(3000,5);
        CPPUNIT_ASSERT(x.size() == 3000);}

    // ----
    // constructor
    // ----

    void test_constructor () {
        const C x(5000);
	CPPUNIT_ASSERT(x.size() == 5000);}

    void test_constructor2 () {
        const C x(123897,5);
	CPPUNIT_ASSERT(x.size() == 123897);
	CPPUNIT_ASSERT(x[123896] == 5);}

    void test_constructor3 () {
        const C x(123897,5);
	const C y(x);
	CPPUNIT_ASSERT(y.size() == 123897);
	CPPUNIT_ASSERT(y[123896] == 5);}

    // ----
    // iterator begin and end
    // ----
	void test_iterator_begin () {
	C d;
	typename C::iterator it1 = d.begin();
	typename C::iterator it2 = d.begin();
	CPPUNIT_ASSERT(it1 == it2);
	it2 = d.end();
	CPPUNIT_ASSERT(it1 == it2);}


        void test_iterator_begin2 () {
	C d(9,5);
	typename C::iterator it1 = d.begin();
	typename C::iterator it2 = d.begin();
	CPPUNIT_ASSERT(it1 == it2);
	it1 = d.begin() + 9;
	CPPUNIT_ASSERT(it1 != it2);
	it2 = d.end();
	CPPUNIT_ASSERT(it1 == it2);}

	void test_iterator_begin3 () {
	C d(36,5);
	typename C::iterator it1 = d.begin();
	typename C::iterator it2 = d.begin();
	CPPUNIT_ASSERT(it1 == it2);
	it1 = d.begin() + 36;
	CPPUNIT_ASSERT(it1 != it2);
	it2 = d.end();
	CPPUNIT_ASSERT(it1 == it2);}

    // ----
    // index
    // ----

    void test_index () {
	C d(36,5);
	CPPUNIT_ASSERT(d[2] == 5);
	CPPUNIT_ASSERT(d[8] == 5);
	CPPUNIT_ASSERT(d[15] == 5);
        CPPUNIT_ASSERT(d[35] == 5);}

    // ----
    // resize
    // ----

    void test_resize () {
	C d(22, 1);
	CPPUNIT_ASSERT(d.size() == 22);
	CPPUNIT_ASSERT(d[20] == 1);
	d.resize(15);
	CPPUNIT_ASSERT(d.size() == 15);
	d.resize(500, 2);
	CPPUNIT_ASSERT(d.size() == 500);
	CPPUNIT_ASSERT(d[20] == 2);
	CPPUNIT_ASSERT(d[31] == 2);
	}

    void test_resize2 () {
	C d(22, 1);
	CPPUNIT_ASSERT(d.size() == 22);
	CPPUNIT_ASSERT(d[20] == 1);
	d.resize(35, 2);
	CPPUNIT_ASSERT(d.size() == 35);
	CPPUNIT_ASSERT(d[23] == 2);
	}

    void test_resize3 () {
	C d(22, 1);
	d.resize(5000, 2);
	CPPUNIT_ASSERT(d.size() == 5000);
	CPPUNIT_ASSERT(d[4999] == 2);
	}

    void test_resize4 () {
	C d(22, 1);
	CPPUNIT_ASSERT(d.size() == 22);
	CPPUNIT_ASSERT(d[20] == 1);
	d.resize(15);
	CPPUNIT_ASSERT(d.size() == 15);
    }
    // ----
    // push_back
    // ----

    void test_pushback () {
	C d;
	for(int i = 0; i < 11; ++i)
		d.push_back(2);
	CPPUNIT_ASSERT(d.size() == 11);
	//CPPUNIT_ASSERT(d[450] == 2);
	}

    void test_pushback2 () {
	C d(2);
        d.push_back(2);
	CPPUNIT_ASSERT(d.size() == 3);
	CPPUNIT_ASSERT(d[2] == 2);
	}

    // ----
    // back
    // ----

    void test_back() {
		C d(1234, 5);
		CPPUNIT_ASSERT(d.back() == 5);

		d.push_back(34343);
		CPPUNIT_ASSERT(d.size() == 1235);
		CPPUNIT_ASSERT(d.back() == 34343);

		for (int i=0; i<1337; ++i) {
			d.push_back(2525);
		}
		CPPUNIT_ASSERT(d.size() == 2572);
		CPPUNIT_ASSERT(d.back() == 2525);

	}

    // ----
    // clear
    // ----

    void test_clear() {
		C d(1234, 5);
		CPPUNIT_ASSERT(d.size() == 1234);
		d.clear();
		CPPUNIT_ASSERT(d.size() == 0);
    }

    void test_clear2() {
		C d(1);
		CPPUNIT_ASSERT(d.size() == 1);
		d.clear();
		CPPUNIT_ASSERT(d.size() == 0);
    }

     void test_clear3() {
		C d;
		CPPUNIT_ASSERT(d.size() == 0);
		d.clear();
		CPPUNIT_ASSERT(d.size() == 0);
    }

    // ----
    // insert
    // ----

     void test_insert() {
		C d(333, 5);
		CPPUNIT_ASSERT(d.size() == 333);
		CPPUNIT_ASSERT(d[99] == 5);
		d.insert(d.begin()+100, 2);
		CPPUNIT_ASSERT(d.size() == 334);
		CPPUNIT_ASSERT(d[100] == 2);
    }

    void test_insert2() {
		C d(523, 5);
		CPPUNIT_ASSERT(d.size() == 523);
		CPPUNIT_ASSERT(d[1] == 5);
		d.insert(d.end(), 2);
		CPPUNIT_ASSERT(d.size() == 524);
		CPPUNIT_ASSERT(d[523] == 2);
    }


    void test_insert3() {
		C d(6, 5);
		CPPUNIT_ASSERT(d.size() == 6);
		CPPUNIT_ASSERT(d[0] == 5);
		d.insert(d.begin(), 2);
		CPPUNIT_ASSERT(d.size() == 7);
		CPPUNIT_ASSERT(d[0] == 2);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDeque);
    CPPUNIT_TEST(test_size);
    CPPUNIT_TEST(test_size2);
    CPPUNIT_TEST(test_size3);
    CPPUNIT_TEST(test_constructor);
    CPPUNIT_TEST(test_constructor2);
    CPPUNIT_TEST(test_constructor3);
    CPPUNIT_TEST(test_iterator_begin);
    CPPUNIT_TEST(test_iterator_begin2);
    CPPUNIT_TEST(test_iterator_begin3);
    CPPUNIT_TEST(test_resize);
    CPPUNIT_TEST(test_resize2);
    CPPUNIT_TEST(test_resize3);
    CPPUNIT_TEST(test_resize4);
    CPPUNIT_TEST(test_pushback);
    CPPUNIT_TEST(test_pushback2);
    CPPUNIT_TEST(test_clear);
    CPPUNIT_TEST(test_clear2);
    CPPUNIT_TEST(test_clear3);
    CPPUNIT_TEST(test_back);
    CPPUNIT_TEST(test_index);
    CPPUNIT_TEST(test_insert);
    CPPUNIT_TEST(test_insert2);
    CPPUNIT_TEST(test_insert3);
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
