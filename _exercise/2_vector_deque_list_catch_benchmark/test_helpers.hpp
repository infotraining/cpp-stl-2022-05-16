#ifndef TEST_HELPERS_HPP
#define TEST_HELPERS_HPP

#include <iostream>
#include <string>
#include <vector>

namespace TestsHelpers
{
    /*inline*/ namespace Moveable
    {
        struct Tester
        {
            std::string first_name;
            std::string last_name;
            std::vector<int> data;

            Tester(std::string fn, std::string ln, std::vector<int> data)
                : first_name{std::move(fn)}, last_name{std::move(ln)}, data{std::move(data)}
            {
            }

            auto tied() const
            {
                return std::tie(last_name, first_name);
            }
        };
    }

    inline namespace NoMoveable
    {
        struct Tester
        {
            std::string first_name;
            std::string last_name;
            std::vector<int> data;

            Tester(const std::string& fn, const std::string& ln, const std::vector<int>& data)
                : first_name{fn}, last_name{ln}, data{data}
            {
            }

            auto tied() const
            {
                return std::tie(last_name, first_name);
            }

            ~Tester() = default;
        };
    }

    std::ostream& operator<<(std::ostream& out, const Tester& t)
    {
        out << "{ " << t.first_name << ", " << t.last_name << ", ";
        out << "[ ";

        for (const auto& item : t.data)
            out << item << " ";

        out << "] }";

        return out;
    }

    bool operator<(const Tester& a, const Tester& b)
    {
        return a.tied() < b.tied();
    }

    template <typename RndGen>
    std::string rnd_string(RndGen&& gen, size_t min_length = 3, size_t max_length = 64)
    {
        std::uniform_int_distribution<size_t> size_distr(min_length, max_length);
        auto size = size_distr(gen);

        std::uniform_int_distribution<int> char_distr(97, 122);

        std::string result;
        result.reserve(size);

        for (size_t i = 0; i < size; ++i)
            result.push_back(static_cast<char>(char_distr(gen)));

        return result;
    }

    template <typename RndGen>
    int rnd_int(RndGen&& gen, int min = 1, int max = 1024)
    {
        std::uniform_int_distribution<int> distr(min, max);
        return distr(gen);
    }

    template <typename RndGen>
    std::vector<int> rnd_vector(RndGen&& gen, size_t min_length = 1, size_t max_length = 256)
    {
        std::uniform_int_distribution<size_t> size_distr(min_length, max_length);
        auto size = size_distr(gen);

        std::vector<int> result;
        result.reserve(size);

        for (size_t i = 0; i < size; ++i)
            result.push_back(rnd_int(gen));

        return result;
    }
}

#endif
