# Win+R 大合集

|命令|作用|
|---|---|
|cmd|打开cmd|
|dxdiag|电脑配置|
|cleanmgr|清理磁盘|
|regedit|注册表|
|msconfig|系统配置|
|mstsc|远程桌面|
|calc|计算器|

# cmd命令大合集

|命令|作用|
|---|---|
|`fsutil behavior query disabledeletenotify`|命令提示符查看系统有无开启TRIM回收指令|
|`fsutil behavior set disabledeletenotify 1`|开启TRIM|
|`fsutil behavior set disabledeletenotify 0`|关闭TRIM|
|`powercfg -h off`|关闭休眠，可节省C盘空间|
|`shutdown /r /fw /t 0`|重启到BIOS|

网络命令已整理到 [Windows 网络命令](../network/windows/commands.md)。
