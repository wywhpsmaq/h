@echo off
set A= 0
:终止处
timeout /t 1 > NUL
set /a A= %A%+ 1
echo 已用秒数：%A% s
goto :终止处