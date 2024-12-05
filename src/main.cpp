// TODO in next session! Look at asserts
#include "vector.h"
#include "testing.h"
#include "vector_tests.h"

#include "uninit.h"

int main()
{    
    jvl::testing::run_tests();

    jvl::vector<int> v{};
    v.at(5);
}