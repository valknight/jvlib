#pragma once

#include "testing.h"
#include "vector.h"

using namespace jvl::testing;

namespace {
    class DeletedDefaultConstructorNonTrivial
    {
public:
        DeletedDefaultConstructorNonTrivial() = delete;
        // Even if `i` doesn't do anything
        // this makes this nontrivially constructable
        DeletedDefaultConstructorNonTrivial(size_t i) {
            
        };
        
        ~DeletedDefaultConstructorNonTrivial() {
        }
    };

    TEST(VectorPushBack, []() {
        jvl::vector<int> v{};

        v.push_back(0);
        equal(v.size(), size_t(1));
        equal(v.capacity(), size_t(2));
        v.push_back(0);
        equal(v.size(), size_t(2));
        equal(v.capacity(), size_t(2));
        v.push_back(0);
        equal(v.size(), size_t(3));
        equal(v.capacity(), size_t(4));
    });

    TEST(VectorEmplaceBack, []() {
        jvl::vector<size_t> v{};

        v.emplace_back(size_t(1));
        v.emplace_back(size_t(2));
        equal(v.size(), size_t(2));
    });

    TEST(VectorEmplaceBackNonTrivialDeletedDefaultConstructor, []() {
        jvl::vector<DeletedDefaultConstructorNonTrivial> v{};
        for (size_t i = 0; i < 32; i++)
        {
            v.emplace_back(size_t(1));
        }
        equal(size_t(32), v.size());
    });

    TEST(VectorPopBackNonTrivialDeletedDefaultConstructor, []() {
        jvl::vector<DeletedDefaultConstructorNonTrivial> v{};
        for (size_t i = 0; i < 32; i++)
        {
            v.emplace_back(size_t(1));
        }
        for (size_t i = 0; i < 32; i++) 
        {
            v.pop_back();
        }
        equal(size_t(0), v.size());
    });

    TEST(VectorEmplaceBackNontrivial, []() {
        jvl::vector<DeletedDefaultConstructorNonTrivial> v{};
        v.emplace_back(size_t(1));
    });

    TEST(VectorShrinkToSize, []() {
        jvl::vector<int> v{};
        // Allocs to size 1
        for (size_t i = 0; i < 32; i++) {
            v.emplace_back(i);
            v.shrink_to_size();
            equal(v.size(), v.capacity());
        }
        for (size_t i = 0; i < 32; i++) {
            v.pop_back();
            v.shrink_to_size();
            equal(v.size(), v.capacity(), "size not equal on shrink");
        }
        assert(false);
    });

    TEST(VectorReserve, [](){
        jvl::vector<int> v{};
        v.reserve(128);
        equal(size_t(0), v.size(), "size non-zero");
        equal(size_t(128), v.capacity(), "capacity");
    });
}