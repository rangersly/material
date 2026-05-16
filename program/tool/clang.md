# clang 项目设置

.clang-format

```
# 使用 Google 风格为基础
BasedOnStyle: Google

# 将缩进宽度改为 4 个空格
IndentWidth: 4
TabWidth: 4
UseTab: Never

# 大括号风格
BreakBeforeBraces: Attach
```

.clang-tidy

```
# ============================================================
# .clang-tidy 配置文件
# 用于 C/C++ 项目的静态分析,提供代码质量、风格和性能建议
# ============================================================

# ---------- 检查器 (Checks) ----------
# 格式: 逗号分隔的检查器名称,支持通配符 *
# 规则:
#   - '* '  禁用所有检查,再从零开始启用需要的组
#   - 'google-*' 启用所有 Google 代码风格相关的检查
#   - 'readability-*' 启用可读性改进建议(如简化表达式、命名建议等)
#   - 'performance-*' 启用性能优化建议(如避免不必要拷贝、使用更快的算法等)
#   - 'modernize-*' 启用现代化 C++ 建议(如使用 nullptr、override、auto 等)
Checks: '
  -*,
  google-*,
  readability-*,
  performance-*,
  modernize-*,
  -modernize-use-trailing-return-type,
  -readability-identifier-naming,
  -readability-magic-numbers,
  -performance-avoid-endl'

# - 禁用 'modernize-use-trailing-return-type' 是因为很多人不习惯尾随返回类型语法
# - 禁用 'readability-identifier-naming' 暂时关闭强制命名规范,可根据项目需求打开
# - 禁用 'readability-magic-numbers' 允许直接使用数字常量,避免代码过度碎片化
# - 禁用 'performance-avoid-endl' 允许使用 std::endl(根据个人习惯,也可启用该检查)
# 如果你想启用命名风格检查,请移除 '-readability-identifier-naming' 并在下方配置 CheckOptions

# ---------- 警告视为错误 ----------
# 若设为 '*', 所有警告都会导致构建失败(或其他工具报错)
WarningsAsErrors: ''

# ---------- 检查器参数 (CheckOptions) ----------
# 许多检查器支持额外的参数配置,这里列出最常用的命名风格配置
CheckOptions:
  # 类名使用 CamelCase 风格(首字母大写)
  - key: readability-identifier-naming.ClassCase
    value: CamelCase
  # 函数名使用 CamelCase 风格(首字母大写)
  - key: readability-identifier-naming.FunctionCase
    value: CamelCase
  # 变量名使用 lower_case 风格(全小写,下划线分隔)
  - key: readability-identifier-naming.VariableCase
    value: lower_case
  # 参数名使用 lower_case 风格
  - key: readability-identifier-naming.ParameterCase
    value: lower_case
  # 常量名使用 UPPER_CASE 风格(全大写,下划线分隔)
  - key: readability-identifier-naming.ConstantCase
    value: UPPER_CASE
  # 命名空间名使用 lower_case 风格
  - key: readability-identifier-naming.NamespaceCase
    value: lower_case
```
