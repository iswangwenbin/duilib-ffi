cmake_minimum_required(VERSION 3.10)
project(duilib_c)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../duilib/DuiLib
)

#=============================================================================
# 核心模块源文件 - Core (对应 duilib/DuiLib/Core)
#=============================================================================
set(DUILIB_C_CORE_SOURCES
    core/duilib_c_base.cpp
    core/duilib_c_control.cpp  
    core/duilib_c_container.cpp
    core/duilib_c_manager.cpp
    core/duilib_c_dlgbuilder.cpp
    core/duilib_c_markup.cpp
    core/duilib_c_render.cpp
)

set(DUILIB_C_CORE_HEADERS
    core/duilib_c_base.h
    core/duilib_c_window.h
    core/duilib_c_control.h
    core/duilib_c_container.h
    core/duilib_c_manager.h
    core/duilib_c_dlgbuilder.h
    core/duilib_c_markup.h
    core/duilib_c_render.h
)

#=============================================================================
# 控件模块源文件 - Control (对应 duilib/DuiLib/Control)
#=============================================================================
set(DUILIB_C_CONTROL_SOURCES
    control/duilib_c_controls.cpp
    control/duilib_c_button.cpp
    control/duilib_c_label.cpp
    control/duilib_c_text.cpp
    control/duilib_c_progress.cpp
    control/duilib_c_option.cpp
)

set(DUILIB_C_CONTROL_HEADERS
    control/duilib_c_controls.h
    control/duilib_c_button.h
    control/duilib_c_label.h
    control/duilib_c_edit.h
    control/duilib_c_text.h
    control/duilib_c_option.h
    control/duilib_c_checkbox.h
    control/duilib_c_progress.h
    control/duilib_c_slider.h
    control/duilib_c_scrollbar.h
    control/duilib_c_combo.h
    control/duilib_c_datetime.h
)

#=============================================================================
# 布局模块源文件 - Layout (对应 duilib/DuiLib/Layout)
#=============================================================================
set(DUILIB_C_LAYOUT_SOURCES
    layout/duilib_c_layouts.cpp
    layout/duilib_c_verticallayout.cpp
    layout/duilib_c_horizontallayout.cpp
    layout/duilib_c_tablayout.cpp
    layout/duilib_c_tilelayout.cpp
    layout/duilib_c_childlayout.cpp
)

set(DUILIB_C_LAYOUT_HEADERS
    layout/duilib_c_layouts.h
    layout/duilib_c_verticallayout.h
    layout/duilib_c_horizontallayout.h
    layout/duilib_c_tablayout.h
    layout/duilib_c_tilelayout.h
    layout/duilib_c_childlayout.h
)

#=============================================================================
# 工具模块源文件 - Utils (对应 duilib/DuiLib/Utils)
#=============================================================================
set(DUILIB_C_UTILS_SOURCES
    utils/duilib_c_utils.cpp
    utils/duilib_c_delegate.cpp
    utils/duilib_c_winimplbase.cpp
    utils/duilib_c_wndshadow.cpp
    utils/duilib_c_flash.cpp
)

set(DUILIB_C_UTILS_HEADERS
    utils/duilib_c_utils.h
    utils/duilib_c_delegate.h
    utils/duilib_c_winimplbase.h
    utils/duilib_c_wndshadow.h
    utils/duilib_c_flash.h
)

#=============================================================================
# 合并所有模块
#=============================================================================
set(DUILIB_C_SOURCES
    ${DUILIB_C_CORE_SOURCES}
    ${DUILIB_C_CONTROL_SOURCES}
    ${DUILIB_C_LAYOUT_SOURCES}
    ${DUILIB_C_UTILS_SOURCES}
)

set(DUILIB_C_HEADERS
    ${DUILIB_C_CORE_HEADERS}
    ${DUILIB_C_CONTROL_HEADERS}
    ${DUILIB_C_LAYOUT_HEADERS}
    ${DUILIB_C_UTILS_HEADERS}
    duilib_c.h
    duilib_c_internal.h
)

# 查找duilib源文件
file(GLOB_RECURSE DUILIB_SOURCES
    "../duilib/DuiLib/*.cpp"
    "../duilib/DuiLib/*.c"
)

# 创建静态库
add_library(duilib_c_static STATIC
    ${DUILIB_C_SOURCES}
    ${DUILIB_SOURCES}
)

# 创建动态库
add_library(duilib_c SHARED
    ${DUILIB_C_SOURCES}
    ${DUILIB_SOURCES}
)

# 设置动态库编译定义
target_compile_definitions(duilib_c PRIVATE DUILIB_C_EXPORTS UILIB_EXPORTS)
target_compile_definitions(duilib_c_static PRIVATE UILIB_STATIC)

# 链接库
if(WIN32)
    target_link_libraries(duilib_c
        comctl32
        gdi32
        user32
        kernel32
        ole32
        oleaut32
        uuid
        shell32
        advapi32
        winmm
    )
    
    target_link_libraries(duilib_c_static
        comctl32
        gdi32
        user32
        kernel32
        ole32
        oleaut32
        uuid
        shell32
        advapi32
        winmm
    )
endif()

# 设置输出目录
set_target_properties(duilib_c PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

set_target_properties(duilib_c_static PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

#=============================================================================
# 安装规则
#=============================================================================
install(TARGETS duilib_c duilib_c_static
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# 安装主头文件
install(FILES duilib_c.h duilib_c_internal.h
    DESTINATION include
)

# 安装核心模块头文件
install(FILES ${DUILIB_C_CORE_HEADERS}
    DESTINATION include/duilib_c/core
)

# 安装控件模块头文件
install(FILES ${DUILIB_C_CONTROL_HEADERS}
    DESTINATION include/duilib_c/control
)

# 安装布局模块头文件
install(FILES ${DUILIB_C_LAYOUT_HEADERS}
    DESTINATION include/duilib_c/layout
)

# 安装工具模块头文件
install(FILES ${DUILIB_C_UTILS_HEADERS}
    DESTINATION include/duilib_c/utils
)