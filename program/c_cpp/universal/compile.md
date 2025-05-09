# 预编译指令

## 目录
- [define](#define)
  - [预定义宏](#预定义宏)
  - [defined](#defined)
- [ifdef](#ifdef)
- [ifndef](#ifndef)
- [undef](#undef) : 若要修改一个宏,先移除再定义
- [endif](#endif)
- [pragma](#pragma)
- [error](#error)
- [warning](#warning)

## define

---

### 预定义宏
1. 平台相关
  + `__STDC__` 如果编译器遵循ANSI C标准，则定义为1
  + `__cplusplus` 如果编译器支持C++，则定义为一个版本号 如199711L表示C++98，201103L表示C++11等
  + `_WIN32` 在Windows平台下定义，表示目标系统是32位或64位
  + `_WIN64`
  + `__unix__`
  + `__linux__`
  + `__APPLE__`

2. 编译器相关
  + `__GNUC__` 如果编译器是GCC,则定义为GCC的主版本号
  + `__clang__` 如果编译器是Clang
  + `_MSC_VER` 如果编译器是Microsoft Visual C++，则定义为一个版本号
  + `__ICC` 如果编译器是Intel C/C++ Compiler，则定义

3. 文件和行号相关的预定义宏
  + `__FILE__` 当前文件的名称
  + `__LINE__` 当前文件的行号
  + `__DATE__` 编译日期
  + `__TIME__` 编译时间

4. 其他
  + `__func__` `__FUNCTION__` 当前函数的名称
  + `__PRETTY_FUNCTION__` 在C++中，包含当前函数的完整声明

---

### defined

如果一个宏被定义,则 `defined(<MACRO_NAME>)` 返回真

---

## pragma
由编译器定义的预处理指令,若不支持则无操作

`#pragma once`  确保头文件只被包含一次
