# cpp-stream 


# INDEX

- [标准IO流](#iostream)
- [cpp stdio](#cpp-stdio)
- [cpp fio](#cpp-fio)
- [关闭缓冲区读取](../linux/ncurses.c)
- [ANSI](#./ansi.md)

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
