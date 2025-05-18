# docker
是一个开源的应用容器引擎

+ 镜像（Image）：只读模板，包含运行应用所需的所有内容，如代码、运行时、库等
+ 容器（Container）：镜像的运行实例，隔离运行应用的环境
+ 仓库（Repository）：存储和分发镜像的地方，Docker Hub 是最常用的公共仓库

## index 
- [核心组件](#)
- [docker](#docker)
  - [install](#install)
  - [基本命令](#docker-command)
  - [数据管理](#)
  - [高级用法](#)
- [docker-compose](#docker-compose)
  - [COMMAND](#docker-compose-command)
  - [YAML](#docker-compose-yml)
- [daemon.json](#)

---

## **docker**

---

### **install**

+ 更新系统并安装依赖包
+ 添加 Docker 官方 GPG 密钥并设置存储库
+ 安装 Docker 引擎并启动服务
+ 设置 Docker 开机自启

```bash
sudo apt-get update
curl -fsSL https://mirrors.aliyun.com/docker-ce/linux/ubuntu/gpg | sudo apt-key add -
echo "deb [arch=amd64] https://mirrors.aliyun.com/docker-ce/linux/ubuntu $(lsb_release -cs) stable" | sudo tee -a /etc/apt/sources.list.d/docker.list
sudo apt-get update
sudo apt-get install docker-ce docker-ce-cli containerd.io
# 验证安装
sudo docker --version
```

__配置/etc/docker/daemon.json__
```
{
	"registry-mirrors":
	[
        "https://dockerproxy.com",
        "https://docker.mirrors.ustc.edu.cn",
        "https://docker.nju.edu.cn"
    ]  
}
```

---

### **docker-command**
1. 镜像操作
  + `docker pull <镜像名>`  : 从仓库拉取镜像
  + `docker image ls`  : 列出本地镜像
  + `docker rmi <镜像ID>`  : 删除镜像
  + `docker search <镜像名>`  搜索镜像
  + `docker build -t <image_name> .` 使用 Dockerfile 构建镜像

2. 容器操作
  + `docker run -d <镜像名>`  : 创建并后台运行容器
    + `-v` : 指定数据卷
    + `-p local_port:port` : 端口映射
  + `docker ps`  : 列出所有运行中容器
    + `-a` : 包括停止的容器
  + `docker stop [ID / NAME]`  : 停止某容器
  + `docker start [ID / NAME]`	: 启动已经停止的容器
  + `docker rm [ID / NAME]`  : 删除容器
  + `docker commit <容器ID或名称> <新镜像名称>:<标签>` 将运行中的容器保存为镜像
  + `docker save -o my-new-image.tar my-new-image:latest` 导出为tar文件
  + `docker load -i my-new-image.tar`  导入镜像到目标环境
  + `docker logs <容器ID>`  : 查看容器日志
  + `docker exec -it [ID / NAME] /bin/bash`  : 进入容器

3. 其他
  + `c-P c-Q` :  退出容器
  + `sudo systemctl daemon-reload && sudo systemctl restart docker`  重启

4. example-command
+ `docker run -it ubuntu /bin/bash` 运行 Ubuntu 容器并进入交互式 shell
+ `docker run -it --name mc-ser ubuntu -v /opt/mc:/opt/mc -p 25565:25565 /bin/bash`

### 数据管理
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
+ 迁移Volume数据
```bash
# 1. 运行临时容器挂载 Volume，并将数据打包到容器内
docker run --rm -v your_volume:/data busybox tar cvf /backup/data.tar /data

# 2. 从容器中复制备份文件到宿主机
docker cp <container_id>:/backup/data.tar ./data.tar

# 3. 恢复时反向操作：将 data.tar 复制回新容器，并解压到 Volume
```

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

### 高级用法
1. Dockerfile
Dockerfile 是用于构建镜像的脚本文件，包含一系列指令，用于定义镜像的构建过程
```
# 使用基础镜像
FROM ubuntu:latest

# 维护者信息
MAINTAINER Your Name <your.email@example.com>

# 更新包索引并安装软件
RUN apt-get update && apt-get install -y \
    software-properties-common \
    python3

# 设置工作目录
WORKDIR /app

# 复制当前目录下的文件到容器中的 /app 目录
COPY . /app

# 暴露端口
EXPOSE 80

# 设置环境变量
ENV NAME World

# 运行命令
CMD ["python3", "app.py"]
```

2. Docker 网络
- `docker network create <network_name>` 创建网络
- `docker network ls` 查看网络
- `docker network connect <network_name> <container_id>` 连接容器到网络

3. Docker 安全
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

- `docker-compose build`            构建镜像
- `docker-compose up -d`            启动在后台运行
- `docker-compose up -d --build`    重建并运行
- `docker-compose down`             停止并删除容器
- `docker-compose logs -f <server>` 查看服务日志
- `docker-compose ps`               查看运行状态
- `docker-compose exec`             进入容器执行命令
- `docker-compose pull`             拉取最新镜像 
- `docker-compose config`           检查配置语法是否正确
- `docker-compose stop`             停止容器
- `docker-compose start`            启动停止的容器
- `docker-compose restart`          stop + start 
- `docker-compose pause`            挂起,不释放资源


---

### docker-compose-yml

```yaml
version: '3.8'              # 指定 Compose 版本（与 Docker 版本兼容性相关）

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

## daemon.json
```
{
  "registry-mirrors": [
    "https://docker.1ms.run",
    "https://docker.xuanyuan.me",
    "https://docker.zhai.cm",
    "https://a.ussh.net",
    "https://hub.littlediary.cn",
    "https://hub.rat.dev",
    "https://atomhub.openatom.cn",
    "https://docker.m.daocloud.io",
    "https://dytt.online",
    "https://func.ink",
    "https://lispy.org",
    "https://docker.xiaogenban1993.com",
    "https://docker.mybacc.com",
    "https://docker.yomansunter.com",
    "https://dockerhub.websoft9.com",
    "https://docker-0.unsee.tech",
    "https://docker-cf.registry.cyou",
    "https://docker.1panel.live",
    "https://docker.imgdb.de",
    "https://docker.hlmirror.com",
    "https://dockerpull.org",
    "https://dockerhub.icu",
    "https://proxy.1panel.live",
    "https://docker.1panel.top",
    "https://docker.ketches.cn"
  ]
}
```
