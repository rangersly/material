# make

## 目录
- [参数](#argv)
- [makefile](#makefile)
  - [变量与赋值](#变量和赋值)
  - [自动变量](#自动变量)
  - [函数](#函数)
  - [条件判断](#条件判断)
  - [包含其他 Makefile](#include)
  - [多目标规则](#多目标规则)
  - [伪目标](#伪目标)
  - [自定义函数](#自定义函数)
  - [错误处理](#错误处理)
  - [环境变量](#环境变量)
  - [多行命令](#多行命令)
  - [命令前缀](#命令前缀)
  - [文件搜索路径](#文件搜索路径)
  - [静态模式规则](#静态模式规则)
  - [自定义后缀规则](#自定义后缀规则)
  - [动态生成规则](#动态生成规则)
  - [使用循环](#使用循环)
  - [执行外部命令](#执行外部命令)
  - [](#)

---

## **argv**
-  `-n`  参数可以打印出make会执行的命令，但不真正执行  
-  `-f <filename>`  指定makefile
-  `-i`  忽略错误
-  `-k`  在某个目标失败时,尽量构建其他
-  `-s`  静默
-  `-j4`  4线程
-  `-C /dir`  进入指定目录再运行
-  `-d`  debug
-  `-w`  打印工作目录
-  `-B`  强制重新构建

## **makefile**
Makefile 是一种用于自动化构建和管理项目的工具，尤其在 C/C++ 项目中广泛使用。除了基本的规则和依赖关系，Makefile 还支持一些高级语法和功能，可以帮助你编写更灵活和高效的构建脚本

```
规则:依赖
	命令
__注意: 命令前面必须要用Tab__
```

- 普通变量定义
`OPTION = -O3 -Wall`

- 变量使用
`g++ $(OPTION) xxx`

---

### 变量和赋值
- **`=`**：递归展开变量，变量值在使用时展开。
- **`:=`**：简单展开变量，变量值在定义时展开。
- **`?=`**：条件赋值，只有当变量未定义时才赋值。
- **`+=`**：追加赋值，将值追加到变量末尾。

---

### 自动变量
- **`$@`**：目标文件名。
- **`$<`**：第一个依赖文件名。
- **`$^`**：所有依赖文件列表。
- **`$?`**：所有比目标新的依赖文件列表。
- **`$*`**：目标文件的主干名（不包含扩展名）。

```makefile
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
```

---

### 函数
Makefile 提供了一些内置函数，用于处理字符串、文件名等。

- **`$(wildcard pattern)`**：匹配文件名模式。
- **`$(patsubst pattern,replacement,text)`**：模式替换。
- **`$(shell command)`**：执行 shell 命令并返回结果。
- **`$(foreach var,list,text)`**：循环遍历列表。

```makefile
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
```

---

### 条件判断
- Makefile 条件判断，可以根据条件执行不同的操作。

```makefile
ifeq ($(DEBUG),1)
	CFLAGS += -DDEBUG
else
	CFLAGS += -DNDEBUG
endif
```

- `if` 函数可以用于条件判断。

```makefile
DEBUG = 1

CFLAGS += $(if $(DEBUG),-g,-O2)
```

- `or` 和 `and` 函数可以用于逻辑操作。

```makefile
ifeq ($(DEBUG),1)
	CFLAGS += -g
else ifeq ($(OPTIMIZE),1)
	CFLAGS += -O2
endif
```

- `not` 函数可以用于取反操作。

```makefile
ifneq ($(DEBUG),1)
	CFLAGS += -O2
endif
```

---

### include
你可以使用 `include` 指令将其他 Makefile 包含到当前 Makefile 中。

```makefile
include config.mk
```

- 你可以在 Makefile 中调用另一个 Makefile，通常用于构建子目录中的项目。

```makefile
SUBDIRS = dir1 dir2

$(SUBDIRS):
	$(MAKE) -C $@

all: $(SUBDIRS)
```

---

### 多目标规则
- 你可以为一个规则定义多个目标，这样它们可以共享相同的命令。

```makefile
all: target1 target2

target1 target2:
	@echo Building $@
```

---

### 伪目标
伪目标是指那些不对应实际文件的目标，通常用于执行一些操作，如清理、安装等。

```makefile
.PHONY: clean

clean:
	rm -f *.o
```

---

### 自定义函数
- 你可以通过 `define` 和 `endef` 定义自定义函数。

```makefile
define greet
	@echo "Hello, $(1)!"
endef

all:
	$(call greet,World)
```

- `call` 函数可以调用自定义函数，并传递参数。

```makefile
define greet
	@echo "Hello, $(1)!"
endef

all:
	$(call greet,World)
```

---

### 错误处理
你可以使用 `$(error text)` 和 `$(warning text)` 来生成错误或警告信息。

```makefile
$(error CC is not set)
$(info Building target $(TARGET))
$(warning This is a warning message)
```

---

### 环境变量
Makefile 可以访问环境变量，并且可以通过 `export` 将变量传递给子 Makefile。

```makefile
export PATH := $(PATH):/usr/local/bin
```

---

### 多行命令
你可以使用反斜杠 `\` 将长命令分成多行。

```makefile
all:
	@echo "This is a long command that spans \
	multiple lines."
```

---

### 命令前缀
命令前缀可以控制命令的执行方式：

- **`@`**：不显示命令本身，只显示输出。
- **`-`**：忽略命令的错误，继续执行。

```makefile
all:
	@echo "This command will not be displayed"
	-rm -f non_existent_file
```

---

### 文件搜索路径
你可以使用 `VPATH` 或 `vpath` 来指定源文件的搜索路径。

```makefile
VPATH = src:include

vpath %.c src
vpath %.h include
```

---

### 静态模式规则
静态模式规则允许你为特定目标定义规则。

```makefile
objects = foo.o bar.o

$(objects): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
```

---

### 自定义后缀规则
你可以定义自定义的后缀规则来处理特定类型的文件。

```makefile
.SUFFIXES: .cpp .o

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@
```

---

### 动态生成规则
`eval` 函数可以动态生成 Makefile 规则。

```makefile
define MAKE_RULE
$(1): $(2)
	$(CC) $(CFLAGS) -c $$< -o $$@
endef

$(eval $(call MAKE_RULE,foo.o,foo.c))
```

---

### 使用循环
`foreach` 函数可以用于循环处理列表中的每个元素。

```makefile
DIRS = dir1 dir2 dir3

all:
	$(foreach dir,$(DIRS),$(MAKE) -C $(dir);)
```

---

### 执行外部命令
`shell` 函数可以执行外部命令并返回结果。

```makefile
DATE := $(shell date)
```

---

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
