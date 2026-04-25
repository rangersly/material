# CMake 构建工具

- [构建命令](#构建命令)
- [基本概念](#基本概念)
- [最小构建](#最小构建)
- [预定义变量](#预定义变量)
- [编译控制](#编译控制)
- [链接库](#链接库)
- [目录组织](#目录组织)
- [其他常用命令](#其他常用命令)

## 构建命令

cmake -B build -S .
cmake --build build

- 构建类型 - CMake自动优化开关
  - `cmake -B build -S . -DCMAKE_BUILD_TYPE=<构建类型>`
    |构建类型|默认标志|用途|
    |---|---|---|
    |**Debug**|`-g`|调试|
    |**Release**|`-O3`|发布,最高性能|
    |**MinSizeRel**|`-Os`|最小体积,嵌入式|
- 仅构建指定目标
  - `cmake --build build --target mytest` 常用于测试

## 基本概念

- **目标** - target
  - 可以是可执行程序,或者库
- **属性**
  - 挂在目标上的,例如编译版本,包含的源文件等
- **传播机制**
  - 控制属性是怎么在链接的目标之间传播
    |**关键字**|**目标本身能否获得属性(私有)**|**目标是否把属性传递出去(外部接口)**|**场景**|
    |---|---|---|---|
    |**PRIVATE**|✅|❌|内部实现|
    |**PUBLIC**|✅|✅|公开API|
    |**INTERFACE**|❌|✅|纯头文件库|

## 最小构建

```cmake
# 限制最低版本
cmake_minimum_required(VERSION 3.20)

# 工程项目名
project(MyFirstProject VERSION 1.0)

# 创建一个目标,这个目标是可执行文件
add_executable(myapp src/main.cpp)
```
## 编译控制

- **目标级编译特性**
  - `target_compile_features(<目标> <传播关键字> <属性(特性列表)>`
  - 特性列表
    - `cxx_std_11` 17,20,23
    - `c_std_11` 17,23
- **优化等级**
  - `target_compile_options(myapp PRIVATE -O2)`

## 预定义变量

|变量名|含义|
|---|---|
|`CMAKE_SOURCE_DIR`|顶层源目录|
|`CMAKE_CURRENT_SOURCE_DIR`|当前`CMakeList`目录|
|`CMAKE_BINARY_DIR`|顶层`build`目录|
|`PROJECT_NAME`|项目名|
|`PROJECT_VERSION`|项目版本|

## 链接库

- 创建目标的关键字
  |关键字|作用|
  |---|---|
  |空|默认构建可执行程序|
  |`STATIC`|构建静态库|
  |`SHARED`|构建动态库|
  |`EXCLUDE_FROM_ALL`|默认状态下不构建,常用于测试代码|

```cmake
# 创建静态库目标
add_library(mylog STATIC src/mylog.cpp)
# 创建动态库目标
add_library(mylog SHARED src/mylog.cpp)
# 链接源文件属性到库目标上
target_link_libraries(myapp PRIVATE mylog)
# 挂载库目录属性到目标上
target_include_directories(mylog
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)
```

> [!NOTE]
> **PUBLIC关键字** : 传播机制核心,任何链接了 `mylog` 的目标都会自动获得这个路径

---

**纯头文件库** : `INTERFACE`

```cmake
# 创建一个伪目标,代表纯头文件库
add_library(myutils INTERFACE)
# 挂载库目录属性到目标上
target_include_directories(myutils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/utils)
# 然后链接两个目标
target_link_libraries(myapp PRIVATE myutils)
```
## 目录组织

随着项目变大,将 `CMakeList.txt` 拆分到各个子目录进行构建是个好方法

需要做的只是把单个 `CMakeList` 关于相应子目录的内容原样拆到各个子目录去,然后在根目录的 `CMakeList` 改造成 **总管**

```cmake
# 引入子目录
add_subdirectory(lib)
add_subdirectory(src)
```

# 其他常用命令

- `message(STATIC "message")` : 输出内容
