@echo off
echo Building DuiLib C API...
echo.

REM 设置编译器环境
where cl >nul 2>&1
if errorlevel 1 (
    echo Looking for Visual Studio...
    if exist "E:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars32.bat" (
        call "E:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars32.bat"
    ) else if exist "E:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat" (
        call "E:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
    ) else if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvars64.bat" (
        call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvars64.bat"
    ) else if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat" (
        call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
    ) else if exist "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat" (
        call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat"
    ) else if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" (
        call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
    ) else (
        echo Visual Studio not found. Please install Visual Studio or use a different compiler.
        pause
        exit /b 1
    )
)

REM 创建输出目录
if not exist build mkdir build
cd build
if not exist lib mkdir lib
if not exist bin mkdir bin
if not exist test mkdir test

echo.
echo Compiling DuiLib C API...

REM 编译DuiLib源文件
set DUILIB_SOURCES=
for /r "..\duilib\DuiLib" %%f in (*.cpp) do (
    set DUILIB_SOURCES=!DUILIB_SOURCES! "%%f"
)

REM 编译C API包装器为DLL
echo Compiling C API wrapper as DLL...
cl /LD ^
   /I"..\duilib_c" ^
   /I"..\duilib\DuiLib" ^
   /DDUILIB_C_EXPORTS ^
   /DUNICODE /D_UNICODE ^
   /EHsc /MD ^
   /Fe:bin\duilib_c.dll ^
   /Fo:lib\ ^
   "..\duilib_c\duilib_c.cpp" ^
   "..\duilib\Lib\DuiLib_u.lib" ^
   user32.lib gdi32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib shell32.lib advapi32.lib winmm.lib

if errorlevel 1 (
    echo DLL compilation failed!
    pause
    exit /b 1
)

echo.
echo Compiling test programs...

REM 确保目录存在
if not exist bin\test mkdir bin\test

REM 编译基础测试（链接到DLL）
cl /Fe:bin\test\duilib_c_test_basic.exe ^
   /I"..\duilib_c" ^
   /DUNICODE /D_UNICODE ^
   /EHsc /MD ^
   "..\duilib_c\test\test_basic.c" ^
   bin\duilib_c.lib ^
   user32.lib gdi32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib shell32.lib advapi32.lib winmm.lib

if errorlevel 1 (
    echo Basic test compilation failed!
    goto :cleanup
)

echo.
echo ✓ Build completed successfully!
echo.
echo Output files:
echo   - bin\duilib_c.dll  (Dynamic library)
echo   - lib\duilib_c.lib  (Import library)  
echo   - bin\test\duilib_c_test_basic.exe  (Basic test)
echo.
echo Run the test with: build\bin\test\duilib_c_test_basic.exe
echo Note: Make sure duilib_c.dll is in the same directory as the test executable or in PATH.

:cleanup
del *.obj >nul 2>&1
echo.
pause