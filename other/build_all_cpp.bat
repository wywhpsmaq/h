@echo off
setlocal enabledelayedexpansion

REM 遍历所有cpp文件
for /r "%~dp0c++code" %%f in (*.cpp) do (
    set "src=%%f"
    set "dir=%%~dpf"
    set "name=%%~nf"
    set "outdir=%%~dpfoutput"
    if not exist "!outdir!" (
        mkdir "!outdir!"
    )
    echo 编译: "!src!"
    g++ -g "!src!" -o "!outdir!\!name!.exe"
    if errorlevel 1 (
        echo 编译失败，跳过: "!src!"
    ) else (
        echo 编译成功: "!src!"
    )
)

echo 全部编译完成
pause
