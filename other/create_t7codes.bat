@echo off
setlocal

:: 创建主目录
set BASE=D:\code\h\c++code\T7codes

:: 创建[12]和[13]文件夹及其子文件夹
for %%A in (14 15) do (
    mkdir "%BASE%\[%%A]" 2>nul
    for /L %%B in (1,1,5) do (
        mkdir "%BASE%\[%%A]\[%%A]-%%B" 2>nul
    )
)
:: [12]-1: BC101.cpp ~ BC112.cpp
for /L %%N in (101,1,112) do (
    type nul > "%BASE%\[14]\[14]-1\BE%%N.cpp"
)
:: [12]-2: BC201.cpp ~ BC212.cpp
for /L %%N in (201,1,212) do (
    type nul > "%BASE%\[14]\[14]-2\BE%%N.cpp"
)
:: [12]-3: BC301.cpp ~ BC312.cpp
for /L %%N in (301,1,312) do (
    type nul > "%BASE%\[14]\[14]-3\BE%%N.cpp"
)
:: [12]-4: BC401.cpp ~ BC412.cpp
for /L %%N in (401,1,412) do (
    type nul > "%BASE%\[14]\[14]-4\BE%%N.cpp"
)
:: [13]-1: BD101.cpp ~ BD112.cpp
for /L %%N in (101,1,112) do (
    type nul > "%BASE%\[15]\[15]-1\BF%%N.cpp"
)
:: [13]-2: BD201.cpp ~ BD212.cpp
for /L %%N in (201,1,212) do (
    type nul > "%BASE%\[15]\[15]-2\BF%%N.cpp"
)
:: [13]-3: BD301.cpp ~ BD312.cpp
for /L %%N in (301,1,312) do (
    type nul > "%BASE%\[15]\[15]-3\BF%%N.cpp"
)
echo 所有文件夹和文件已创建完成。
pause
