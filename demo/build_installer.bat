@echo off
REM ==============================================================================
REM 完整安装程序编译脚本
REM 1. 编译NSIS插件
REM 2. 编译NSIS安装程序
REM ==============================================================================

echo 开始构建完整的安装程序...

REM 设置路径
set PROJECT_DIR=%~dp0
set NSIS_PATH="C:\Program Files (x86)\NSIS"

echo 项目目录: %PROJECT_DIR%

REM 第一步：编译NSIS插件
echo.
echo ==============================================================================
echo 第1步: 编译NSIS DuiLib插件
echo ==============================================================================
call "%PROJECT_DIR%build_nsis_plugin.bat"
if %ERRORLEVEL% neq 0 (
    echo 插件编译失败!
    pause
    exit /b 1
)

REM 检查插件是否存在
if not exist "%PROJECT_DIR%nsis_installer.dll" (
    echo 错误: 插件编译失败，找不到 nsis_installer.dll
    pause
    exit /b 1
)

REM 第二步：准备示例应用程序文件
echo.
echo ==============================================================================
echo 第2步: 准备应用程序文件
echo ==============================================================================

REM 创建示例应用程序文件（如果不存在）
if not exist "%PROJECT_DIR%MyApp.exe" (
    echo 创建示例应用程序文件...
    copy /Y "%WINDIR%\System32\notepad.exe" "%PROJECT_DIR%MyApp.exe" >nul
    if %ERRORLEVEL% neq 0 (
        echo 警告: 无法创建示例应用程序文件，请手动提供 MyApp.exe
    ) else (
        echo 已创建示例应用程序文件: MyApp.exe
    )
)

REM 创建配置文件
if not exist "%PROJECT_DIR%config.ini" (
    echo 创建配置文件...
    echo [Settings] > "%PROJECT_DIR%config.ini"
    echo Version=1.0.0 >> "%PROJECT_DIR%config.ini"
    echo InstallDate=%DATE% >> "%PROJECT_DIR%config.ini"
    echo 已创建配置文件: config.ini
)

REM 第三步：检查NSIS是否安装
echo.
echo ==============================================================================
echo 第3步: 检查NSIS安装
echo ==============================================================================

if not exist %NSIS_PATH%\makensis.exe (
    echo 错误: 找不到NSIS，请安装NSIS或修改脚本中的NSIS_PATH变量
    echo NSIS下载地址: https://nsis.sourceforge.io/
    pause
    exit /b 1
)

echo 找到NSIS: %NSIS_PATH%\makensis.exe

REM 第四步：编译NSIS安装程序
echo.
echo ==============================================================================
echo 第4步: 编译NSIS安装程序
echo ==============================================================================

echo 正在编译安装程序脚本...
%NSIS_PATH%\makensis.exe "%PROJECT_DIR%installer_setup.nsi"

if %ERRORLEVEL% neq 0 (
    echo NSIS编译失败!
    pause
    exit /b 1
)

REM 检查输出文件
if not exist "%PROJECT_DIR%MyAppInstaller.exe" (
    echo 错误: 安装程序生成失败
    pause
    exit /b 1
)

echo.
echo ==============================================================================
echo 构建完成!
echo ==============================================================================
echo.
echo 生成的文件:
echo   • nsis_installer.dll  - NSIS DuiLib插件
echo   • MyAppInstaller.exe  - 最终安装程序
echo.
echo 文件大小:
for %%f in ("%PROJECT_DIR%nsis_installer.dll") do echo   插件大小: %%~zf 字节
for %%f in ("%PROJECT_DIR%MyAppInstaller.exe") do echo   安装程序大小: %%~zf 字节
echo.
echo 测试安装程序:
echo   双击 MyAppInstaller.exe 进行测试
echo.
echo 注意事项:
echo   1. 安装程序需要管理员权限
echo   2. 确保目标机器有Visual C++运行时库
echo   3. 可以在installer_setup.nsi中自定义安装内容
echo ==============================================================================

pause