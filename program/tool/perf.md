# perf 功能强大的linux性能分析工具
  
`perf [command] [options] [arguments]`  
子命令   额外选项   要分析的程序或命令

##	性能概览
`perf stat <command>`
>	性能计数器
```
		  0.60 		msec task-clock       #    0.589 CPUs utilized 		cpu利用率
             0      context-switches      #    0.000 /sec				上下文切换次数
             0      cpu-migrations        #    0.000 /sec				cpu切换
            68      page-faults           #  113.661 K/sec				页错误次数
     1,772,372      cycles                #    2.963 GHz				时钟周期
     1,247,336      instructions          #    0.70  insn per cycle		指令数量
       229,972      branches              #  384.396 M/sec				分支数量
         8,262      branch-misses         #    3.59% of all branches	未命中分支

       0.001016124 seconds time elapsed				总用时

       0.000000000 seconds user
       0.001106000 seconds sys
```

##	记录性能数据
`perf record -g -o output.data <command>`
+	-o			指定输出文件 
+	-g			启用调用图  

`sudo perf record -a -g -o system.data`
+	-a 			采集系统级数据  
  

##	分析性能数据
`perf report -i output.data`
+	-i			指定输入文件

##	实时性能监控
`sudo perf top`

## 操作快捷键
| 快捷键               | 功能说明                                                                 |
|----------------------|--------------------------------------------|
| **h / ? / F1**       | 显示帮助窗口                               |
| **↑/↓/PgUp/PgDn/空格** | 上下浏览数据                             |
| **q / Esc / Ctrl+C** | 退出浏览器或返回上一屏                     |
| **Tab / Shift+Tab**  | 切换不同事件组（多事件会话）               |
| **Enter**            | 深入查看当前符号（DSO/线程）并注解         |
| **Esc**              | 退回上一级视图                             |
| **+**                | 展开/折叠一级调用链（callchain）           |
| **a**                | 注解当前符号（显示汇编代码与采样分布）     |
| **C**                | 折叠所有调用链                             |
| **d**                | 聚焦到当前动态共享库（DSO）                |
| **e**                | 展开/折叠主入口调用链                      |
| **E**                | 展开全部调用链                             |
| **F**                | 切换显示过滤条目的百分比                   |
| **K**                | 显示/隐藏列标题                            |
| **L**                | 聚焦到内核映射区域                         |
| **S**                | 调整显示的百分比阈值                       |
| **i**                | 显示上下文菜单                             |
| **P**                | 聚焦到当前处理器插槽（Socket）             |
| **r**                | 显示头部信息（如记录参数）                 |
| **s**                | 将直方图保存到 `perf.hist.N` 文件          |
| **t**                | 运行可用脚本（如火焰图生成）               |
| **V**                | 切换到 PMD 文件中的其他数据文件            |
| **/**                | 聚焦到当前线程                             |
| **0-9**              | 切换详细模式（如显示调用链中的 DSO 名称）  |
| **输入符号名**        | 按名称过滤符号                            |
| **事件编号（如1/2/3）** | 按事件组中的特定事件排序                |
