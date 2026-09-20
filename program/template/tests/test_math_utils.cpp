// Copyright (c) 2026 Rangerlsy
// SPDX-License-Identifier: MIT
//
// math_utils 的 CTest 测试用例。

#include <cstdlib>
#include <iostream>

#include "math_utils/math_utils.h"

namespace {

bool ExpectEqual(int actual, int expected, const char* message) {
    if (actual != expected) {
        std::cerr << "FAIL: " << message << " (expected " << expected
                  << ", got " << actual << ")\n";
        return false;
    }
    return true;
}

}  // namespace

int main() {
    bool ok = true;
    ok &= ExpectEqual(MathUtilsAdd(2, 3), 5, "add positive");
    ok &= ExpectEqual(MathUtilsAdd(-2, -3), -5, "add negative");
    ok &= ExpectEqual(MathUtilsMultiply(4, 5), 20, "multiply positive");
    ok &= ExpectEqual(MathUtilsMultiply(-4, 5), -20, "multiply negative");

    if (!ok) {
        std::cerr << "Some tests failed\n";
        return EXIT_FAILURE;
    }
    std::cout << "All tests passed\n";
    return EXIT_SUCCESS;
}
