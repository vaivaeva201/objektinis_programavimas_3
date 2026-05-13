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
}
