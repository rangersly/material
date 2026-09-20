# CMake 构建工具

> [!TIP] 本文怎么读
> 下面先用 `program/template/CMakeLists.txt` 这个**完整小工程**走一遍（主线示例），每个概念在它出现的地方讲解「为什么」；末尾有速查表方便查阅。

> [!NOTE] 核心理念
> CMake 围绕**目标(target)**组织，而不是围绕文件。文件只是生成目标的原料，`target_*` 命令才是核心。

## 0. 主线示例

贯穿全文的例子，取自 `program/template/CMakeLists.txt`：一个 **C 静态库** `math_utils` + 一个 **C++ 可执行程序** `app` + 一组 **CTest 测试** `test_math_utils`。

```cmake
# 1. 最低 CMake 版本
cmake_minimum_required(VERSION 3.20)

# 2. 项目信息，project() 会返回一个「顶层项目目标」
project(cpp_template
    VERSION 1.0.0
    DESCRIPTION "C/C++ 项目模板"
    LANGUAGES C CXX
)

# --- 全局设置（作用于整个工程）---

# 3. 默认构建类型：Release；命令行 -DCMAKE_BUILD_TYPE=Debug 可覆盖
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "构建类型(Debug/Release/MinSizeRel/RelWithDebInfo)" FORCE)
endif()

# 4. C / C++ 标准（全局）
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 5. 导出 compile_commands.json，供 clangd / clang-tidy 使用
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 6. 生成物统一输出到构建根目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# 7. 全局警告选项（对所有目标生效）
add_compile_options(-Wall -Wextra)

# --- 定义目标 ---

# 8. 创建静态库
add_library(math_utils STATIC src/math_utils.c)

# 9. 库的包含路径：include/ 对外的接口，src/ 自用
target_include_directories(math_utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 10. 创建可执行程序，链接上面的库
add_executable(app
    src/main.cpp
)

target_link_libraries(app
    PRIVATE
        math_utils
)

# --- 测试 ---

# 11. 引入 CTest
include(CTest)

if(BUILD_TESTING)
    add_executable(test_math_utils
        tests/test_math_utils.cpp
    )
    target_link_libraries(test_math_utils
        PRIVATE
            math_utils
    )
    # 12. 把可执行目标注册成一条测试
    add_test(NAME math_utils_test COMMAND test_math_utils)
endif()
```

> [!IMPORTANT] 为什么 build 目录放在根目录
> 现代 CMake 约定把 `build/` 直接放在项目根目录下（`cmake -B build -S .`），而不是嵌套 `build/build/`。这样做是为了让 `.clangd` 在 `build/` 里读到 `compile_commands.json`，从而让编辑器正确识别跨目录头文件（如 `include/math_utils/math_utils.h`）。

---

## 1. 入门三步

```bash
# 配置（默认 Release）
cmake -B build -S .

# 构建
cmake --build build

# 运行测试（CTest）
ctest --test-dir build
```

- `cmake -B build -S .`：`-B` 指定构建目录，`-S .` 指定源目录（当前目录）
- `cmake --build build`：编译生成产物
- `cmake --build build --target app`：只构建指定目标
- `ctest --test-dir build`：运行测试

> [!TIP] 为什么 -B 而不是旧式的 `cmake .`
> 旧式 `cmake .` 会把 build 目录嵌套在源码下（`build/build/`），并直接修改源码目录里的缓存文件。现代 CMake 用「out-of-source」构建：源码与构建产物完全分开，更干净。

---

## 2. 项目骨架

```cmake
cmake_minimum_required(VERSION 3.20)

project(cpp_template
    VERSION 1.0.0
    DESCRIPTION "C/C++ 项目模板"
    LANGUAGES C CXX
)
```

- `cmake_minimum_required`：声明最低 CMake 版本，低于此版本会报错
- `project()`：声明项目、启用语言（C/C++）、设置版本。**它返回一个「顶层项目目标」**，后续所有 `target_*` 操作都围绕它组织

> [!NOTE] 顶层项目目标
> `project(cpp_template ...)` 本身定义了一个名为 `cpp_template` 的目标，它是整个工程的根，`CMAKE_PROJECT_NAME` 就等于这个名字。

---

## 3. 全局设置（作用于整个工程）

```cmake
# 默认构建类型
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "构建类型(Debug/Release/MinSizeRel/RelWithDebInfo)" FORCE)
endif()

# C / C++ 标准
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 导出编译数据库
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 生成物统一输出到构建根目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# 全局警告选项
add_compile_options(-Wall -Wextra)
```

### 构建类型

| 类型 | 默认标志 | 用途 |
|---|---|---|
| **Debug** | `-g` | 调试，带调试信息 |
| **Release** | `-O3` | 发布，最高性能 |
| **MinSizeRel** | `-Os` | 最小体积，嵌入式 |
| **RelWithDebInfo** | `-O2 -g` | 发布 + 调试信息 |

命令行覆盖：`cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug`

### C/C++ 标准

- `CMAKE_C_STANDARD 17` + `CMAKE_C_STANDARD_REQUIRED ON`：强制要求 C17，`ON` 表示不满足就报错
- 类似地有 `CMAKE_CXX_STANDARD`（C++11/14/17/20/23）

### 全局 vs 目标级

> [!IMPORTANT] 全局选项 vs 目标级选项
> - **全局**（`add_compile_options`、`set(CMAKE_CXX_STANDARD ...)`）：对所有目标生效，简单但不灵活
> - **目标级**（`target_compile_options`、`target_compile_features`）：只对特定目标生效，灵活，但要理解「传播」
>
> 上面的模板用全局方式，是因为工程简单。当某个选项只应作用于某几个目标时，应改用目标级。

### 输出目录

- `CMAKE_RUNTIME_OUTPUT_DIRECTORY`：可执行程序输出位置
- `CMAKE_LIBRARY_OUTPUT_DIRECTORY`：库输出位置
- `CMAKE_ARCHIVE_OUTPUT_DIRECTORY`：静态库输出位置
- 模板把它们都设为 `${CMAKE_BINARY_DIR}`（构建根目录），这样产物都在 `build/` 下，便于统一管理和让编辑器识别

---

## 4. 定义目标

### 4.1 创建目标

```cmake
# 创建静态库
add_library(math_utils STATIC src/math_utils.c)

# 创建可执行程序（空关键字=默认可执行）
add_executable(app src/main.cpp)
```

目标创建关键字：

| 关键字 | 作用 |
|---|---|
| （空） | 默认类型（`add_executable` 为可执行程序；`add_library` 为静态库） |
| `STATIC` | 构建静态库 |
| `SHARED` | 构建动态库 |
| `EXCLUDE_FROM_ALL` | 默认不构建，常用于测试代码 |

> [!NOTE] `add_library` 不带关键字的默认类型
> `add_library(foo ...)` 省略关键字时，类型由变量 `BUILD_SHARED_LIBS` 决定：该变量为 `ON` 时是**动态库（SHARED）**，否则默认是**静态库（STATIC）**。想明确类型就显式写 `STATIC` 或 `SHARED`；想全局统一切换可用 `set(BUILD_SHARED_LIBS ON)`。

### 4.2 包含路径

```cmake
target_include_directories(math_utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
```

- `target_include_directories`：给目标添加头文件搜索根
- `${CMAKE_CURRENT_SOURCE_DIR}`：当前 `CMakeLists.txt` 所在的目录
- 这里 `include/` 挂 `PUBLIC`、`src/` 挂 `PRIVATE`，传播机制决定谁能用它们（见下）

### 4.3 链接库

```cmake
target_link_libraries(app
    PRIVATE
        math_utils
)
```

- `target_link_libraries`：让一个目标链接另一个目标（或第三方库）
- 这里 `app` 链接 `math_utils`，`PRIVATE` 表示只有 `app` 自己用它

---

## 5. 传播机制（核心：PRIVATE / PUBLIC / INTERFACE）

这是 CMake 最核心的概念，控制**属性**（包含路径、链接依赖等）如何在目标之间流动。

用上面的工程举例：
- `math_utils` 库挂载了两个包含路径：`include/`（PUBLIC）和 `src/`（PRIVATE）
- `app` 链接了 `math_utils`

那么：

| 传播关键字 | 目标本身能否用 | 传给链接它的外部目标 | 典型用途 |
|---|---|---|---|
| **PRIVATE** | ✅ | ❌ | 内部实现 |
| **PUBLIC** | ✅ | ✅ | 公开 API |
| **INTERFACE** | ❌ | ✅ | 纯头文件库 |

> [!TIP] 用 math_utils 讲透
> - `math_utils` 自己编译 `src/math_utils.c` 时，需要 `include/` 和 `src/` 两个路径 → 两个都挂，自己能用
> - `include/` 挂 **PUBLIC**：`app` 也用了 `include/` 里的公开头文件（`math_utils/math_utils.h`）→ 自动传给 `app`
> - `src/` 挂 **PRIVATE**：只有 `math_utils` 自己用它（`math_utils.c` 内部 `#include "math_utils_internal.h"`），`app` 完全不需要 → 不传
>
> 结果：`app` 自动获得了 `include/` 路径，却不会拿到 `src/` 路径。这就是 PRIVATE/PUBLIC 的差别。

> [!NOTE] INTERFACE：纯头文件库
> 一个只有头文件、没有 `.cpp` 的库，既不自己用路径、又把路径传给依赖方，用 `INTERFACE`：
> ```cmake
> add_library(myutils INTERFACE)
> target_include_directories(myutils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
> target_link_libraries(myapp PRIVATE myutils)
> ```
> 链接 `myutils` 的每个目标都会自动获得该包含路径。

---

## 6. 目标级编译控制

```cmake
# 目标级：只对这个目标生效
target_compile_features(app PRIVATE cxx_std_17)
target_compile_options(app PRIVATE -O2)
```

- `target_compile_features`：声明目标需要的编译特性，如 `cxx_std_11/14/17/20/23`、`c_std_11/17/23`
- `target_compile_options`：直接加编译选项，如 `-O2`、`-DNDEBUG`

> [!TIP] 全局 vs 目标级怎么选
> - 全局（`add_compile_options`、`CMAKE_CXX_STANDARD`）：全工程统一，简单
> - 目标级（`target_compile_options`、`target_compile_features`）：只对个别目标生效，灵活
> - 全局和目标的设置会**合并**，目标级可以补充或覆盖全局的选项

---

## 7. 测试（CTest）

```cmake
# 引入 CTest 框架
include(CTest)

if(BUILD_TESTING)
    add_executable(test_math_utils tests/test_math_utils.cpp)
    target_link_libraries(test_math_utils PRIVATE math_utils)

    # 把可执行目标注册成一条测试
    add_test(NAME math_utils_test COMMAND test_math_utils)
endif()
```

- `include(CTest)`：启用 CMake 内置的测试框架（会定义 `BUILD_TESTING` 变量）
- `add_executable(...)`：普通地创建一个测试用可执行目标
- `add_test(NAME ... COMMAND ...)`：把某个可执行目标注册成一条测试，`COMMAND` 后面是运行时要执行的命令
- 注册后自动支持 `ctest --test-dir build`

> [!NOTE] 用 `--build` 也能跑测试
> `cmake --build build --target test` 会先构建所有测试，再自动运行 `ctest`。

> [!TIP] 关闭测试
> 重新配置时加 `-DBUILD_TESTING=OFF` 即可跳过测试：
> ```bash
> cmake -B build -S . -DBUILD_TESTING=OFF
> ```

---

## 8. 链接第三方库

```cmake
# 方式一：find_package
find_package(fmt REQUIRED)
target_link_libraries(app PRIVATE fmt::fmt)

# 方式二：FetchContent（自动下载）
include(FetchContent)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        10.0.0
)
FetchContent_MakeAvailable(fmt)
```

- `find_package(<包名> [版本] [REQUIRED] [COMPONENTS ...])`：查找系统已安装的库
  - `REQUIRED`：找不到就报错退出
  - `COMPONENTS`：很多库分组件，只找自己需要的
  - 链接时用 `包名::库名` 命名，如 `fmt::fmt`（建议以官方文档为准）
- `FetchContent`：让 CMake 自动下载并构建第三方项目

> [!NOTE] 子目录拆分
> 项目变大时，把 `CMakeLists.txt` 拆分到各子目录，在根目录用 `add_subdirectory` 汇总：
> ```cmake
> add_subdirectory(lib)
> add_subdirectory(src)
> ```
> 子目录里定义的 `target_*` 在根目录依然可见、可用。

---

## 附录：速查表

### 构建命令

```bash
cmake -B build -S .        # 配置
cmake --build build        # 构建
cmake --build build --target app   # 只构建指定目标
ctest --test-dir build     # 运行测试
```

| 构建类型 | 标志 | 用途 |
|---|---|---|
| Debug | `-g` | 调试 |
| Release | `-O3` | 发布，最高性能 |
| MinSizeRel | `-Os` | 最小体积 |
| RelWithDebInfo | `-O2 -g` | 发布 + 调试 |

### 预定义变量

| 变量名 | 含义 |
|---|---|
| `CMAKE_SOURCE_DIR` | 顶层源目录 |
| `PROJECT_SOURCE_DIR` | 最近的 `project()` 对应的源码目录 |
| `CMAKE_CURRENT_SOURCE_DIR` | 当前 `CMakeLists.txt` 目录 |
| `CMAKE_BINARY_DIR` | 顶层 build 目录 |
| `CMAKE_PROJECT_NAME` | 项目名（`project()` 的目标名） |
| `PROJECT_VERSION` | 项目版本 |

### 目标创建关键字

| 关键字 | 作用 |
|---|---|
| （空） | 默认类型（`add_executable` 可执行程序 / `add_library` 静态库） |
| `STATIC` | 静态库 |
| `SHARED` | 动态库 |
| `EXCLUDE_FROM_ALL` | 默认不构建 |

### 传播机制

| 关键字 | 目标本身能用 | 传给外部目标 | 用途 |
|---|---|---|---|
| PRIVATE | ✅ | ❌ | 内部实现 |
| PUBLIC | ✅ | ✅ | 公开 API |
| INTERFACE | ❌ | ✅ | 纯头文件库 |

### 其他常用命令

| 命令 | 作用 |
|---|---|
| `message(STATUS "…")` | 输出构建信息（`DEBUG`/`STATUS`/`FATAL_ERROR`/`AUTHOR_WARNING` 控制级别）|
| `file(GLOB SRC "*.c")` | 收集目录下匹配的文件到变量（不推荐用于生产构建，顺序不保证）|
