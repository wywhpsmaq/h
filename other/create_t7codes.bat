@echo off
setlocal

:: 创建主目录
set BASE=E:\h\c++code\T7codes

:: 创建[16]和[17]文件夹及其子文件夹
for %%A in (16 17) do (
    mkdir "%BASE%\[%%A]" 2>nul
    for /L %%B in (1,1,5) do (
        mkdir "%BASE%\[%%A]\[%%A]-%%B" 2>nul
    )
)
:: [12]-1: BG101.cpp ~ BG112.cpp
for /L %%N in (101,1,112) do (
    type nul > "%BASE%\[16]\[16]-1\BG%%N.cpp"
)
:: [12]-2: BG201.cpp ~ BG212.cpp
for /L %%N in (201,1,212) do (
    type nul > "%BASE%\[16]\[16]-2\BG%%N.cpp"
)
:: [12]-3: BG301.cpp ~ BG312.cpp
for /L %%N in (301,1,312) do (
    type nul > "%BASE%\[16]\[16]-3\BG%%N.cpp"
)
:: [12]-4: BG401.cpp ~ BG412.cpp
for /L %%N in (401,1,412) do (
    type nul > "%BASE%\[16]\[16]-4\BG%%N.cpp"
)
:: [13]-1: BH101.cpp ~ BH112.cpp
for /L %%N in (101,1,112) do (
    type nul > "%BASE%\[17]\[17]-1\BH%%N.cpp"
)
:: [13]-2: BH201.cpp ~ BH212.cpp
for /L %%N in (201,1,212) do (
    type nul > "%BASE%\[17]\[17]-2\BH%%N.cpp"
)
:: [13]-3: BH301.cpp ~ BH312.cpp
for /L %%N in (301,1,312) do (
    type nul > "%BASE%\[17]\[17]-3\BH%%N.cpp"
)
echo 所有文件夹和文件已创建完成。
pause
