@echo off
setlocal

:: 创建主目录
set BASE=f:\h\c++code\T7codes

:: 创建[12]和[13]文件夹及其子文件夹
for %%A in (12 13) do (
    mkdir "%BASE%\[%%A]" 2>nul
    for /L %%B in (1,1,5) do (
        mkdir "%BASE%\[%%A]\[%%A]-%%B" 2>nul
    )
)
:: [12]-1: BC101.cpp ~ BC112.cpp
for /L %%N in (101,1,112) do (
    type nul > "%BASE%\[12]\[12]-1\BC%%N.cpp"
)
:: [12]-2: BC201.cpp ~ BC212.cpp
for /L %%N in (201,1,212) do (
    type nul > "%BASE%\[12]\[12]-2\BC%%N.cpp"
)
:: [12]-3: BC301.cpp ~ BC312.cpp
for /L %%N in (301,1,312) do (
    type nul > "%BASE%\[12]\[12]-3\BC%%N.cpp"
)
:: [12]-4: BC401.cpp ~ BC412.cpp
for /L %%N in (401,1,412) do (
    type nul > "%BASE%\[12]\[12]-4\BC%%N.cpp"
)
:: [12]-5: BC501.cpp ~ BC512.cpp
for /L %%N in (501,1,512) do (
    type nul > "%BASE%\[12]\[12]-5\BC%%N.cpp"
)
:: [13]-1: BD101.cpp ~ BD112.cpp
for /L %%N in (101,1,112) do (
    type nul > "%BASE%\[13]\[13]-1\BD%%N.cpp"
)
:: [13]-2: BD201.cpp ~ BD212.cpp
for /L %%N in (201,1,212) do (
    type nul > "%BASE%\[13]\[13]-2\BD%%N.cpp"
)
:: [13]-3: BD301.cpp ~ BD312.cpp
for /L %%N in (301,1,312) do (
    type nul > "%BASE%\[13]\[13]-3\BD%%N.cpp"
)
:: [13]-4: BD401.cpp ~ BD412.cpp
for /L %%N in (401,1,412) do (
    type nul > "%BASE%\[13]\[13]-4\BD%%N.cpp"
)
:: [13]-5: BD501.cpp ~ BD512.cpp
for /L %%N in (501,1,512) do (
    type nul > "%BASE%\[13]\[13]-5\BD%%N.cpp"
)
echo 所有文件夹和文件已创建完成。
pause
