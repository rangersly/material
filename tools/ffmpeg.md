# ffmpeg 强大的多媒体框架

## 基本命令结构

- `ffmpeg [全局选项] -i 输入文件 [输入选项] [输入文件选项] 输出文件`
  - 全局选项  影响整个命令
  - 输入选项  作用于输入文件
  - 输出选项  作用于输出文件

## 常用操作

1. 查看媒体信息
  - `ffmpeg -i input.mp4`
  - `ffmpeg -i input.mp4 -f null -` 只显示信息不转码,避免错误
2. 格式转换
  - `ffmpeg -i input.mp4 output.avi`  转换容器
  - `ffmpeg -i input.mp4 -c:v libx264 -c:a aac output.mp4`  指定编码器
    - `-c:v`  指定视频编码器(`libx264 - H.264`,`libx265 - H.265)
    - `-c:a`  指定音频编码器(`acc`,`mp3`,`copy` 不编码直接复制)
3. 提取音频
  - `ffmpeg -i input.mp4 -vn -c:a mp3 output.mp3`
    - `-vn`  禁用视频流
4. 更改分辨率
  - `ffmpeg -i input.mp4 -vf "scale=1280:720" -c:a copy output.mp4`
    - `-vf`  用于视频滤镜,保持长宽比可指定一边自动计算 ` scale=1280:-1`
5. 裁剪视频
  - `ffmpeg -i input.mp4 -ss 00:00:10 -t 5 -c copy output.mp4`  
    - `-ss HH:MM:SS`  起始时间(放在`-i`参数前会快速跳转,但不精确,放在后面会先解码,慢)
    - `-t`  持续时间
    - `-c copy` 直接复制流
6. 调整比特率
  - `ffmpeg -i input.mp4 -b:v 1M -b:a 128k output.mp4`

## 视频编码器

- `libsvtav1`  AV1 crf=32~34 综合推荐
- `libx265` H.265 目前最佳首选,crf=23~26
- `libx264` H.264 兼容老设备,crf=23

## 预设 preset

按需求选择即可,faster,medium,slower等等
