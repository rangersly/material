# 文件系统损坏或误删除文件处理

## Linux

1. 备份
  ```bash
  sudo dd if=/dev/sdX of=/tmp/image.img bs=4M status=progress
  ```
2. 尝试重建

## windows

1. 备份,使用linux镜像dd备份或者DiskGenius图形界面工具
2. winfr恢复文件
  - `winfr 源盘符: [/模式] [/开关]
  - **模式选择**
  |文件系统|丢失情况|模式|说明|
  |NTFS|最近|`/regular`|快速|
  |NTFS|删除已久,磁盘损坏|`/extensive`|彻底,但速度慢|
  |FAT|任何|`/extensive`|非NTFS只能用这个|
  - 示例
    - `winfr C: D: /regular /n *.docx` 恢复所有DOCX文件
    - `winfr C: D: /extensive /n *project*` 恢复文件名包含project的文件夹
    - `winfr C: D: /regular /n \Users\ ` 恢复指定文件夹
