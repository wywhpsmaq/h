@echo off
cd /d %~dp0
where python >nul 2>nul
if %errorlevel%==0 (
    python main.py
) else (
    echo δ��⵽Python�������������°氲װ��...
    powershell -Command "Invoke-WebRequest -Uri https://www.python.org/ftp/python/3.11.8/python-3.11.8-amd64.exe -OutFile python-installer.exe"
    if exist python-installer.exe (
        echo ������ɣ�����������װ����...
        start python-installer.exe
        echo �����Python��װ���������б�����
        pause
    ) else (
        echo ����ʧ�ܣ����ֶ����� https://www.python.org/downloads/ ���ز���װ��
        pause
    )
)
