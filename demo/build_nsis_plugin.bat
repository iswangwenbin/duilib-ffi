@echo off
REM ==============================================================================
REM NSIS DuiLib插件编译脚本
REM 编译nsis_installer.cpp为NSIS插件DLL
REM ==============================================================================

echo 正在编译NSIS DuiLib插件...

REM 设置编译器路径（请根据实际情况修改）
set MSVC_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64"
set INCLUDE_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133\include"
set LIB_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133\lib\x64"

REM 设置项目路径
set PROJECT_DIR=%~dp0
set DUILIB_C_DIR=%PROJECT_DIR%..\duilib_c
set OUTPUT_DIR=%PROJECT_DIR%

echo 项目目录: %PROJECT_DIR%
echo DuiLib C目录: %DUILIB_C_DIR%
echo 输出目录: %OUTPUT_DIR%

REM 检查源文件是否存在
if not exist "%PROJECT_DIR%nsis_installer.cpp" (
    echo 错误: 找不到源文件 nsis_installer.cpp
    pause
    exit /b 1
)

REM 检查DuiLib C头文件是否存在
if not exist "%DUILIB_C_DIR%\duilib_c.h" (
    echo 错误: 找不到DuiLib C头文件
    pause
    exit /b 1
)

REM 编译插件DLL
echo 正在编译插件...
%MSVC_PATH%\cl.exe /nologo ^
    /I"%DUILIB_C_DIR%" ^
    /I"%INCLUDE_PATH%" ^
    /D"WIN32" /D"_WINDOWS" /D"_USRDLL" /D"NSIS_PLUGIN" ^
    /EHsc /MD /O2 ^
    "%PROJECT_DIR%nsis_installer.cpp" ^
    /link /DLL /OUT:"%OUTPUT_DIR%nsis_installer.dll" ^
    /LIBPATH:"%LIB_PATH%" ^
    /LIBPATH:"%DUILIB_C_DIR%" ^
    user32.lib gdi32.lib ole32.lib comctl32.lib shell32.lib ^
    duilib_c.lib

if %ERRORLEVEL% neq 0 (
    echo 编译失败!
    pause
    exit /b 1
)

echo 插件编译成功: nsis_installer.dll

REM 清理临时文件
if exist "%OUTPUT_DIR%nsis_installer.obj" del "%OUTPUT_DIR%nsis_installer.obj"
if exist "%OUTPUT_DIR%nsis_installer.exp" del "%OUTPUT_DIR%nsis_installer.exp"
if exist "%OUTPUT_DIR%nsis_installer.lib" del "%OUTPUT_DIR%nsis_installer.lib"

echo.
echo ==============================================================================
echo 编译完成!
echo 生成文件: %OUTPUT_DIR%nsis_installer.dll
echo.
echo 接下来的步骤:
echo 1. 确保有要安装的应用程序文件 (MyApp.exe, config.ini等)
echo 2. 运行 makensis installer_setup.nsi 生成最终安装程序
echo 3. 或者使用 build_installer.bat 一键编译整个安装程序
echo ==============================================================================

pause