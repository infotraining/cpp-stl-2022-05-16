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

TEST_CASE("STL container - nested types")
{
    std::vector<int> vec_int;

    std::vector<int>::value_type item; // int item
    std::vector<int>::reference ref_item = item; // int& ref_item

    std::vector<int>::iterator it = vec_int.begin();
    REQUIRE(it == vec_int.end());
}

TEST_CASE("std::vector - constructors")
{
    SECTION("default constructor")
    {
        std::vector<int> vec_int;

        REQUIRE(vec_int.size() == 0);
        REQUIRE(vec_int.begin() == vec_int.end());
    }

    SECTION("constructor with size")
    {
        std::vector<int> vec_int(10);

        REQUIRE(vec_int.size() == 10);
        REQUIRE(vec_int.capacity() == 10);
        helpers::print(vec_int, "vec_int");

        std::vector<std::string> words(5, "empty");
        helpers::print(words, "words");
    }

    SECTION("since C++11 - constructor with initializer list")
    {
        std::vector<int> vec = {1, 2, 3, 4, 5};
        REQUIRE(vec.size() == 5);
        helpers::print(vec, "vec");
    }

    SECTION("constructor with range - iterators")
    {
        SECTION("with legacy code")
        {
            int data[10] = {1, 2, 3, 4, 5};
            int* start = std::begin(data); //int* start = data;
            int* end = std::end(data); // int* end = data + 10;

            std::vector<int> vec(start, end);
            helpers::print(vec, "vec");
        }

        SECTION("without legacy")
        {
            std::array<int, 10> data = {1, 2, 3, 4, 5};
            std::vector<int> vec(data.begin(), data.end());
            vec.push_back(11);
            vec.push_back(12);

            std::array<int, 12> big_data;
            std::copy(vec.begin(), vec.end(), big_data.begin());
            helpers::print(big_data, "big_data");
        }
    }
}

TEST_CASE("std::vector - push_backs")
{
    std::vector<int> vec;
    vec.reserve(100);
    helpers::describe(vec, "vec");

    for(int i = 0; i < 100; ++i)
    {
        vec.push_back(i);
        helpers::describe(vec, "vec");
    }

    vec.push_back(100);
    helpers::describe(vec, "vec");

    vec.resize(10);
    helpers::describe(vec, "vec");

    vec.clear();
    helpers::describe(vec, "vec");

    vec.shrink_to_fit();
    helpers::describe(vec, "vec");
}

struct Gadget
{
    int id;
    std::string name;

    Gadget(int id, std::string name) : id{id}, name{std::move(name)}
    {}
};

TEST_CASE("std::vector - emplace_back")
{
    std::vector<Gadget> gadgets;

    gadgets.push_back(Gadget{1, "ipad"});
    gadgets.emplace_back(2, "smartwatch");
}

TEST_CASE("iterating over container")
{
    std::vector<Gadget> gadgets;

    gadgets.push_back(Gadget{1, "ipad"});
    gadgets.emplace_back(2, "smartwatch");

    SECTION("1 - indexing")
    {
        for(size_t i = 0; i < gadgets.size(); ++i)
        {
            std::cout << gadgets[i].name << " ";
        }
        std::cout << "\n";
    }

    SECTION("2 - iterators")
    {
        SECTION("modifing")
        {
            for(std::vector<Gadget>::iterator it = gadgets.begin(); it != gadgets.end(); ++it)
            {
                it->name += "!";
            }

            SECTION("read-only")
            {
                for(std::vector<Gadget>::const_iterator it = gadgets.begin(); it != gadgets.end(); ++it)
                {
                    std::cout << it->name << " ";
                }
                std::cout << "\n";
            }
        }

        SECTION("modifing - C++11")
        {
            for(auto it = gadgets.begin(); it != gadgets.end(); ++it)
            {
                it->name += "!";
            }

            SECTION("read-only - C++11")
            {
                for(auto it = gadgets.cbegin(); it != gadgets.cend(); ++it)
                {
                    std::cout << it->name << " ";
                }
                std::cout << "\n";
            }
        }
    }

    SECTION("3 - range-based-for")
    {
        for(auto& item : gadgets)
        {
            item.name += "!";
        }

        SECTION("is interpreted is as")
        {
            for(auto it = gadgets.begin(); it != gadgets.end(); ++it)
            {
                auto& item = *it;
                item.name += "!";
            }
        }

        for(const auto& item : gadgets)
        {
            std::cout << item.name << " ";
        }
        std::cout << "\n";
    }
}

TEST_CASE("vector + iterators")
{
    std::vector<int> vec(20);
    helpers::print(vec, "vec");

    std::vector<int>::iterator pos = vec.begin();
    pos += 10;

    //    for(auto it = vec.begin(); it != pos; ++it)
    //    {
    //        *it = 42;
    //    }

    std::fill(vec.begin(), pos, 42);

    //    for(auto it = pos; it != vec.end(); ++it)
    //    {
    //        *it = 665;
    //    }

    std::fill(pos, vec.end(), 665);

    helpers::print(vec, "vec");
}


TEST_CASE("invalidating iterators & references")
{
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 9, 10};
    //vec.reserve(100);

    std::vector<int>::iterator pos = vec.begin() + 4;
    int& value = *pos;

    vec.push_back(11); // invalidates all iterators & references pos!!!

    REQUIRE(*pos == 5); // UB
}

namespace helpers
{
    template <typename T>
    void erase(std::vector<T>& vec, const T& value)
    {
        auto new_end = std::remove(vec.begin(), vec.end(), value);
        vec.erase(new_end, vec.end());
    }
}


TEST_CASE("dealing with invalidations")
{
    std::vector<int> vec = {1, 14, 2, 3, 4, 2, 5, 6, 7, 2, 9};

    for(auto it = vec.begin(); it != vec.end(); ++it)
    {
        if (*it == 2)
        {
            it = vec.insert(it, 14);
            ++it;
        }
    }

    helpers::print(vec, "vec");

    vec.push_back(14);

    //auto new_end = std::remove(vec.begin(), vec.end(), 14);
    //vec.erase(new_end, vec.end());

    helpers::erase(vec, 14);

    REQUIRE(vec == std::vector<int>{1, 2, 3, 4, 2, 5, 6, 7, 2, 9});
}

TEST_CASE("indexing")
{
    std::vector<int> vec = {1, 2, 3};

    REQUIRE(vec.front() == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec.back() == 3);

    //vec[10] = 18; // UB

    REQUIRE_THROWS_AS(vec.at(10) = 18, std::out_of_range);
}


namespace Legacy
{
    void print_array(int* data, int size)
    {
        for(int* ptr = data; ptr < data + size; ++ptr)
        {
            std::cout << *ptr << " ";
        }
        std::cout << "\n";
    }
}

TEST_CASE("vector + legacy")
{
    std::vector<int> vec = {1, 2, 3, 4};

    Legacy::print_array(&vec[0], vec.size());

    vec.assign(10, 4);

    Legacy::print_array(vec.data(), vec.size());

    vec.assign({1, 2, 3, 4});

    Legacy::print_array(vec.data(), vec.size());
}

TEST_CASE("append")
{
    std::vector<int> vec = {1, 2, 3, 4};

    vec.insert(vec.end(), {5, 6, 7, 8});

    helpers::print(vec, "vec");

    vector<int> data = {9, 10, 11};

    helpers::describe(vec);

    vec.insert(vec.end(), data.begin(), data.end());

    helpers::print(vec, "vec");

    helpers::describe(vec);
}


TEST_CASE("vector<bool>")
{
    std::vector<bool> flags = {0, 1, 1, 0, 0, 0, 1};

    helpers::print(flags, "flags");

    flags[3] = 1;

    helpers::print(flags, "flags");

    flags.flip();

    helpers::print(flags, "flags");

    flags[3].flip();

    //bool& ref_flag = flags[3];
}


TEST_CASE("std::deque")
{
    std::deque<int> dq = {1, 2, 3, 4, 5, 6};

    dq.push_back(7);
    dq.push_front(0);

    helpers::print(dq, "dq");

    SECTION("indexing")
    {
        dq[3] = -4;
    }

    //std::deque<int>::iterator pos = dq.begin() + dq.size() / 2;
    std::deque<int>::iterator pos = dq.begin();
    std::advance(pos, dq.size() / 2);


    std::fill(dq.begin(), pos, 42);

    helpers::print(dq, "dq");
}

TEST_CASE("std::list")
{
    std::list<int> lst = {1, 2, 3, 4, 5, 6, 7};

    lst.push_front(0);
    lst.push_back(8);

    std::list<int>::iterator it = lst.begin();
//    for(int i = 0; i < lst.size() / 2; ++i)
//        ++it;
    std::advance(it, lst.size() / 2);

    lst.insert(it, 665);

    helpers::print(lst, "lst");

    auto pos = std::next(lst.begin(), 4);

    lst.erase(lst.begin());

    REQUIRE(*pos == 665);
}

TEST_CASE("special operations for list")
{
    std::list<int> lst1 = helpers::create_rnd_dataset<list>(15, 0, 20);
    std::list<int> lst2 = helpers::create_rnd_dataset<list>(15, 0, 20, 42);
    helpers::print(lst1, "lst1");
    helpers::print(lst2, "lst1");

    lst1.sort();
    lst2.sort();
    helpers::print(lst1, "lst1");
    helpers::print(lst2, "lst2");

    lst1.merge(lst2);
    helpers::print(lst1, "lst1 after merge");
    helpers::print(lst2, "lst2 after merge");

    lst1.remove(13);
    lst1.unique();
    helpers::print(lst1, "lst1 after unique");

    auto pos1 = std::next(lst1.begin(), 2);
    auto pos2 = std::next(pos1, 6);
    lst2.splice(lst2.begin(), lst1, pos1, pos2);
    helpers::print(lst1, "lst1 after splice");
    helpers::print(lst2, "lst2 after splice");
}


TEST_CASE("reverse iterators")
{
    std::vector<int> vec = {1, 2, 3, 4, 5};

    for(auto it = vec.rbegin(); it != vec.rend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}
