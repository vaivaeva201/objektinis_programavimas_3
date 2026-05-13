#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "vector.h"

TEST_CASE("Vector konstruktoriai, rule of five", "[Vector]") 
{
    SECTION("Default konstruktorius")
    {
        Vector<int> v;
        REQUIRE(v.size() == 0);
        REQUIRE(v.capacity() == 1);
        REQUIRE(v.empty());
    }

    SECTION("Copy konstruktorius")
    {
        Vector<int> original = {1, 2, 3, 4};
        Vector<int> copy(original);

        REQUIRE(copy.size() == original.size());
        REQUIRE(copy.capacity() == original.capacity());

        for (size_t i = 0; i < original.size(); ++i) {
            REQUIRE(copy.at(i) == original.at(i));
        }
//
        copy.at(0) = 99;
        REQUIRE(original.at(0) == 1);
        REQUIRE(copy.at(0) == 99);
    }

    SECTION("Copy asignment operatorius")
    {
        Vector<int> original = {1, 2, 3};
        Vector<int> copy;
        copy = original;

        REQUIRE(copy.size() == original.size());
        REQUIRE(copy.capacity() == original.capacity());

        for (size_t i = 0; i < original.size(); ++i) {
            REQUIRE(copy.at(i) == original.at(i));
        }
//
        copy.at(1) = 42;
        REQUIRE(original.at(1) == 2);
        REQUIRE(copy.at(1) == 42);
    }

    SECTION("move construktor")
    {
        Vector<int> source = {1, 2, 3};
        Vector<int> moved(std::move(source));

        REQUIRE(moved.size() == 3);
        REQUIRE(moved.at(0) == 1);
        REQUIRE(moved.at(1) == 2);
        REQUIRE(moved.at(2) == 3);

        REQUIRE(source.size() == 0);
    }

    SECTION ("move asignment operator")
    {
        Vector<int> source = {1, 2, 3};
        Vector<int> target;
        target = std::move(source);

        REQUIRE(target.size() == 3);
        REQUIRE(target.at(0) == 1);
        REQUIRE(target.at(1) == 2);
        REQUIRE(target.at(2) == 3);
        REQUIRE(source.size() == 0);
    }

    SECTION ("list constructor")
    {
        Vector<int> v = {1, 2, 3, 4, 5};
        int arr[] = {1, 2, 3, 4, 5};
        REQUIRE(v.size() == 5);
        for (int i = 0; i < v.size(); ++i) {
            REQUIRE(v.at(i) == arr[i]);
        }
    }
}

TEST_CASE("dydis/talpa", "[Vector]") 
{
    Vector<int> v;

    SECTION("empty")
    {
        REQUIRE(v.empty());
        REQUIRE(v.size() == 0);
    }

    SECTION("size ir capacity")
    {
        v.push_back(1);
        v.push_back(2);

        REQUIRE_FALSE(v.empty());
        REQUIRE(v.size() == 2);
        REQUIRE(v.capacity() >= 2); 
    }

    SECTION("max_size")
    {
        size_t expected = std::numeric_limits<size_t>::max() / sizeof(int);
    
        REQUIRE(v.max_size() == expected);
        REQUIRE(v.max_size() > 0); 
    }

    SECTION("reverse")
    {
        size_t oldCap = v.capacity();
        v.reserve(oldCap + 10);
        REQUIRE(v.capacity() == oldCap + 10);
    }

    
}
