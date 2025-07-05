#!/bin/bash

# 监控网络环境来检测是否断电自动关机

# 配置文件路径
FLAG_FILE="/tmp/network_down.flag"
LOG_FILE="/var/log/network_watchdog.log"

# 检测网络连通性（使用Google DNS检测）
check_network() {
    if ping -c 2 -W 1 8.8.8.8 >/dev/null 2>&1; then
        return 0  # 网络正常
    else
        return 1  # 网络断开
    fi
}

# 主循环
while true; do
    if check_network; then
        # 网络正常
        if [[ -f "$FLAG_FILE" ]]; then
            # 取消关机计划
            shutdown -c
            rm -f "$FLAG_FILE"
        fi
    else
        # 网络断开
        if [[ ! -f "$FLAG_FILE" ]]; then
            # 首次检测到断网，记录时间
            date +%s > "$FLAG_FILE"
            echo "$(date): Network down!" | tee -a "$LOG_FILE"
        else
            # 检查是否达到30分钟
            start_time=$(cat "$FLAG_FILE")
            current_time=$(date +%s)
            elapsed=$((current_time - start_time))
            
            if ((elapsed >= 1800)); then  # 1800秒=30分钟
                echo "$(date): Shutting down now!" | tee -a "$LOG_FILE"
                shutdown -h now
            fi
        fi
    fi
    sleep 300  # 等待5分钟（300秒）
done
