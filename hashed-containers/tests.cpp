#include <algorithm>
#include <numeric>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>

#include "catch.hpp"
#include "stl_helpers.hpp"

using namespace std;

template <typename HashedContainer>
void print_unordered(const HashedContainer& container, const std::string& prefix)
{
    cout << prefix << ": "
         << "size: " << container.size()
         << "; bucket_count: " << container.bucket_count()
         << "; max_load_factor: " << container.max_load_factor()
         << "; load_factor: " << container.load_factor()
         << "\n";
}

TEST_CASE("stl helpers")
{
    auto vec = helpers::create_rnd_dataset(20);
    helpers::print(vec, "vec");
    helpers::describe(vec);
}
