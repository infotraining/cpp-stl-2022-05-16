// pre & post increment for iterators

#include <list>
#include <set>
#include <unordered_set>

template <typename Container>
class ContainerFx : public benchmark::Fixture
{
protected:
    Container data;

    void SetUp(benchmark::State& st) override
    {
        std::vector<int> prep(st.range(0));
        std::iota(prep.begin(), prep.end(), 0);        
        for(auto item : prep)      
          data.insert(item);
    }

    void TearDown(benchmark::State&) override
    {
        data.clear();
    }
};

BENCHMARK_TEMPLATE_DEFINE_F(ContainerFx, PreIncrement, std::multiset<int>)
(benchmark::State& st)
{
    for (auto _ : st)
    {
        for(auto it = data.begin(); it != data.end(); ++it)
        {
          benchmark::DoNotOptimize(*it);
        }  
    }
}

BENCHMARK_REGISTER_F(ContainerFx, PreIncrement)->Arg(1256);


BENCHMARK_TEMPLATE_DEFINE_F(ContainerFx, PostIncrement, std::multiset<int>)
(benchmark::State& st)
{
    for (auto _ : st)
    {
        for(auto it = data.begin(); it != data.end(); it++)
        {
          benchmark::DoNotOptimize(*it);
        }  
    }
}

BENCHMARK_REGISTER_F(ContainerFx, PostIncrement)->Arg(1256);