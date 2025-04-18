#!/bin/bash

# 并行运行多个命令
command1 &
command2 &
command3 &

# 等待所有后台任务完成
wait

echo "所有任务执行完毕"
