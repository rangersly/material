# docker
是一个开源的应用容器引擎

+ 镜像（Image）：只读模板，包含运行应用所需的所有内容，如代码、运行时、库等
+ 容器（Container）：镜像的运行实例，隔离运行应用的环境
+ 仓库（Repository）：存储和分发镜像的地方，Docker Hub 是最常用的公共仓库

## index 

- [install](#install)
- [docker](#docker)
- [数据管理](#数据管理)
- [Dockerfile](#dockerfile)
- [杂项](#杂项)
- [docker compose](#docker-compose)
  - [COMMAND](#docker-compose-command)
  - [YAML](#docker-compose-yml)
- [Docker 网络](../network/services/docker-network.md)

---

## **install**

```bash
# 更新软件包和安装依赖
sudo apt-get update
sudo apt-get install -y ca-certificates curl gnupg

# 创建密钥环并导入GPG密钥
sudo install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://mirrors.aliyun.com/docker-ce/linux/ubuntu/gpg | sudo gpg --dearmor --yes -o /etc/apt/keyrings/docker.gpg
sudo chmod a+r /etc/apt/keyrings/docker.gpg

# 添加软件源
echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://mirrors.aliyun.com/docker-ce/linux/ubuntu $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

# 安装docker引擎
sudo apt-get update
sudo apt-get install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
sudo systemctl enable --now docker
docker --version
```

```bash
# Arch Linux 安装 docker
sudo pacman -S --needed docker docker-compose
sudo systemctl enable --now docker
docker --version
```

```bash
# 将特定用户免root（执行后需重新登录才生效）
sudo usermod -aG docker $USER
```

```bash
# 配置镜像加速器并生效（一行命令）
sudo mkdir -p /etc/docker && echo '{"registry-mirrors":["https://docker.1ms.run","https://docker.m.daocloud.io","https://docker.1panel.live"]}' | sudo tee /etc/docker/daemon.json > /dev/null && sudo systemctl daemon-reload && sudo systemctl restart docker

# 验证镜像源是否生效
sudo docker info | grep -A3 "Registry Mirrors"
```

```bash
# 使用代理加速镜像拉取（dockerd + containerd 都要配）
# 新版 Docker 用 containerd 拉取镜像，只配 docker.service 会拉取超时
PROXY="http://你的代理地址:端口"

sudo mkdir -p /etc/systemd/system/docker.service.d /etc/systemd/system/containerd.service.d

sudo tee /etc/systemd/system/docker.service.d/http-proxy.conf >/dev/null <<EOF
[Service]
Environment="HTTP_PROXY=${PROXY}"
Environment="HTTPS_PROXY=${PROXY}"
Environment="NO_PROXY=localhost,127.0.0.1"
EOF

sudo tee /etc/systemd/system/containerd.service.d/http-proxy.conf >/dev/null <<EOF
[Service]
Environment="HTTP_PROXY=${PROXY}"
Environment="HTTPS_PROXY=${PROXY}"
Environment="NO_PROXY=localhost,127.0.0.1"
EOF

sudo systemctl daemon-reload
sudo systemctl restart containerd docker

# 验证是否生效（两个都要有输出）
sudo systemctl show --property=Environment containerd
sudo systemctl show --property=Environment docker
```

---

## **docker**

定期使用`docker system prune`清理垃圾,保持环境整洁

**镜像操作**

+ `docker pull <镜像名>`  : 从仓库拉取镜像
+ `docker image ls`  : 列出本地镜像
+ `docker rmi <镜像ID>`  : 删除镜像
+ `docker search <镜像名>`  搜索镜像
+ `docker build -t <image_name> .` 使用 Dockerfile 构建镜像

**容器操作**

+ `docker run -d <镜像名>`  : 创建并后台运行容器
  - `-v` : 指定数据卷
  - `-p local_port:port` : 端口映射
  - `--rm` 在容器运行结束后删除容器
  - `-it` 进入交互式shell
+ `docker ps`  : 列出运行中容器(-a 列出所有)
+ `docker stop [ID / NAME]`  : 停止某容器
+ `docker start [ID / NAME]`	: 启动已经停止的容器
+ `docker rm [ID / NAME]`  : 删除容器
+ `docker commit <容器ID或名称> <新镜像名称>:<标签>` 将运行中的容器保存为镜像
+ `docker save -o my-new-image.tar my-new-image:latest` 导出为tar文件
+ `docker load -i my-new-image.tar`  导入镜像到目标环境
+ `docker logs <容器ID>`  : 查看容器日志
+ `docker exec -it [ID / NAME] /bin/bash`  : 进入容器

**其他**

+ `c-P c-Q` 退出容器交互式shell
+ `sudo systemctl daemon-reload && sudo systemctl restart docker`  重启

**命令示例**

+ `docker run -it ubuntu /bin/bash` 运行 Ubuntu 容器并进入交互式 shell
+ `docker run -it --name mc-ser -v /opt/mc:/opt/mc -p 25565:25565 ubuntu /bin/bash` 创建名为 mc-ser 的容器

## 数据管理

Docker 提供了多种数据管理方式，包括 数据卷（Volumes）、绑定挂载（Bind Mounts） 和 临时文件系统（tmpfs）

1. Docker 数据卷（Volumes）
是 Docker 推荐的数据持久化方式。数据卷存储在 Docker 管理的文件系统中（通常是 /var/lib/docker/volumes/），与容器的生命周期分离，即使容器被删除，数据卷仍然存在

+ 高性能：数据卷通常比绑定挂载性能更好。
+ 易于备份和迁移：数据卷可以通过 Docker 命令轻松备份和恢复。

+ `docker volume create my_volume`  创建数据卷
+ `docker volume ls`  查看数据卷
+ `docker volume inspect my_volume`  查看数据卷详细信息
+ `docker run -d --name my_container -v my_volume:/path/in/container <image_name>`  挂载数据卷到容器
+ `docker volume rm my_volume`  删除数据卷
+ `docker volume prune`  清理未使用的数据卷

**迁移Volume数据**

思路：起一个临时容器，把数据卷挂到 `/data`，同时把宿主机当前目录挂到 `/backup`，用 `tar` 打包后压缩包直接落在宿主机上，无需 `docker cp`。

```bash
# 备份：数据卷 -> 宿主机当前目录的 data.tar
docker run --rm -v your_volume:/data -v "$(pwd)":/backup busybox \
  tar cvf /backup/data.tar -C /data .
```

```bash
# 恢复：宿主机 data.tar -> 数据卷
docker run --rm -v your_volume:/data -v "$(pwd)":/backup busybox \
  tar xvf /backup/data.tar -C /data
```

`-C /data .` 表示切到 `/data` 再打包当前目录内容，解压回去时不会带多余的目录层级。

2. 绑定挂载
将主机上的文件或目录直接挂载到容器中

+ 灵活性：可以直接挂载主机上的任意文件或目录。
+ 实时同步：主机和容器之间的文件修改会实时同步。
  - `docker run -d --name my_container -v /host/path:/container/path <image_name>`  挂载主机目录到容器

3. 临时文件系统（tmpfs）
tmpfs 是一种基于内存的文件系统，适用于需要临时存储数据的场景。数据仅存储在内存中，容器停止后数据会丢失

+ 高性能：数据存储在内存中，读写速度快。
+ 临时性：数据不会持久化，容器停止后数据丢失。

`docker run -d --name my_container --tmpfs /container/path <image_name>`  挂载 tmpfs 到容器

4. 数据卷的高级用法

+ 多个容器可以共享同一个数据卷，实现数据共享

+ 可以将数据卷或绑定挂载设置为只读，防止容器修改数据
  - `docker run -d --name my_container -v my_volume:/data:ro <image_name>`

---

## dockerfile

Dockerfile 是用于构建镜像的脚本文件，包含一系列指令，用于定义镜像的构建过程

```Dockerfile
# 指定基础镜像
FROM node:18-alpine

# 设置工作目录
WORKDIR /app

# 复制依赖文件（利用缓存）
COPY package*.json ./

# 安装依赖
RUN npm install

# 复制项目源码
COPY . .

# 声明容器端口
EXPOSE 3000

# 设置容器启动命令
CMD ["node", "app.js"]
```

## 杂项

**Docker 安全**
- 使用非 root 用户运行容器
```dockerfile
FROM ubuntu
RUN useradd -m myuser
USER myuser
```

---

## **docker-compose**

---

### docker-compose-command

- `docker compose build`            构建镜像
- `docker compose up -d`            启动在后台运行
- `docker compose up -d --build`    重建并运行
- `docker compose down`             停止并删除容器
- `docker compose logs -f <server>` 查看服务日志
- `docker compose ps`               查看运行状态
- `docker compose exec`             进入容器执行命令
- `docker compose pull`             拉取最新镜像 
- `docker compose config`           检查配置语法是否正确
- `docker compose stop`             停止容器
- `docker compose start`            启动停止的容器
- `docker compose restart`          stop + start 
- `docker compose pause`            挂起,不释放资源


---

### docker-compose-yml

```yaml
services:
  myapp:                    # 服务名称（容器间通过此名称通信）
    image: nginx:latest     # 使用镜像
    container_name: myapp   # 容器名
#   build: .                # 基于当前目录的 Dockerfile 构建镜像
    restart: always         # 重启策略
    ports:                  # 端口映射
      - "80:80"     
    volumes:
      - ./html:/usr/share/nginx/html  # 挂载宿主机目录
    depends_on:
      - db                  # 依赖的服务（仅控制启动顺序，不保证服务就绪）

  db:
    image: postgres:13
    environment:
      POSTGRES_PASSWORD: example
    volumes:
      - postgres_data:/var/lib/postgresql/data  # 使用命名卷

volumes:
  postgres_data:    # 声明命名卷（由 Docker 自动管理）

networks:           # 定义网络
  mynet:
    driver: bridge
```
