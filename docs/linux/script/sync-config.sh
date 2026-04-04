#!/usr/bin/env bash
# 用法: ./sync.sh push   # 将本地配置更新到仓库(script目录)
#       ./sync.sh pull   # 将仓库配置部署到本机

# 脚本所在目录(即 docs/linux/script/)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# 映射关系 "本地路径:仓库相对路径(相对于脚本目录)"
MAPPINGS=(
    ".bashrc:.bashrc"
    ".vimrc:../../tools/vim/.vimrc"
    ".tmux.conf:.tmux.conf"
    ".vim/config:../../tools/vim/.vim/config"
    ".vim/dict:../../tools/vim/.vim/dict"
)

usage() {
    echo "用法: $0 {push|pull}"
    exit 1
}

[ $# -ne 1 ] && usage

# 复制函数(自动创建目标目录)
copy_item() {
    local src="$1" dst="$2" desc="$3"
    mkdir -p "$(dirname "$dst")"
    if [ -d "$src" ]; then
        # 如果目标已存在，先删除
        [ -d "$dst" ] && rm -rf "$dst"
        cp -r "$src" "$dst" && echo "  ✓ $desc" || { echo "  ✗ 复制目录失败: $desc" >&2; exit 1; }
    elif [ -f "$src" ]; then
        cp "$src" "$dst" && echo "  ✓ $desc" || { echo "  ✗ 复制文件失败: $desc" >&2; exit 1; }
    else
        echo "  ✗ 源不存在: $src" >&2
        exit 1
    fi
}

# 推送:本地 -> 仓库(script目录)
push_mode() {
    echo "将本地配置同步到仓库..."
    for mapping in "${MAPPINGS[@]}"; do
        local_path="${mapping%%:*}"
        repo_path="${mapping#*:}"
        src="$HOME/$local_path"
        dst="$SCRIPT_DIR/$repo_path"
        if [ ! -e "$src" ]; then
            echo "  本地不存在: $src"
            continue
        fi
        copy_item "$src" "$dst" "$local_path -> $repo_path"
    done
}

# 拉取:仓库(script目录) -> 本地
pull_mode() {
    echo "从仓库部署配置到本机..."
    for mapping in "${MAPPINGS[@]}"; do
        local_path="${mapping%%:*}"
        repo_path="${mapping#*:}"
        src="$SCRIPT_DIR/$repo_path"
        dst="$HOME/$local_path"
        if [ ! -e "$src" ]; then
            echo "  仓库中不存在: $src"
            continue
        fi
        copy_item "$src" "$dst" "$repo_path -> $local_path"
    done
    echo "部署完成."
}

# 主逻辑
case "$1" in
    push) push_mode ;;
    pull) pull_mode ;;
    *) usage ;;
esac
