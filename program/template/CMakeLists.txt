cmake_minimum_required(VERSION 3.20)

project(cpp_template
    VERSION 1.0.0
    DESCRIPTION "C/C++ 项目模板"
    LANGUAGES C CXX
)

# ============================================================
# 全局设置
# ============================================================

# 默认构建类型为 Release,可用 -DCMAKE_BUILD_TYPE=Debug 覆盖
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "构建类型(Debug/Release/MinSizeRel/RelWithDebInfo)" FORCE)
endif()

# C / C++ 标准
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 导出 compile_commands.json,供 clangd / clang-tidy 使用
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 生成物统一输出到构建根目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# 通用警告选项
add_compile_options(-Wall -Wextra)

# ============================================================
# 静态库:C 实现,对外公开 include/ 下的头文件
# ============================================================
add_library(math_utils STATIC
    src/math_utils.c
)

target_include_directories(math_utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# ============================================================
# 可执行程序:C++ 实现,链接上面的 C 静态库
# ============================================================
add_executable(app
    src/main.cpp
)

target_link_libraries(app
    PRIVATE
        math_utils
)

# ============================================================
# 测试:CTest,可用 -DBUILD_TESTING=OFF 关闭
# ============================================================
include(CTest)

if(BUILD_TESTING)
    add_executable(test_math_utils
        tests/test_math_utils.cpp
    )
    target_link_libraries(test_math_utils
        PRIVATE
            math_utils
    )
    add_test(NAME math_utils_test COMMAND test_math_utils)
endif()
