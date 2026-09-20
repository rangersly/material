// Copyright (c) 2026 Rangerlsy
// SPDX-License-Identifier: MIT
//
// math_utils 的内部辅助函数,仅供本库实现使用,不属于公开接口。

#ifndef CPP_TEMPLATE_SRC_MATH_UTILS_INTERNAL_H_
#define CPP_TEMPLATE_SRC_MATH_UTILS_INTERNAL_H_

// 将 value 限制到 [low, high] 区间内。
int MathUtilsClamp(int value, int low, int high);

#endif  // CPP_TEMPLATE_SRC_MATH_UTILS_INTERNAL_H_
