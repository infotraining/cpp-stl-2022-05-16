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

namespace Explain
{

    template <typename TContainer>
    typename TContainer::iterator begin(TContainer& container)
    {
        return container.begin();
    }

    template <typename TContainer>
    typename TContainer::iterator end(TContainer& container)
    {
        return container.end();
    }

    template <typename T, size_t N>
    T* begin(T(&tab)[N])
    {
        return tab;
    }

    template <typename T, size_t N>
    T* end(T(&tab)[N])
    {
        return tab + N;
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

//    for (int i = 0; i < 100; ++i)
//        data[i] = distr(rnd);
    std::generate(std::begin(data), std::end(data), [&]{ return distr(rnd); });

    SECTION("create a vector containing copy of all elements from data")
    {
        std::vector<int> vec(std::begin(data), std::end(data));

        // 1. for with push_backs
        // 2. insert with iterators
        // vec.insert(vec.end(), std::begin(data), std::end(data));

        REQUIRE(equal(begin(data), end(data), vec.begin(), vec.end()));

        SECTION("create a copy of a vector")
        {
            std::vector<int> vec2 = vec;

            REQUIRE_THAT(vec, Equals(vec2));

            SECTION("clear all items from vec2 and free a memory")
            {
                vec2.clear();
                vec2.shrink_to_fit();

                REQUIRE(vec2.size() == 0);
                REQUIRE(vec2.capacity() == 0);
            }
        }

        SECTION("calculate average for a vec using legacy code")
        {
            // TODO
            double avg = LegacyCode::avg(vec.data(), vec.size());

            REQUIRE(avg == Approx(9.45));
        }

        const int tail[] = {1, 2, 3, 4, 5};

        SECTION("append tail to vec")
        {
            vec.insert(vec.end(), std::begin(tail), std::end(tail));

            REQUIRE(equal(vec.end() - 5, vec.end(), begin(tail), end(tail)));
        }

        SECTION("create vector containing items from vec but in reveresed order")
        {
            sort(vec.begin(), vec.end());

            vector<int> reversed_vec(vec.rbegin(), vec.rend());

//            for(auto it = vec.rbegin(); it != vec.rend(); it++)
//            {
//                reversed_vec.push_back(*it);
//            }

//            vector<int> reversed_vec = vec;
//            std::reverse(reversed_vec.begin(), reversed_vec.end());

            REQUIRE(equal(reversed_vec.begin(), reversed_vec.end(), vec.rbegin(), vec.rend()));
        }

        SECTION("create a list from vector")
        {
            // TODO
            list<int> numbers(vec.begin(), vec.end());

            REQUIRE(equal(vec.begin(), vec.end(), numbers.begin()));

            SECTION("remove duplicates from numbers")
            {
                numbers.sort();
                numbers.unique();

                REQUIRE(adjacent_find(numbers.begin(), numbers.end()) == numbers.end());
            }

            SECTION("remove evens from a list")
            {
                numbers.remove_if(&LegacyCode::is_even);

                REQUIRE(all_of(numbers.begin(), numbers.end(), [](int x) { return x % 2; }));
            }

            SECTION("move evens to another list")
            {
                list<int> evens;

                for(auto it = numbers.begin(); it != numbers.end(); )
                {
                    if (LegacyCode::is_even(*it))
                    {
                        auto node_to_move = it;
                        ++it;
                        evens.splice(evens.end(), numbers, node_to_move);
                        continue;
                    }

                    ++it;
                }

                REQUIRE(all_of(numbers.begin(), numbers.end(), [](int x) { return x % 2; }));
                REQUIRE(all_of(evens.begin(), evens.end(), [](int x) { return x % 2 == 0; }));
            }
        }
    }
}
