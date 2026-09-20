// Copyright (c) 2026 Rangerlsy
// SPDX-License-Identifier: MIT
//
// math_utils 的实现。

#include "math_utils/math_utils.h"

#include "math_utils_internal.h"

#define MATH_UTILS_LIMIT 1000000

int MathUtilsClamp(int value, int low, int high) {
    if (value < low) {
        return low;
    }
    if (value > high) {
        return high;
    }
    return value;
}

int MathUtilsAdd(int a, int b) {
    return MathUtilsClamp(a + b, -MATH_UTILS_LIMIT, MATH_UTILS_LIMIT);
}

int MathUtilsMultiply(int a, int b) {
    return MathUtilsClamp(a * b, -MATH_UTILS_LIMIT, MATH_UTILS_LIMIT);
}
