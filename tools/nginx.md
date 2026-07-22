# nginx

开源、高性能的 HTTP 和反向代理服务器

## config

- `/etc/nginx/nginx.conf` 是最基础的配置文件

使用`nginx -t`命令来检查配置文件

`nginx -s reload` 重新加载配置文件

### 配置文件基础结构

```
# 全局块（影响整体，如用户、worker数）
worker_processes  1;

# 事件块（控制连接处理方式）
events {
    worker_connections  1024;
}

# HTTP块（所有HTTP相关配置）
http {
    server {
        listen       80;          # 监听端口
        server_name  localhost;   # 域名/IP

        location / {
            root   html;          # 网站根目录
            index  index.html;    # 默认首页
        }
    }
}
```
