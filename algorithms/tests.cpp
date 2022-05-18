#include <algorithm>
#include <numeric>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <cctype>

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
