#include <algorithm>
#include <array>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <string>

#include "simple_nn.hpp"

namespace {

template<size_t list_size> void test_scale_constant()
{
    const float initial_value = 5.0;
    const float scalar = 2.0;

    std::array<float, list_size> data;
    std::fill(data.begin(), data.end(), initial_value);

    int result = scale_by_constant(data, scalar);
    SECTION("verify kernel status")
    {
        CAPTURE(list_size);
        REQUIRE(result == 0);
    }
    SECTION("verify scaling")
    {
        CAPTURE(list_size);
        CAPTURE(data);
        for(const float val : data)
        {
            REQUIRE_THAT(static_cast<double>(val), Catch::Matchers::WithinRel(initial_value * scalar));
        }
    }
}

TEST_CASE("test scale_by_constant with multiple array sizes")
{
    // test regular sizes
    test_scale_constant<4>();
    test_scale_constant<8>();
    test_scale_constant<16>();
    test_scale_constant<256>();

    // test odd sizes
    test_scale_constant<3>();
    test_scale_constant<7>();
    test_scale_constant<19>();
    test_scale_constant<173>();
}

}// namespace
