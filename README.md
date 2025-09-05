# DuiLib C API 封装

这个项目将 DuiLib C++ UI框架封装为 C API，使其能够被其他编程语言调用。

## 特性

- **完整的C API接口**: 提供简洁易用的C语言接口
- **事件处理**: 支持鼠标、键盘和自定义事件
- **控件管理**: 查找、创建和操作各种UI控件
- **布局支持**: 从XML文件或字符串加载界面布局
- **跨语言友好**: 可被Python、Rust、Go等语言调用
- **内存安全**: 自动管理C++对象生命周期

## 目录结构

```
duilib-ffi/
├── duilib/          # 原始DuiLib源码
├── duilib_c/        # C API封装
│   ├── duilib_c.h   # C API头文件
│   ├── duilib_c.cpp # C API实现
│   ├── test/        # 测试用例
│   └── CMakeLists.txt
└── README.md
```

## 构建

### 前提条件
- Windows系统
- Visual Studio 2022（已安装在 E:\Program Files\Microsoft Visual Studio\2022）
- Windows SDK

### 构建步骤

#### 方法一：使用构建脚本（推荐）

```bash
# 运行自动构建脚本
build_simple.bat
```

构建脚本会自动：
1. 设置 Visual Studio 2022 环境
2. 编译 DuiLib 动态库 (x86架构)
3. 编译 C API 包装器为 DLL
4. 编译并链接测试程序
5. 清理临时文件

#### 方法二：手动构建

1. **设置编译环境**：
```bash
# 设置 VS2022 x86 环境
"E:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
```

2. **编译 DuiLib 核心库**：
```bash
# 更新工具集到 v143 (VS2022)
# 编译 DuiLib 动态库
msbuild "duilib\DuiLib\DuiLib.vcxproj" /p:Configuration=UnicodeRelease /p:Platform=Win32
```

3. **编译 C API 包装器为 DLL**：
```bash
cd build
cl /LD /I"..\duilib_c" /I"..\duilib\DuiLib" /DDUILIB_C_EXPORTS /DUNICODE /D_UNICODE /EHsc /MD /Fe:bin\duilib_c.dll /Fo:lib\ "..\duilib_c\duilib_c.cpp" "..\duilib\Lib\DuiLib_u.lib" user32.lib gdi32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib shell32.lib advapi32.lib winmm.lib
```

4. **编译测试程序**：
```bash
cl /Fe:bin\test\duilib_c_test_basic.exe /I"..\duilib_c" /DUNICODE /D_UNICODE /EHsc /MD "..\duilib_c\test\test_basic.c" bin\duilib_c.lib user32.lib gdi32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib shell32.lib advapi32.lib winmm.lib
```

### 输出文件

构建成功后，会生成以下文件：

```
build/
├── bin/
│   ├── duilib_c.dll          # C API 动态库
│   ├── duilib_c.lib          # 导入库
│   └── test/
│       └── duilib_c_test_basic.exe  # 测试程序
└── lib/
    └── (临时文件)
```

### 清理构建文件

清理不必要的构建文件：

```bash
# 手动清理
del /Q build\lib\*.obj
del /Q build\bin\*.manifest
del /Q build\bin\*.exp
del /Q build\bin\test\*.manifest
del /Q build\bin\test\*.exp
del /Q build\bin\test\*.lib

# 或使用 PowerShell 批量清理
powershell -Command "Remove-Item -Path 'build\**\*.obj', 'build\**\*.manifest', 'build\**\*.exp', 'build\**\*.pdb', 'build\**\*.ilk' -Force -ErrorAction SilentlyContinue"
```

## API 使用示例

### 基本使用

```c
#include "duilib_c.h"

int main() {
    // 初始化库
    duilib_init();
    
    // 创建窗口
    HWND hwnd = CreateWindow(...);
    duilib_manager_t manager = duilib_create_manager(hwnd, "main");
    
    // 加载界面
    duilib_load_layout(manager, "layout.xml");
    
    // 设置事件回调
    duilib_set_event_callback(manager, on_event);
    
    // 查找控件
    duilib_control_t button = duilib_find_control(manager, "my_button");
    duilib_control_set_text(button, "点击我");
    
    // 运行消息循环
    duilib_message_loop();
    
    // 清理资源
    duilib_destroy_manager(manager);
    duilib_cleanup();
    return 0;
}

void on_event(const duilib_event_t* event) {
    if (event->type == DUILIB_EVENT_CLICK) {
        printf("按钮被点击: %s\n", duilib_control_get_name(event->sender));
    }
}
```

### XML 布局示例

```xml
<?xml version="1.0" encoding="utf-8"?>
<Window size="400,300">
    <VerticalLayout padding="10,10,10,10">
        <Text name="title" text="DuiLib C API" height="30" />
        <Button name="btn_test" text="测试按钮" height="40" />
        <Edit name="input" text="输入框" height="25" />
    </VerticalLayout>
</Window>
```

## API 参考

### 核心函数

| 函数 | 说明 |
|------|------|
| `duilib_init()` | 初始化库 |
| `duilib_cleanup()` | 清理资源 |
| `duilib_create_manager()` | 创建窗口管理器 |
| `duilib_load_layout()` | 从XML文件加载布局 |
| `duilib_message_loop()` | 运行消息循环 |

### 控件操作

| 函数 | 说明 |
|------|------|
| `duilib_find_control()` | 按名称查找控件 |
| `duilib_control_get_text()` | 获取控件文本 |
| `duilib_control_set_text()` | 设置控件文本 |
| `duilib_control_set_visible()` | 设置可见性 |
| `duilib_control_set_bk_color()` | 设置背景色 |

### 事件处理

```c
typedef void (*duilib_event_callback_t)(const duilib_event_t* event);

typedef enum {
    DUILIB_EVENT_CLICK,
    DUILIB_EVENT_BUTTON_DOWN,
    DUILIB_EVENT_MOUSE_ENTER,
    // ...
} duilib_event_type_t;
```

## 错误处理

所有API函数返回 `duilib_result_t` 类型：

```c
typedef enum {
    DUILIB_OK = 0,
    DUILIB_ERROR_INVALID_PARAM = -1,
    DUILIB_ERROR_NOT_INITIALIZED = -2,
    DUILIB_ERROR_NOT_FOUND = -3,
    DUILIB_ERROR_MEMORY = -4
} duilib_result_t;
```

## 其他语言绑定

基于此C API，可以轻松创建其他语言的绑定：

### Python (ctypes)
```python
from ctypes import *

# 加载库
duilib = CDLL('./duilib_c.dll')

# 初始化
duilib.duilib_init()

# 创建管理器
manager = duilib.duilib_create_manager(hwnd, b"main")
```

### Rust
```rust
use std::ffi::CString;

extern "C" {
    fn duilib_init() -> i32;
    fn duilib_create_manager(hwnd: *mut c_void, name: *const c_char) -> *mut c_void;
}

fn main() {
    unsafe {
        duilib_init();
        let name = CString::new("main").unwrap();
        let manager = duilib_create_manager(hwnd, name.as_ptr());
    }
}
```

## 注意事项

1. **线程安全**: DuiLib不是线程安全的，所有API调用应在主线程进行
2. **内存管理**: C API会自动管理C++对象的生命周期
3. **字符编码**: 所有字符串参数使用UTF-8编码
4. **错误检查**: 建议检查所有API函数的返回值

## 许可证

本项目基于 DuiLib 的许可证发布。详见 [LICENSE](../duilib/LICENSE) 文件。

## 贡献

欢迎提交问题和改进建议！

## 更新日志

### v1.0.0
- 初始版本
- 完整的C API封装
- 基本事件处理
- 控件操作API
- 测试用例和示例