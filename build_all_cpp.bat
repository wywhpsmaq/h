@echo off
setlocal enabledelayedexpansion

REM ��������cpp�ļ�
for /r "%~dp0c++code" %%f in (*.cpp) do (
    set "src=%%f"
    set "dir=%%~dpf"
    set "name=%%~nf"
    set "outdir=%%~dpfoutput"
    if not exist "!outdir!" (
        mkdir "!outdir!"
    )
    echo ����: "!src!"
    g++ -g "!src!" -o "!outdir!\!name!.exe"
    if errorlevel 1 (
        echo ����ʧ�ܣ�����: "!src!"
    ) else (
        echo ����ɹ�: "!src!"
    )
)

echo ȫ���������
pause
