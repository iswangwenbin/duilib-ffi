# ==============================================================================
# CMake构建脚本 - NSIS DuiLib插件和安装程序
# 支持跨平台编译NSIS插件
# ==============================================================================

cmake_minimum_required(VERSION 3.10)
project(NSISDuiLibInstaller)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 平台检查
if(NOT WIN32)
    message(FATAL_ERROR "This project only supports Windows platform")
endif()

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 查找DuiLib C库
find_path(DUILIB_C_INCLUDE_DIR
    NAMES duilib_c.h
    PATHS ${CMAKE_SOURCE_DIR}/../duilib_c
    NO_DEFAULT_PATH
)

find_library(DUILIB_C_LIBRARY
    NAMES duilib_c
    PATHS ${CMAKE_SOURCE_DIR}/../duilib_c
    NO_DEFAULT_PATH
)

if(NOT DUILIB_C_INCLUDE_DIR)
    message(FATAL_ERROR "Could not find duilib_c.h. Please ensure duilib_c is built.")
endif()

if(NOT DUILIB_C_LIBRARY)
    message(WARNING "Could not find duilib_c library. You may need to build it first.")
endif()

message(STATUS "DuiLib C include directory: ${DUILIB_C_INCLUDE_DIR}")
message(STATUS "DuiLib C library: ${DUILIB_C_LIBRARY}")

# ==============================================================================
# NSIS插件目标
# ==============================================================================

add_library(nsis_installer SHARED
    nsis_installer.cpp
)

# 设置包含目录
target_include_directories(nsis_installer PRIVATE
    ${DUILIB_C_INCLUDE_DIR}
)

# 链接库
target_link_libraries(nsis_installer PRIVATE
    ${DUILIB_C_LIBRARY}
    user32
    gdi32
    ole32
    comctl32
    shell32
    comdlg32
)

# 设置插件属性
set_target_properties(nsis_installer PROPERTIES
    PREFIX ""  # 去掉lib前缀
    SUFFIX ".dll"
)

# 定义预处理宏
target_compile_definitions(nsis_installer PRIVATE
    WIN32
    _WINDOWS
    _USRDLL
    NSIS_PLUGIN
    UNICODE
    _UNICODE
)

# 设置编译选项
if(MSVC)
    target_compile_options(nsis_installer PRIVATE
        /W3
        /EHsc
        /MD
    )
endif()

# ==============================================================================
# 独立安装程序目标（可选）
# ==============================================================================

add_executable(installer_window_code WIN32
    installer_window_code.cpp
)

target_include_directories(installer_window_code PRIVATE
    ${DUILIB_C_INCLUDE_DIR}
)

target_link_libraries(installer_window_code PRIVATE
    ${DUILIB_C_LIBRARY}
    user32
    gdi32
    ole32
    comctl32
    shell32
)

target_compile_definitions(installer_window_code PRIVATE
    WIN32
    _WINDOWS
    UNICODE
    _UNICODE
)

if(MSVC)
    target_compile_options(installer_window_code PRIVATE
        /W3
        /EHsc
        /MD
    )
endif()

# ==============================================================================
# 资源文件复制
# ==============================================================================

# 复制资源文件到输出目录
set(RESOURCE_FILES
    ../nsis/bg.png
    ../nsis/logo.png
    ../nsis/install_normal.png
    ../nsis/windows_close.png
    ../nsis/windows_small.png
    ../nsis/checkbox_black_selected.png
    ../nsis/check_project_checked.png
    ../nsis/down.png
    ../nsis/folder.png
    ../nsis/customInstallBg.png
)

foreach(RESOURCE_FILE ${RESOURCE_FILES})
    if(EXISTS ${CMAKE_SOURCE_DIR}/${RESOURCE_FILE})
        get_filename_component(FILENAME ${RESOURCE_FILE} NAME)
        configure_file(
            ${CMAKE_SOURCE_DIR}/${RESOURCE_FILE}
            ${CMAKE_BINARY_DIR}/bin/${FILENAME}
            COPYONLY
        )
    endif()
endforeach()

# 复制NSIS脚本
configure_file(
    ${CMAKE_SOURCE_DIR}/installer_setup.nsi
    ${CMAKE_BINARY_DIR}/bin/installer_setup.nsi
    COPYONLY
)

# ==============================================================================
# 自定义目标 - 构建NSIS安装程序
# ==============================================================================

# 查找NSIS
find_program(NSIS_MAKENSIS
    NAMES makensis makensis.exe
    PATHS
        "C:/Program Files (x86)/NSIS"
        "C:/Program Files/NSIS"
        "$ENV{PROGRAMFILES}/NSIS"
        "$ENV{PROGRAMFILES(x86)}/NSIS"
    DOC "NSIS makensis executable"
)

if(NSIS_MAKENSIS)
    message(STATUS "Found NSIS: ${NSIS_MAKENSIS}")
    
    # 添加自定义目标来构建最终的安装程序
    add_custom_target(build_installer
        COMMAND ${NSIS_MAKENSIS} "${CMAKE_BINARY_DIR}/bin/installer_setup.nsi"
        DEPENDS nsis_installer
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        COMMENT "Building final installer with NSIS"
    )
    
    message(STATUS "To build the final installer, run: cmake --build . --target build_installer")
else()
    message(STATUS "NSIS not found. Install NSIS to build the final installer automatically.")
    message(STATUS "NSIS can be downloaded from: https://nsis.sourceforge.io/")
endif()

# ==============================================================================
# 安装规则
# ==============================================================================

install(TARGETS nsis_installer installer_window_code
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
)

install(FILES
    installer_setup.nsi
    README.md
    DESTINATION .
)

# 安装资源文件
foreach(RESOURCE_FILE ${RESOURCE_FILES})
    if(EXISTS ${CMAKE_SOURCE_DIR}/${RESOURCE_FILE})
        get_filename_component(FILENAME ${RESOURCE_FILE} NAME)
        install(FILES ${CMAKE_SOURCE_DIR}/${RESOURCE_FILE}
                DESTINATION bin
                RENAME ${FILENAME})
    endif()
endforeach()

# ==============================================================================
# 打包配置
# ==============================================================================

set(CPACK_PACKAGE_NAME "NSIS DuiLib Installer")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "NSIS installer with custom DuiLib interface")
set(CPACK_PACKAGE_VENDOR "MyCompany")

include(CPack)

# ==============================================================================
# 显示构建信息
# ==============================================================================

message(STATUS "")
message(STATUS "==============================================================================")
message(STATUS "NSIS DuiLib Installer Configuration Summary")
message(STATUS "==============================================================================")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Target platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "")
message(STATUS "Targets:")
message(STATUS "  nsis_installer      - NSIS plugin DLL")
message(STATUS "  installer_window_code - Standalone installer executable")
if(NSIS_MAKENSIS)
message(STATUS "  build_installer     - Build final NSIS installer")
endif()
message(STATUS "")
message(STATUS "Build commands:")
message(STATUS "  cmake --build . --config Release")
if(NSIS_MAKENSIS)
message(STATUS "  cmake --build . --target build_installer --config Release")
endif()
message(STATUS "==============================================================================")
message(STATUS "")