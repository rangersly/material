# archlinux安装

## 目录
- [基础安装](#基础安装)
  - [修改控制台字体](#修改控制台字体)
  - [验证引导](#验证引导)
  - [验证网络和更改系统时间](#验证网络和更改系统时间)
  - [硬盘分区](#disk)
  - [安装基础软件包](#安装基础软件包)
  - [生成fstab](#fstab)
  - [chroot配置](#chroot)
- [新系统](#新系统)
  - [换源](#mirrors)
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

### disk 

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
+ grub efibootmgr
+ vim base-devel networkmanager

---

+ yay
  1. /etc/pacman.conf
  ```
  [archlinuxcn]
  Server = https://mirrors.tuna.tsinghua.edu.cn/archlinuxcn/$arch
  ```
  2. archlinuxcn
  ```bash
  sudo pacman-key --lsign-key "farseerfc@archlinux.org"
  sudo pacman -Sy archlinuxcn-keyring
  sudo pacman -Syyu  # 更新源
  sudo pacman -S yay  # 直接安装 Yay
  ```

### fstab

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

sudo systemctl enable NetworkManager

passwd 

# 安装引导
grub-install --target=i386-pc /dev/sdX   # BIOS 
grub-install --target=x86_64-efi --efi-directory=/boot --bootloader-id=GRUB  # UEFI
grub-mkconfig -o /boot/grub/grub.cfg

umount -R /mnt

reboot
```

## 新系统

### mirrors
- `/etc/pacman.d/mirrorlist`
```
Server = https://mirrors.tuna.tsinghua.edu.cn/archlinux/$repo/os/$arch
Server = http://mirrors.aliyun.com/archlinux/$repo/os/$arch
Server = https://mirrors.ustc.edu.cn/archlinux/$repo/os/$arch
```

### 普通用户

`useradd -m -G wheel username`
`vim /etc/sudoers`


### 配置中文双拼输入法

```bash
# 配置好后记得设置全局脚本
#!/usr/bin/env sh
export GTK_IM_MODULE=fcitx5
export QT_IM_MODULE=fcitx5
export XMODIFIERS=@im=fcitx5
```
