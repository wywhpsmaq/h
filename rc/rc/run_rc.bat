@echo off
cd /d %~dp0
where python >nul 2>nul
if %errorlevel%==0 (
    python main.py
) else (
    echo 未检测到Python，正在下载最新版安装包...
    powershell -Command "Invoke-WebRequest -Uri https://www.python.org/ftp/python/3.11.8/python-3.11.8-amd64.exe -OutFile python-installer.exe"
    if exist python-installer.exe (
        echo 下载完成，正在启动安装程序...
        start python-installer.exe
        echo 请完成Python安装后，重新运行本程序。
        pause
    ) else (
        echo 下载失败，请手动访问 https://www.python.org/downloads/ 下载并安装。
        pause
    )
)
