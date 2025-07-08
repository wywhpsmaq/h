@echo off 

color 0a 

:start 

set num=0 

set "echos= " 

:num 

set /a a1=%random%%%3 

if "%a1%" == "1" set "a1= " 

if "%a1%" == "2" set "a1= " 

if "%a1%" == "0" set /a a1=%random%%%2 

set echos=%echos%%a1% 

set /a num=%num%+1 

if "%num%" == "75" echo %echos%&&goto :start 

goto :num

%0
