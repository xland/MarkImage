#pragma once
#include <functional>
#include <vector>
#include <any>
#include <string>
#include <memory>
#include <stdexcept>
#include <unordered_map>

// ����������ȡ - ����ģ��
template<typename F>
struct function_traits;

// std::function �ػ�
template<typename R, typename... Args>
struct function_traits<std::function<R(Args...)>> {
    using type = std::function<R(Args...)>;
};

// ����ָ���ػ�
template<typename ReturnType, typename... Args>
struct function_traits<ReturnType(*)(Args...)> {
    using type = std::function<ReturnType(Args...)>;
};

// ��Ա����ָ���ػ�
template<typename Class, typename ReturnType, typename... Args>
struct function_traits<ReturnType(Class::*)(Args...)> {
    using type = std::function<ReturnType(Args...)>;
};

// �ɵ��ö����� lambda���ػ�
template<typename F>
struct function_traits : function_traits<decltype(&F::operator())> {};

// ת������
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

    // �����¼�ע��
    template<typename F>
    static size_t on(std::string name, F&& handler) {
        static size_t handle = 0;
        handle += 1;
        auto wrapped = to_function_auto(std::forward<F>(handler));
        Eventer::get()->handlers[name].emplace_back(handle, std::any(std::move(wrapped)));
        return handle;
    }

    // �����¼�
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
                    // ����ѡ���¼��������
                }
            }
        }
    }

    static void off(std::string& name, size_t& handle);

private:
    std::unordered_map<std::string, std::vector<std::pair<uint64_t, std::any>>> handlers;
};