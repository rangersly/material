#!/bin/bash

pacman -S man man-pages bash-completion
pacman -S noto-fonts noto-fonts-cjk noto-fonts-emoji   # 安装字体
pacman -S plasma
pacman -S fcitx5-im fcitx5-chinese-addons fcitx5-rime
pacman -S btop firefox konsole gcc g++ gdb sdcc

sudo usermod -a -G uucp $USER   # 允许用户使用串口

systemctl enable sddm
sudo systemctl enable bluetooth.service  # 设置开机自启

