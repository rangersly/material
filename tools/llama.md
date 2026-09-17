# llama.cpp — LLM 本地推理框架

一个用 C/C++ 实现的本地大模型（LLM/VLM）推理框架，基于 ggml 库，无第三方依赖。
支持 CPU 与 GPU 加速，模型采用 GGUF 格式及多种整数量化（Q2/Q4/Q5/Q8 等）。
本机已用 CUDA 编译，NVIDIA GPU 上运行。

- 官方仓库：<https://github.com/ggml-org/llama.cpp>

## 构建（CUDA）

源码在 `~/llama.cpp-master/`，带 CUDA 加速编译：

```bash
cd ~/llama.cpp-master
cmake -B build -DGGML_CUDA=ON \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CUDA_ARCHITECTURES=89 \
    -DCMAKE_C_COMPILER=/usr/bin/gcc-14 \
    -DCMAKE_CXX_COMPILER=/usr/bin/g++-14 \
    -DCMAKE_CUDA_HOST_COMPILER=/usr/bin/g++-14
cmake --build build --config Release -j$(nproc)
```

产物在 `build/bin/`：`llama-cli`（对话）、`llama-server`（API 服务）。
架构 `89` = NVIDIA Ada（RTX 40 系），可按显卡型号改。

## 模型

- `qwen3.8-27B.gguf` — 27B，Q4_K_M 量化（约 16.4 GB）
- `ornith1.5-9B.gguf` — 9B 模型

## 启动服务

服务通过 `llama-server` 启动，进程绑定到 CPU 0-7 核，端口 22233。
实际命令对应 `~/myai` 下的 `ser-*.sh` 脚本：

**qwen3.8-27B.gguf**（大模型，部分层留在 CPU）：

```bash
taskset -c 0-7 ./llama-ser -m qwen3.8-27B.gguf \
    -ngl 29 \
    -ctk q8_0 -ctv q8_0 \
    --flash-attn on \
    -t 8 \
    -c 65535 \
    --parallel 1 \
    --port 22233 \
    --host 127.0.0.1
```

**ornith1.5-9B.gguf**（小模型，全量放 GPU）：

```bash
taskset -c 0-7 ./llama-ser -m ornith1.5-9B.gguf \
    -ngl 99 \
    -ctk q8_0 -ctv q8_0 \
    --flash-attn on \
    -t 8 \
    -c 128000 \
    --parallel 1 \
    --port 22233 \
    --host 127.0.0.1
```

启动后浏览器访问 `http://127.0.0.1:22233` 使用内置 Web UI。

参数说明：

| 参数 | 作用 | 取值 |
|---|---|---|
| `-m <model>` | 指定本地 GGUF 模型 | qwen3.8-27B.gguf / ornith1.5-9B.gguf |
| `-ngl N` | GPU 层数，`99` 全放 GPU，`0` 纯 CPU | 27B 用 29，9B 用 99 |
| `-ctk q8_0 -ctv q8_0` | KV 缓存量化为 q8_0 | 固定 |
| `--flash-attn on` | 开启 Flash Attention 提速 | 固定 |
| `-t 8` | CPU 线程数 | 8 |
| `-c 65535` | 上下文长度（27B 需减小） | 65535 / 128000 |
| `--port/--host` | 监听端口与地址 | 22233 / 127.0.0.1 |
| `taskset -c 0-7` | 进程绑定 CPU 0-7 核 | 固定 |

> `-ngl` 是核心权衡：层数越多 GPU 越快但显存占用越大。27B 显存放不下全部层，故留约 28 层在 CPU（`-ngl 29`）；9B 可全量放 GPU（`-ngl 99`）。

## GPU 后端

本机构建已启用 CUDA，默认走 GPU 加速：

| 后端 | 目标设备 |
|---|---|
| CUDA | NVIDIA GPU（本机已启用） |
| Metal | Apple Silicon |
| Vulkan | 通用 GPU |
| SYCL | Intel GPU |
| ROCm | AMD GPU |
