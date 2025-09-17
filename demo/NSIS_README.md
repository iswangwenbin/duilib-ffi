# NSIS + DuiLib_C 集成安装程序

这是一个完整的NSIS与duilib_c集成方案，使用自定义DuiLib界面替代默认的NSIS安装界面。

## 项目结构

```
demo/
├── nsis_installer.cpp       # NSIS插件源代码（DLL）
├── installer_setup.nsi      # NSIS安装脚本
├── build_nsis_plugin.bat    # 插件编译脚本
├── build_installer.bat      # 完整安装程序构建脚本
├── CMakeLists.txt           # CMake构建配置
├── NSIS_README.md           # 本文档
└── installer_window_code.cpp # 独立安装程序（参考用）
```

## 工作原理

### 1. 架构设计

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   NSIS Script   │───▶│  DuiLib Plugin  │───▶│  DuiLib UI     │
│ installer_setup │    │ nsis_installer  │    │  Custom GUI    │
│     .nsi        │    │     .dll        │    │                │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

### 2. 组件说明

- **NSIS脚本** - 处理实际的文件安装、注册表操作、快捷方式创建
- **DuiLib插件** - 提供自定义界面，替代NSIS默认界面
- **资源文件** - 界面所需的图片、样式文件

## 功能特性

### ✅ 自定义界面功能
- 美观的现代化界面设计
- 自定义安装路径选择
- 实时安装进度显示  
- 用户协议确认
- 安装选项配置（桌面快捷方式、开机启动等）
- 窗口控制（最小化、关闭）

### ✅ NSIS集成功能
- 与NSIS安装流程无缝集成
- 支持标准NSIS功能（文件安装、注册表、快捷方式）
- 完整的卸载程序支持
- 管理员权限检查
- 版本检测和升级支持

## 编译和使用

### 方法一：使用批处理脚本（推荐）

```bash
# 1. 编译插件和生成安装程序
build_installer.bat

# 或者分步骤：
# 1a. 仅编译插件
build_nsis_plugin.bat

# 1b. 编译NSIS安装程序（需要安装NSIS）
makensis installer_setup.nsi
```

### 方法二：使用CMake

```bash
# 创建构建目录
mkdir build && cd build

# 配置项目
cmake .. -A x64

# 编译插件
cmake --build . --config Release

# 构建最终安装程序（如果已安装NSIS）
cmake --build . --target build_installer --config Release
```

## 依赖要求

### 编译时依赖
- **Visual Studio 2017+** 或 **MinGW-w64**
- **CMake 3.10+**（可选，用于CMake构建）
- **NSIS 3.0+** - 用于生成最终安装程序
- **DuiLib_C库** - 需要先编译duilib_c项目

### 运行时依赖
- **Windows 7+**
- **Visual C++ Redistributable**
- **DuiLib_C运行时库**

## 插件API参考

### 导出函数

#### `ShowInstaller`
显示自定义安装界面
```nsis
nsis_installer::ShowInstaller
Pop $Result  ; "OK", "CANCEL", or "ERROR"
```

#### `UpdateProgress` 
更新安装进度
```nsis
Push "75"  ; 进度值 (0-100)
nsis_installer::UpdateProgress
Pop $Result  ; "OK"
```

#### `GetInstallPath`
获取用户选择的安装路径
```nsis
nsis_installer::GetInstallPath
Pop $InstallPath  ; 用户选择的路径
```

### NSIS脚本示例

```nsis
Section "安装程序"
    ; 显示自定义界面
    nsis_installer::ShowInstaller
    Pop $Result
    
    ${If} $Result == "OK"
        ; 获取安装路径
        nsis_installer::GetInstallPath
        Pop $INSTDIR
        
        ; 开始安装文件
        SetOutPath "$INSTDIR"
        File "MyApp.exe"
        
        ; 更新进度
        Push "50"
        nsis_installer::UpdateProgress
        
        ; 继续安装...
    ${ElseIf} $Result == "CANCEL"
        Abort "用户取消安装"
    ${EndIf}
SectionEnd
```

## 自定义和扩展

### 修改界面样式
编辑 `nsis_installer.cpp` 中的 `create_installer_layout()` 函数：
```cpp
// 修改颜色
duilib_control_set_bk_color(main_layout, 0xFF2C3E50);  // 深蓝背景

// 修改字体
duilib_control_set_font_size(title_control, 20);      // 更大标题

// 添加新控件
duilib_checkbox_t chk_autostart = duilib_checkbox_create();
// ...配置控件...
```

### 添加新的插件功能
在 `nsis_installer.cpp` 中添加新的导出函数：
```cpp
extern "C" __declspec(dllexport) void MyCustomFunction(
    HWND hwndParent, int string_size, TCHAR* variables,
    stack_t** stacktop, extra_parameters* extra) {
    EXDLL_INIT();
    
    // 你的自定义逻辑
    
    pushstring("结果");
}
```

### 修改安装流程
编辑 `installer_setup.nsi`：
```nsis
Section "自定义安装步骤"
    ; 添加你的安装逻辑
    File "additional_file.dll"
    WriteRegStr HKLM "SOFTWARE\MyApp" "CustomKey" "CustomValue"
SectionEnd
```

## 故障排除

### 常见问题

1. **插件编译失败**
   - 检查Visual Studio路径配置
   - 确认duilib_c库已编译
   - 验证头文件路径

2. **界面不显示**
   - 确认资源文件路径正确
   - 检查图片文件是否存在
   - 验证DLL依赖项

3. **NSIS编译错误**
   - 确认NSIS版本兼容性
   - 检查脚本语法错误
   - 验证插件DLL可用性

### 调试技巧

```nsis
; 在NSIS脚本中添加调试信息
DetailPrint "调试: 当前状态 = $Status"
MessageBox MB_OK "调试信息: $Variable"
```

```cpp
// 在插件中添加日志输出
#ifdef _DEBUG
    OutputDebugStringA("Debug: 函数被调用");
#endif
```

## 版本历史

- **v1.0** - 初始版本，基本界面功能
- **v1.1** - 添加进度更新支持
- **v1.2** - 支持自定义安装路径
- **v1.3** - 完整的CMake构建支持

## 许可证

本项目遵循 MIT 许可证。详见项目根目录的 LICENSE 文件。

## 技术支持

如有问题或建议，请在项目的GitHub页面提交Issue。