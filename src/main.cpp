#include <iostream>

#include "array.h"
#include "vector.h"

int main()
{
    jvl::vector<uint32_t> vec;
    vec.push_back(4);
    vec.push_back(7);
    vec.reserve(4);
    vec.push_back(8);
    vec.pop_back();

    for (auto& i : vec)
    {
        std::cout << i << std::endl;
    }

    std::cout << vec[0] << std::endl;
    
    return 0;
}