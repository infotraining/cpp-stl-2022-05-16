#include "catch.hpp"
#include <memory>
#include <list>
#include <algorithm>

class Gadget
{
    int id_;
    size_t use_count_;

public:
    explicit Gadget(int id)
        : id_{id}
    {
    }

    void use()
    {
        ++use_count_;
    }

    int id() const
    {
        return id_;
    }
};

using SPtrGadget = std::shared_ptr<Gadget>;
using WPtrGadget = std::weak_ptr<Gadget>;
using GadgetPool = std::vector<SPtrGadget>;

auto create_gadget_pool(size_t size)
{
    std::vector<SPtrGadget> gadget_pool;
    gadget_pool.reserve(size);

    for (size_t i = 0; i < size; ++i)
        gadget_pool.push_back(std::make_shared<Gadget>(i));

    return gadget_pool;
}

auto create_observers(const GadgetPool& gadgets)
{
    // TODO
    std::list<WPtrGadget> observers;

    return observers;
}

SCENARIO("Lifetime management")
{
    GIVEN("GadgetPool")
    {
        auto gadget_pool = create_gadget_pool(100);

        auto observers = create_observers(gadget_pool);        

        REQUIRE(observers.size() == gadget_pool.size());

        WHEN("life of some objects is expired")
        {
            for (size_t i = 0; i < gadget_pool.size(); i += 2)
            {
                gadget_pool[i].reset();
            }

            THEN("method use is called and expired gadgets are removed from observers in a single pass")
            {
                // TODO               

                REQUIRE(std::all_of(observers.begin(), observers.end(), [](const auto& o) { return o.lock() != nullptr; }));
            }
        }
    }
}
