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

    C getTestDeque() {
        C x;

        x.push_back(1);
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.push_back(5);
        x.push_back(8);
        x.push_back(13);
        x.push_back(21);
        x.push_back(34);

        return x;
    }

    void test_size () {
        const C x;
        CPPUNIT_ASSERT(x.size() == 0);}


    //==========================================
    void test_at1 () {
        C x;
        x.push_back(2);
        x.push_front(1);
        x.push_back(3);
        x.push_front(0);

        CPPUNIT_ASSERT(x.at(0) == 0);
        CPPUNIT_ASSERT(x.at(1) == 1);
        CPPUNIT_ASSERT(x.at(2) == 2);
        CPPUNIT_ASSERT(x.at(3) == 3);}

    void test_at2 () {
        C x;
        x.push_back(2);
        x.push_front(1);
        x.push_back(3);
        x.push_front(0);

        x.pop_front();
        x.pop_back();

        CPPUNIT_ASSERT(x.at(0) == 1);
        CPPUNIT_ASSERT(x.at(1) == 2);}

    void test_at3 () {
        C x;
        x.push_back(2);
        x.push_front(1);
        x.push_back(3);
        x.push_front(0);

        x.pop_front();
        x.pop_back();

        x.push_back(100);
        x.push_front(-100);

        CPPUNIT_ASSERT(x.at(0) == -100);
        CPPUNIT_ASSERT(x.at(1) == 1);
        CPPUNIT_ASSERT(x.at(2) == 2);
        CPPUNIT_ASSERT(x.at(3) == 100);}

    //==========================================
    void test_back1 () {
        C x = getTestDeque();


        CPPUNIT_ASSERT(x.back() == 34);}

    void test_back2 () {
        C x = getTestDeque();

        x.pop_back();

        CPPUNIT_ASSERT(x.back() == 21);}

    void test_back3 () {
        C x = getTestDeque();

        x.pop_back();
        x.pop_back();

        CPPUNIT_ASSERT(x.back() == 13);}

    //==========================================
    void test_begin1 () {
        C x = getTestDeque();

        typename C::iterator it_begin = x.begin();

        CPPUNIT_ASSERT(*it_begin == 1);}

    void test_begin2 () {
        C x = getTestDeque();

        x.pop_front();
        x.pop_front();

        typename C::iterator it_begin = x.begin();

        CPPUNIT_ASSERT(*it_begin == 2);}

    void test_begin3 () {
        C x = getTestDeque();

        x.pop_front();
        x.pop_front();
        x.pop_front();
        x.pop_front();

        typename C::iterator it_begin = x.begin();

        CPPUNIT_ASSERT(*it_begin == 5);}

    //==========================================
    void test_clear1 () {
        C x = getTestDeque();
        x.clear();

        CPPUNIT_ASSERT(x.size() == 0);}

    void test_clear2 () {
        C x;
        x.clear();
        CPPUNIT_ASSERT(x.size() == 0);}

    void test_clear3 () {
        C x = getTestDeque();
        x.clear();

        x.push_front(10);
        x.push_front(20);

        CPPUNIT_ASSERT(x.size() == 2);
        CPPUNIT_ASSERT(x[0] == 20);
        CPPUNIT_ASSERT(x[1] == 10);}

    //==========================================
    void test_empty1 () {
        const C x;
        CPPUNIT_ASSERT(x.empty());}

    void test_empty2 () {
        C x;

        x.push_back(5);

        CPPUNIT_ASSERT(!x.empty());}

    void test_empty3 () {
        C x;

        x.push_back(5);
        x.pop_back();

        CPPUNIT_ASSERT(x.empty());}

    //==========================================
    void test_erase1 () {
        C x = getTestDeque();

        CPPUNIT_ASSERT(x.size() == 9);

        typename C::iterator it_begin = x.begin();
        x.erase(it_begin + 1);

        CPPUNIT_ASSERT(x.size() == 8);}

    void test_erase2 () {
        C x = getTestDeque();

        CPPUNIT_ASSERT(x.size() == 9);

        x.erase(x.end() - 1);

        CPPUNIT_ASSERT(x.size() == 8);
        CPPUNIT_ASSERT(x[7] == 21);}

    void test_erase3 () {
        C x = getTestDeque();

        CPPUNIT_ASSERT(x.size() == 9);

        x.erase(x.begin());
        x.erase(x.begin());

        CPPUNIT_ASSERT(x.size() == 7);
        CPPUNIT_ASSERT(x[0] == 2);
        CPPUNIT_ASSERT(x[1] == 3);}

    //==========================================
    void test_front1 () {
        C x = getTestDeque();

        CPPUNIT_ASSERT(x.front() == 1);}

    void test_front2 () {
        C x = getTestDeque();

        x.pop_front();
        x.pop_front();

        CPPUNIT_ASSERT(x.front() == 2);}

    void test_front3 () {
        C x = getTestDeque();

        x.pop_front();
        x.pop_front();
        x.pop_front();
        x.pop_front();

        CPPUNIT_ASSERT(x.front() == 5);}

    //==========================================
    void test_insert1 () {
        C x = getTestDeque();

        CPPUNIT_ASSERT(x.size() == 9);

        x.insert(x.begin(), 100);

        CPPUNIT_ASSERT(x.size() == 10);
        CPPUNIT_ASSERT(x[0] == 100);
        CPPUNIT_ASSERT(x[1] == 1);}

    void test_insert2 () {
        C x = getTestDeque();

        CPPUNIT_ASSERT(x.size() == 9);

        x.insert(x.begin() + 2, 100);

        CPPUNIT_ASSERT(x.size() == 10);
        CPPUNIT_ASSERT(x[0] == 1);
        CPPUNIT_ASSERT(x[1] == 1);
        CPPUNIT_ASSERT(x[2] == 100);}

    void test_insert3 () {
        C x = getTestDeque();

        CPPUNIT_ASSERT(x.size() == 9);

        x.insert(x.end(), 100);

        CPPUNIT_ASSERT(x.size() == 10);
        CPPUNIT_ASSERT(x[8] == 34);
        CPPUNIT_ASSERT(x[9] == 100);}

    //==========================================
    void test_lessThan1 () {
        C firstArgument;

        firstArgument.push_back(1);
        firstArgument.push_back(2);
        firstArgument.push_back(3);

        C secondArgument;

        secondArgument.push_back(1);
        secondArgument.push_back(2);
        secondArgument.push_back(4);

        CPPUNIT_ASSERT(firstArgument < secondArgument);}

    void test_lessThan2 () {
        C firstArgument;

        firstArgument.push_back(1);
        firstArgument.push_back(2);
        firstArgument.push_back(3);

        C secondArgument;

        secondArgument.push_back(1);
        secondArgument.push_back(2);
        secondArgument.push_back(3);

        CPPUNIT_ASSERT(!(firstArgument < secondArgument));}

    void test_lessThan3 () {
        C firstArgument;

        firstArgument.push_back(1);
        firstArgument.push_back(2);
        firstArgument.push_back(3);

        C secondArgument;

        secondArgument.push_back(1);
        secondArgument.push_back(2);
        secondArgument.push_back(3);
        secondArgument.push_back(4);

        CPPUNIT_ASSERT(firstArgument < secondArgument);}

    //==========================================
    void test_assignment1 () {
        C x;

        x = getTestDeque();

        CPPUNIT_ASSERT(x.size() == 9);
        CPPUNIT_ASSERT(x[0] == 1);
        CPPUNIT_ASSERT(x[8] == 34);}

    //==========================================
   void test_equality1 () {
        C firstArgument;

        firstArgument.push_back(1);
        firstArgument.push_back(2);
        firstArgument.push_back(3);

        C secondArgument;

        secondArgument.push_back(1);
        secondArgument.push_back(2);
        secondArgument.push_back(4);

        CPPUNIT_ASSERT(firstArgument != secondArgument);}

    void test_equality2 () {
        C firstArgument;

        firstArgument.push_back(1);
        firstArgument.push_back(2);
        firstArgument.push_back(3);

        C secondArgument;

        secondArgument.push_back(1);
        secondArgument.push_back(2);
        secondArgument.push_back(3);

        CPPUNIT_ASSERT(firstArgument == secondArgument);}

    void test_equality3 () {
        C firstArgument;

        firstArgument.push_back(1);
        firstArgument.push_back(2);
        firstArgument.push_back(3);

        C secondArgument;

        secondArgument.push_back(1);
        secondArgument.push_back(2);
        secondArgument.push_back(3);
        secondArgument.push_back(4);

        CPPUNIT_ASSERT(firstArgument != secondArgument);}

    //==========================================
    void test_indexing1 () {
        C x = getTestDeque();
        CPPUNIT_ASSERT(x[0] == 1);
        CPPUNIT_ASSERT(x[1] == 1);
        CPPUNIT_ASSERT(x[8] == 34);}

    //==========================================
    void test_popBack1 () {
        C x = getTestDeque();

        CPPUNIT_ASSERT(x[x.size() - 1] == 34);

        x.pop_back();

        CPPUNIT_ASSERT(x[x.size() - 1] == 21);}

    void test_popBack2 () {
        C x = getTestDeque();

        CPPUNIT_ASSERT(x[x.size() - 1] == 34);

        x.pop_back();
        x.pop_back();
        x.pop_back();

        CPPUNIT_ASSERT(x[x.size() - 1] == 8);}

    void test_popBack3 () {
        C x;

        CPPUNIT_ASSERT(x.size() == 0);

        x.push_back(1);
        x.pop_back();

        CPPUNIT_ASSERT(x.size() == 0);}

    //==========================================
    void test_popFront1 () {
        C x = getTestDeque();

        CPPUNIT_ASSERT(x[0] == 1);
        CPPUNIT_ASSERT(x[1] == 1);

        x.pop_front();

        CPPUNIT_ASSERT(x[0] == 1);
        CPPUNIT_ASSERT(x[1] == 2);}

    void test_popFront2 () {
        C x = getTestDeque();

        CPPUNIT_ASSERT(x[0] == 1);

        x.pop_front();
        x.pop_front();

        CPPUNIT_ASSERT(x[0] == 2);}

    void test_popFront3 () {
        C x;

        CPPUNIT_ASSERT(x.size() == 0);

        x.push_front(1);
        x.pop_front();

        CPPUNIT_ASSERT(x.size() == 0);}

    //==========================================
    void test_pushBack1 () {
        C x;

        CPPUNIT_ASSERT(x.size() == 0);

        x.push_back(1);

        CPPUNIT_ASSERT(x.size() == 1);
        CPPUNIT_ASSERT(x[0] == 1);}

    void test_pushBack2 () {
        C x;

        CPPUNIT_ASSERT(x.size() == 0);

        x.push_back(1);
        x.push_back(2);
        x.push_back(3);

        CPPUNIT_ASSERT(x.size() == 3);
        CPPUNIT_ASSERT(x[0] == 1);
        CPPUNIT_ASSERT(x[1] == 2);
        CPPUNIT_ASSERT(x[2] == 3);}

    void test_pushBack3 () {
        C x = getTestDeque();

        x.push_back(100);

        CPPUNIT_ASSERT(x[x.size() - 1] == 100);}

    //==========================================
    void test_pushFront1 () {
        C x;

        CPPUNIT_ASSERT(x.size() == 0);

        x.push_front(1);

        CPPUNIT_ASSERT(x.size() == 1);
        CPPUNIT_ASSERT(x[0] == 1);}

    void test_pushFront2 () {
        C x;

        CPPUNIT_ASSERT(x.size() == 0);

        x.push_front(1);
        x.push_front(2);
        x.push_front(3);

        CPPUNIT_ASSERT(x.size() == 3);
        CPPUNIT_ASSERT(x[0] == 3);
        CPPUNIT_ASSERT(x[1] == 2);
        CPPUNIT_ASSERT(x[2] == 1);}

    void test_pushFront3 () {
        C x = getTestDeque();

        x.push_front(100);

        CPPUNIT_ASSERT(x[0] == 100);
        CPPUNIT_ASSERT(x[x.size() - 1] == 34);}

    //==========================================
    void test_resize1 () {
        C x;

        CPPUNIT_ASSERT(x.size() == 0);

        x.resize(10);

        CPPUNIT_ASSERT(x.size() == 10);}

    void test_resize2 () {
        C x = getTestDeque();

        CPPUNIT_ASSERT(x.size() == 9);

        x.resize(20);

        CPPUNIT_ASSERT(x.size() == 20);}

    void test_resize3 () {
        C x = getTestDeque();

        CPPUNIT_ASSERT(x.size() == 9);

        x.resize(3);

        CPPUNIT_ASSERT(x.size() == 3);}

    //==========================================
    void test_swap1 () {
        C firstArgument;
        C secondArgument = getTestDeque();

        firstArgument.swap(secondArgument);

        CPPUNIT_ASSERT(firstArgument.size() == 9);
        CPPUNIT_ASSERT(secondArgument.size() == 0);}

    void test_swap2 () {
        C firstArgument;
        C secondArgument = getTestDeque();

        secondArgument.swap(firstArgument);

        CPPUNIT_ASSERT(firstArgument.size() == 9);
        CPPUNIT_ASSERT(secondArgument.size() == 0);}

    void test_swap3 () {
        C firstArgument;
        C secondArgument = getTestDeque();

        firstArgument.swap(secondArgument);
        firstArgument.swap(secondArgument);

        CPPUNIT_ASSERT(firstArgument.size() == 0);
        CPPUNIT_ASSERT(secondArgument.size() == 9);}

    //==========================================
    void test_iter1 () {
        C x = getTestDeque();

        typename C::iterator iter = x.begin();

        CPPUNIT_ASSERT(*iter == 1);

        iter += 5;
        CPPUNIT_ASSERT(*iter == 8);

        iter++;
        CPPUNIT_ASSERT(*iter == 13);

        iter -= 2;
        CPPUNIT_ASSERT(*iter == 5);

        iter--;
        CPPUNIT_ASSERT(*iter == 3);

        *iter = 100;
        CPPUNIT_ASSERT(*iter == 100);

        iter -=3;
        CPPUNIT_ASSERT(iter == x.begin());
    }

    void test_iter2 () {
        const C x = getTestDeque();

        typename C::const_iterator iter = x.begin();

        CPPUNIT_ASSERT(*iter == 1);

        iter += 5;
        CPPUNIT_ASSERT(*iter == 8);

        iter++;
        CPPUNIT_ASSERT(*iter == 13);

        iter -= 2;
        CPPUNIT_ASSERT(*iter == 5);

        iter--;
        CPPUNIT_ASSERT(*iter == 3);

        iter -=3;
        CPPUNIT_ASSERT(iter == x.begin());
    }

    //==========================================
    void test_manyElements(){
        C x;

    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDeque);
    CPPUNIT_TEST(test_size);

    CPPUNIT_TEST(test_at1);
    CPPUNIT_TEST(test_at2);
    CPPUNIT_TEST(test_at3);

    CPPUNIT_TEST(test_back1);
    CPPUNIT_TEST(test_back2);
    CPPUNIT_TEST(test_back3);

    CPPUNIT_TEST(test_begin1);
    CPPUNIT_TEST(test_begin2);
    CPPUNIT_TEST(test_begin3);

    CPPUNIT_TEST(test_clear1);
    CPPUNIT_TEST(test_clear2);
    CPPUNIT_TEST(test_clear3);

    CPPUNIT_TEST(test_empty1);
    CPPUNIT_TEST(test_empty2);
    CPPUNIT_TEST(test_empty3);

    CPPUNIT_TEST(test_erase1);
    CPPUNIT_TEST(test_erase2);
    CPPUNIT_TEST(test_erase3);

    CPPUNIT_TEST(test_front1);
    CPPUNIT_TEST(test_front2);
    CPPUNIT_TEST(test_front3);

    CPPUNIT_TEST(test_insert1);
    CPPUNIT_TEST(test_insert2);
    CPPUNIT_TEST(test_insert3);

    CPPUNIT_TEST(test_lessThan1);
    CPPUNIT_TEST(test_lessThan2);
    CPPUNIT_TEST(test_lessThan3);

    CPPUNIT_TEST(test_assignment1);

    CPPUNIT_TEST(test_equality1);
    CPPUNIT_TEST(test_equality2);
    CPPUNIT_TEST(test_equality3);

    CPPUNIT_TEST(test_indexing1);

    CPPUNIT_TEST(test_popBack1);
    CPPUNIT_TEST(test_popBack2);
    CPPUNIT_TEST(test_popBack3);

    CPPUNIT_TEST(test_popFront1);
    CPPUNIT_TEST(test_popFront2);
    CPPUNIT_TEST(test_popFront3);

    CPPUNIT_TEST(test_pushBack1);
    CPPUNIT_TEST(test_pushBack2);
    CPPUNIT_TEST(test_pushBack3);

    CPPUNIT_TEST(test_pushFront1);
    CPPUNIT_TEST(test_pushFront2);
    CPPUNIT_TEST(test_pushFront3);

    CPPUNIT_TEST(test_resize1);
    CPPUNIT_TEST(test_resize2);
    CPPUNIT_TEST(test_resize3);

    CPPUNIT_TEST(test_swap1);
    CPPUNIT_TEST(test_swap2);
    CPPUNIT_TEST(test_swap3);

    CPPUNIT_TEST(test_iter1);
    CPPUNIT_TEST(test_iter2);

    CPPUNIT_TEST(test_manyElements);
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
