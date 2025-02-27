#	perf 功能强大的linux性能分析工具
  
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
