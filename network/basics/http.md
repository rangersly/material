# HTTP 与 HTTPS

## 一句话

HTTP 是请求-响应协议，HTTPS 是 HTTP 加 TLS 加密。

## 请求

```http
GET /index.html HTTP/1.1
Host: example.com
User-Agent: curl/8.0
```

常用方法：

- `GET` 查询
- `POST` 提交
- `PUT` 更新
- `DELETE` 删除

常见请求头：`Host`、`Content-Type`、`Content-Length`、`Authorization`、`Cookie`、`User-Agent`。

## 响应

```http
HTTP/1.1 200 OK
Content-Type: text/html
```

状态码分类：

- `2xx` 成功
- `3xx` 重定向
- `4xx` 客户端错误
- `5xx` 服务端错误

常见状态码：`200`、`301`、`302`、`304`、`400`、`401`、`403`、`404`、`500`、`502`、`503`。

## HTTPS

- HTTPS = HTTP + TLS
- 证书由 CA 签发，客户端校验证书和域名
- TLS 握手协商密钥，之后用对称加密传输数据
- `curl -v -I https://example.com` 可以观察握手和响应头
- `curl -k` 忽略证书校验，只用于测试

## 代理

- **正向代理**：客户端配置，替客户端访问外网
- **反向代理**：部署在服务端，替后端接收请求
- 反向代理常用于 HTTPS 终止、负载均衡、静态文件和隐藏后端

## 常用命令

```bash
curl -I https://example.com
curl -v https://example.com
curl -i https://example.com
```

`-I` 只看响应头，`-i` 带头输出，`-v` 显示完整通信过程。

## 相关

- [Nginx](../services/nginx.md)
- [Linux 网络命令](../linux/commands.md)
