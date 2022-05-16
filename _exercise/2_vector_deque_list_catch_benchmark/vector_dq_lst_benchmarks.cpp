#define CATCH_CONFIG_ENABLE_BENCHMARKING
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "test_helpers.hpp"

#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>

using namespace TestsHelpers;

constexpr int64_t n = 10'000;

const auto data_ints = [] {
    std::vector<int> container;
    container.reserve(n);
    std::random_device rd;
    std::mt19937_64 rnd {rd()};
    std::uniform_int_distribution<int> distr(-1'000'000, 1'000'000);

    auto size = n;

    for (int64_t i = 0; i < size; ++i)
    {
        container.push_back(distr(rnd));
    }

    return container;
}();

const auto data_objects = [] {
    std::vector<Tester> container;

    std::random_device rd;
    std::mt19937_64 rnd {rd()};

    for (int64_t i = 0; i < n; ++i)
    {
        container.emplace_back(rnd_string(rnd), rnd_string(rnd), rnd_vector(rnd));
    }

    return container;
}();

using namespace TestsHelpers;

TEMPLATE_TEST_CASE("push_backs of ints", "[push_back]", (std::vector<int>), (std::deque<int>), (std::list<int>))
{
    using Container = TestType;

    BENCHMARK("push_back")
    {
        Container container;

        for (const auto& item : data_ints)
        {
            container.push_back(item);
        }
    };
}

TEST_CASE("--- sorting ---")
{
    std::cout << "\n\n#################################################################################\n\n";
}

TEMPLATE_TEST_CASE("sorting ints", "[sort]", (std::vector<int>), (std::deque<int>))
{
    using Container = TestType;

    Container container(data_ints.begin(), data_ints.end());

    BENCHMARK("sort")
    {
        sort(container.begin(), container.end());
        return container.front();
    };
}

TEST_CASE("sorting ints - std::list<int>")
{
    std::list<int> container(data_ints.begin(), data_ints.end());

    BENCHMARK("sort")
    {
        container.sort();
        return container.front();
    };
}

TEST_CASE("--- push_backs of objects ---")
{
    std::cout << "\n\n#################################################################################\n\n";
}

TEMPLATE_TEST_CASE("push_backs of objects", "[push_back]", (std::vector<Tester>), (std::deque<Tester>), (std::list<Tester>))
{
    using Container = TestType;

    BENCHMARK("push_back")
    {
        Container container;

        for (const auto& item : data_objects)
        {
            container.push_back(item);
        }
    };
}

TEST_CASE("--- sorting objects ---")
{
    std::cout << "\n\n#################################################################################\n\n";
}

TEMPLATE_TEST_CASE("sorting obejcts", "[sort]", (std::vector<Tester>), (std::deque<Tester>))
{
    using Container = TestType;

    Container container(data_objects.begin(), data_objects.end());

    BENCHMARK("sort")
    {
        sort(container.begin(), container.end());
        return container.front();
    };
}

TEST_CASE("sorting obejcts - std::list<Tester>")
{
    std::list<Tester> container(data_objects.begin(), data_objects.end());

    BENCHMARK("sort")
    {
        container.sort();
        return container.front();
    };
}