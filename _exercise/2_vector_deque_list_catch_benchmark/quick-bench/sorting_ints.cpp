// sorting of ints
// http://quick-bench.com/ByKgLUN1XxReLGcQD_YMo8ru_Cw

#include <random>
#include <deque>
#include <list>
#include <algorithm>

template <typename Container>
class IntContainerFx : public benchmark::Fixture
{
protected:
    Container data;

    void SetUp(benchmark::State& st) override
    {
        std::random_device rd;
        std::mt19937_64 rnd{rd()};
        std::uniform_int_distribution<> distr(0, 100'000);

        auto size = st.range(0);

        for (int64_t i = 0; i < size; ++i)
        {
            data.push_back(distr(rnd));
        }
    }

    void TearDown(benchmark::State&) override
    {
        data.clear();
    }
};

BENCHMARK_TEMPLATE_DEFINE_F(IntContainerFx, SortVectorInt, std::vector<int>)
(benchmark::State& st)
{
    for (auto _ : st)
    {
        std::sort(data.begin(), data.end());
    }
}

BENCHMARK_REGISTER_F(IntContainerFx, SortVectorInt)/*->Arg(1024)*/->Arg(4096);

//////////////////////////////////////////////////////////////////////////////

BENCHMARK_TEMPLATE_DEFINE_F(IntContainerFx, SortDequeInt, std::deque<int>)
(benchmark::State& st)
{
    for (auto _ : st)
    {
        std::sort(data.begin(), data.end());
    }
}

BENCHMARK_REGISTER_F(IntContainerFx, SortDequeInt)/*->Arg(1024)*/->Arg(4096);

//////////////////////////////////////////////////////////////////////////////

BENCHMARK_TEMPLATE_DEFINE_F(IntContainerFx, SortListInt, std::list<int>)
(benchmark::State& st)
{
    for (auto _ : st)
    {
        data.sort();
    }
}

BENCHMARK_REGISTER_F(IntContainerFx, SortListInt)/*->Arg(1024)*/->Arg(4096);
