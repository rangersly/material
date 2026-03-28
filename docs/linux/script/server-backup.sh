# Copyright(c) 2024 ely. All rights reserved.
#
# Name: format.sh v1.0
#
# Program:
#	Shell Script format
#
# History:
#	2024/07/24		e0x1a			new commit
#
# AUTHOR:
#		e0x1a "e0x1a@aliyun.com"
#!/bin/bash
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

SOURCE_DIR="$(dirname "$(realpath "$0")")"
BACKUP_DIR="/mnt/backup/app"
RETENTION=30                # 保留的备份数量

# 创建备份目录（如果不存在）
mkdir -p "$BACKUP_DIR"

# 遍历源目录下的所有子目录
for dir in "$SOURCE_DIR"/*/; do
    dir_name=$(basename "${dir%/}")
    # 跳过非目录文件（如 backup.sh）
    if [ -d "$dir" ]; then
        # 生成带日期的备份文件名
        backup_file="$BACKUP_DIR/${dir_name}_$(date +%Y%m%d).tar.gz"
        # 压缩并备份目录
        tar -czf "$backup_file" -C "$SOURCE_DIR" "$dir_name"

        # 清理旧备份
        find "$BACKUP_DIR" -name "${dir_name}_*.tar.gz" -type f \
          | sort -r \
          | tail -n +$(($RETENTION + 1)) \
          | xargs rm -f 2>/dev/null
    fi
done

