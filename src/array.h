#pragma once

#include <cstddef>


namespace jvl
{
    template<typename T, std::size_t N>
    struct array
    {
        using pointer = T*;
        using reference = T&;
        using const_pointer = const T*;
        using const_reference = const T&;

        using value_type = T;
        using iterator = T*;
        using const_iterator = const T*;

        T _data[N]; 

        constexpr array() = default;

        constexpr iterator begin() noexcept { return _data; }
        constexpr const_iterator begin() const noexcept { return _data; }
        constexpr const_iterator cbegin() const noexcept { return _data; }

        constexpr iterator end() noexcept { return std::data(_data) + N; }
        constexpr const_iterator end() const noexcept { return _data; }
        constexpr const_iterator cend() const noexcept { return _data; }

        constexpr std::size_t size() const noexcept { return N; }
        constexpr pointer data() noexcept { return _data; }

        constexpr const_pointer data() const noexcept { return _data; }

        constexpr reference operator[](std::size_t i) noexcept { return _data[i]; }
        constexpr const_reference operator[](std::size_t i) const noexcept { return _data[i]; }
    };
    
}
