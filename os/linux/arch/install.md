# archlinux安装

## 目录
- [基础安装](#基础安装)
  - [修改控制台字体](#修改控制台字体)
  - [验证引导](#验证引导)
  - [验证网络和更改系统时间](#验证网络和更改系统时间)
  - [硬盘分区](#硬盘分区)
  - [安装基础软件包](#安装基础软件包)
  - [生成fstab](#生成fstab)
  - [chroot配置](#chroot)
- [新系统](#新系统)
  - [换源](#换源)
  - [普通用户](#普通用户)
  - [KDE](#kde)

## 基础安装

### 修改控制台字体

`/usr/share/kbd/consolefonts/`  存放字体的位置  
`# setfont ter-132b`

### 验证引导

`# cat /sys/firmware/efi/fw_platform_size`  

### 验证网络和更改系统时间

`ip addr`
`timedatectl`

### 硬盘分区

```bash
parted /dev/sdX  # 进入parted交互界面
> mklabel gpt    # 创建分区表格式

gdisk /dev/sdX   # 分区
ef00  ->  1G
ef02  ->  2M
8300  ->  /

**先用最小系统启动**

mkfs.fat -F 32 /dev/sdX1  # 分区格式化
mkfs.ext4 /dev/sdX3

mount /dev/sdX3 /mnt
mount --mkdir /dev/sdX1 /mnt/boot
```

### 安装基础软件包

`pacstrap -K /mnt xxx`
+ base linux linux-firmware
+ vim base-devel networkmanager archlinuxcn-keyring
---
以下是可以等系统启动后安装的
+ sof-firmware 
+ yay
`pacman -S git base-devel && git clone https://aur.archlinux.org/yay.git && cd yay && makepkg -si`
+ man
+ fcitx5-im fcitx5-rime  # 输入法
+ alsa-utils  # 声卡驱动
+ 其他固件

### 生成fstab

`genfstab -U /mnt > /mnt/etc/fstab`

### chroot

```bash
ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime   # 配置时间
hwclock --systohc

vim /etc/locale.gen 
> 去掉 en_GB.UTF-8 以及 zh_CN.
locale-gen
vim /etc/locale.conf
> LANG=en_US.UTF-8

vim /etc/hostname
> [hostname]

passwd 

**安装引导**
pacman -S grub
grub-install --target=i386-pc /dev/sdX
grub-mkconfig -o /boot/grub/grub.cfg

umount -R /mnt

reboot
```

## 新系统

### 换源
- `/etc/pacman.d/mirrorlist`
```
Server = https://mirrors.tuna.tsinghua.edu.cn/archlinux/$repo/os/$arch
Server = http://mirrors.aliyun.com/archlinux/$repo/os/$arch
Server = https://mirrors.ustc.edu.cn/archlinux/$repo/os/$arch
```

### 普通用户

`useradd -m -G wheel username`
`vim /etc/sudoers`

### kde

```
pacman -S noto-fonts noto-fonts-cjk noto-fonts-emoji   # 安装字体
pacman -S plasma
systemctl enable sddm

cd ~/.local/share/fcitx5/rime   # 配置输入法
git clone https://github.com/iDvel/rime-ice.git
cp -r ./rime-ice/* .

sudo usermod -a -G uucp $USER   # 允许用户使用串口
