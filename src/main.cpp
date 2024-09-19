#include <iostream>

#include "array.h"

int main()
{
    jvl::array<int, 5> arr { 0, 1, 2, 3, 4 };
    for (int i : arr)
    {
        std::cout << i << std::endl;
    }
    arr[3] = 10;
    std::cout << arr[3] << std::endl;

    return 0;
}