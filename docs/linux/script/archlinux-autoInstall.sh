#!/bin/bash

pacman -Syyu  # 更新源
pacman-key --lsign-key "farseerfc@archlinux.org"
pacman -Sy archlinuxcn-keyring
pacman -Syyu  # 更新源

pacman -S --noconfirm --needed man man-pages base-devel bash-completion noto-fonts noto-fonts-cjk noto-fonts-emoji fcitx5-im fcitx5-chinese-addons fcitx5-rime plasma yay btop firefox konsole gcc g++ gdb sdcc timeshift v2raya openssh perf

sudo usermod -a -G uucp $USER   # 允许用户使用串口

git clone http://git@e0x1a.cn:23000/rangersly/material.git
cp -rf ./material /home/rangersly
cp /home/rangersly/material/tool/vim/.vimrc /home/rangersly/
mkdir -p /home/rangersly/.vim/dict/
cp /home/rangersly/material/tool/vim/cpp.dict /home/rangersly/.vim/dict/
cp /home/rangersly/material/linux/config/.bashrc /home/rangersly/


systemctl enable v2ray
systemctl enable v2raya
systemctl enable sddm
systemctl enable bluetooth.service  # 设置开机自启

reboot
