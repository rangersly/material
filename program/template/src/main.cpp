// Copyright (c) 2026 Rangerlsy
// SPDX-License-Identifier: MIT
//
// 可执行程序入口,演示 C++ 代码链接并调用 C 库。

#include <iostream>

#include "math_utils/math_utils.h"

namespace {

constexpr int kLeftOperand = 6;
constexpr int kRightOperand = 7;

}  // namespace

int main() {
    std::cout << kLeftOperand << " + " << kRightOperand << " = "
              << MathUtilsAdd(kLeftOperand, kRightOperand) << '\n';
    std::cout << kLeftOperand << " * " << kRightOperand << " = "
              << MathUtilsMultiply(kLeftOperand, kRightOperand) << '\n';
    return 0;
}
