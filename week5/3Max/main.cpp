// Created by Youri "youridv1" de Vor
// Licensed under the Pakken Wat Je Pakken Kan Public License
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <array>
#include <iostream>
#include <sstream>
#include <vector>

#include "mySet.hpp"

// Test if set accepts duplicates
TEST_CASE("no duplicates") {
    mySet<int, 10> set;
    set.add(1);
    set.add(5);
    set.add(20);
    set.add(20);
    set.add(20);
    set.add(20);
    set.add(100);
    std::stringstream ss;
    ss << set;
    REQUIRE(ss.str() == "1 5 20 100 ");
}

// Test's what happens when trying to add too many values to the set
TEST_CASE("max size") {
    mySet<int, 5> set;
    for (int i = 0; i < 10; i++)
        set.add(i);
    std::stringstream ss;
    ss << set;
    REQUIRE(ss.str() == "0 1 2 3 4 ");
}

// Tests if removing strings works as intended
TEST_CASE("remove string item") {
    mySet<std::string, 5> set;
    set.add("test");
    set.add("string");
    set.add("remove");
    set.remove("remove");
    set.remove("ohno");
    std::stringstream ss;
    ss << set;
    REQUIRE(ss.str() == "test string ");
}

// Test if removing an int works as intended
TEST_CASE("remove int item") {
    mySet<int, 5> set;
    for (int i = 0; i < 5; i++)
        set.add(i);
    set.remove(2);
    std::stringstream ss;
    ss << set;
    REQUIRE(ss.str() == "0 1 4 3 ");
}

// Tests if the max function returns the char with the highest value
TEST_CASE("char max") {
    mySet<char, 10> set;
    for (int i = 0; i < 10; i++)
        set.add('a' + i);
    REQUIRE(set.max() == 'a' + 9); // 106 == 'j'
}

// Tests max with char arrays against the standard c++ implementation
TEST_CASE("std::array<char, 3> max") {
    std::vector<std::array<char, 3>> items = {
        std::array<char, 3>{' ', ' ', ' '},
        std::array<char, 3>{'u', 's', 'e'},
        std::array<char, 3>{'l', 'e', 's'},
        std::array<char, 3>{'s', ' ', 'w'},
        std::array<char, 3>{'a', 't', 'e'},
        std::array<char, 3>{'r', ' ', ':'},
        std::array<char, 3>{'(', ' ', ' '},
    };

    mySet<std::array<char, 3>, 10> set;
    for (const auto& item : items)
        set.add(item);

    // Taken from https://stackoverflow.com/a/36315647/2125072
    REQUIRE(set.max() == *max_element(items.begin(), items.end()));
}
