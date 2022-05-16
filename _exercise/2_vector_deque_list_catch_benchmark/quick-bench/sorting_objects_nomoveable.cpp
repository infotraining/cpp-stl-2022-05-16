// Sorting large nomoveable objects
// http://quick-bench.com/LjcsADtLcyGd4qPJDXWzo_eNSC

#include <random>
#include <tuple>
#include <deque>
#include <list>
#include <algorithm>

namespace Utils
{
    namespace Moveable
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

template <typename Container>
class ObjContainerFx : public benchmark::Fixture
{
protected:
    Container data;

    void SetUp(benchmark::State& st) override
    {
        using namespace Utils;

        std::random_device rd;
        std::mt19937_64 rnd{rd()};

        auto size = st.range(0);

        for (int64_t i = 0; i < st.range(0); ++i)
        {
            data.push_back(Tester{rnd_string(rnd), rnd_string(rnd), rnd_vector(rnd)});
        }
    }

    void TearDown(benchmark::State&) override
    {
        data.clear();
    }
};

//////////////////////////////////////////////////////////////////////////////

BENCHMARK_TEMPLATE_DEFINE_F(ObjContainerFx, SortVectorObj, std::vector<Utils::Tester>)
(benchmark::State& st)
{
    for (auto _ : st)
    {
        std::sort(data.begin(), data.end());
    }
}

BENCHMARK_REGISTER_F(ObjContainerFx, SortVectorObj)/*->Arg(1024)*/->Arg(4096);

//////////////////////////////////////////////////////////////////////////////

BENCHMARK_TEMPLATE_DEFINE_F(ObjContainerFx, SortDequeObj, std::deque<Utils::Tester>)
(benchmark::State& st)
{
    for (auto _ : st)
    {
        std::sort(data.begin(), data.end());
    }
}

BENCHMARK_REGISTER_F(ObjContainerFx, SortDequeObj)/*->Arg(1024)*/->Arg(4096);

//////////////////////////////////////////////////////////////////////////////

BENCHMARK_TEMPLATE_DEFINE_F(ObjContainerFx, SortListObj, std::list<Utils::Tester>)
(benchmark::State& st)
{
    for (auto _ : st)
    {
        data.sort();
    }
}

BENCHMARK_REGISTER_F(ObjContainerFx, SortListObj)/*->Arg(1024)*/->Arg(4096);