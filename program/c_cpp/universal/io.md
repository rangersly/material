# c with cpp IO


# INDEX

- [标准IO流](#iostream)
- [C](#c)
  - [格式化IO](#format-io)
  - [字符IO](#char-io)
  - [Cstring](#cstring)
  - [C二进制IO](#cbin)
  - [C文件操作](#c-file)
  - [error](#c-error)
- [cpp stdio](#cpp-stdio)
- [cpp fio](#cpp-fio)
- [关闭缓冲区读取](#../linux/ncurses.c)
- [ANSI](#./ansi.md)
- [宏](#macro)

---

## **iostream**

+ stdin
+ stdout
+ stderr

---

## **c**

`#include <stdio.h>`

---

### **format-io**

- scanf        格式化输入函数
- printf       格式化输出函数
- fscanf        格式化输入函数(第一个参数是`FILE *stream`)
- fprintf       格式化输出函数(第一个参数是`FILE *stream`)

__控制符__
  +    %d %nd %ld %x %o         整数
  +    %f %n.mf %lf            浮点数
  +    %c
  +    %s
  +    %p                        ptr

---

### char-io

+ IN
|function prototype        |remark                               |
|--------------------------|-------------------------------------|
|`int getchar(void)`       |宏,标准IO                            |
|`int getc(FILE *stream)`  |宏,所有流                            |
|`int fgetc(FILE *stream)` |真正的函数                           |
|`int ungetc(int c,FILE *stream)`|将一个字符返回流中             |

+ OUT
|function prototype        |remark                               |
|--------------------------|-------------------------------------|
|`int putchar(int c)`      |宏,标准IO                            |
|`int putc(int c,FILE *stream)`|宏,所有流                        |
|`int fputc(int c,FILE *stream)`|真正的函数                      |

---

### **cstring**

|function prototype                                       |remark                          |
|---------------------------------------------------------|--------------------------------|
|`char *fgets(char *s,int size,FILE *stream)`             |到达行尾(包含换行符),EOF,size-1返回|
|`int fputs(const char *restrict s, FILE *restrict stream)`|不在后添加换行符               |

---

### cbin

`size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);`
 + size   读写的块大小
 + nmemb  读写的块数量
`size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);`

---

### c-file

- `FILE *fp` 文件指针
- `FILE *fopen(const char *pathname, const char *mode);` 错误返回NULL
- `int fclose(FILE *stream);` 关闭文件 返回0为正常关闭
- `FILE *tmpfile(void)`  创建一个临时文件,返回一个'wb+'模式的文件指针
- `char *tmpnam(char *name)`  创建一个临时文件名,最长`L_tmpnam`
- `int remove(const char *pathname)`  删除一个文件
- `int rename(const char *oldname, const char *newname)`  修改文件名字

**mode**
+ "r"   读
+ "w"   写，截0，新建
+ "a"   写，尾+，新建
+ "r+"  读写
+ "w+"  读写，截0，新建
+ "a+"  读写，仅尾+，新建
+ "b"   搭配表二进制，仅win

`long ftell(FILE *stream);` 获取当前文件指针位置
`int fseek(FILE *stream, long offset, int whence);` 移动文件指针
 + offset    移动字节数
 + whence    参考位置
  + `SEEK_SET`  文件头
  + `SEEK_CUR`  当前位置
  + `SEEK_END`  文件尾

`int fflush(FILE *stream);`  刷新缓冲区
`int setvbuf(FILE *stream, char *buf, int mode, size_t size);` 设置缓冲区,return 0
+ buf  设置的缓冲区
+ mode
 - `_IOFBF` 完全缓冲
 - `_IOLBF` 行缓冲
 - `_IONBF` 无缓冲
+ size  指定缓冲区的大小，无缓冲时无效

---

## c-error

- `void perror(const char *message);`
  - 打印message并在后面根据errno错误码生成错误信息
  - errno全局变量定义于`<errno.h>`,仅在发生错误时被设置

- `int ferror(FILE *stream);` 流异常时return非0
- `int feof(FILE *stream)`  文件尾时返回真
- `void clearerr(FILE *stream)`  重置错误位

---

## cpp-stdio

>    头文件
#include <iostream>

`ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);`    关闭缓冲加速

>
```cpp
    cin.get(c);        //返回一个流引用
    c = cin.get();    //返回char，略快
    cin.get(str, 100, '\n');    //读入字符串
    cin.width(10);    //设置场宽
```

>    
```cpp
    std::flush        // 立即刷新缓冲区
    std::endl        // 换行加刷新
```
________________________________________________

## cpp-fio 

>    头文件
#include <fstream>

```cpp
    //文件流的创建 打开 关闭
    fstream fin;
    fstream fout;

    fin.open("in");
    fout.open("out");

    fin.close();
    fout.close();
/*
    open函数的原型如下：
    void open(char const *,int filemode,int =filebuf::openprot);
    它有3个参数，第1个是要打开的文件名，第2个是文件的打开方式，第3个是文件的保护方式，一般都使用默认值。
    第2个参数可以取如下所示的值：
    打开方式    解释
    ios::in    打开文件进行读操作，这种方式可避免删除现存文件的内容
    ios::out    打开文件进行写操作，这是默认模式
    ios::ate    打开一个已有的输入或输出文件并查找到文件尾开始
    ios::app    在文件尾追加方式写文件
    ios::binary    指定文件以二进制方式打开，默认为文本方式
    ios::trunc    如文件存在，将其长度截断为零并清除原有内容，如果文件存在先删除，再创建
    除ios_base::app方式之外，文件刚刚打开时当前读写位置的文件指针都定位于文件的开始位置，而ios_base::app使文件当前的写指针定位于文件尾

    函数    功能
    bad()    如果进行非法操作，返回true，否则返回false
    clear()    设置内部错误状态，如果用缺省参量调用则清除所有错误位
    eof()    如果提取操作已经到达文件尾，则返回true，否则返回false
    good()    如果没有错误条件和没有设置文件结束标志，返回true，否则返回false
    fail()    与good相反，操作失败返回false，否则返回true
    is_open()    判定流对象是否成功地与文件关联，若是，返回true，否则返回false
*/
    
    // 二进制文件读写
    fin.write((char*)&data, sizeof data);
    fin.read((char*)&data, sizeof data);

/*
    随机存取
        seekg(pos,ios::);
        seekg(pos);
        seekp(pos,ios::);
        seekp(pos);
    
        tellg();
        tellp();

    文件位置
        ios::beg
        ios::cur
        ios::end
*/
```

---

### **macro**
- `BUFSIZ` : 系统级缓冲区大小
