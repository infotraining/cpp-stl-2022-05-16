#include <algorithm>
#include <numeric>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <boost/functional/hash.hpp>

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

TEST_CASE("unordered_set")
{
    std::unordered_set<int> uset_int = {1, 5, 756, 42, 345, 64, 42, 665 };
    helpers::print(uset_int, "uset_int");
}

TEST_CASE("buckets")
{
    std::unordered_set<int> uset;
    uset.max_load_factor(3.0);
//    REQUIRE(uset.max_load_factor() == Approx(0.5));

    print_unordered(uset, "uset");

    std::vector<int> rnd_numbers = helpers::create_rnd_dataset(100, 0, 100);

    for(const auto& item : rnd_numbers)
    {
        uset.insert(item);
        print_unordered(uset, "uset");
    }

    print_unordered(uset, "uset");

    std::cout << "\n------------------ Buckets:\n";
    std::cout << "\nDetailed stat:\n";

    for (size_t i = 0; i < uset.bucket_count(); ++i) {
        std::cout << "Bucket " << i << ": [ ";
        for (auto it = uset.begin(i); it != uset.end(i); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "]\n";
    }

    uset.rehash(100);

    std::cout << "\n------------------ Buckets:\n";
    std::cout << "\nDetailed stat:\n";

    for (size_t i = 0; i < uset.bucket_count(); ++i) {
        std::cout << "Bucket " << i << ": [ ";
        for (auto it = uset.begin(i); it != uset.end(i); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "]\n";
    }
}

struct GeoLocation
{
    int lat, lon;

    bool operator==(const GeoLocation& other) const
    {
        //return lat == other.lat && lon == other.lon;
        return std::tie(lat, lon) == std::tie(other.lat, other.lon);
    }
};

struct GeoLocationHasher
{
    size_t operator()(const GeoLocation& loc) const
    {
        size_t seed = 0;
        boost::hash_combine(seed, loc.lat);
        boost::hash_combine(seed, loc.lon);
        return seed;
    }
};

namespace std
{
    template <>
    struct hash<GeoLocation>
    {
        size_t operator()(const GeoLocation& loc) const
        {
            size_t seed = 0;
            boost::hash_combine(seed, loc.lat);
            boost::hash_combine(seed, loc.lon);
            return seed;
        }
    };
}

TEST_CASE("hashing")
{
    //std::unordered_map<GeoLocation, std::string, GeoLocationHasher> cities;
    std::unordered_map<GeoLocation, std::string> cities;

    cities.emplace(GeoLocation{53, 18}, "Gdynia");
    cities.emplace(GeoLocation{51, 19}, "Rumia");
    cities.emplace(GeoLocation{5, 17}, "Sopot");
    cities.emplace(GeoLocation{0, 0}, "Londyn");

    std::cout << cities.at(GeoLocation{0, 0}) << "\n";
}
