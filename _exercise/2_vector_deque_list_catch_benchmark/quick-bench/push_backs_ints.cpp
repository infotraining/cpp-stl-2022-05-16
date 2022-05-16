// push_backs of ints into containers
// http://quick-bench.com/IYYi_HRs_jWFz1cA03kVqOVLC9s

#include <random>
#include <deque>
#include <list>

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

//////////////////////////////////////////////////////////////////////////////

BENCHMARK_TEMPLATE_DEFINE_F(IntContainerFx, VectorIntPushBack, std::vector<int>)
(benchmark::State& st)
{
    for (auto _ : st)
    {
        std::vector<int> coll;

        for (const auto& item : data)
            coll.push_back(item);
    }
}

BENCHMARK_REGISTER_F(IntContainerFx, VectorIntPushBack)/*->Arg(1024)*/->Arg(4096);

//////////////////////////////////////////////////////////////////////////////

BENCHMARK_TEMPLATE_DEFINE_F(IntContainerFx, VectorIntPushBackRsrv, std::vector<int>)
(benchmark::State& st)
{
    for (auto _ : st)
    {
        std::vector<int> coll;
        coll.reserve(data.size());

        for (const auto& item : data)
            coll.push_back(item);
    }
}

BENCHMARK_REGISTER_F(IntContainerFx, VectorIntPushBackRsrv)/*->Arg(1024)*/->Arg(4096);

//////////////////////////////////////////////////////////////////////////////

BENCHMARK_TEMPLATE_DEFINE_F(IntContainerFx, DequeIntPushBack, std::vector<int>)
(benchmark::State& st)
{
    for (auto _ : st)
    {
        std::deque<int> coll;

        for (const auto& item : data)
        {
            coll.push_back(item);
            benchmark::ClobberMemory();
        }
    }
}

BENCHMARK_REGISTER_F(IntContainerFx, DequeIntPushBack)/*->Arg(1024)*/->Arg(4096);

//////////////////////////////////////////////////////////////////////////////

BENCHMARK_TEMPLATE_DEFINE_F(IntContainerFx, ListIntPushBack, std::vector<int>)
(benchmark::State& st)
{
    for (auto _ : st)
    {
        std::list<int> coll;

        for (const auto& item : data)
        {
            coll.push_back(item);
        }
    }
}

BENCHMARK_REGISTER_F(IntContainerFx, ListIntPushBack)/*->Arg(1024)*/->Arg(4096);