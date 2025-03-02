#pragma once
#include <functional>
#include <vector>
#include <any>
#include <string>
#include <memory>
#include <stdexcept>
#include <unordered_map>

// 函数特征萃取 - 基础模板
template<typename F>
struct function_traits;

// std::function 特化
template<typename R, typename... Args>
struct function_traits<std::function<R(Args...)>> {
    using type = std::function<R(Args...)>;
};

// 函数指针特化
template<typename ReturnType, typename... Args>
struct function_traits<ReturnType(*)(Args...)> {
    using type = std::function<ReturnType(Args...)>;
};

// 成员函数指针特化
template<typename Class, typename ReturnType, typename... Args>
struct function_traits<ReturnType(Class::*)(Args...)> {
    using type = std::function<ReturnType(Args...)>;
};

// 可调用对象（如 lambda）特化
template<typename F>
struct function_traits : function_traits<decltype(&F::operator())> {};

// 转换函数
template<typename F>
auto to_function_auto(F&& f) -> typename function_traits<std::decay_t<F>>::type {
    return typename function_traits<std::decay_t<F>>::type(std::forward<F>(f));
}

class Eventer {
public:
    Eventer();
    ~Eventer();

    static Eventer* get();

    template<typename... Args>
    using GenericHandler = std::function<void(Args...)>;

    // 处理事件注册
    template<typename F>
    static size_t on(std::string name, F&& handler) {
        static size_t handle = 0;
        handle += 1;
        auto wrapped = to_function_auto(std::forward<F>(handler));
        Eventer::get()->handlers[name].emplace_back(handle, std::any(std::move(wrapped)));
        return handle;
    }

    // 发射事件
    template<typename... Args>
    static void emit(std::string name, Args&&... args) {
        auto eventer = Eventer::get();
        auto it = eventer->handlers.find(name);
        if (it != eventer->handlers.end()) {
            for (auto& [handle, handler] : it->second) {
                try {
                    auto& func = std::any_cast<GenericHandler<Args...>&>(handler);
                    func(std::forward<Args>(args)...);
                }
                catch (const std::bad_any_cast&) {
                    // 可以选择记录错误或忽略
                }
            }
        }
    }

    static void off(std::string& name, size_t& handle);

private:
    std::unordered_map<std::string, std::vector<std::pair<uint64_t, std::any>>> handlers;
};