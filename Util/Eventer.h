#pragma once
#include <iostream>
#include <unordered_map>
#include <functional>
#include <vector>
#include <any>
#include <tuple>

class Eventer {
public:
    using HandlerId = size_t;

    template <typename... Args>
    using Handler = std::function<void(Args...)>;

    // 处理带参数的回调
    template <typename... Args>
    HandlerId on(const std::string& name, Handler<Args...> handler) {
        HandlerId id = nextId++;
        handlers[name].emplace_back(id, [handler](std::any args) {
            auto unpackedArgs = std::any_cast<std::tuple<Args...>>(args);
            std::apply(handler, unpackedArgs);
            });
        return id;
    }

    // 处理无参数的回调
    HandlerId on(const std::string& name, std::function<void()> handler) {
        HandlerId id = nextId++;
        handlers[name].emplace_back(id, [handler](std::any) {
            handler();
            });
        return id;
    }

    // 触发事件（支持带参数和无参数）
    template <typename... Args>
    void emit(const std::string& name, Args&&... args) {
        auto it = handlers.find(name);
        if (it != handlers.end()) {
            std::any packedArgs = std::make_tuple(std::forward<Args>(args)...);
            for (auto& [id, handler] : it->second) {
                handler(packedArgs);
            }
        }
    }

    // 触发无参数事件
    void emit(const std::string& name) {
        auto it = handlers.find(name);
        if (it != handlers.end()) {
            for (auto& [id, handler] : it->second) {
                handler(std::any()); // 传递一个空的 std::any
            }
        }
    }

    void off(const std::string& name, const HandlerId& handle) {
        auto it = handlers.find(name);
        if (it != handlers.end()) {
            auto& vec = it->second;
            vec.erase(std::remove_if(vec.begin(), vec.end(),
                [&](const auto& pair) { return pair.first == handle; }), vec.end());
        }
    }

private:
    using AnyHandler = std::function<void(std::any)>;
    std::unordered_map<std::string, std::vector<std::pair<HandlerId, AnyHandler>>> handlers;
    HandlerId nextId = 0;
};