#include <algorithm>
#include <numeric>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <memory>

#include "catch.hpp"
#include "stl_helpers.hpp"

using namespace std;

TEST_CASE("sets")
{
    std::set<int> set_int = {1, 5, 346, 45, 665, 346, 42, 1, 645, 654, 235, 42, 42};

    helpers::print(set_int, "set_int");

    SECTION("inserting")
    {
        std::pair<std::set<int>::iterator, bool> result = set_int.insert(43);
        REQUIRE(result.second == true);
        REQUIRE(*result.first == 43);

        result = set_int.insert(42);
        REQUIRE(result.second == false);
        REQUIRE(*result.first == 42);
    }

    SECTION("finding & counting")
    {
        auto pos = set_int.find(42);
        if (pos != set_int.end())
            std::cout << "Found " << *pos << "\n";
        else
            std::cout << "42 not found\n";

        REQUIRE(set_int.count(42) == 1);

        set_int.emplace_hint(set_int.end(), 2048);
    }

    SECTION("erasing")
    {
        set_int.erase(42);

        REQUIRE(set_int.count(42) == 0);
    }
}

TEST_CASE("multiset")
{
    std::multiset<int, std::less<int>> mset_int = {1, 5, 346, 45, 665, 346, 42, 1, 645, 654, 235, 42, 42};

    helpers::print(mset_int, "mset_int");

    REQUIRE(mset_int.count(42) == 3);

    auto pos_42_starts = mset_int.lower_bound(42);
    auto pos_42_ends = mset_int.upper_bound(42);

    for(auto it = pos_42_starts; it!= pos_42_ends; ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    REQUIRE(std::distance(pos_42_starts, pos_42_ends) == mset_int.count(42));

    auto it_42_range = mset_int.equal_range(42);
    REQUIRE(it_42_range.first == pos_42_starts);
    REQUIRE(it_42_range.second == pos_42_ends);

    auto it_50_range = mset_int.equal_range(50);

    REQUIRE(it_50_range.first == it_50_range.second);
    mset_int.insert(it_50_range.first, 50);

    helpers::print(mset_int, "mset_int");
}

struct Id
{
    int value;

    bool operator<(const Id& other) const
    {
        return value < other.value;
    }
};


struct ComparePtrsByValue
{
    template <typename Ptr>
    bool operator()(const Ptr& ptr_a, const Ptr& ptr_b) const
    {
        return *ptr_a < *ptr_b;
    }
};


TEST_CASE("sorting criteria")
{
    SECTION("custom < operator")
    {
        std::set<Id> id_set;

        id_set.insert(Id{42});
        id_set.insert(Id{1});
        id_set.insert(Id{665});

        for(const auto& id : id_set)
            std::cout << id.value << " ";
        std::cout << "\n";
    }

    SECTION("descending order")
    {
        std::multiset<int, std::greater<>> mset_int = {1, 5, 346, 45, 665, 346, 42, 1, 645, 654, 235, 42, 42};

        helpers::print(mset_int, "mset_int");
    }

    SECTION("custom comparer")
    {
        SECTION("with functor")
        {
            std::multiset<std::shared_ptr<int>, ComparePtrsByValue> mset_ptrs;

            mset_ptrs.insert(std::make_unique<int>(13));
            mset_ptrs.insert(std::make_unique<int>(1));
            mset_ptrs.insert(std::make_unique<int>(42));
            mset_ptrs.insert(std::make_unique<int>(665));
            mset_ptrs.insert(std::make_unique<int>(42));

            for(const auto& ptr : mset_ptrs)
                std::cout << *ptr << " ";
            std::cout << "\n";
        }

        SECTION("with functor")
        {
            auto cmpr_by_pointed_value = [](const auto& ptr_a, const auto& ptr_b) { return *ptr_a < *ptr_b; };

            std::multiset<std::shared_ptr<int>, decltype(cmpr_by_pointed_value)> mset_ptrs(cmpr_by_pointed_value);

            mset_ptrs.insert(std::make_unique<int>(13));
            mset_ptrs.insert(std::make_unique<int>(1));
            mset_ptrs.insert(std::make_unique<int>(42));
            mset_ptrs.insert(std::make_unique<int>(665));
            mset_ptrs.insert(std::make_unique<int>(42));

            for(const auto& ptr : mset_ptrs)
                std::cout << *ptr << " ";
            std::cout << "\n";
        }
    }
}

template <typename TMap>
std::vector<typename TMap::mapped_type> get_equal_values(const TMap& mp, const typename TMap::key_type& key)
{
    std::vector<typename TMap::mapped_type> results;

    auto range = mp.equal_range(key);
    for(auto it = range.first; it != range.second; ++it)
    {
        results.push_back(it->second);
    }

    return results;
}

TEST_CASE("maps")
{
    std::map<int, std::string> dict = { {1, "one"}, {2, "two"}, {5, "five"} };

    auto result = dict.insert(std::make_pair(3, "three"));
    REQUIRE(result.second == true);

    SECTION("index operator")
    {
        REQUIRE(dict[1] == "one");

        dict[5] = "FIVE";

        dict[6] = "six";

        std::cout << "7 - " << dict[7] << std::endl;

        std::cout << "\n---- dict:\n";
        for(const auto& key_value : dict)
            std::cout << key_value.first << " - " << key_value.second << "\n";
    }

    std::multimap<int, std::string, std::greater<int>> multi_dict_desc(dict.begin(), dict.end());

    multi_dict_desc.insert(std::make_pair(2, "due"));
    multi_dict_desc.emplace(2, "dwa");

    std::cout << "\n---- multi_dict_desc:\n";
    for(const auto& key_value : multi_dict_desc)
        std::cout << key_value.first << " - " << key_value.second << "\n";

    auto range_2 = get_equal_values(multi_dict_desc, 2);
    helpers::print(range_2, "2");

}
