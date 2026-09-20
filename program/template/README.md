# cpp_template

一个开箱即用的 C/C++ 项目模板,演示 **C 静态库 + C++ 可执行程序** 的混合工程结构,内置 clang-format / clang-tidy / CMake / CTest 配置。

## 特性

- 现代 CMake(目标级 `target_*` 用法,构建文件直接放在根目录)
- C17 + C++17
- 默认 Release,保留 Debug 与测试选项
- `.clang-format`(Google 基础 + 4 空格缩进)与 `.clang-tidy`(Google 命名约定)
- CTest 测试,零第三方依赖
- MIT 许可证

## 目录结构

```text
.
├── .clang-format              # clang-format 风格配置
├── .clang-tidy                # clang-tidy 静态检查配置
├── .clangd                    # clangd 配置(指向 build/ 的编译数据库)
├── .gitignore
├── CMakeLists.txt             # 根构建文件
├── LICENSE                    # MIT
├── README.md
├── CONTEXT.md                 # 本项目词汇表
├── docs/
│   └── adr/                   # 架构决策记录
├── include/
│   └── math_utils/
│       └── math_utils.h       # 公开头文件(extern "C" 守卫)
├── src/
│   ├── math_utils.c           # C 库实现
│   ├── math_utils_internal.h  # 内部头文件
│   └── main.cpp               # C++ 可执行程序
└── tests/
    └── test_math_utils.cpp    # CTest 测试
```

### 头文件分层约定

- `include/<库名>/` 只放**公开头文件**,使用引号带完整路径包含:`#include "math_utils/math_utils.h"`
- `src/` 放**内部头文件**(`*_internal.h`)与全部实现,内部头文件不对外暴露
- 公开头文件统一用 `#ifndef` 防护符 + `extern "C"` 守卫,以便 C++ 调用
- `include/` 始终是搜索根,把公开头文件放进库名子目录只是为了避免多个库的同名头文件冲突,无需改动 CMake

## 快速开始

```bash
# 配置(默认 Release)
cmake -B build -S .

# 构建
cmake --build build

# 运行
./build/app

# 测试
ctest --test-dir build
```

### 常用选项

```bash
# Debug 构建
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug

# 关闭测试
cmake -B build -S . -DBUILD_TESTING=OFF

# 只构建某个目标
cmake --build build --target app
```

## 代码规范

格式化(需安装 clang-format):

```bash
clang-format -i include/*.h src/*.c src/*.cpp tests/*.cpp
```

静态检查(需安装 clang-tidy;本模板**不**把 clang-tidy 集成进构建,按需手动运行):

```bash
clang-tidy -p build src/math_utils.c src/main.cpp tests/test_math_utils.cpp
```

### 命名约定速查(Google C++ Style Guide)

| 元素 | 风格 | 示例 |
|---|---|---|
| 类型 / 类 / 结构体 / 枚举 / typedef | `CamelCase` | `MathUtils` |
| 函数 / 方法 | `CamelCase` | `MathUtilsAdd` |
| 变量 / 参数 / 成员 | `snake_case`(成员加尾下划线) | `left_operand`, `count_` |
| 常量 / 枚举值 / `constexpr` | `k` + `CamelCase` | `kLeftOperand` |
| 宏 | `UPPER_CASE` | `MATH_UTILS_LIMIT` |
| 命名空间 | `lower_case` | `my_namespace` |
| 文件 | `lower_snake_case` | `math_utils.h` |

## 编辑器支持(clangd)

本模板自带 `.clangd`,让 clangd 到 `build/` 目录读取 `compile_commands.json`,从而正确解析跨目录头文件(如 `include/math_utils/math_utils.h`)。

1. 先生成编译数据库:

   ```bash
   cmake -B build -S .
   ```

2. clangd(nvim / VS Code 等)随后即可识别所有头文件搜索路径。

> 若编辑器不读取 `.clangd`,也可在项目根建立软链接:
>
> ```bash
> ln -s build/compile_commands.json compile_commands.json
> ```

## 基于本模板新建项目

在目标目录中复制本模板后,按下表替换:

1. `CMakeLists.txt` 里的 `project(cpp_template ...)` 及目标名
2. `include/`、`src/`、`tests/` 下的示例文件
3. 头文件防护符前缀 `CPP_TEMPLATE_`
4. `LICENSE` 与各文件头的 `Copyright`
