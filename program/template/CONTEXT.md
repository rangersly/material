# cpp_template

C/C++ 项目模板的语境,约定源文件如何组织、头文件如何分层、以及目标如何构建。

## Language

**公开头文件 (public header)**:
位于 `include/<库名>/` 下、对外暴露的头文件。使用引号带完整路径包含(如 `"math_utils/math_utils.h"`),`include/` 为搜索根,文件名用小写下划线,内容需包裹 `extern "C"` 守卫以便 C++ 调用。
_Avoid_: 对外头文件、公共接口头

**内部头文件 (internal header)**:
位于 `src/` 下、仅供本库实现使用的头文件,文件名以 `_internal.h` 结尾。不出现在 `include/`,不对外暴露。
_Avoid_: 私有头文件

**库目标 (library target)**:
由 `add_library` 定义的静态库,如 `math_utils`。`include/` 通过 `PUBLIC` 传播给链接它的目标,`src/` 通过 `PRIVATE` 仅自用。
_Avoid_: 模块

**可执行目标 (executable target)**:
由 `add_executable` 定义的可执行程序,如 `app`,通过 `target_link_libraries` 链接库目标。
_Avoid_: 程序、入口

**测试目标 (test target)**:
由 `add_executable` + `add_test` 定义、通过 CTest 运行的测试程序,如 `test_math_utils`。
_Avoid_: 用例
