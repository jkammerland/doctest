#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// Define type aliases to avoid comma parsing issues
using IntFloat   = std::tuple<int, float>;
using CharDouble = std::tuple<char, double>;

// Test the cartesian product functionality with type aliases
TEST_CASE_TEMPLATE_2D("cartesian product test", T, U, CARTESIAN_PRODUCT(IntFloat, CharDouble)) {
    T a = T(1);
    U b = U(2);

    // Basic check to ensure both types work
    CHECK(a == T(1));
    CHECK(b == U(2));

    // This should automatically generate 4 test cases:
    // 1. int, char
    // 2. int, double
    // 3. float, char
    // 4. float, double
}