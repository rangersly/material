# 采用 Google C++ 命名约定,而非 C 风格 snake_case

本模板同时包含 C 库与 C++ 程序,而两种语言的常规命名习惯不同:C 倾向 `snake_case` 函数,Google C++ 风格则要求函数 `CamelCase`。为让 clang-tidy 的 `readability-identifier-naming` 对全项目保持一套规则,我们统一采用 Google C++ Style Guide:类型/函数 `CamelCase`,变量 `snake_case`,常量 `k` + `CamelCase`,宏 `UPPER_CASE`。因此 C 库中的公开函数也写作 `MathUtilsAdd` 这类 CamelCase,而非 `math_utils_add`。

## Considered Options

- **C 风格 snake_case**(函数 `math_utils_add`)——更贴合 C 语言与 Linux 内核习惯,但与 C++ 侧不一致,且偏离 Google 指南
- **按文件类型分别配置 clang-tidy**——复杂度高,收益有限,暂不采用

## Consequences

- 阅读 C 源码时需注意:本模板 C 库的函数名不是常见的 C 风格,而是 CamelCase
- 若日后更看重 C 语言惯例,可改为 per-file clang-tidy 配置
