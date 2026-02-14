# 在 Linux 系统中用于显示 ELF 格式文件信息的命令行工具

+   -a, --all
	    显示所有可用的信息。
+   -h, --file-header
    	显示 ELF 文件头信息。
+   -l, --program-headers
    	显示程序头表。
+   -S, --section-headers
    	显示节头表。
+   -g, --section-groups
   		显示节组。
+   -t, --section-details
    	显示节的详细信息。
+   -e, --headers
    	等同于 -h -l -S。
+   -s, --syms
    	显示符号表。
+   --dyn-syms
   	 	显示动态符号表。
+   -N, --dynamic
    	显示动态段。
+   -u, --unwind
    	显示 unwind 信息。
+   -I, --histogram
    	显示桶的直方图。
+   -x, --hex-dump=<section>
    	以十六进制形式转储指定节的内容。
+   -d, --use-dynamic
    	使用动态符号表代替静态符号表。
+   -r, --relocs
    	显示重定位入口。
+   -i, --notes
    	显示.note 节。
+   -A, --arch-specific
    	显示架构特定的信息。
+   -D, --dynamic-symbols
    	显示动态符号表。
+   -W, --wide
    	允许输出超过 80 个字符宽。
+   -H, --help
    	显示帮助信息。
+   -V, --version
    	显示版本信息。
