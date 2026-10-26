# ============================================================
# C/C++ 项目模板
#
# 目录约定:
#   include/<库名>/  公开头文件(通过 PUBLIC 传播给消费方)
#   src/             库实现与内部头文件(PRIVATE,不对外暴露)
#   tests/           CTest 测试
#
# 使用方式:
#   1. 复制整个目录到新项目位置
#   2. 将下面的 cpp_template / math_utils / app 替换为实际名称
#   3. 按需增删源文件与目标
#
# 常用命令:
#   cmake -B build -S .                        # 配置,默认 Release
#   cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
#   cmake --build build                        # 构建
#   ctest --test-dir build                     # 运行测试
#   cmake -B build -S . -DBUILD_TESTING=OFF    # 关闭测试
# ============================================================

# 3.21 起提供 PROJECT_IS_TOP_LEVEL,用于区分
# “本模板作为独立项目”与“被其他项目引入”两种场景。
cmake_minimum_required(VERSION 3.21)

project(cpp_template
    VERSION 1.0.0
    DESCRIPTION "C/C++ 项目模板"
    LANGUAGES C CXX
)

# ============================================================
# 1. 核心库目标
#    无论本仓库是顶层项目,还是被其他项目通过
#    FetchContent / add_subdirectory 引入,都只构建这一部分。
#    改名时同步修改:add_library、ALIAS、target_* 中的目标名。
# ============================================================

add_library(math_utils STATIC
    src/math_utils.c
)

# 对外统一使用 math_utils::math_utils 链接,避免消费方依赖裸目标名。
# 消费方写法:target_link_libraries(xxx PRIVATE math_utils::math_utils)
add_library(math_utils::math_utils ALIAS math_utils)

# include/ 是公开接口:BUILD_INTERFACE 表示该路径只在构建树内生效。
# 若将来增加 install(EXPORT),需要再补 $<INSTALL_INTERFACE:include>。
# src/ 只供库自身使用,不对外传播。
target_include_directories(math_utils
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 这些属性只作用于 math_utils 目标本身,不会传播给消费方,
# 因此即使本模板被 FetchContent 引入也依然成立。
#   C_STANDARD:库源码使用 C17
#   C_STANDARD_REQUIRED:编译器不支持 C17 时直接报错
#   POSITION_INDEPENDENT_CODE:生成 -fPIC 代码,便于被链接进消费方的共享库
set_target_properties(math_utils PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE ON
)

# 警告选项只加在库自身,不通过 add_compile_options 污染消费方。
# 这里是 GCC / Clang 风格;若使用 MSVC,请改为 /W4。
target_compile_options(math_utils PRIVATE
    -Wall -Wextra
)

# ============================================================
# 2. 仅顶层项目才构建的内容
#    被其他项目引入时 PROJECT_IS_TOP_LEVEL 为 false,
#    下面整块都不会执行:
#      - 不构建示例程序 app
#      - 不构建测试 tests
#      - 不引入 CTest
#      - 不修改消费方的构建类型、输出目录与编译数据库设置
# ============================================================

if(PROJECT_IS_TOP_LEVEL)
    # 默认 Release;不覆盖用户显式传入的 -DCMAKE_BUILD_TYPE=...
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Release CACHE STRING
            "构建类型(Debug/Release/MinSizeRel/RelWithDebInfo)" FORCE)
    endif()

    # 示例程序与测试使用 C17 / C++17。
    # 库目标已在上面单独设置,这里主要作用于 app 与 tests。
    set(CMAKE_C_STANDARD 17)
    set(CMAKE_C_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    # 生成 compile_commands.json,供 clangd / clang-tidy 使用。
    # 模板自带 .clangd,会到 build/ 目录读取该文件。
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    # 所有生成物统一输出到构建根目录,便于运行与清理。
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

    # --------------------------------------------------------
    # 2.1 示例程序:C++ 入口,链接 C 静态库
    # --------------------------------------------------------
    add_executable(app
        src/main.cpp
    )

    target_compile_options(app PRIVATE
        -Wall -Wextra
    )

    target_link_libraries(app
        PRIVATE
            math_utils::math_utils
    )

    # --------------------------------------------------------
    # 2.2 测试
    #     BUILD_TESTING 由 include(CTest) 提供,默认 ON;
    #     可用 -DBUILD_TESTING=OFF 关闭。
    # --------------------------------------------------------
    include(CTest)

    if(BUILD_TESTING)
        add_executable(test_math_utils
            tests/test_math_utils.cpp
        )

        target_compile_options(test_math_utils PRIVATE
            -Wall -Wextra
        )

        target_link_libraries(test_math_utils
            PRIVATE
                math_utils::math_utils
        )

        add_test(NAME math_utils_test COMMAND test_math_utils)
    endif()
endif()
