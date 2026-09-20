// Copyright (c) 2026 Rangerlsy
// SPDX-License-Identifier: MIT
//
// math_utils: 简单的整数数学工具库,演示 C 库对外公开的接口。

#ifndef CPP_TEMPLATE_MATH_UTILS_H_
#define CPP_TEMPLATE_MATH_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

// 返回 a 与 b 之和(结果被限制在 [-1000000, 1000000] 内)。
int MathUtilsAdd(int a, int b);

// 返回 a 与 b 之积(结果被限制在 [-1000000, 1000000] 内)。
int MathUtilsMultiply(int a, int b);

#ifdef __cplusplus
}
#endif

#endif  // CPP_TEMPLATE_MATH_UTILS_H_
