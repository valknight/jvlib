#pragma once

#include "testing.h"
#include "vector.h"

using namespace jvl::testing;

TEST(VectorShrinkToSize, []() {
    jvl::vector<int> v{};
    // Allocs to size 1
    for (size_t i = 0; i < 32; i++)
    {
        v.emplace_back(i);
        v.shrink_to_size();
        equal(v.size(), v.capacity());
    }
});

TEST(VectorReserve, [](){
    jvl::vector<int> v{};
    v.reserve(128);
    equal(v.size(), size_t(0), "size non-zero");
    equal(v.capacity(), size_t(128), "capacity");
});

