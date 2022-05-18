#include <algorithm>
#include <numeric>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <cctype>
#include <iterator>

#include "catch.hpp"
#include "stl_helpers.hpp"

using namespace std;

void print_item(int x)
{
    std::cout << "item: " << x << "\n";
}

struct BiggerThan
{
    int value;

    bool operator()(int x) const { return x > value; }
};

TEST_CASE("function & predicates")
{
    auto vec = helpers::create_rnd_dataset(20, 0, 200);

    std::for_each(vec.begin(), vec.end(), &print_item);

    auto pos_gt_190 = std::find_if(vec.begin(), vec.end(), BiggerThan{190});

    if (pos_gt_190 != vec.end())
        std::cout << "First bigger than 100: " << *pos_gt_190 << "\n";

    std::cout << "Index: " << std::distance(vec.begin(), pos_gt_190) << "\n";

    std::cout << "Count > 100: "
              << std::count_if(vec.begin(), vec.end(), [](int x) { return x > 100; }) << "\n";
}

TEST_CASE("STL functors")
{
    std::plus<int> add;
    REQUIRE(add(1, 10) == 11);

    std::vector<int> data1 = {1, 2, 3};
    int data2[] = {3, 2, 1};

    std::vector<int> sum(3);

    std::transform(data1.begin(), data1.end(), std::begin(data2), sum.begin(), std::plus<int>{});

    helpers::print(sum, "sum");
    REQUIRE(std::all_of(sum.begin(), sum.end(), [](int x) { return x == 4; }));

    std::transform(sum.begin(), sum.end(), sum.begin(), std::negate<int>{});
    helpers::print(sum, "sum");

    std::string text = "text";

    std::transform(text.begin(), text.end(), text.begin(), [](char c) { return std::toupper(c); });

    REQUIRE(text == "TEXT");

    auto vec = helpers::create_rnd_dataset(20);

    std::sort(vec.begin(), vec.end());
    helpers::print(vec, "vec");

    std::sort(vec.begin(), vec.end(), std::greater<int>{});
    helpers::print(vec, "vec");

    std::vector<std::string> words = { "'one'", "'seek & destroy'", "'sad but true'", "'unforgiven'" };
    std::sort(words.begin(), words.end(),
        [](const std::string& a, const std::string& b) { return a.size() < b.size(); });
    helpers::print(words, "words");
}

bool is_palindrome(const std::string& text)
{
    //    string::const_iterator it = text.begin();
    //    string::const_reverse_iterator rit = text.rbegin();

    //    for(; it < rit.base(); ++it, ++rit)
    //    {
    //        if (*it != *rit)
    //            return false;
    //    }

    //    return true;

    auto middle = text.begin() + text.size() / 2;

    return std::equal(text.begin(), middle, text.rbegin());
}

TEST_CASE("is_palindrome")
{
    REQUIRE(is_palindrome("kajak"));
    REQUIRE(is_palindrome("potop"));
    REQUIRE(is_palindrome("kajaki") == false);
}


TEST_CASE("min & max")
{
    auto vec = helpers::create_rnd_dataset(20);

    auto pos_min = std::min_element(vec.begin(), vec.end());

    std::cout << "min_element: " << *pos_min << "\n";
}

TEST_CASE("find_first_of")
{
    std::string text = "token1 token2,token3";
    std::string separators = " ,;:";

    auto pos_sep = std::find_first_of(text.begin(), text.end(), separators.begin(), separators.end());

    std::string token(text.begin(), pos_sep);

    REQUIRE(token == "token1");
}

TEST_CASE("binary searching")
{
    auto vec = helpers::create_rnd_dataset(20);

    std::sort(vec.begin(), vec.end());
    REQUIRE(std::is_sorted(vec.begin(), vec.end()));

    helpers::print(vec, "vec");

    REQUIRE(std::binary_search(vec.begin(), vec.end(), 45));

    auto range_50 = std::equal_range(vec.begin(), vec.end(), 50);

    if(range_50.first == range_50.second)
        vec.insert(range_50.first, 50);

    helpers::print(vec, "vec");
}

TEST_CASE("unique")
{
    auto vec = helpers::create_rnd_dataset(20);
    std::sort(vec.begin(), vec.end());

    SECTION("simple unique")
    {
        auto new_end = std::unique(vec.begin(), vec.end());
        vec.erase(new_end, vec.end());

        helpers::print(vec, "vec");

        REQUIRE(std::adjacent_find(vec.begin(), vec.end()) == vec.end());
    }

    SECTION("unique_copy")
    {
        std::list<int> unique_vec;

        std::unique_copy(vec.begin(), vec.end(), std::front_inserter(unique_vec));

        helpers::print(vec, "vec");
        helpers::print(unique_vec, "unique_vec");

        std::replace_if(unique_vec.begin(), unique_vec.end(), [](int x) { return x % 2 == 0;}, -1);

        helpers::print(unique_vec, "unique_vec");
    }
}

TEST_CASE("sorting")
{
    auto vec = helpers::create_rnd_dataset(100, 0, 500);

    SECTION("5 largest values in vec")
    {
        std::nth_element(vec.begin(), vec.begin() + 5, vec.end(), std::greater<int>{});

        std::copy_n(vec.begin(), 5, std::ostream_iterator<int>(cout, " "));
        std::cout << "\n";
    }

    SECTION("5 largest values in vec (descending order)")
    {
        std::partial_sort(vec.begin(), vec.begin() + 5, vec.end(), std::greater<int>{});

        std::copy_n(vec.begin(), 5, std::ostream_iterator<int>(cout, " "));
        std::cout << "\n";
    }

    SECTION("partial sort copy")
    {
        std::array<int, 5> largest;

        std::partial_sort_copy(vec.begin(), vec.end(), largest.begin(), largest.end(),
            std::greater<int>{});

        helpers::print(largest, "largest");
    }
}

TEST_CASE("partitioning")
{
    auto vec = helpers::create_rnd_dataset(20);

    auto boundary = std::partition(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });

    std::cout << "evens: ";
    std::copy(vec.begin(), boundary, std::ostream_iterator<int>(std::cout, " "));

    std::cout << "\nodds: ";
    std::copy(boundary, vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}

TEST_CASE("itersections")
{
    auto vec1 = helpers::create_rnd_dataset(20);
    auto vec2 = helpers::create_rnd_dataset(20, 0, 100, 888);

    std::sort(vec1.begin(), vec1.end());
    std::sort(vec2.begin(), vec2.end());

    std::vector<int> inter_vec;

    std::set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(),
        std::back_inserter(inter_vec));

    helpers::print(inter_vec, "intersection");
}

TEST_CASE("iota")
{
    std::vector<int> vec(100);

    std::iota(vec.begin(), vec.end(), 1);
    helpers::print(vec, "vec");

    int result = std::accumulate(vec.begin(), vec.end(), 0);

    std::cout << "sum: " << result << "\n";

    std::vector<std::string> words = {"This", "is", "text", "..."};

    std::cout << std::accumulate(words.begin(), words.end(), ""s) << "\n";

    std::vector<double> numbers = {3.14, 4.24, 66.665};
    double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
    std::cout << sum << "\n";

    size_t total_length =
        std::accumulate(words.begin(), words.end(), 0,
            [](int total, const std::string& str) { return total + str.size(); });

    std::cout << "total length: " << total_length << "\n";
}
