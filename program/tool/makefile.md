# make

## 目录
- [参数](#参数)
- [makefile](#makefile)

## 参数
`-n`  参数可以打印出make会执行的命令，但不真正执行  
`-f <filename>`  指定makefile
`-i`  忽略错误
`-k`  在某个目标失败时,尽量构建其他
`-s`  静默
`-j4`  4线程
`-C /dir`  进入指定目录再运行
`-d`  debug
`-w`  打印工作目录
`-B`  强制重新构建

## makefile
Makefile 是一种用于自动化构建和管理项目的工具，尤其在 C/C++ 项目中广泛使用。除了基本的规则和依赖关系，Makefile 还支持一些高级语法和功能，可以帮助你编写更灵活和高效的构建脚本

规则:依赖
	命令
__注意: 命令前面必须要用Tab__

## 普通变量定义
OPTION = -O3 -Wall

## 变量使用
	g++ $(OPTION) xxx

### 1. 变量和赋值
Makefile 支持多种变量赋值方式：

- **`=`**：递归展开变量，变量值在使用时展开。
- **`:=`**：简单展开变量，变量值在定义时展开。
- **`?=`**：条件赋值，只有当变量未定义时才赋值。
- **`+=`**：追加赋值，将值追加到变量末尾。

```makefile
CC = gcc
CFLAGS := -Wall -O2
CFLAGS += -g
```

### 2. 自动变量
Makefile 提供了一些自动变量，用于简化规则的编写：

- **`$@`**：目标文件名。
- **`$<`**：第一个依赖文件名。
- **`$^`**：所有依赖文件列表。
- **`$?`**：所有比目标新的依赖文件列表。
- **`$*`**：目标文件的主干名（不包含扩展名）。

```makefile
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
```

### 3. 模式规则
模式规则允许你使用通配符来定义规则，适用于多个文件。

```makefile
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
```

### 4. 函数
Makefile 提供了一些内置函数，用于处理字符串、文件名等。

- **`$(wildcard pattern)`**：匹配文件名模式。
- **`$(patsubst pattern,replacement,text)`**：模式替换。
- **`$(shell command)`**：执行 shell 命令并返回结果。
- **`$(foreach var,list,text)`**：循环遍历列表。

```makefile
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
```

### 5. 条件判断
Makefile 支持条件判断，可以根据条件执行不同的操作。

```makefile
ifeq ($(DEBUG),1)
	CFLAGS += -DDEBUG
else
	CFLAGS += -DNDEBUG
endif
```

### 6. 包含其他 Makefile
你可以使用 `include` 指令将其他 Makefile 包含到当前 Makefile 中。

```makefile
include config.mk
```

### 7. 多目标规则
你可以为一个规则定义多个目标，这样它们可以共享相同的命令。

```makefile
all: target1 target2

target1 target2:
	@echo Building $@
```

### 8. 伪目标
伪目标是指那些不对应实际文件的目标，通常用于执行一些操作，如清理、安装等。

```makefile
.PHONY: clean

clean:
	rm -f *.o
```

### 9. 嵌套 Makefile
你可以在 Makefile 中调用另一个 Makefile，通常用于构建子目录中的项目。

```makefile
SUBDIRS = dir1 dir2

$(SUBDIRS):
	$(MAKE) -C $@

all: $(SUBDIRS)
```

### 10. 自定义函数
你可以通过 `define` 和 `endef` 定义自定义函数。

```makefile
define greet
	@echo "Hello, $(1)!"
endef

all:
	$(call greet,World)
```

### 11. 错误处理
你可以使用 `$(error text)` 和 `$(warning text)` 来生成错误或警告信息。

```makefile
ifeq ($(CC),)
	$(error CC is not set)
endif
```

### 13. 隐式规则
Makefile 有一些内置的隐式规则，可以自动推导如何从源文件生成目标文件。你可以通过定义自己的隐式规则来覆盖默认行为。

```makefile
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
```

### 14. 动态依赖
你可以使用 `-include` 来包含动态生成的依赖文件，通常用于自动生成头文件依赖。

```makefile
-include $(OBJS:.o=.d)

%.d: %.c
	@$(CC) -MM $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
```

### 16. 环境变量
Makefile 可以访问环境变量，并且可以通过 `export` 将变量传递给子 Makefile。

```makefile
export PATH := $(PATH):/usr/local/bin
```

### 17. 多行命令
你可以使用反斜杠 `\` 将长命令分成多行。

```makefile
all:
	@echo "This is a long command that spans \
	multiple lines."
```

### 18. 命令前缀
命令前缀可以控制命令的执行方式：

- **`@`**：不显示命令本身，只显示输出。
- **`-`**：忽略命令的错误，继续执行。

```makefile
all:
	@echo "This command will not be displayed"
	-rm -f non_existent_file
```

### 19. 文件搜索路径
你可以使用 `VPATH` 或 `vpath` 来指定源文件的搜索路径。

```makefile
VPATH = src:include

vpath %.c src
vpath %.h include
```

### 20. 递归扩展变量
递归扩展变量在使用时才会展开，可以用于动态生成内容。

```makefile
FOO = $(BAR)
BAR = $(BAZ)
BAZ = Hello

all:
	@echo $(FOO)  # 输出 Hello
```

### 21. 静态模式规则
静态模式规则允许你为特定目标定义规则。

```makefile
objects = foo.o bar.o

$(objects): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
```

### 22. 多架构支持
你可以通过条件判断来支持多架构编译。

```makefile
ifeq ($(ARCH),x86)
	CFLAGS += -m32
else ifeq ($(ARCH),x64)
	CFLAGS += -m64
endif
```

### 23. 自定义后缀规则
你可以定义自定义的后缀规则来处理特定类型的文件。

```makefile
.SUFFIXES: .cpp .o

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@
```

### 24. 使用 `eval` 动态生成规则
`eval` 函数可以动态生成 Makefile 规则。

```makefile
define MAKE_RULE
$(1): $(2)
	$(CC) $(CFLAGS) -c $$< -o $$@
endef

$(eval $(call MAKE_RULE,foo.o,foo.c))
```

### 25. 使用 `foreach` 循环
`foreach` 函数可以用于循环处理列表中的每个元素。

```makefile
DIRS = dir1 dir2 dir3

all:
	$(foreach dir,$(DIRS),$(MAKE) -C $(dir);)
```

### 26. 使用 `call` 调用自定义函数
`call` 函数可以调用自定义函数，并传递参数。

```makefile
define greet
	@echo "Hello, $(1)!"
endef

all:
	$(call greet,World)
```

### 27. 使用 `shell` 函数执行外部命令
`shell` 函数可以执行外部命令并返回结果。

```makefile
DATE := $(shell date)
```

### 28. 使用 `info` 和 `warning` 输出信息
`info` 和 `warning` 函数可以用于输出信息。

```makefile
$(info Building target $(TARGET))
$(warning This is a warning message)
```

### 29. 使用 `if` 条件判断
`if` 函数可以用于条件判断。

```makefile
DEBUG = 1

CFLAGS += $(if $(DEBUG),-g,-O2)
```

### 30. 使用 `or` 和 `and` 逻辑操作
`or` 和 `and` 函数可以用于逻辑操作。

```makefile
ifeq ($(DEBUG),1)
	CFLAGS += -g
else ifeq ($(OPTIMIZE),1)
	CFLAGS += -O2
endif
```

### 31. 使用 `not` 取反
`not` 函数可以用于取反操作。

```makefile
ifneq ($(DEBUG),1)
	CFLAGS += -O2
endif
```

### 32. 使用 `filter` 和 `filter-out` 过滤列表
`filter` 和 `filter-out` 函数可以用于过滤列表。

```makefile
SRCS = foo.c bar.c baz.c

C_SRCS = $(filter %.c,$(SRCS))
NON_C_SRCS = $(filter-out %.c,$(SRCS))
```

### 33. 使用 `sort` 排序列表
`sort` 函数可以用于排序列表。

```makefile
SRCS = foo.c bar.c baz.c

SORTED_SRCS = $(sort $(SRCS))
```

### 34. 使用 `strip` 去除空格
`strip` 函数可以用于去除字符串中的空格。

```makefile
STR =   foo bar

STRIPED_STR = $(strip $(STR))
```

### 35. 使用 `findstring` 查找子字符串
`findstring` 函数可以用于查找子字符串。

```makefile
ifeq ($(findstring foo,$(STR)),foo)
	@echo "Found foo"
endif
```

### 36. 使用 `subst` 替换字符串
`subst` 函数可以用于替换字符串。

```makefile
STR = foo bar baz

NEW_STR = $(subst foo,FOO,$(STR))
```

### 37. 使用 `patsubst` 模式替换
`patsubst` 函数可以用于模式替换。

```makefile
SRCS = foo.c bar.c baz.c

OBJS = $(patsubst %.c,%.o,$(SRCS))
```

### 38. 使用 `wildcard` 匹配文件名
`wildcard` 函数可以用于匹配文件名。

```makefile
SRCS = $(wildcard *.c)
```

### 39. 使用 `dir` 和 `notdir` 获取目录和文件名
`dir` 和 `notdir` 函数可以用于获取目录和文件名。

```makefile
FILE = /path/to/file.c

DIR = $(dir $(FILE))
NAME = $(notdir $(FILE))
```

### 40. 使用 `suffix` 和 `basename` 获取后缀和主干名
`suffix` 和 `basename` 函数可以用于获取文件的后缀和主干名。

```makefile
FILE = file.c

SUFFIX = $(suffix $(FILE))
BASENAME = $(basename $(FILE))
```

### 41. 使用 `addsuffix` 和 `addprefix` 添加后缀和前缀
`addsuffix` 和 `addprefix` 函数可以用于添加后缀和前缀。

```makefile
FILES = foo bar baz

FILES_WITH_SUFFIX = $(addsuffix .c,$(FILES))
FILES_WITH_PREFIX = $(addprefix src/,$(FILES))
```

### 42. 使用 `join` 连接列表
`join` 函数可以用于连接两个列表。

```makefile
LIST1 = foo bar
LIST2 = baz qux

JOINED_LIST = $(join $(LIST1),$(LIST2))
```

### 43. 使用 `word` 和 `wordlist` 获取列表中的元素
`word` 和 `wordlist` 函数可以用于获取列表中的元素。

```makefile
LIST = foo bar baz

FIRST = $(word 1,$(LIST))
SUBLIST = $(wordlist 2,3,$(LIST))
```

### 44. 使用 `words` 获取列表长度
`words` 函数可以用于获取列表的长度。

```makefile
LIST = foo bar baz

LENGTH = $(words $(LIST))
```

### 45. 使用 `firstword` 获取列表的第一个元素
`firstword` 函数可以用于获取列表的第一个元素。

```makefile
LIST = foo bar baz

FIRST = $(firstword $(LIST))
```

### 46. 使用 `lastword` 获取列表的最后一个元素
`lastword` 函数可以用于获取列表的最后一个元素。

```makefile
LIST = foo bar baz

LAST = $(lastword $(LIST))
```

### 47. 使用 `abspath` 获取绝对路径
`abspath` 函数可以用于获取绝对路径。

```makefile
FILE = file.c

ABS_PATH = $(abspath $(FILE))
```

### 48. 使用 `realpath` 获取规范化的绝对路径
`realpath` 函数可以用于获取规范化的绝对路径。

```makefile
FILE = ../file.c

REAL_PATH = $(realpath $(FILE))
```
