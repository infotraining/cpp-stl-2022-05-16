#include <algorithm>
#include <numeric>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <execution>

#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include "catch.hpp"
#include "stl_helpers.hpp"

using namespace std;

TEST_CASE("stl helpers")
{
    auto vec = helpers::create_rnd_dataset(1'000'000);

    BENCHMARK("sort - classic") {
        std::sort(vec.begin(), vec.end());
        return vec.front();
    };

    BENCHMARK("sort - seq") {
        std::sort(std::execution::seq, vec.begin(), vec.end());
        return vec.front();
    };

    BENCHMARK("sort - par") {
        std::sort(std::execution::par, vec.begin(), vec.end());
        return vec.front();
    };

    BENCHMARK("sort - par_unseq") {
        std::sort(std::execution::par_unseq, vec.begin(), vec.end());
        return vec.front();
    };

    BENCHMARK("count_if - classic")
    {
        return std::count_if(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });
    };

    BENCHMARK("count_if - par_unseq")
    {
        return std::count_if(std::execution::par_unseq, vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });
    };

    BENCHMARK("accumulate")
    {
        return std::accumulate(vec.begin(), vec.end(), 0ull, [](uint64_t total, int x) { return total + x * x; });
    };

    BENCHMARK("reduce")
    {
        return std::reduce(std::execution::par_unseq, vec.begin(), vec.end(), 0ull,
            [](uint64_t total, int x) { return total + x * x; });
    };

    BENCHMARK("transform_reduce")
    {
        return std::transform_reduce(std::execution::par_unseq, vec.begin(), vec.end(), 0ull,
            std::plus<>{}, [](int x) { return x * x; });
    };
}
