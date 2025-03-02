#include "Eventer.h"

namespace{
    std::unique_ptr<Eventer> eventer;
}
Eventer::Eventer()
{
}

Eventer::~Eventer()
{
}

Eventer* Eventer::get()
{
    if (!eventer) {
        eventer = std::make_unique<Eventer>();
    }
    return eventer.get();
}

void Eventer::off(std::string& name, size_t& handle)
{
    auto it = eventer->handlers.find(name);
    if (it != eventer->handlers.end()) {
        auto& eventHandlers = it->second;
        eventHandlers.erase(
            std::remove_if(eventHandlers.begin(), eventHandlers.end(),
                [handle](const auto& pair) { return pair.first == handle; }),
            eventHandlers.end()
        );
        if (eventHandlers.empty()) {
            eventer->handlers.erase(name);
        }
    }
}
