#include <doctest/doctest.h>

DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_BEGIN
#include <vector>
#include <string>
#include <type_traits>
DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_END

// =================================================================================================
// 2D TEMPLATE TEST CASES - CARTESIAN PRODUCT OF TWO TYPE LISTS
// =================================================================================================

// Test basic arithmetic operations on combinations of numeric types
TEST_CASE_TEMPLATE_2D("arithmetic operations", T, U, 
                      TYPE_PAIR(signed char, unsigned char),
                      TYPE_PAIR(signed char, unsigned int),
                      TYPE_PAIR(signed char, unsigned long),
                      TYPE_PAIR(int, unsigned char),
                      TYPE_PAIR(int, unsigned int),
                      TYPE_PAIR(int, unsigned long),
                      TYPE_PAIR(long, unsigned char),
                      TYPE_PAIR(long, unsigned int),
                      TYPE_PAIR(long, unsigned long)) {
    T a = T(5);
    U b = U(3);
    
    // Test that we can perform operations between different numeric types
    auto sum = a + b;
    CHECK(sum == 8);
    
    auto product = a * b;
    CHECK(product == 15);
    
    // Test type properties
    CHECK(std::is_signed_v<T> == true);
    CHECK(std::is_unsigned_v<U> == true);
}

// Test container operations with different value types and container types
template <typename T>
struct TestVector {
    std::vector<T> data;
    TestVector(std::initializer_list<T> init) : data(init) {}
    size_t size() const { return data.size(); }
    T& operator[](size_t i) { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }
};

template <typename T>
struct TestArray {
    T data[3];
    TestArray(std::initializer_list<T> init) { 
        size_t i = 0;
        for (auto& item : init) {
            if (i < 3) data[i++] = item;
        }
    }
    size_t size() const { return 3; }
    T& operator[](size_t i) { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }
};

TEST_CASE_TEMPLATE_2D("container operations", Container, ValueType,
                      TYPE_PAIR(TestVector, int),
                      TYPE_PAIR(TestVector, double),
                      TYPE_PAIR(TestVector, std::string),
                      TYPE_PAIR(TestArray, int),
                      TYPE_PAIR(TestArray, double),
                      TYPE_PAIR(TestArray, std::string)) {
    Container<ValueType> container{ValueType{}, ValueType{}, ValueType{}};
    
    CHECK(container.size() >= 3);
    
    // Test assignment
    container[0] = ValueType{};
    container[1] = ValueType{};
    container[2] = ValueType{};
    
    // Basic container tests
    CHECK(container[0] == ValueType{});
    CHECK(container[1] == ValueType{});
    CHECK(container[2] == ValueType{});
}

// =================================================================================================
// 2D TEMPLATE TEST CASES WITH DEFERRED INSTANTIATION
// =================================================================================================

TEST_CASE_TEMPLATE_2D_DEFINE("matrix multiplication", T, U, matrix_test_id) {
    T a = T(2);
    U b = U(3);
    
    // Simulate matrix-like operations
    auto result = a * b;
    CHECK(result == 6);
    
    // Test that both types are arithmetic
    CHECK(std::is_arithmetic_v<T>);
    CHECK(std::is_arithmetic_v<U>);
}

// Instantiate the test for specific type combinations
TEST_CASE_TEMPLATE_2D_INVOKE(matrix_test_id, 
                             TYPE_PAIR(int, double),
                             TYPE_PAIR(int, long),
                             TYPE_PAIR(float, double),
                             TYPE_PAIR(float, long));

// =================================================================================================
// COMPLEX EXAMPLE: TESTING CONVERSION OPERATIONS
// =================================================================================================

TEST_CASE_TEMPLATE_2D("type conversion safety", From, To,
                      TYPE_PAIR(int, char),
                      TYPE_PAIR(int, short),
                      TYPE_PAIR(int, int),
                      TYPE_PAIR(int, long),
                      TYPE_PAIR(float, char),
                      TYPE_PAIR(float, short),
                      TYPE_PAIR(float, int),
                      TYPE_PAIR(float, long),
                      TYPE_PAIR(double, char),
                      TYPE_PAIR(double, short),
                      TYPE_PAIR(double, int),
                      TYPE_PAIR(double, long)) {
    From source = From(42);
    To destination;
    
    // Test safe conversion
    destination = static_cast<To>(source);
    
    // Verify conversion worked as expected
    if constexpr (sizeof(From) <= sizeof(To)) {
        // Safe conversion - should preserve value
        CHECK(static_cast<From>(destination) == source);
    } else {
        // Potentially lossy conversion - just verify it compiles
        CHECK(destination == static_cast<To>(source));
    }
    
    // Test type properties
    CHECK(std::is_arithmetic_v<From>);
    CHECK(std::is_arithmetic_v<To>);
}

// =================================================================================================
// DEMONSTRATING ERROR CASES (intentionally failing tests)
// =================================================================================================

TEST_CASE_TEMPLATE_2D("intentional failures for demo", T, U,
                      TYPE_PAIR(int, double),
                      TYPE_PAIR(int, char),
                      TYPE_PAIR(float, double),
                      TYPE_PAIR(float, char)) {
    T a = T(1);
    U b = U(1);
    
    // This will fail for some combinations to show the feature works
    if constexpr (std::is_same_v<T, int> && std::is_same_v<U, double>) {
        CHECK(a == 999); // This will fail
    } else {
        CHECK(a == T(1)); // This will pass
    }
    
    CHECK(b == U(1)); // This should pass for all
}