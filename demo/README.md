# DuiLib 安装程序界面演示

这个目录包含了使用 duilib-ffi C API 创建安装软件界面的代码示例。

## 文件说明

- `installer_window_code.cpp` - 纯代码实现的安装程序界面，无需XML布局文件

## 特性

- **纯代码界面创建** - 完全使用 C API 创建所有界面元素
- **完整的安装界面** - 包含标题、Logo、按钮、复选框、编辑框、进度条等
- **交互功能** - 支持窗口控制、安装进度、自定义选项切换
- **事件处理** - 完整的事件回调系统
- **模块化设计** - 清晰的代码结构和功能分离

## 界面元素

### 主要控件
- Logo 显示区域
- 应用标题标签
- 立即安装按钮
- 状态文本显示
- 安装进度条

### 用户协议区域
- 协议复选框
- 协议文本链接

### 自定义安装区域（可展开/收起）
- 安装路径编辑框
- 文件夹选择按钮
- 磁盘空间信息
- 附加选项（桌面快捷方式、快捷启动栏、开机自启动）

### 窗口控制
- 关闭按钮
- 最小化按钮

## 编译要求

1. Windows 平台
2. 支持 C99 的编译器（如 MSVC、MinGW）
3. DuiLib C API 库文件
4. Windows 系统库：user32.lib, gdi32.lib, ole32.lib, comctl32.lib

## 编译示例

```bash
# 使用 MSVC
cl installer_window_code.cpp /I"../duilib_c" /link duilib_c.lib user32.lib gdi32.lib ole32.lib comctl32.lib

# 使用 MinGW
g++ installer_window_code.cpp -I"../duilib_c" -L"../duilib_c" -lduilib_c -luser32 -lgdi32 -lole32 -lcomctl32
```

## 资源文件

程序需要以下资源文件（位于 `../nsis/` 目录）：
- `logo.png` - 应用程序图标
- `install_normal.png` - 安装按钮背景
- `windows_close.png` - 关闭按钮图标
- `windows_small.png` - 最小化按钮图标
- `down.png` - 下拉按钮图标
- `folder.png` - 文件夹选择按钮图标
- `checkbox_black_selected.png` - 复选框选中状态图标
- `check_project_checked.png` - 项目复选框选中图标
- `customInstallBg.png` - 自定义安装区域背景

## 代码结构

```
installer_window_code.cpp
├── 数据结构定义
│   └── installer_window_t - 安装程序窗口结构
├── 窗口初始化
│   ├── on_window_init() - 创建所有界面元素
│   ├── 创建布局容器
│   ├── 创建控件并设置属性
│   └── 组装界面布局
├── 事件处理
│   ├── on_notify() - 通知事件分发
│   └── on_button_click() - 按钮点击处理
├── 功能实现
│   ├── start_installation() - 开始安装
│   ├── simulate_installation_progress() - 模拟安装进度
│   ├── finish_installation() - 完成安装
│   ├── toggle_custom_area() - 切换自定义区域
│   └── choose_install_path() - 选择安装路径
└── 程序入口
    └── WinMain() - 主程序入口
```

## 使用说明

1. 确保项目已正确编译 duilib_c 库
2. 将资源文件放置在正确位置
3. 编译并运行 installer_window_code.cpp
4. 程序将显示一个完整的安装程序界面

## 扩展功能

可以基于此示例添加：
- 实际的文件安装逻辑
- 注册表操作
- 快捷方式创建
- 卸载程序生成
- 多语言支持
- 皮肤主题切换

## 注意事项

- 此示例主要用于演示 API 使用方法
- 实际项目中应使用线程处理安装逻辑
- 需要添加适当的错误处理和验证
- 资源文件路径可根据实际部署调整