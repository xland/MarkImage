#pragma once
#include <functional>
#include <vector>
#include <any>
#include <string>
#include <memory>
#include <stdexcept>

using EventHandler = std::function<void(std::any&)>;
class Eventer
{
public:
	Eventer();
	~Eventer();
    static Eventer* get();
    template<typename F>
    static size_t on(std::string name, F&& handler) {
        auto wrappedHandler = [h = std::forward<F>(handler)](std::any& arg) {
            if constexpr (std::is_invocable_v<F, std::any&>) {
                h(arg);
            }
            else if constexpr (std::is_invocable_v<F>) {
                h();
            }
            else {
                throw std::invalid_argument("Handler signature not supported");
            }
        };
        static size_t handle = 0;
        handle += 1;
        Eventer::get()->handlers[name].emplace_back(handle, std::move(wrappedHandler));
        return handle;
    }
    static void emit(std::string name, std::any arg = {});
    static void off(std::string name, uint64_t handle);
private:
    std::unordered_map<std::string, std::vector<std::pair<uint64_t, EventHandler>>> handlers;
};

