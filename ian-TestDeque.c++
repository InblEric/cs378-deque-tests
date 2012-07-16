// ----------------------------
// projects/deque/TestDeque.c++
// Copyright(C) 2012
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

template <typename Deque>
struct TestDeque : CppUnit::TestFixture {

    void test_size() {
        const Deque x;
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, x.size());
    }

    void test_count_constructor() {
        Deque x(100, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)100, x.size());
    }
    void test_count_constructor_has_correct_elements() {
        Deque x(100, 20);
        CPPUNIT_ASSERT_EQUAL(20, x[0]);
        CPPUNIT_ASSERT_EQUAL(20, x[1]);
        CPPUNIT_ASSERT_EQUAL(20, x[99]);
    }
    void test_count_constructor_uneven_multiple_of_array_size() {
        Deque x(105, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)105, x.size());
        CPPUNIT_ASSERT_EQUAL(20, x[104]);
    }
    void test_count_constructor_less_than_array_size() {
        Deque x(5, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)5, x.size());
        CPPUNIT_ASSERT_EQUAL(20, x[4]);
    }
    void test_count_constructor_zero() {
        Deque x(0, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, x.size());
    }

    void test_copy_constructor_empty() {
        Deque x;
        Deque y(x);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, x.size());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, y.size());
    }
    void test_copy_constructor_simple() {
        Deque x(15, 50);
        Deque y(x);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, y.size());
        for(int i = 0; i < 15; i++)
            CPPUNIT_ASSERT_EQUAL(50, y[i]);
    }
    void test_copy_constructor_duplicating() {
        Deque x(15, 50);
        Deque y(x);
        Deque z(y);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, y.size());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, z.size());
        for(int i = 0; i < 15; i++)
            CPPUNIT_ASSERT_EQUAL(50, z[i]);
    }

    void test_push_back() {
        Deque x(5, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)5, x.size());
        x.push_back(10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)6, x.size());
        CPPUNIT_ASSERT_EQUAL(10, x.back());
    }
    void test_push_back_resize() {
        Deque x(10, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)10, x.size());
        x.push_back(10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)11, x.size());
        CPPUNIT_ASSERT_EQUAL(10, x.back());
    }
    void test_push_back_empty() {
        Deque x;
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, x.size());
        x.push_back(10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)1, x.size());
        CPPUNIT_ASSERT_EQUAL(10, x.back());
    }
    void test_push_back_empty_count() {
        Deque x(0, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, x.size());
        x.push_back(10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)1, x.size());
        CPPUNIT_ASSERT_EQUAL(10, x.back());
    }
    void test_push_back_multiple() {
        Deque x;
        int expected[] = { 5, 4, 6, 7, 8, 9, 10, 40, 11, -1, -20 };
        int i;
        for(i = 0; i < 11; i++)
            x.push_back(expected[i]);

        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)11, x.size());

        for(i = 0; i < 11; i++)
            CPPUNIT_ASSERT_EQUAL(expected[i], x[i]);
    }

    void test_push_front() {
        Deque x(5, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)5, x.size());
        x.push_front(10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)6, x.size());
        CPPUNIT_ASSERT_EQUAL(10, x.front());
    }
    void test_push_front_resize() {
        Deque x(10, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)10, x.size());
        x.push_front(10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)11, x.size());
        CPPUNIT_ASSERT_EQUAL(10, x.front());
    }
    void test_push_front_empty() {
        Deque x;
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, x.size());
        x.push_front(10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)1, x.size());
        CPPUNIT_ASSERT_EQUAL(10, x.front());
    }
    void test_push_front_empty_count() {
        Deque x(0, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, x.size());
        x.push_front(10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)1, x.size());
        CPPUNIT_ASSERT_EQUAL(10, x.front());
    }
    void test_push_front_multiple() {
        Deque x;
        int expected[] = { 5, 4, 6, 7, 8, 9, 10, 40, 11, -1, -20 };
        int i;
        for(i = 10; i >= 0; i--)
            x.push_front(expected[i]);

        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)11, x.size());

        for(i = 0; i < 11; i++)
            CPPUNIT_ASSERT_EQUAL(expected[i], x[i]);
    }

    void test_push_front_and_back() {
        Deque x;
        int expected[] = { 5, 4, 6, 7, 8, 9, 10, 40, 11, -1, -20 };
        int i;
        for(i = 10; i >= 0; i--)
            x.push_front(expected[i]);
        for(i = 0; i < 11; i++)
            x.push_back(expected[i]);

        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)22, x.size());

        for(i = 0; i < (int)x.size(); i++)
            CPPUNIT_ASSERT_EQUAL(expected[i % 11], x[i]);
    }

    void test_pop_back() {
        Deque x(5, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)5, x.size());
        x.pop_back();
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)4, x.size());
    }
    void test_pop_back_over_boundaries() {
        Deque x(11, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)11, x.size());
        x.pop_back();
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)10, x.size());
        x.pop_back();
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)9, x.size());
    }
    void test_pop_back_everything() {
        Deque x(15, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        for(int i = 0; i < 15; i++)
            x.pop_back();
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, x.size());
    }
    void test_pop_back_and_push_back() {
        Deque x(15, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        for(int i = 0; i < 15; i++)
            x.pop_back();
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, x.size());
        for(int i = 0; i < 15; i++)
            x.push_back(1);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
    }

    void test_pop_front() {
        Deque x(5, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)5, x.size());
        x.pop_front();
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)4, x.size());
    }
    void test_pop_front_over_boundaries() {
        Deque x(11, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)11, x.size());
        x.pop_front();
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)10, x.size());
        x.pop_front();
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)9, x.size());
    }
    void test_pop_front_everything() {
        Deque x(15, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        for(int i = 0; i < 15; i++)
            x.pop_front();
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, x.size());
    }
    void test_pop_front_and_push_front() {
        Deque x(15, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        for(int i = 0; i < 15; i++)
            x.pop_front();
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, x.size());
        for(int i = 0; i < 15; i++)
            x.push_front(1);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
    }

    void test_iterator() {
        Deque x;
        int expected[] = { 5, 4, 6, 7, 8, 9, 10, 40, 11, -1, -20 };
        int i;
        for(i = 0; i < 11; i++)
            x.push_back(expected[i]);

        i = 0;
        for(typename Deque::iterator it = x.begin(); it != x.end(); ++it, i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], *it);
        }
    }
    void test_iterator_begin() {
        Deque x;
        x.push_back(10);
        typename Deque::iterator b = x.begin();
        CPPUNIT_ASSERT_EQUAL(10, *b);
    }
    void test_iterator_end() {
        Deque x;
        x.push_back(10);
        typename Deque::iterator b = x.begin();
        typename Deque::iterator e = x.end();
        CPPUNIT_ASSERT(b != e);
    }
    void test_iterator_begin_and_end_empty() {
        Deque x;
        typename Deque::iterator b = x.begin();
        typename Deque::iterator e = x.end();
        CPPUNIT_ASSERT(b == e);
    }
    void test_iterator_increment() {
        Deque x;
        int expected[] = { 5, 4, 6, 7, 8, 9, 10, 40, 11, -1, -20, 30 };
        int i;
        for(i = 0; i < 12; i++)
            x.push_back(expected[i]);
        typename Deque::iterator it = x.begin();

        CPPUNIT_ASSERT_EQUAL(expected[0], *it);
        CPPUNIT_ASSERT_EQUAL(expected[0], *(it++));
        CPPUNIT_ASSERT_EQUAL(expected[1], *it);
        ++it;
        CPPUNIT_ASSERT_EQUAL(expected[2], *it);
    }
    void test_iterator_decrement() {
        Deque x;
        int expected[] = { 5, 4, 6, 7, 8, 9, 10, 40, 11, -1, -20, 30 };
        int i;
        for(i = 0; i < 12; i++)
            x.push_back(expected[i]);
        typename Deque::iterator it = x.end();

        --it;

        CPPUNIT_ASSERT_EQUAL(expected[11], *it);
        CPPUNIT_ASSERT_EQUAL(expected[11], *(it--));
        CPPUNIT_ASSERT_EQUAL(expected[10], *it);
        --it;
        CPPUNIT_ASSERT_EQUAL(expected[9], *it);
    }
    void test_iterator_equality() {
        Deque x;
        CPPUNIT_ASSERT(x.begin() == x.end());
        x.push_back(10);
        CPPUNIT_ASSERT(x.begin() != x.end());
        CPPUNIT_ASSERT((x.begin() + 1) == x.end());
        x.push_back(20);
        CPPUNIT_ASSERT(x.begin() != x.end());
        CPPUNIT_ASSERT((x.begin() + 2) == x.end());
    }
    void test_const_iterator() {
        Deque y;
        int expected[] = { 5, 4, 6, 7, 8, 9, 10, 40, 11, -1, -20 };
        int i;
        for(i = 0; i < 11; i++)
            y.push_back(expected[i]);

        const Deque x(y);

        i = 0;
        for(typename Deque::const_iterator it = x.begin(); it != x.end(); ++it, i++) {
            CPPUNIT_ASSERT_EQUAL(expected[i], *it);
        }
    }
    void test_const_iterator_begin() {
        const Deque x(1, 10);
        typename Deque::const_iterator b = x.begin();
        CPPUNIT_ASSERT_EQUAL(10, *b);
    }
    void test_const_iterator_end() {
        const Deque x(1, 10);
        typename Deque::const_iterator b = x.begin();
        typename Deque::const_iterator e = x.end();
        CPPUNIT_ASSERT(b != e);
    }
    void test_const_iterator_begin_and_end_empty() {
        const Deque x;
        typename Deque::const_iterator b = x.begin();
        typename Deque::const_iterator e = x.end();
        CPPUNIT_ASSERT(b == e);
    }
    void test_const_iterator_increment() {
        Deque y;
        int expected[] = { 5, 4, 6, 7, 8, 9, 10, 40, 11, -1, -20, 30 };
        int i;
        for(i = 0; i < 12; i++)
            y.push_back(expected[i]);
        const Deque x = y;
        typename Deque::const_iterator it = x.begin();

        CPPUNIT_ASSERT_EQUAL(expected[0], *it);
        CPPUNIT_ASSERT_EQUAL(expected[0], *(it++));
        CPPUNIT_ASSERT_EQUAL(expected[1], *it);
        ++it;
        CPPUNIT_ASSERT_EQUAL(expected[2], *it);
    }
    void test_const_iterator_decrement() {
        Deque y;
        int expected[] = { 5, 4, 6, 7, 8, 9, 10, 40, 11, -1, -20, 30 };
        int i;
        for(i = 0; i < 12; i++)
            y.push_back(expected[i]);
        const Deque x = y;
        typename Deque::const_iterator it = x.end();

        --it;

        CPPUNIT_ASSERT_EQUAL(expected[11], *it);
        CPPUNIT_ASSERT_EQUAL(expected[11], *(it--));
        CPPUNIT_ASSERT_EQUAL(expected[10], *it);
        --it;
        CPPUNIT_ASSERT_EQUAL(expected[9], *it);
    }
    void test_const_iterator_equality() {
        Deque x;
        CPPUNIT_ASSERT(x.begin() == x.end());
        x.push_back(10);
        CPPUNIT_ASSERT(x.begin() != x.end());
        CPPUNIT_ASSERT((x.begin() + 1) == x.end());
        x.push_back(20);
        CPPUNIT_ASSERT(x.begin() != x.end());
        CPPUNIT_ASSERT((x.begin() + 2) == x.end());
    }

    void test_at_zero() {
        Deque x;
        x.push_back(10);
        CPPUNIT_ASSERT_EQUAL(10, x.at(0));
    }
    void test_at_empty() {
        Deque x;
        CPPUNIT_ASSERT_THROW(x.at(0), std::out_of_range);
    }
    void test_at_negative() {
        Deque x;
        x.push_back(10);
        CPPUNIT_ASSERT_THROW(x.at(-1), std::out_of_range);
    }
    void test_at_beyond_end() {
        Deque x;
        x.push_back(10);
        CPPUNIT_ASSERT_THROW(x.at(10), std::out_of_range);
    }
    void test_at_end() {
        Deque x(25, 10);
        CPPUNIT_ASSERT_NO_THROW(x.at(24));
    }
    void test_at_just_after_end() {
        Deque x(25, 10);
        CPPUNIT_ASSERT_THROW(x.at(25), std::out_of_range);
    }

    void test_clear() {
        Deque x(25, 10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)25, x.size());
        x.clear();
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, x.size());
    }
    void test_clear_empty() {
        Deque x;
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, x.size());
        x.clear();
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, x.size());
    }
    void test_clear_followed_by_push_back() {
        Deque x;
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, x.size());
        x.clear();
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, x.size());
        for(int i = 0; i < 25; i++)
            x.push_back(i);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)25, x.size());
    }

    void test_insert_front() {
        Deque x(15, 10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        CPPUNIT_ASSERT_EQUAL(10, x.front());
        x.insert(x.begin(), 50);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)16, x.size());
        CPPUNIT_ASSERT_EQUAL(50, x.front());
        x.insert(x.begin(), 40);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)17, x.size());
        CPPUNIT_ASSERT_EQUAL(40, x[0]);
        CPPUNIT_ASSERT_EQUAL(50, x[1]);
        for(int i = 2; i < (int)x.size(); i++) {
            CPPUNIT_ASSERT_EQUAL(10, x[i]);
        }
    }
    void test_insert_back() {
        Deque x(15, 10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        CPPUNIT_ASSERT_EQUAL(10, x.back());
        x.insert(x.end(), 50);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)16, x.size());
        CPPUNIT_ASSERT_EQUAL(50, x.back());
        x.insert(x.end(), 40);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)17, x.size());
        CPPUNIT_ASSERT_EQUAL(40, x[16]);
        CPPUNIT_ASSERT_EQUAL(50, x[15]);
        for(int i = 0; i < 15; i++) {
            CPPUNIT_ASSERT_EQUAL(10, x[i]);
        }
    }
    void test_insert_near_front() {
        Deque x(15, 10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        CPPUNIT_ASSERT_EQUAL(10, x.front());
        x.insert(x.begin() + 1, 50);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)16, x.size());
        CPPUNIT_ASSERT_EQUAL(10, x[0]);
        CPPUNIT_ASSERT_EQUAL(50, x[1]);
        x.insert(x.begin() + 2, 40);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)17, x.size());
        CPPUNIT_ASSERT_EQUAL(10, x[0]);
        CPPUNIT_ASSERT_EQUAL(50, x[1]);
        CPPUNIT_ASSERT_EQUAL(40, x[2]);
        for(int i = 3; i < (int)x.size(); i++) {
            CPPUNIT_ASSERT_EQUAL(10, x[i]);
        }
    }
    void test_insert_near_back() {
        Deque x(15, 10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        CPPUNIT_ASSERT_EQUAL(10, x.front());
        x.insert(x.end() - 1, 50);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)16, x.size());
        CPPUNIT_ASSERT_EQUAL(10, x[15]);
        CPPUNIT_ASSERT_EQUAL(50, x[14]);
        x.insert(x.end() - 2, 40);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)17, x.size());
        CPPUNIT_ASSERT_EQUAL(10, x[16]);
        CPPUNIT_ASSERT_EQUAL(50, x[15]);
        CPPUNIT_ASSERT_EQUAL(40, x[14]);
        for(int i = 0; i < 14; i++) {
            CPPUNIT_ASSERT_EQUAL(10, x[i]);
        }
    }
    void test_insert_middle() {
        Deque x(15, 10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        x.insert(x.begin() + 7, 50);
        CPPUNIT_ASSERT_EQUAL(50, x[7]);
        x.insert(x.begin() + 7, 40);
        CPPUNIT_ASSERT_EQUAL(40, x[7]);
        CPPUNIT_ASSERT_EQUAL(50, x[8]);
        x.insert(x.begin() + 8, 30);
        CPPUNIT_ASSERT_EQUAL(40, x[7]);
        CPPUNIT_ASSERT_EQUAL(30, x[8]);
        CPPUNIT_ASSERT_EQUAL(50, x[9]);
    }
    void test_insert_multiple() {
        int i;
        Deque x(15, 10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        for(i = 0; i < 50; i++)
            x.insert(x.begin() + i + 7, i);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)65, x.size());
        for(i = 0; i < 7; i++)
            CPPUNIT_ASSERT_EQUAL(10, x[i]);
        for(i = 7; i < 57; i++)
            CPPUNIT_ASSERT_EQUAL(i - 7, x[i]);
        for(i = 57; i < 65; i++)
            CPPUNIT_ASSERT_EQUAL(10, x[i]);
    }

    void test_erase_front() {
        Deque x(15, 10);
        x.push_front(1);
        x.push_front(2);
        x.push_front(3);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)18, x.size());
        CPPUNIT_ASSERT_EQUAL(3, x.front());
        x.erase(x.begin());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)17, x.size());
        CPPUNIT_ASSERT_EQUAL(2, x.front());
        x.erase(x.begin());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)16, x.size());
        CPPUNIT_ASSERT_EQUAL(1, x.front());
        x.erase(x.begin());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        CPPUNIT_ASSERT_EQUAL(10, x.front());
    }
    void test_erase_back() {
        Deque x(15, 10);
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)18, x.size());
        CPPUNIT_ASSERT_EQUAL(3, x.back());
        x.erase(x.end() - 1);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)17, x.size());
        CPPUNIT_ASSERT_EQUAL(2, x.back());
        x.erase(x.end() - 1);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)16, x.size());
        CPPUNIT_ASSERT_EQUAL(1, x.back());
        x.erase(x.end() - 1);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        CPPUNIT_ASSERT_EQUAL(10, x.back());
    }
    void test_erase_near_front() {
        Deque x(15, 10);
        x.push_front(1);
        x.push_front(2);
        x.push_front(3);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)18, x.size());
        CPPUNIT_ASSERT_EQUAL(3, x[0]);
        CPPUNIT_ASSERT_EQUAL(2, x[1]);
        x.erase(x.begin() + 1);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)17, x.size());
        CPPUNIT_ASSERT_EQUAL(3, x[0]);
        CPPUNIT_ASSERT_EQUAL(1, x[1]);
        x.erase(x.begin() + 1);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)16, x.size());
        CPPUNIT_ASSERT_EQUAL(3, x[0]);
        CPPUNIT_ASSERT_EQUAL(10, x[1]);
        x.erase(x.begin() + 1);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        CPPUNIT_ASSERT_EQUAL(3, x[0]);
        CPPUNIT_ASSERT_EQUAL(10, x[1]);
    }
    void test_erase_near_back() {
        Deque x(15, 10);
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)18, x.size());
        CPPUNIT_ASSERT_EQUAL(3, x[17]);
        CPPUNIT_ASSERT_EQUAL(2, x[16]);
        x.erase(x.end() - 2);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)17, x.size());
        CPPUNIT_ASSERT_EQUAL(3, x[16]);
        CPPUNIT_ASSERT_EQUAL(1, x[15]);
        x.erase(x.end() - 2);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)16, x.size());
        CPPUNIT_ASSERT_EQUAL(3, x[15]);
        CPPUNIT_ASSERT_EQUAL(10, x[14]);
        x.erase(x.end() - 2);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        CPPUNIT_ASSERT_EQUAL(3, x[14]);
        CPPUNIT_ASSERT_EQUAL(10, x[13]);
    }
    void test_erase_middle() {
        Deque x(15, 10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        x.erase(x.begin() + 7);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)14, x.size());
        x.erase(x.begin() + 7);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)13, x.size());
        for(int i = 0; i < 13; i++)
            CPPUNIT_ASSERT_EQUAL(10, x[i]);
    }
    void test_erase_multiple() {
        Deque x(15, 10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        for(int i = 0; i < 15; i++)
            x.erase(x.begin());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, x.size());
    }

    void test_resize_grow() {
        Deque x(15, 10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        x.resize(25, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)25, x.size());
        int i;
        for(i = 0; i < 15; i++)
            CPPUNIT_ASSERT_EQUAL(10, x[i]);
        for(i = 15; i < 25; i++)
            CPPUNIT_ASSERT_EQUAL(20, x[i]);
    }
    void test_resize_shrink() {
        Deque x(15, 10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        x.resize(5, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)5, x.size());
        for(int i = 0; i < 5; i++)
            CPPUNIT_ASSERT_EQUAL(10, x[i]);
    }
    void test_resize_noop() {
        Deque x(15, 10);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        x.resize(15, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        for(int i = 0; i < 15; i++)
            CPPUNIT_ASSERT_EQUAL(10, x[i]);
    }

    void test_swap_simple() {
        Deque x(15, 10);
        Deque y(15, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, y.size());
        x.swap(y);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, y.size());
        for(int i = 0; i < 15; i++)
            CPPUNIT_ASSERT_EQUAL(10, y[i]);
        for(int i = 0; i < 15; i++)
            CPPUNIT_ASSERT_EQUAL(20, x[i]);
    }
    void test_swap_different_sizes() {
        Deque x(15, 10);
        Deque y(25, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)25, y.size());
        x.swap(y);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)25, x.size());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, y.size());
        for(int i = 0; i < 15; i++)
            CPPUNIT_ASSERT_EQUAL(10, y[i]);
        for(int i = 0; i < 25; i++)
            CPPUNIT_ASSERT_EQUAL(20, x[i]);
    }
    void test_swap_empty() {
        Deque x;
        Deque y(25, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, x.size());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)25, y.size());
        x.swap(y);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)25, x.size());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)0, y.size());
        for(int i = 0; i < 25; i++)
            CPPUNIT_ASSERT_EQUAL(20, x[i]);
    }

    void test_assignment_same_size() {
        Deque x(15, 10);
        Deque y(15, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, y.size());
        x = y;
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, y.size());
        for(int i = 0; i < 15; i++)
            CPPUNIT_ASSERT_EQUAL(20, x[i]);
        for(int i = 0; i < 15; i++)
            CPPUNIT_ASSERT_EQUAL(20, y[i]);
    }
    void test_assignment_to_larger_deque() {
        Deque x(15, 10);
        Deque y(25, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)25, y.size());
        x = y;
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)25, x.size());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)25, y.size());
        for(int i = 0; i < 25; i++)
            CPPUNIT_ASSERT_EQUAL(20, x[i]);
        for(int i = 0; i < 25; i++)
            CPPUNIT_ASSERT_EQUAL(20, y[i]);
    }
    void test_assignment_to_smaller_deque() {
        Deque x(15, 10);
        Deque y(5, 20);
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)15, x.size());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)5, y.size());
        x = y;
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)5, x.size());
        CPPUNIT_ASSERT_EQUAL((typename Deque::size_type)5, y.size());
        for(int i = 0; i < 5; i++)
            CPPUNIT_ASSERT_EQUAL(20, x[i]);
        for(int i = 0; i < 5; i++)
            CPPUNIT_ASSERT_EQUAL(20, y[i]);
    }

    void test_equality_empty() {
        CPPUNIT_ASSERT(Deque() == Deque());
    }
    void test_equality_equal() {
        Deque x(15, 50);
        Deque y(15, 50);
        Deque z(y);
        CPPUNIT_ASSERT(x == y);
        CPPUNIT_ASSERT(z == y);
        CPPUNIT_ASSERT(x == z);
    }
    void test_equality_not_equal() {
        Deque x(15, 50);
        Deque y(15, 60);
        CPPUNIT_ASSERT(x != y);
    }
    void test_equality_different_sizes() {
        Deque x(15, 50);
        Deque y(25, 50);
        CPPUNIT_ASSERT(x != y);
    }

    void test_less_than_same() {
        Deque x(15, 50);
        Deque y(x);
        CPPUNIT_ASSERT(!(x < y));
    }
    void test_less_than_less() {
        Deque x;
        Deque y;
        x.push_back(10);
        y.push_back(20);
        CPPUNIT_ASSERT(x < y);
    }
    void test_less_than_greater() {
        Deque x;
        Deque y;
        x.push_back(20);
        y.push_back(10);
        CPPUNIT_ASSERT(!(x < y));
    }
    void test_less_than_empty() {
        Deque x, y;
        CPPUNIT_ASSERT(!(x < y));
    }
    void test_less_than_different_sizes() {
        Deque x;
        Deque y;
        x.push_back(10);
        y.push_back(10);
        y.push_back(10);
        CPPUNIT_ASSERT(x < y);
    }

    CPPUNIT_TEST_SUITE(TestDeque);
    CPPUNIT_TEST(test_size);
    CPPUNIT_TEST(test_count_constructor);
    CPPUNIT_TEST(test_count_constructor_has_correct_elements);
    CPPUNIT_TEST(test_count_constructor_uneven_multiple_of_array_size);
    CPPUNIT_TEST(test_count_constructor_less_than_array_size);
    CPPUNIT_TEST(test_count_constructor_zero);

    CPPUNIT_TEST(test_copy_constructor_empty);
    CPPUNIT_TEST(test_copy_constructor_simple);
    CPPUNIT_TEST(test_copy_constructor_duplicating);

    CPPUNIT_TEST(test_push_back);
    CPPUNIT_TEST(test_push_back_resize);
    CPPUNIT_TEST(test_push_back_empty);
    CPPUNIT_TEST(test_push_back_empty_count);
    CPPUNIT_TEST(test_push_back_multiple);

    CPPUNIT_TEST(test_push_front);
    CPPUNIT_TEST(test_push_front_resize);
    CPPUNIT_TEST(test_push_front_empty);
    CPPUNIT_TEST(test_push_front_empty_count);
    CPPUNIT_TEST(test_push_front_multiple);

    CPPUNIT_TEST(test_pop_back);
    CPPUNIT_TEST(test_pop_back_over_boundaries);
    CPPUNIT_TEST(test_pop_back_everything);
    CPPUNIT_TEST(test_pop_back_and_push_back);

    CPPUNIT_TEST(test_pop_front);
    CPPUNIT_TEST(test_pop_front_over_boundaries);
    CPPUNIT_TEST(test_pop_front_everything);
    CPPUNIT_TEST(test_pop_front_and_push_front);

    CPPUNIT_TEST(test_push_front_and_back);

    CPPUNIT_TEST(test_iterator);
    CPPUNIT_TEST(test_iterator_begin);
    CPPUNIT_TEST(test_iterator_end);
    CPPUNIT_TEST(test_iterator_begin_and_end_empty);
    CPPUNIT_TEST(test_iterator_increment);
    CPPUNIT_TEST(test_iterator_decrement);
    CPPUNIT_TEST(test_iterator_equality);
    CPPUNIT_TEST(test_const_iterator);
    CPPUNIT_TEST(test_const_iterator_begin);
    CPPUNIT_TEST(test_const_iterator_end);
    CPPUNIT_TEST(test_const_iterator_begin_and_end_empty);
    CPPUNIT_TEST(test_const_iterator_increment);
    CPPUNIT_TEST(test_const_iterator_decrement);
    CPPUNIT_TEST(test_const_iterator_equality);

    CPPUNIT_TEST(test_at_zero);
    CPPUNIT_TEST(test_at_empty);
    CPPUNIT_TEST(test_at_negative);
    CPPUNIT_TEST(test_at_beyond_end);
    CPPUNIT_TEST(test_at_end);

    CPPUNIT_TEST(test_clear);
    CPPUNIT_TEST(test_clear_empty);
    CPPUNIT_TEST(test_clear_followed_by_push_back);

    CPPUNIT_TEST(test_insert_front);
    CPPUNIT_TEST(test_insert_back);
    CPPUNIT_TEST(test_insert_near_front);
    CPPUNIT_TEST(test_insert_near_back);
    CPPUNIT_TEST(test_insert_middle);
    CPPUNIT_TEST(test_insert_multiple);

    CPPUNIT_TEST(test_erase_front);
    CPPUNIT_TEST(test_erase_back);
    CPPUNIT_TEST(test_erase_near_front);
    CPPUNIT_TEST(test_erase_near_back);
    CPPUNIT_TEST(test_erase_middle);
    CPPUNIT_TEST(test_erase_multiple);

    CPPUNIT_TEST(test_resize_grow);
    CPPUNIT_TEST(test_resize_shrink);
    CPPUNIT_TEST(test_resize_noop);

    CPPUNIT_TEST(test_swap_simple);
    CPPUNIT_TEST(test_swap_empty);
    CPPUNIT_TEST(test_swap_different_sizes);

    CPPUNIT_TEST(test_assignment_same_size);
    CPPUNIT_TEST(test_assignment_to_larger_deque);
    CPPUNIT_TEST(test_assignment_to_smaller_deque);

    CPPUNIT_TEST(test_equality_empty);
    CPPUNIT_TEST(test_equality_equal);
    CPPUNIT_TEST(test_equality_not_equal);
    CPPUNIT_TEST(test_equality_different_sizes);

    CPPUNIT_TEST(test_less_than_same);
    CPPUNIT_TEST(test_less_than_less);
    CPPUNIT_TEST(test_less_than_greater);
    CPPUNIT_TEST(test_less_than_empty);
    CPPUNIT_TEST(test_less_than_different_sizes);
    CPPUNIT_TEST_SUITE_END();
};

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false);        // turn off synchronization with C I/O
    cout << "TestDeque.c++" << endl << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDeque< MyDeque<int> >::suite());
    tr.addTest(TestDeque<   deque<int> >::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
