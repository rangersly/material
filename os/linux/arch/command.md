# arch常用命令

 - [pacman](#pacman)


## pacman
 
 +  `-S` 同步
 +  `-y` 更新软件包数据库
 +  `-u` 升级已有安装包
 +  `-R` 卸载
 +  `-Q` 查看已安装
> example
 +  `pacman -Sy` 同步数据库
 +  `pacman -S <package_name>` 安装软件包
 +  `pacman -Syu` 更新系统
 +  `pacman -Rs <package_name>` 卸载同时删除无用的依赖
 +  `pacman -Ss <keyword>` 搜索软件包
 +  `sudo pacman -Sc` 清除缓存
