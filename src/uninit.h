#pragma once

#include <cstdint>

namespace jvl
{
    template<typename T>
    struct uninit
    {
        uninit() {}
        ~uninit() {}

        uninit(const uninit&) = delete;
        uninit& operator=(const uninit&) = delete;
        
        uninit(uninit&&) = delete;
        uninit&& operator=(uninit&&) = delete;

        void emplace(T& value) {
            new(data()) T{ value };
        }

        template<typename ...Args>
        void emplace(Args&& ...args) {
            new(data()) T{ std::forward<Args>(args)... };
        }

        T access_init() {
            T res { std::move(*data()) };
            data()->~T();
            return res;
        }

        T* data() noexcept {
            return reinterpret_cast<T*>(storage);
        }

    private:

        union {
            alignas(alignof(T)) uint8_t storage[sizeof(T)];
        };
    };
}