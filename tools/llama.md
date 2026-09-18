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
- `ornith1.5-9B.gguf` — 9B 模型(推荐12g显存部署)

## 启动服务

服务通过 `llama-server` 启动，端口 22233。
实际命令对应 `~/myai` 下的 `ser-*.sh` 脚本：

**ornith1.5-9B.gguf**（小模型，全量放 GPU）：

```bash
./llama-ser -m ornith1.5-9B.gguf \
    -ngl 34 \
    -ctk q8_0 -ctv q8_0 \
    --flash-attn on \
    -c 80000 \
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

## 基准测试（llama-bench）

单文件 CLI，测模型推理吞吐与延迟，输出 `avg t/s ± stdev`。
用法：`llama-bench [OPTIONS] MODEL [N_CTX]`。多值可用逗号或重复指定，范围用 `first-last`。

### 基础用法

默认测 512 个 prompt（`pp`）+ 128 个生成 token（`tg`），无需显式指定 `-p/-n`：

```bash
llama-bench ornith1.5-9B.gguf
```

自定义 prompt/生成长度与测试类型：

```bash
llama-bench -m ornith1.5-9B.gguf -p 512 -n 128 -pg pp,tg
```

`-pg <pp,tg>` 控制测试类型：`pp`（提示词处理）、`tg`（生成）、`pp+tg`（综合）。
另支持 `--embeddings` 测嵌入向量。

### 常用参数

| 参数 | 作用 | 默认 | 说明 |
|---|---|---|---|
| `-m/--model` | 指定 GGUF 模型 | — | 必填 |
| `-t/--threads` | CPU 线程数 | 自动 | 影响 prompt 处理速度 |
| `-d/--n-depth` | 上下文长度 | 0 | 测试不同上下文下的吞吐 |
| `-b/--batch-size` | batch 大小 | 2048 | 越大吞吐越高 |
| `-ngl/--n-gpu-layers` | GPU 层数 | -1(自动) | 越大越快越占显存 |
| `-ctk/-ctv` | KV 缓存量化 | f16 | q4_0/q8_0 权衡速度精度 |
| `-fa/--flash-attn` | Flash Attention | auto | on/off 提速 |
| `-sm/--split-mode` | 张量切分策略 | layer | 多卡负载均衡 |

### 参数调优（示例）

- **显存/CPU 平衡**：固定上下文，扫 `ngl` 找最优（范围 `30-50`）：
  ```bash
  llama-bench -m ornith1.5-9B.gguf -t 8 -fa on -d 32000 -ngl 30-50
  ```
- **上下文长度权衡**：观察 t/s 随上下文增长：
  ```bash
  for d in 1000 32000 64000 80000 128000; do
    llama-bench -m ornith1.5-9B.gguf -fa on -d $d -ngl 34
  done
  ```
- **量化取舍**：
  ```bash
  llama-bench -m ornith1.5-9B.gguf -ngl 34 -fa on -ctk q4_0 -ctv q4_0
  llama-bench -m ornith1.5-9B.gguf -ngl 34 -fa on -ctk q8_0 -ctv q8_0
  ```
- **flash-attn**：`-fa on`（开）vs `-fa off`（关）对比。

### 输出格式

默认 Markdown 表格；`-o {csv,json,jsonl,md,sql}` 改格式。
指标 `avg t/s ± stdev`：`pp` 提示处理、`tg` 生成、`pp+tg` 综合。
