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

// ---------
// TestDeque
// ---------

template <typename C>
struct TestDeque : CppUnit::TestFixture {

//-------------------------------------------------------------------------------------------------------
//ITERATOR
//-------------------------------------------------------------------------------------------------------
    // ----
    //  ==
    // ----
    void test_it_equal_1 () {
        C x;
        x.push_back(5);


        typename C::iterator xit = x.begin();
        typename C::iterator yit = x.begin();

        CPPUNIT_ASSERT( xit == yit );
    }

    void test_it_equal_2 () {
        C x;

        x.push_back(8);

        typename C::iterator xit = x.begin();
        typename C::iterator yit = x.begin();

        CPPUNIT_ASSERT( xit == yit );
    }

    void test_it_equal_3 () {
        C x;

        x.push_back(8);

        typename C::iterator xit = x.begin();
        typename C::iterator yit = x.begin();

        CPPUNIT_ASSERT( xit == yit );
    }


    // ----
    //  +=
    // ----
    void test_it_plusequal_1 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.begin();
        xit += 0;

        CPPUNIT_ASSERT( *xit == 4 );
    }

    void test_it_plusequal_2 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.begin();
        xit += 1;

        CPPUNIT_ASSERT( *xit == 5 );
    }

    void test_it_plusequal_3 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator  xit = x.begin();
        xit += 3;

        CPPUNIT_ASSERT( *xit == 7 );
    }


    // ----
    //  -=
    // ----
    void test_it_minusequal_1 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.end();
        xit -= 1;

        CPPUNIT_ASSERT( *xit == 7 );
    }

    void test_it_minusequal_2 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit = x.end();
        xit -= 2;

        CPPUNIT_ASSERT( *xit == 6 );
    }

    void test_it_minusequal_3 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.end();
        xit -= 4;

        CPPUNIT_ASSERT( *xit == 4);
    }


    // ----
    //   *
    // ----
    void test_it_star_1 () {
        C x;
        x.push_back(4);
        typename C::iterator xit = x.begin();

        CPPUNIT_ASSERT( *xit == 4 );
    }

    void test_it_star_2 () {
        C x;
        x.push_back(12);
        typename C::iterator xit = x.begin();

        CPPUNIT_ASSERT( *xit == 12 );
    }

    void test_it_star_3 () {
        C x;
        x.push_back(999);
        typename C::iterator xit = x.begin();

        CPPUNIT_ASSERT( *xit == 999 );
    }

    // ----
    //  --
    // ----
    void test_it_minusminus_1 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.end();
        xit--;
        xit--;

        CPPUNIT_ASSERT( *xit == 6 );
    }

    void test_it_minusminus_2 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.end();
        xit--;
        xit--;
        xit--;

        CPPUNIT_ASSERT( *xit == 5 );
    }

    void test_it_minusminus_3 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.end();
        xit--;
        xit--;
        xit--;
        xit--;

        CPPUNIT_ASSERT( *xit == 4 );
    }


    // ----
    //  ++
    // ----
    void test_it_plusplus_1 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.begin();
        xit++;

        CPPUNIT_ASSERT( *xit == 5 );
    }

    void test_it_plusplus_2 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.begin();
        xit++;
        xit++;

        CPPUNIT_ASSERT( *xit == 6 );
    }

    void test_it_plusplus_3 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.begin();
        xit++;
        xit++;
        xit++;

        CPPUNIT_ASSERT( *xit == 7 );
    }

//-------------------------------------------------------------------------------------------------------
//CONST ITERATOR
//-------------------------------------------------------------------------------------------------------
    // ----
    //  ==
    // ----
    void test_consit_equal_1 () {
        C x;

        x.push_back(5);

        typename C::iterator xit =  x.begin();
        typename C::iterator yit = x.begin();

        CPPUNIT_ASSERT( xit==yit );
    }

    void test_consit_equal_2 () {
        C x;

        x.push_back(8);

        typename C::iterator xit =  x.begin();
        typename C::iterator yit = x.begin();

        CPPUNIT_ASSERT( xit==yit );
    }

    void test_consit_equal_3 () {
        C x;

        x.push_back(8);

        typename C::iterator xit =  x.begin();
        typename C::iterator yit = x.begin();

        CPPUNIT_ASSERT( xit==yit );
    }


    // ----
    //  +=
    // ----
    void test_consit_plusequal_1 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.begin();
        xit += 0;

        CPPUNIT_ASSERT( *xit == 4 );
    }

    void test_consit_plusequal_2 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.begin();
        xit += 1;

        CPPUNIT_ASSERT( *xit == 5 );
    }

    void test_consit_plusequal_3 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator  xit = x.begin();
        xit += 3;

        CPPUNIT_ASSERT( *xit == 7 );
    }


    // ----
    //  -=
    // ----
    void test_consit_minusequal_1 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.end();
        xit -= 1;

        CPPUNIT_ASSERT( *xit == 7 );
    }

    void test_consit_minusequal_2 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit = x.end();
        xit -= 2;

        CPPUNIT_ASSERT( *xit == 6 );
    }

    void test_consit_minusequal_3 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.end();
        xit -= 4;

        CPPUNIT_ASSERT( *xit == 4);
    }


    // ----
    //   *
    // ----
    void test_consit_star_1 () {
        C x;
        x.push_back(4);
        typename C::iterator xit = x.begin();

        CPPUNIT_ASSERT( *xit == 4 );
    }

    void test_consit_star_2 () {
        C x;
        x.push_back(12);
        typename C::iterator xit = x.begin();

        CPPUNIT_ASSERT( *xit == 12 );
    }

    void test_consit_star_3 () {
        C x;
        x.push_back(999);
        typename C::iterator xit = x.begin();

        CPPUNIT_ASSERT( *xit == 999 );
    }

    // ----
    //  --
    // ----
    void test_consit_minusminus_1 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.end();
        xit--;
        xit--;

        CPPUNIT_ASSERT( *xit == 6 );
    }

    void test_consit_minusminus_2 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.end();
        xit--;
        xit--;
        xit--;

        CPPUNIT_ASSERT( *xit == 5 );
    }

    void test_consit_minusminus_3 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.end();
        xit--;
        xit--;
        xit--;
        xit--;

        CPPUNIT_ASSERT( *xit == 4 );
    }


    // ----
    //  ++
    // ----
    void test_consit_plusplus_1 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.begin();
        xit++;

        CPPUNIT_ASSERT( *xit == 5 );
    }

    void test_consit_plusplus_2 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.begin();
        xit++;
        xit++;

        CPPUNIT_ASSERT( *xit == 6 );
    }

    void test_consit_plusplus_3 () {
        C x;

        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        x.push_back(7);

        typename C::iterator xit =  x.begin();
        xit++;
        xit++;
        xit++;

        CPPUNIT_ASSERT( *xit == 7 );
    }




//-------------------------------------------------------------------------------------------------------
//MYDEQUE TESTS
//-------------------------------------------------------------------------------------------------------
    // ----
    // default constructor test
    // ----

    void test_default_constructor_1 () {
        C x;
        CPPUNIT_ASSERT(x.size() == 0);}
        
    void test_default_constructor_2 () {
        C x;
        x.push_back(9);
        CPPUNIT_ASSERT(x.back() == 9);}

    void test_default_constructor_3 () {
        C x;
        x.push_back(9);
        CPPUNIT_ASSERT(x.size() == 1);}

    // ----
    // sized constructor test
    // ----
    void test_sized_constructor_1 () {
        C x(3, 3);
        CPPUNIT_ASSERT(x.front() == 3);
        CPPUNIT_ASSERT(x.back() == 3);
        CPPUNIT_ASSERT(x.size() == 3);}
    
    void test_sized_constructor_2 () {
        C x(6666, 3);
        CPPUNIT_ASSERT(x.front() == 3);
        CPPUNIT_ASSERT(x.back() == 3);
        CPPUNIT_ASSERT(x.size() == 6666);}
    
    void test_sized_constructor_3 () {
        C x(312, 30);
        CPPUNIT_ASSERT(x.front() == 30);
        CPPUNIT_ASSERT(x.back() == 30);
        CPPUNIT_ASSERT(x.size() == 312);}

    void test_sized_constructor_4 () {
        C x(3, 3);
        x.push_back(9);
        x.push_back(10);
        x.push_back(11);
        CPPUNIT_ASSERT(x.back() == 11);}

    

    // ----
    // copy constructor test
    // ----
    void test_copy_constructor_1 () {
        C x(3, 3);
        C x_c(x);
        CPPUNIT_ASSERT(x  ==  x_c);}
        
    void test_copy_constructor_2 () {
        C x(5000, 3);
        C x_c(x);
        CPPUNIT_ASSERT(x  ==  x_c);}

    void test_copy_constructor_3 () {
        C x(333, 55);
        C x_c(x);
        CPPUNIT_ASSERT(x  ==  x_c);}
        
        

    // ----
    // assignment
    // ----
        
    void test_assignment_1 () {
        C x(3, 3);
        C x_a = x;
        CPPUNIT_ASSERT(x  ==  x_a);}
        
    void test_assignment_2 () {
        C x(3, 3);
        C x_a = x;
        CPPUNIT_ASSERT(x  ==  x_a);}

    void test_assignment_3 () {
        C x(3, 3);
        C x_a = x;
        CPPUNIT_ASSERT(x  ==  x_a);}
        
    // ----
    // bracket
    // ----
    void test_bracket_1 () {
        C x;
        x.push_back(0);
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        CPPUNIT_ASSERT(x[0]  ==  0);
    }
        
    void test_bracket_2 () {
        C x;
        x.push_back(0);
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        CPPUNIT_ASSERT(x[3]  ==  3);
    }
        
    void test_bracket_3 () {
        C x;
        x.push_back(0);
        x.push_back(1);
        x.push_back(2);
        x.push_back(3);
        x.push_back(4);
        x.push_back(5);
        x.push_back(6);
        CPPUNIT_ASSERT(x[6]  ==  6);
    }
        

// ----
// begin
// ----        
    void test_begin_1 () {
        C x;
        x.push_back(0);
        typename C::iterator xit = x.begin();
        CPPUNIT_ASSERT(*xit == 0);}
        
    void test_begin_2 () {
        C x;
        x.push_back(1);
        typename C::iterator xit = x.begin();
        CPPUNIT_ASSERT(*xit  ==  1);}

    void test_begin_3 () {
        C x;
        x.push_back(0);
        x.push_back(1);
        x.push_back(2);
        typename C::iterator xit = x.begin();
        ++xit;
        ++xit;
        CPPUNIT_ASSERT(*xit  ==  2);}
        
// ----
// constbegin
// ----        
    void test_constbegin_1 () {
        const C x(3,3);
        typename C::const_iterator xit = x.begin();
        CPPUNIT_ASSERT(*xit == 3);}
        
    void test_constbegin_2 () {
        const C x(3333,1);
        typename C::const_iterator xit = x.begin();
        CPPUNIT_ASSERT(*xit  ==  1);}

    void test_constbegin_3 () {
        const C x(342,2);
        typename C::const_iterator xit = x.begin();
        ++xit;
        ++xit;
        CPPUNIT_ASSERT(*xit  ==  2);}
        

// ----
// end
// ----        
    void test_end_1 () {
        C x;
        x.push_back(0);
        typename C::iterator xit = x.end();
        --xit;
        CPPUNIT_ASSERT(*xit == 0);}
        
    void test_end_2 () {
        C x;
        x.push_back(1);
        typename C::iterator xit = x.end();
        --xit;
        CPPUNIT_ASSERT(*xit  ==  1);}

    void test_end_3 () {
        C x;
        x.push_back(0);
        x.push_back(1);
        x.push_back(2);
        typename C::iterator xit = x.end();
        --xit;
        --xit;
        --xit;
        CPPUNIT_ASSERT(*xit  ==  0);}


// ----
//  const end
// ----        
    void test_constend_1 () {
        const C x(1,2);
        typename C::const_iterator xit = x.end();
        --xit;
        CPPUNIT_ASSERT(*xit == 2);}
        
    void test_constend_2 () {
        const C x(112,222);
        typename C::const_iterator xit = x.end();
        --xit;
        CPPUNIT_ASSERT(*xit  ==  222);}

    void test_constend_3 () {
        const C x(342,2);
        typename C::const_iterator xit = x.end();
        --xit;
        --xit;
        CPPUNIT_ASSERT(*xit  ==  2);}












                                
    // -----
    // clear
    // -----
                
    void test_clear_1 () {
        C x;
        x.clear();
        CPPUNIT_ASSERT(x.empty());}
                
    void test_clear_2 () {
        C x(100);
        x.clear();
        CPPUNIT_ASSERT(x.empty());}        
                    
    void test_clear_3() {
        C x(10);
        x.clear();
        CPPUNIT_ASSERT(x.begin() == x.end());}
                
                
        // -----
    // empty
    // -----
                
    void test_empty_1 () {
        C x;
        CPPUNIT_ASSERT(x.empty());}
                
    void test_empty_2 () {
        C x;
        x.push_front(2);
        CPPUNIT_ASSERT(!x.empty());}        
                    
    void test_empty_3() {
        C x(10);
        for(int i = 1; i <= 10; ++i)
            x.pop_front();
        CPPUNIT_ASSERT(x.empty());}
                
                
    // -----
    // erase
    // -----
        
    void test_erase_1 () {
        C x(1);
        x.erase(x.begin());
        CPPUNIT_ASSERT(x.size() == 0);
        }
                
    void test_erase_2 () {
        C x(10, 10);
        typename C::iterator it = x.begin();
        for(int i = 1; i <= 10; ++i) 
            it = x.erase(it);
        CPPUNIT_ASSERT(it == x.end());}        

    void test_erase_3() {
        C x(2, 2); //2 2
        C y(1, 2); //2
        y.push_back(3); // 2 3
        y.push_back(2); // 2 3 2
        y.erase(++y.begin()); // 2 2
        CPPUNIT_ASSERT(x.size() == y.size());
        CPPUNIT_ASSERT(x[0] == y[0]);
        CPPUNIT_ASSERT(x[1] == y[1]);}
                
        
    // -----
    // front
    // -----
                
    void test_front_1 () {
        C x;
        x.push_back(1);
        CPPUNIT_ASSERT(x.front() == 1);}
                
    void test_front_2 () {
        C x;
        x.push_front(2);
        CPPUNIT_ASSERT(x.front() == 2);}        
                    
    void test_front_3() {
        C x(10);
        for(int i = 1; i <= 10; ++i)
            x.front();
        CPPUNIT_ASSERT(x.size() == 10);}
            

// ----
// back
// ----
                
    void test_back_1 () {
        C x;
        x.push_back(1);
        CPPUNIT_ASSERT(x.back() == 1);}
                
    void test_back_2 () {
        C x;
        x.push_front(2);
        CPPUNIT_ASSERT(x.back() == 2);}        
                    
    void test_back_3() {
        C x(10);
        for(int i = 1; i <= 10; ++i)
            x.back();
        CPPUNIT_ASSERT(x.size() == 10);}
                
// ------
// insert
// ------
        
    void test_insert_1 () {
        C x(1);
        x.insert(x.begin(), 2);
        C y(1);
        y.push_front(2);
        CPPUNIT_ASSERT(x.front() == y.front());}
        
                
    void test_insert_2 () {
        C x(1);
        x.insert(x.end(), 2);
        C y(1);
        y.push_back(2);
        CPPUNIT_ASSERT(x.back() == y.back());}        
            
    void test_insert_3() {
        C x(2, 2);
        x.insert(++x.begin(), 3);
        C y(1, 2);
        y.push_back(3);
        y.push_back(2);
        CPPUNIT_ASSERT(x[1] == y[1]);
        }
// ---------
// pop_back
// ---------
        
    void test_pop_back_1 () {
        C x(10);
        for(int i = 1; i <= 10; ++i)
            x.pop_back();
        CPPUNIT_ASSERT(x.size() == 0);
        }
                
    void test_pop_back_2 () {
        C x(3, 3);
        for(int i = 1; i <= 3; ++i)
            x.push_back(5);
        CPPUNIT_ASSERT(x.size() == 6);
        for(int i = 3; i < 6; ++i) {
            x.pop_back();
        }
        CPPUNIT_ASSERT(x.size() == 3);
        }
        
                    
    void test_pop_back_3() {
        C x;
        for(int i = 1; i <= 1000; ++i) {
            x.push_front(0);
            x.pop_back();}
        CPPUNIT_ASSERT(x.size() == 0);
        }
                
        
// ----------
// pop_front
// ----------
        
    void test_pop_front_1 () {
        C x(10);
        for(int i = 1; i <= 10; ++i)
            x.pop_front();
        CPPUNIT_ASSERT(x.size() == 0);}
                
    void test_pop_front_2 () {
        C x(3, 3);
        for(int i = 1; i <= 3; ++i)
            x.push_back(5);
        CPPUNIT_ASSERT(x.size() == 6);
        for(int i = 3; i < 6; ++i) {
            x.pop_front();
        }
            CPPUNIT_ASSERT(x.size() == 3);
    }            
            
    void test_pop_front_3() {
        C x;
        for(int i = 1; i <= 1000; ++i) {
            x.push_back(0);
            x.pop_front();
        }
        CPPUNIT_ASSERT(x.size() == 0);
    }
              
// ---------
// push_back
// ---------
        
    void test_push_back_1 () {
        C x;
        for(int i = 1; i <= 3; ++i)
            x.push_back(3);
        CPPUNIT_ASSERT(x.size() == 3);
        for(int i = 0; i < 3; ++i)
            CPPUNIT_ASSERT(x[i] == 3);}        
                    
    void test_push_back_2 () {
        C x(3, 3);
        for(int i = 1; i <= 3; ++i)
            x.push_back(5);
        CPPUNIT_ASSERT(x.size() == 6);
        for(int i = 3; i < 6; ++i)
            CPPUNIT_ASSERT(x[i] == 5);}        
                    
    void test_push_back_3() {
        C x(3, 3);
        for(int i = 1; i <= 25; ++i)
            x.push_back(i);
        CPPUNIT_ASSERT(x.size() == 28);}
                
    
// ----------
// push_front
// ----------
        
    void test_push_front_1 () {
        C x;
        x.push_front(3);
        x.push_front(3);
        x.push_front(3);

        CPPUNIT_ASSERT(x.size() == 3);

        for(int i = 0; i < 3; ++i)
        {
            CPPUNIT_ASSERT(x[i] == 3);
        }
    }        
                    
    void test_push_front_2 () {
        C x(3, 3);
        x.push_front(5);
        x.push_front(5);
        x.push_front(5);

        // 5 5 5 3 3 3
        CPPUNIT_ASSERT(x.size() == 6);
        for(int i = 0; i < 3; ++i)
            CPPUNIT_ASSERT(x[i] == 5);}        
                    
    void test_push_front_3() {
        C x(3, 3);
        for(int i = 1; i <= 25; ++i)
            x.push_front(i);
        CPPUNIT_ASSERT(x.size() == 28);
        }
        
    // ------
    // resize
    // ------

    void test_resize_1 () {
        C x;
        CPPUNIT_ASSERT(x.size() == 0);
        x.resize(9000);
        CPPUNIT_ASSERT(x.size() == 9000);
    }

    void test_resize_2 () {
        C x(3);
        CPPUNIT_ASSERT(x.size() == 3);
        x.resize(2);
        CPPUNIT_ASSERT(x.size() == 2);}

    void test_resize_3 () {
        C x(3, 3);
        C y;
        y.resize(3, 3);
        CPPUNIT_ASSERT(x == y);}
        
    void test_resize_4 () {
        C x(3, 3);
        for(int i = 1; i <= 3; ++i)
            x.push_back(5);
        C y(x);
        y.resize(3);
        CPPUNIT_ASSERT(y.size() == 3);
        for(int i = 0; i < 3; ++i)
            CPPUNIT_ASSERT(y[i] == 3);}
        


// ----
// size
// ----

    void test_size_1 () {
        C x(9000);
        CPPUNIT_ASSERT(x.size() == 9000);}

    void test_size_2 () {
        C x(3);
        CPPUNIT_ASSERT(x.size() == 3);}

    void test_size_3 () {
        C x;
        CPPUNIT_ASSERT(x.size() == 0);}
        
    void test_size_4 () {
        C x(3);
        for(int i = 2; i >= 0; --i) {
            x.pop_back();
            CPPUNIT_ASSERT(x.size() == i);}}
        

// ----
// swap
// ----
    
    void test_swap_1() {
        C x;
        C y(15);
        x.swap(y);
        CPPUNIT_ASSERT(x.size() == 15);
        CPPUNIT_ASSERT(y.size() == 0);}
        
    void test_swap_2() {
        C x(3, 3); // 3 3 3
        C y(3, 5); // 5 5 5
        x.swap(y);
        CPPUNIT_ASSERT(x.size() == 3);
        CPPUNIT_ASSERT(x.size() == 3);
        CPPUNIT_ASSERT(x.back() == 5);
        CPPUNIT_ASSERT(y.back() == 3);}
        
    void test_swap_3() {
        C x(2, 3);
        C y(3, 3);
        x.push_back(3);
        x.swap(y);
        x.push_back(3);
        CPPUNIT_ASSERT(x.size() == 4);
        CPPUNIT_ASSERT(y.size() == 3);}



        
        
//-------------------------------------------------------------------------------------------------------
//SUITE
//-------------------------------------------------------------------------------------------------------
 
    CPPUNIT_TEST_SUITE(TestDeque);

//iterator tests
    CPPUNIT_TEST(test_it_equal_1);
    CPPUNIT_TEST(test_it_equal_2);
    CPPUNIT_TEST(test_it_equal_3);

    CPPUNIT_TEST(test_it_plusequal_1);
    CPPUNIT_TEST(test_it_plusequal_2);
    CPPUNIT_TEST(test_it_plusequal_3);

    CPPUNIT_TEST(test_it_minusequal_1);
    CPPUNIT_TEST(test_it_minusequal_2);
    CPPUNIT_TEST(test_it_minusequal_3);

    CPPUNIT_TEST(test_it_star_1);
    CPPUNIT_TEST(test_it_star_2);
    CPPUNIT_TEST(test_it_star_3);

    CPPUNIT_TEST(test_it_plusplus_1);
    CPPUNIT_TEST(test_it_plusplus_2);
    CPPUNIT_TEST(test_it_plusplus_3);

    CPPUNIT_TEST(test_it_minusminus_1);
    CPPUNIT_TEST(test_it_minusminus_2);
    CPPUNIT_TEST(test_it_minusminus_3);

//const iterator tests
    CPPUNIT_TEST(test_consit_equal_1);
    CPPUNIT_TEST(test_consit_equal_2);
    CPPUNIT_TEST(test_consit_equal_3);

    CPPUNIT_TEST(test_consit_plusequal_1);
    CPPUNIT_TEST(test_consit_plusequal_2);
    CPPUNIT_TEST(test_consit_plusequal_3);

    CPPUNIT_TEST(test_consit_minusequal_1);
    CPPUNIT_TEST(test_consit_minusequal_2);
    CPPUNIT_TEST(test_consit_minusequal_3);

    CPPUNIT_TEST(test_consit_star_1);
    CPPUNIT_TEST(test_consit_star_2);
    CPPUNIT_TEST(test_consit_star_3);

    CPPUNIT_TEST(test_consit_plusplus_1);
    CPPUNIT_TEST(test_consit_plusplus_2);
    CPPUNIT_TEST(test_consit_plusplus_3);

    CPPUNIT_TEST(test_consit_minusminus_1);
    CPPUNIT_TEST(test_consit_minusminus_2);
    CPPUNIT_TEST(test_consit_minusminus_3);

//mydeque
    CPPUNIT_TEST(test_default_constructor_1);
    CPPUNIT_TEST(test_default_constructor_2);
    CPPUNIT_TEST(test_default_constructor_3);

    CPPUNIT_TEST(test_sized_constructor_1);
    CPPUNIT_TEST(test_sized_constructor_2);
    CPPUNIT_TEST(test_sized_constructor_3);
    CPPUNIT_TEST(test_sized_constructor_4);

    CPPUNIT_TEST(test_copy_constructor_1);
    CPPUNIT_TEST(test_copy_constructor_2);
    CPPUNIT_TEST(test_copy_constructor_3);

    CPPUNIT_TEST(test_assignment_1);
    CPPUNIT_TEST(test_assignment_2);
    CPPUNIT_TEST(test_assignment_3);

    CPPUNIT_TEST(test_bracket_1);
    CPPUNIT_TEST(test_bracket_2);
    CPPUNIT_TEST(test_bracket_3);

    CPPUNIT_TEST(test_begin_1);
    CPPUNIT_TEST(test_begin_2);
    CPPUNIT_TEST(test_begin_3);

    CPPUNIT_TEST(test_constbegin_1);
    CPPUNIT_TEST(test_constbegin_2);
    CPPUNIT_TEST(test_constbegin_3);

    CPPUNIT_TEST(test_end_1);
    CPPUNIT_TEST(test_end_2);
    CPPUNIT_TEST(test_end_3);

    CPPUNIT_TEST(test_constend_1);
    CPPUNIT_TEST(test_constend_2);
    CPPUNIT_TEST(test_constend_3);
    
    CPPUNIT_TEST(test_clear_1);
    CPPUNIT_TEST(test_clear_2);
    CPPUNIT_TEST(test_clear_3);

    CPPUNIT_TEST(test_empty_1);
    CPPUNIT_TEST(test_empty_2);
    CPPUNIT_TEST(test_empty_3);

    CPPUNIT_TEST(test_erase_1);
    CPPUNIT_TEST(test_erase_2);
    CPPUNIT_TEST(test_erase_3);

    CPPUNIT_TEST(test_back_1);
    CPPUNIT_TEST(test_back_2);
    CPPUNIT_TEST(test_back_3);

    CPPUNIT_TEST(test_front_1);
    CPPUNIT_TEST(test_front_2);
    CPPUNIT_TEST(test_front_3);

    CPPUNIT_TEST(test_insert_1);
    CPPUNIT_TEST(test_insert_2);
    CPPUNIT_TEST(test_insert_3);

    CPPUNIT_TEST(test_pop_back_1);
    CPPUNIT_TEST(test_pop_back_2);
    CPPUNIT_TEST(test_pop_back_3);

    CPPUNIT_TEST(test_pop_front_1);
    CPPUNIT_TEST(test_pop_front_2);
    CPPUNIT_TEST(test_pop_front_3);

    CPPUNIT_TEST(test_push_back_1);
    CPPUNIT_TEST(test_push_back_2);
    CPPUNIT_TEST(test_push_back_3);

    CPPUNIT_TEST(test_push_front_1);
    CPPUNIT_TEST(test_push_front_2);
    CPPUNIT_TEST(test_push_front_3);

    CPPUNIT_TEST(test_resize_1);
    CPPUNIT_TEST(test_resize_2);
    CPPUNIT_TEST(test_resize_3);
    CPPUNIT_TEST(test_resize_4);

    CPPUNIT_TEST(test_size_1);
    CPPUNIT_TEST(test_size_2);
    CPPUNIT_TEST(test_size_3);

    CPPUNIT_TEST(test_swap_1);
    CPPUNIT_TEST(test_swap_2);
    CPPUNIT_TEST(test_swap_3);

    
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);        // turn off synchronization with C I/O
    CppUnit::TextTestRunner tr;
    tr.addTest(TestDeque< MyDeque<int> >::suite());
    tr.addTest(TestDeque<   deque<int> >::suite());
    tr.run();

    return 0;}
