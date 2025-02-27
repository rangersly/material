## 配置dhcp

vim /etc/network/interfaces
auto eth0
iface eth0 inet dhcp


## 手动配置
iface eth0 inet static
address 192.168.0.108
netmask 255.255.255.0
gateway 192.168.0.101
network 192.168.0.108

service network restart //cpwl

2.配置dns
vim /etc/resolv.conf
nameserver 114.114.114.114
nameserver 8.8.8.8
search localdomain

