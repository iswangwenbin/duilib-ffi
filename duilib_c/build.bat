@echo off
REM 设置Visual Studio环境
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

REM 创建构建目录
if not exist build mkdir build
cd build

REM 编译所有cpp文件为目标文件
set CL_FLAGS=/std:c++17 /DDUILIB_C_EXPORTS /DUILIB_EXPORTS /I.. /I..\..\duilib\DuiLib /utf-8

echo 编译核心模块...
cl %CL_FLAGS% /c ..\core\duilib_c_base.cpp
cl %CL_FLAGS% /c ..\core\duilib_c_control.cpp
cl %CL_FLAGS% /c ..\core\duilib_c_container.cpp
cl %CL_FLAGS% /c ..\core\duilib_c_manager.cpp
cl %CL_FLAGS% /c ..\core\duilib_c_dlgbuilder.cpp
cl %CL_FLAGS% /c ..\core\duilib_c_markup.cpp
cl %CL_FLAGS% /c ..\core\duilib_c_render.cpp

echo 编译控件模块...
cl %CL_FLAGS% /c ..\control\duilib_c_controls.cpp
cl %CL_FLAGS% /c ..\control\duilib_c_button.cpp
cl %CL_FLAGS% /c ..\control\duilib_c_label.cpp
cl %CL_FLAGS% /c ..\control\duilib_c_text.cpp
cl %CL_FLAGS% /c ..\control\duilib_c_progress.cpp
cl %CL_FLAGS% /c ..\control\duilib_c_option.cpp

echo 编译布局模块...
cl %CL_FLAGS% /c ..\layout\duilib_c_layouts.cpp
cl %CL_FLAGS% /c ..\layout\duilib_c_verticallayout.cpp
cl %CL_FLAGS% /c ..\layout\duilib_c_horizontallayout.cpp
cl %CL_FLAGS% /c ..\layout\duilib_c_tablayout.cpp
cl %CL_FLAGS% /c ..\layout\duilib_c_tilelayout.cpp
cl %CL_FLAGS% /c ..\layout\duilib_c_childlayout.cpp

echo 编译工具模块...
cl %CL_FLAGS% /c ..\utils\duilib_c_utils.cpp
cl %CL_FLAGS% /c ..\utils\duilib_c_delegate.cpp
cl %CL_FLAGS% /c ..\utils\duilib_c_winimplbase.cpp
cl %CL_FLAGS% /c ..\utils\duilib_c_wndshadow.cpp
cl %CL_FLAGS% /c ..\utils\duilib_c_flash.cpp

REM 编译duilib源文件 (假设存在)
for /R "..\..\duilib\DuiLib" %%f in (*.cpp) do (
    echo 编译 %%f
    cl %CL_FLAGS% /c "%%f"
)

REM 编译duilib的C源文件 (包括stb_image.c)
for /R "..\..\duilib\DuiLib" %%f in (*.c) do (
    echo 编译 %%f
    cl %CL_FLAGS% /c "%%f"
)

echo 链接DLL...
link /DLL /OUT:duilib_c.dll *.obj comctl32.lib gdi32.lib user32.lib kernel32.lib ole32.lib oleaut32.lib uuid.lib shell32.lib advapi32.lib winmm.lib

echo 编译完成！
pause