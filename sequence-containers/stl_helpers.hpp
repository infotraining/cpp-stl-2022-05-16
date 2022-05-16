#ifndef STL_HELPERS_HPP
#define STL_HELPERS_HPP

#include <string>
#include <iostream>
#include <random>
#include <algorithm>

namespace helpers
{
    template<typename TContainer_>
    void print(const TContainer_& container, const std::string& description = "items")
    {
        std::cout << description << " - { ";
        for(const auto& item : container)
        {
            std::cout << item << " ";
        }
        std::cout << "}\n";
    }

    template<template<typename, typename> class TContainer_ = std::vector, template <typename> class TAllocator_ = std::allocator>
    auto create_rnd_dataset(size_t size, int low = 0, int high = 100, size_t seed = 665)
    {
        std::mt19937_64 rnd_engine{seed};
        std::uniform_int_distribution<int> rnd_distr{low, high};

        TContainer_<int, TAllocator_<int>> dataset(size);

        std::generate(dataset.begin(), dataset.end(), [&] { return rnd_distr(rnd_engine); });

        return dataset;
    }

    template <typename T>
    void describe(const std::vector<T>& vec, const std::string& description = "vector")
    {
        std::cout << description << " - size: " << vec.size() << "; capacity: " << vec.capacity() << "\n";
    }
}

#endif // STL_HELPERS_HPP
