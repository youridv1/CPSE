#include "mySet.hpp"
#include "catch.hpp"
#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN

TEST_CASE( "add values and output" ){
    mySet test;
    test.add(9);
    test.add(10);
    test.add(5);
    test.add(7);
    test.add(5);
    test.add(3);
    test.add(4);
    test.add(9);
    std::stringstream a;
    a << test;
    REQUIRE(a.str() == "9 10 5 7 3 4 ");
}
