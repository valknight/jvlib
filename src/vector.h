#pragma once

#include <cstddef>
#include <memory>
#include <utility>
#include <algorithm>
#include <type_traits>

namespace jvl
{
    template <typename T>
    class vector
    {
    public:
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        using const_pointer = const T *;
        using const_reference = const T &;

        using iterator = T *;
        using const_iterator = const T *;

        using size_type = std::size_t;
        using allocator_type = std::allocator<T>;

    protected :
        pointer _data {nullptr};
        size_type _size{0};
        size_type _capacity{0};
        allocator_type _alloc{};

        void grow() {
            reserve(std::max(size_type(1), _capacity) * 2);
        }

        template<typename ...Args>
        void construct(pointer ptr, Args&& ...args) {
            new(ptr) value_type(std::forward<Args>(args)...);
        }

    public:
        constexpr vector() noexcept = default;

        vector(size_t capacity, allocator_type allocator = allocator_type{})
            : _data{ allocator.allocate(capacity) }
            , _size { 0 }
            , _capacity { capacity }
        {}

        void push_back(value_type value) {
            if (_size + 1 >= _capacity) {
                grow();
            }
            construct(_data + _size, value);
            _size += 1;
        }

        void reserve(size_type capacity) {
            if (capacity <= _capacity)
                return;
            
            pointer data = _alloc.allocate(capacity);
            if (_data) {

                if constexpr (std::is_trivial_v<value_type>) {
                    std::memcpy(data, _data, sizeof(value_type) * _size);
                }
                else {
                    pointer new_it { data };
                    pointer new_end = data + _size;
                    pointer it = _data;
                    pointer iend = _data + _size;
                    
                    for (; it != iend; ++new_it, ++it)
                    {
                        construct(new_it, std::move(*it));
                        it->~value_type();
                    }
                }
            }

            std::swap(_data, data);
            std::swap(_capacity, capacity);
            
            if (data) _alloc.deallocate(data, capacity);
        }

        void shrink(size_type capacity) {
            if (capacity >= _capacity) {
                return;
            }

            int new_size = std::min(_capacity - 1, _size);

            pointer data = _alloc.allocate(capacity);
            if (_data) {
                if constexpr (std::is_trivial_v<value_type>) {
                    // use new size so we don't go out of bounds
                    std::memcpy(data, _data, new_size);
                }
                pointer new_it { data };
                pointer new_end = data + _size;
                pointer it = _data;
                pointer iend = _data + _size;
                
                for (; new_it != new_end; ++new_it, ++it)
                {
                    construct(new_it, std::move(*it));
                    it->~value_type();
                }
                // cleanup rest
                for (; it != iend; ++it) {
                    it->~value_type();
                }
            }

            std::swap(_data, data);
            std::swap(_capacity, capacity);
            _size = new_size;
            if (data) _alloc.deallocate(data, capacity);
        }

        void shrink_to_size() {
            if (_size < _capacity) {
                shrink(_size);
            }
        }

        void pop_back() {
            _size -= 1;
        }

        size_type capacity() const noexcept { return _capacity; }

        iterator begin() noexcept { return _data; }
        const_iterator begin() const noexcept { return _data; }
        const_iterator cbegin() const noexcept { return _data; }

        iterator end() noexcept { return _data + _size; }
        const_iterator end() const noexcept { return _data; }
        const_iterator cend() const noexcept { return _data; }
        
        reference operator[](std::size_t i) noexcept { return _data[i]; };
        const_reference operator[](std::size_t i) const noexcept { return _data[i]; };

        iterator insert(const_iterator position, const_reference i);
        iterator insert(const_iterator position, value_type i);

        iterator erase(const_iterator position);
        iterator erase(const_iterator first, const_iterator last);
    };
}
