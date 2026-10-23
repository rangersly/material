# Docker 网络

## 网络模式

|模式|说明|
|---|---|
|`bridge`|默认模式，容器通过 NAT 访问外网|
|`host`|共享宿主机网络栈|
|`none`|不配置网络|
|`overlay`|跨主机通信，通常用于 Swarm|
|`macvlan`|让容器获得局域网 MAC/IP|

单机日常使用默认 `bridge` 或自定义 `bridge` 即可。

## 常用命令

```bash
docker network ls
docker network create mynet
docker network inspect mynet
docker network connect mynet <container>
docker network disconnect mynet <container>
```

## 端口映射

```bash
docker run -d -p 8080:80 nginx
docker run -d -P nginx
```

`-p` 的格式是 `宿主机端口:容器端口`，`-P` 会随机映射 Dockerfile 中 `EXPOSE` 的端口。`EXPOSE` 只声明端口，不负责发布。

## Compose 网络

```yaml
services:
  web:
    image: nginx
    ports:
      - "8080:80"
    networks:
      - mynet

  db:
    image: postgres
    networks:
      - mynet

networks:
  mynet:
    driver: bridge
```

同一自定义网络内，容器可以通过服务名互相访问，例如 `db:5432`。

## 防火墙注意事项

Docker 会自行管理 iptables/nftables 规则，可能绕过 ufw。不要直接用 `"iptables": false` 关闭 Docker 的网络规则，否则端口映射和容器网络可能异常。优先只发布必要端口；ufw 与 Docker 冲突时可考虑 `ufw-docker`。

其他 Docker 用法见 [Docker](../../tools/docker.md)。
