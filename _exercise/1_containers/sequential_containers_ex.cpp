#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <list>
#include <random>
#include <vector>
#include <array>
#include <numeric>

namespace LegacyCode
{
    double avg(int array[], size_t size)
    {
        double sum = 0.0;
        for (size_t i = 0; i < size; ++i)
            sum += array[i];

        return sum / size;
    }

    bool is_even(int n)
    {
        return n % 2 == 0;
    }
}

TEST_CASE("Exercises")
{
    using namespace std;

    using Catch::Matchers::Equals;

    constexpr int size = 20;

    int data[size];

    std::mt19937_64 rnd{665};
    std::uniform_int_distribution<> distr{0, 20};

    for (int i = 0; i < 100; ++i)
        data[i] = distr(rnd);

    SECTION("create a vector containing copy of all elements from data")
    {
        // TODO
        std::vector<int> vec;

        REQUIRE(equal(begin(data), end(data), vec.begin(), vec.end()));

        SECTION("create a copy of a vector")
        {
            // TODO
            std::vector<int> vec2;

            REQUIRE_THAT(vec, Equals(vec2));

            SECTION("clear all items from vec2 and free a memory")
            {
                // TODO

                REQUIRE(vec2.size() == 0);
                REQUIRE(vec2.capacity() == 0);
            }
        }

        SECTION("calculate average for a vec using legacy code")
        {
            // TODO
            double avg{};

            REQUIRE(avg == Approx(9.45));
        }

        const int tail[] = {1, 2, 3, 4, 5};

        SECTION("append tail to vec")
        {
            // TODO

            REQUIRE(equal(vec.end() - 5, vec.end(), begin(tail), end(tail)));
        }

        SECTION("create vector containing items from vec but in reveresed order")
        {
            sort(vec.begin(), vec.end());

            // TODO
            vector<int> reversed_vec;

            REQUIRE(equal(reversed_vec.begin(), reversed_vec.end(), vec.rbegin(), vec.rend()));
        }

        SECTION("create a list from vector")
        {
            // TODO
            list<int> numbers;

            REQUIRE(equal(vec.begin(), vec.end(), numbers.begin()));

            SECTION("remove duplicates from numbers")
            {
                // TODO

                REQUIRE(adjacent_find(numbers.begin(), numbers.end()) == numbers.end());
            }

            SECTION("remove evens from a list")
            {
                // TODO

                REQUIRE(all_of(numbers.begin(), numbers.end(), [](int x) { return x % 2; }));
            }

            SECTION("move evens to another list")
            {
                list<int> evens;

                // TODO

                REQUIRE(all_of(numbers.begin(), numbers.end(), [](int x) { return x % 2; }));
                REQUIRE(all_of(evens.begin(), evens.end(), [](int x) { return x % 2 == 0; }));
            }
        }
    }
}