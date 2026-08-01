@echo off
chcp 65001 >nul
setlocal

echo 用于塔科夫视频压制提亮的脚本

:: ================== 用户可调参数 ==================
echo 请输入开始时间（秒，例如0）:
set /p start_time=
if "%start_time%"=="" (
    echo 开始时间不能为空，按任意键退出...
    pause >nul
    exit /b
)

echo 请输入结束时间（秒，例如300）:
set /p end_time=
if "%end_time%"=="" (
    echo 结束时间不能为空，按任意键退出...
    pause >nul
    exit /b
)

set "brightness=0.3"         :: 曝光 
set "contrast=1.55"          :: 对比度 
set "saturation=1.6"        :: 饱和度 
set "cq=33"                  :: 硬件编码质量（0-51，类似CRF，越小越好）
set "preset=p4"              :: NVENC预设：p1最快 p7最高质量（默认p4）
:: =================================================

if "%~1"=="" (
    echo 请将视频文件拖放到本脚本上运行。
    pause
    exit /b
)

set "input=%~1"
set "output=%~dpn1_out%~x1"

echo 正在处理: "%input%"
echo 将从 %start_time% 秒处开始剪切，并使用 NVENC HEVC 硬件编码...
echo 输出文件: "%output%"
echo.

:: 硬件解码 + NVENC 硬件编码
ffmpeg -hide_banner ^
    -ss %start_time% -to %end_time% -i "%input%" ^
    -vf "eq=brightness=%brightness%:contrast=%contrast%:saturation=%saturation%" ^
    -c:v hevc_nvenc -preset %preset% -cq %cq% ^
    -acodec copy "%output%" -y

if %errorlevel% equ 0 (
    echo.
    echo ✅ 处理成功！输出文件："%output%"
) else (
    echo.
    echo ❌ 处理失败，请检查错误信息。
)
pause
