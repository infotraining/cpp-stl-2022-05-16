http://quick-bench.com/jDQH6IeEkapZsuLFM_w2Z0iYQIs

#include <random>
#include <numeric>
#include <list>

template <typename Container>
class ContainerFx : public benchmark::Fixture
{
protected:
    Container data;

    void SetUp(benchmark::State& st) override
    {
        data.resize(st.range(0));
        std::iota(data.begin(), data.end(), 0);        
    }

    void TearDown(benchmark::State&) override
    {
        data.clear();
    }
};

template <typename Container, typename RndEngine>
void erase_in_random_way(Container& c, RndEngine&& rnd)
{
    while (!c.empty())
    {
        auto index = rnd() % c.size();
        auto pos = std::next(std::begin(c), index);
        c.erase(pos);
    }
}

BENCHMARK_TEMPLATE_DEFINE_F(ContainerFx, VectorRemove, std::vector<int>)
(benchmark::State& st)
{
    std::random_device rd;
    std::mt19937_64 rnd_engine{rd()};

    for (auto _ : st)
    {
        erase_in_random_way(data, rnd_engine);    
    }
}

BENCHMARK_REGISTER_F(ContainerFx, VectorRemove)/*->Arg(1024)*/->Arg(10'000);

//////////////////////////////////////////////////////////////////////////////

BENCHMARK_TEMPLATE_DEFINE_F(ContainerFx, ListRemove, std::list<int>)
(benchmark::State& st)
{
    std::random_device rd;
    std::mt19937_64 rnd_engine{rd()};

    for (auto _ : st)
    {
        erase_in_random_way(data, rnd_engine);    
    }
}

BENCHMARK_REGISTER_F(ContainerFx, ListRemove)/*->Arg(1024)*/->Arg(10'000);

