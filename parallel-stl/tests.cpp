#include <algorithm>
#include <numeric>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <execution>

#include "catch.hpp"
#include "stl_helpers.hpp"

using namespace std;

TEST_CASE("stl helpers")
{
    auto vec = helpers::create_rnd_dataset(2'000'000);
    helpers::print(vec, "vec");
    helpers::describe(vec);

    std::sort(std::execution::par, vec.begin(), vec.end());
}
