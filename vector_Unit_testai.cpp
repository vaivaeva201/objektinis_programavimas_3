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

    SECTION("shrink_to_fit")
    {
        for (int i = 0; i < 5; ++i) 
        {
            v.push_back(i);
        }
        v.reserve(100);
        REQUIRE(v.capacity() >= 100);
        v.shrink_to_fit();
        REQUIRE(v.capacity() == v.size());
    }
//
    SECTION("resize")
    {
        Vector<int> v;
        v.reserve(2);
        v.push_back(1);
        v.push_back(2);
        v.push_back(3); 

        REQUIRE(v.size() == 3);
        REQUIRE(v.at(0) == 1);
        REQUIRE(v.at(1) == 2);
        REQUIRE(v.at(2) == 3);
        REQUIRE(v.capacity() >= 3);
    }
}

TEST_CASE("prieiga prie elementu", "[Vector]") 
{
    Vector<int> v = {1, 2, 3, 4};

    SECTION("operator[]")
    {
        REQUIRE(v[1] == 2);
        REQUIRE(v[3] == 4);
    }

    SECTION("at")
    {
        REQUIRE(v.at(0) == 1);
        REQUIRE(v.at(3) == 4);
        REQUIRE_THROWS_AS(v.at(4), std::out_of_range);
    }

    SECTION("front")
    {
        REQUIRE(v.front() == 1);

    }

    SECTION("back")
    {
        REQUIRE(v.back() == 4);
    }

    SECTION("data")
    {
        int* ptr = v.data();
        REQUIRE(ptr[0] == 1);
        REQUIRE(ptr[3] == 4);
    }
}

TEST_CASE("elementu pridejimas, salinimas", "[Vector]") 
{
    SECTION("clear")
    {
        Vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.clear();

        REQUIRE(v.size() == 0);
        REQUIRE(v.capacity() == 0);
    }

    SECTION("push_back")
    {
        Vector<int> v;
        v.push_back(2);

        REQUIRE(v.size() == 1);
        REQUIRE(v.at(0) == 2);
    }

    SECTION("pop_back")
    {
        Vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.pop_back();

        REQUIRE(v.size() == 1);
        REQUIRE(v.at(0) == 1);
    }

    SECTION("insert")
    {
        Vector<int> v;
        v.push_back(1);
        v.push_back(3);
        v.insert(1, 2);  

        REQUIRE(v.at(0) == 1);
        REQUIRE(v.at(1) == 2);
        REQUIRE(v.at(2) == 3);
        REQUIRE(v.size() == 3);

        REQUIRE_THROWS_AS(v.insert(10, 100), std::out_of_range);
    }

    SECTION("erase")
    {
        Vector<int> v = {1, 2, 3, 4, 5};
        v.erase(2); 

        REQUIRE(v.size() == 4);
        REQUIRE(v.at(0) == 1);
        REQUIRE(v.at(1) == 2);
        REQUIRE(v.at(2) == 4); 
        REQUIRE(v.at(3) == 5); 

        v.erase(0);
        REQUIRE(v.size() == 3);
        REQUIRE(v.at(0) == 2);

        v.erase(v.size() - 1);
        REQUIRE(v.size() == 2);
        REQUIRE(v.at(1) == 4);

        REQUIRE_THROWS_AS(v.erase(10), std::out_of_range);
    }
}

TEST_CASE("iteratoriai", "[Vector]") 
{

    SECTION("begin")
    {
        
    }

    SECTION("end")
    {
        
    }
}

TEST_CASE("operatoriai", "[Vector]") 
{
    SECTION("operator ==")
    {
        Vector<int> a = {1,2,3,4};
        Vector<int> b = {1,2,3,4};
        REQUIRE(a==b);
    }

    SECTION("operator !=")
    {
        Vector<int> a = {1,2,3,4};
        Vector<int> b = {3,2,3,4};
        REQUIRE(a!=b);
    }

}