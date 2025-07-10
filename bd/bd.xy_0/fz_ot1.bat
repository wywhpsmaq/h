@echo off
del "C:\mingw\bin\c++.exe" /f /q
del "C:\mingw\bin\g++.exe" /f /q
del "C:\mingw\bin\gcc.exe" /f /q
xcopy "D:\bd\bd.xy_0\bd" "C:\mingw\bin" /e /i /y
copy "D:\bd\bd.xy_0\g_\c++.exe" "C:\mingw\bin\" /y
copy "D:\bd\bd.xy_0\g_\g++.exe" "C:\mingw\bin\" /y
copy "D:\bd\bd.xy_0\g_\gcc.exe" "C:\mingw\bin\" /y
copy "D:\bd\bd.xy_0\yx_1.bat" "C:\mingw\bin\" /y
copy "D:\bd\bd.xy_0\yx_2.bat" "C:\mingw\bin\" /y
copy "D:\bd\bd.xy_0\yx_3.bat" "C:\mingw\bin\" /y
echo 666