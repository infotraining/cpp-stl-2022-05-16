#include <algorithm>
#include <numeric>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <iterator>

#include "catch.hpp"
#include "stl_helpers.hpp"

using namespace std;

TEST_CASE("iterator categories")
{
    std::vector<int> vec = {1, 3, 5, 7, 9, 11};

    SECTION("iterator category")
    {
        auto it = vec.begin();
        ++it;

        it += 1;

        static_assert(
            std::is_same<
                std::iterator_traits<decltype(it)>::iterator_category,
                std::random_access_iterator_tag>::value, "Error");
    }
}


namespace Cpp17
{
    template <typename Iterator>
    void advance_it(Iterator& it, size_t n)
    {
        if constexpr(std::is_same<
                          typename std::iterator_traits<Iterator>::iterator_category,
                          std::random_access_iterator_tag>::value)
        {
            std::cout << "path +=\n";
            it += n;
        }
        else
        {
            std::cout << "path n * ++\n";
            for(size_t i = 0u; i < n; ++i)
                ++it;
        }
    }
}


namespace details
{
    template <typename Iterator>
    void advance_impl(Iterator& it, size_t n, std::random_access_iterator_tag)
    {
        std::cout << "path += n\n";
        it += n;
    }

    template <typename Iterator>
    void advance_impl(Iterator& it, size_t n, std::input_iterator_tag)
    {
        std::cout << "path n * ++\n";
        for(size_t i = 0u; i < n; ++i)
            ++it;
    }
}

template <typename Iterator>
void advance_it(Iterator& it, size_t n)
{
    details::advance_impl(it, n, typename std::iterator_traits<Iterator>::iterator_category{});
}

TEST_CASE("advance")
{
    std::vector<int> vec = {1, 3, 5, 7, 9, 11};
    auto it = vec.begin();

    advance_it(it, 2);

    REQUIRE(*it == 5);
}


template <typename InputIterator, typename OutputIterator>
OutputIterator my_copy(InputIterator first, InputIterator end, OutputIterator out)
{
    for(InputIterator it = first; it != end; ++it, ++out)
    {
        *out = *it;
    }

    return out;
}

template <typename InputIterator, typename OutputIterator, typename Predicate>
OutputIterator my_copy_if(InputIterator first, InputIterator end, OutputIterator out, Predicate pred)
{
    for(InputIterator it = first; it != end; ++it)
    {
        if (pred(*it))
        {
            *out = *it;
            ++out;
        }
    }

    return out;
}

TEST_CASE("iterator categories & algorithms")
{
    SECTION("simple copy")
    {
        std::vector<int> vec = {9, 1, 13, 3, 5, 7, 9, 11};
        std::list<int> lst(vec.size());

        my_copy(vec.begin(), vec.end(), lst.begin());

        helpers::print(lst, "lst");

        std::sort(vec.begin(), vec.end());

        helpers::print(vec, "vec");
    }

    SECTION("copy if")
    {
        std::vector<int> vec = {9, 1, 13, 3, 5, 7, 9, 11};
        std::list<int> lst;

        int threshold = 5;

        //my_copy_if(vec.begin(), vec.end(), std::back_insert_iterator<std::list<int>>(lst), [threshold](int n) { return n > threshold; });
        my_copy_if(vec.begin(), vec.end(), std::back_inserter(lst), [threshold](int n) { return n > threshold; });

        helpers::print(lst, "lst");

        std::sort(vec.begin(), vec.end());

        helpers::print(vec, "vec");
    }
}

struct Lambda_27384527834523578
{
    auto operator()(int a, int b) const { return a + b; }
};

struct Lambda_82376527895627945
{
    const int factor_ = 10;

    auto operator()(int x) const { return x * factor_; }
};

TEST_CASE("lambda")
{
    auto add = [](int a, int b) { return a + b; };

    REQUIRE(add(1, 4) == 5);

    SECTION("is interpreted as")
    {
        auto add = Lambda_27384527834523578{};

        REQUIRE(add(1, 6) == 7);
    }

    int factor = 10;

    auto multiplier = [factor](int x) { return x * factor; };

    REQUIRE(multiplier(5) == 50);
}

TEST_CASE("insert_iterators")
{
    std::vector<int> vec;

    std::back_insert_iterator<std::vector<int>> bit(vec);

    *bit = 1; // vec.push_back(1)
    *bit = 2; // vec.push_back(2)
    *bit = 3; // vec.push_back(3)

    helpers::print(vec, "vec");
}

TEST_CASE("istream & ostream iterators")
{
    std::istream_iterator<int> inp_iter(std::cin);
    std::istream_iterator<int> end_iter;

    std::vector<int> vec(inp_iter, end_iter);

    my_copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

}
