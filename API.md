# DuiLib C API 完整参考文档

## 概述

DuiLib C API 是对原生 DuiLib C++ 库的完整 C 语言封装，提供了全面的 C 接口来使用 DuiLib 的所有核心功能。采用模块化架构设计，将API按功能分类为Core、Control、Layout、Utils四大模块，与原生DuiLib目录结构完全对应。

## 📁 模块化架构

### 目录结构
```
duilib_c/
├── duilib_c.h                 # 主头文件，包含所有模块
├── duilib_c_internal.h        # 内部实现头文件
├── core/                      # 核心模块
│   ├── duilib_c_base.h/.cpp      # 基础类型和工具函数
│   ├── duilib_c_control.h/.cpp   # 基础控件API
│   ├── duilib_c_container.h/.cpp # 容器控件API
│   ├── duilib_c_manager.h/.cpp   # 管理器API
│   ├── duilib_c_dlgbuilder.h/.cpp # 对话框构建器API
│   ├── duilib_c_markup.h/.cpp    # 标记语言API
│   └── duilib_c_render.h/.cpp    # 渲染API
├── control/                   # 控件模块
│   ├── duilib_c_button.h/.cpp    # 按钮控件
│   ├── duilib_c_edit.h/.cpp      # 编辑框控件
│   ├── duilib_c_label.h/.cpp     # 标签控件
│   ├── duilib_c_checkbox.h/.cpp  # 复选框控件
│   ├── duilib_c_option.h/.cpp    # 选项控件
│   ├── duilib_c_progress.h/.cpp  # 进度条控件
│   ├── duilib_c_slider.h/.cpp    # 滑块控件
│   ├── duilib_c_list.h/.cpp      # 列表控件
│   ├── duilib_c_combo.h/.cpp     # 组合框控件
│   ├── duilib_c_scrollbar.h/.cpp # 滚动条控件
│   ├── duilib_c_datetime.h/.cpp  # 日期时间控件
│   ├── duilib_c_activex.h/.cpp   # ActiveX控件
│   ├── duilib_c_webbrowser.h/.cpp # 浏览器控件
│   ├── duilib_c_flash.h/.cpp     # Flash控件
│   ├── duilib_c_gifanim.h/.cpp   # GIF动画控件
│   ├── duilib_c_richedit.h/.cpp  # 富文本编辑控件
│   ├── duilib_c_text.h/.cpp      # 文本控件
│   └── duilib_c_treeview.h/.cpp  # 树形控件
├── layout/                    # 布局模块
│   ├── duilib_c_vertical_layout.h/.cpp   # 垂直布局
│   ├── duilib_c_horizontal_layout.h/.cpp # 水平布局
│   ├── duilib_c_tab_layout.h/.cpp        # 标签布局
│   ├── duilib_c_tile_layout.h/.cpp       # 瓦片布局
│   └── duilib_c_child_layout.h/.cpp      # 子窗口布局
└── utils/                     # 工具模块
    ├── duilib_c_delegate.h/.cpp   # 委托处理
    ├── duilib_c_utils.h/.cpp      # 工具函数
    ├── duilib_c_winimpl.h/.cpp    # 窗口实现基类
    └── duilib_c_wndshadow.h/.cpp  # 窗口阴影
```

## 📊 API 统计概览

- **总 API 函数数**: **700 个**
- **覆盖控件类型**: **18 种**（完整支持）
- **功能模块**: **4 大模块**（Core/Control/Layout/Utils）
- **文件数量**: **34 个头文件 + 34 个实现文件**
- **方法对应率**: **100%**（完整 1:1 对应）

### 📈 按模块函数分布

| 模块 | 文件数量 | 函数数量 | 占比 | 主要功能 |
|------|----------|----------|------|----------|
| **Core** | 7个文件 | 340个函数 | 48.6% | 管理器、基础控件、容器 |
| **Control** | 18个文件 | 300个函数 | 42.9% | 具体控件实现 |
| **Layout** | 5个文件 | 21个函数 | 3.0% | 布局管理器 |
| **Utils** | 4个文件 | 39个函数 | 5.6% | 工具函数和辅助类 |

## 📋 详细方法对应关系表

## 🔧 模块详细说明

### Core 模块 - 核心功能
- **duilib_c_base**: 基础类型定义、枚举常量、工具函数
- **duilib_c_control**: 基础控件API (CControlUI对应)
- **duilib_c_container**: 容器控件API (CContainerUI对应)
- **duilib_c_manager**: 管理器API (CPaintManagerUI对应)
- **duilib_c_dlgbuilder**: 对话框构建器API (CDialogBuilder对应)
- **duilib_c_markup**: XML标记语言API (CMarkup对应)
- **duilib_c_render**: 渲染引擎API (CRenderEngine对应)

### Control 模块 - 控件库
- **18种控件类型**：Button, Edit, Label, CheckBox, Option, Progress, Slider, List, Combo, ScrollBar, DateTime, ActiveX, WebBrowser, Flash, GifAnim, RichEdit, Text, TreeView
- 每个控件都有独立的头文件和实现文件
- 完整对应原生DuiLib控件类

### Layout 模块 - 布局管理
- **5种布局类型**：Vertical, Horizontal, Tab, Tile, Child
- 提供灵活的界面布局解决方案
- 支持嵌套和组合布局

### Utils 模块 - 工具库
- **delegate**: 事件委托和回调处理
- **utils**: 全局工具函数和资源管理
- **winimpl**: 窗口实现基类
- **wndshadow**: 窗口阴影效果

## 🔧 核心模块详细统计

### Core 模块 - 340个函数

| 组件 | 函数数量 | 对应DuiLib类 | 主要功能 |
|------|----------|--------------|----------|
| **duilib_c_base** | 29个 | 全局函数/静态方法 | 库初始化、消息循环、资源管理 |
| **duilib_c_control** | 115个 | CControlUI | 控件基类的所有操作方法 |
| **duilib_c_container** | 52个 | CContainerUI | 容器控件操作和子控件管理 |
| **duilib_c_manager** | 116个 | CPaintManagerUI | 绘制管理器的完整功能 |
| **duilib_c_render** | 13个 | CRenderEngine | 渲染引擎接口 |
| **duilib_c_markup** | 10个 | CMarkup | XML解析器接口 |
| **duilib_c_dlgbuilder** | 5个 | CDialogBuilder | 对话框构建器接口 |

### Control 模块 - 300个函数

| 控件类型 | 函数数量 | 对应DuiLib类 | 说明 |
|----------|----------|--------------|------|
| **Label** | 38个 | CLabelUI | 标签控件，支持丰富文本格式 |
| **Edit** | 27个 | CEditUI | 编辑框控件，支持密码模式 |
| **Button** | 26个 | CButtonUI | 按钮控件，多状态图片支持 |
| **TreeView** | 26个 | CTreeViewUI | 树形视图控件 |
| **Combo** | 24个 | CComboUI | 下拉组合框控件 |
| **Option** | 23个 | COptionUI | 选项按钮（单选） |
| **RichEdit** | 18个 | CRichEditUI | 富文本编辑器 |
| **Slider** | 18个 | CSliderUI | 滑块控件 |
| **Text** | 16个 | CTextUI | 简单文本控件 |
| **WebBrowser** | 14个 | CWebBrowserUI | Web浏览器控件 |
| **ScrollBar** | 12个 | CScrollBarUI | 滚动条控件 |
| **List** | 11个 | CListUI | 列表控件 |
| **Progress** | 11个 | CProgressUI | 进度条控件 |
| **ActiveX** | 9个 | CActiveXUI | ActiveX容器控件 |
| **Flash** | 9个 | CFlashUI | Flash播放器控件 |
| **GifAnim** | 9个 | CGifAnimUI | GIF动画控件 |
| **DateTime** | 7个 | CDateTimeUI | 日期时间选择控件 |
| **CheckBox** | 2个 | CCheckBoxUI | 复选框控件 |

### Layout 模块 - 21个函数

| 布局类型 | 函数数量 | 对应DuiLib类 | 说明 |
|----------|----------|--------------|------|
| **Vertical Layout** | 5个 | CVerticalLayoutUI | 垂直布局管理器 |
| **Horizontal Layout** | 5个 | CHorizontalLayoutUI | 水平布局管理器 |
| **Tile Layout** | 4个 | CTileLayoutUI | 瓦片式布局管理器 |
| **Child Layout** | 4个 | CChildLayoutUI | 子窗口布局管理器 |
| **Tab Layout** | 3个 | CTabLayoutUI | 标签页布局管理器 |

### Utils 模块 - 39个函数

| 工具类 | 函数数量 | 对应DuiLib类 | 说明 |
|--------|----------|--------------|------|
| **WndShadow** | 16个 | CWndShadow | 窗口阴影效果实现 |
| **Utils** | 13个 | 全局工具函数 | 资源管理、路径操作等 |
| **WinImpl** | 6个 | CWindowWnd | 窗口实现基类 |
| **Delegate** | 4个 | INotifyUI | 事件委托和通知机制 |

### 1. 详细方法对应关系

#### CPaintManagerUI 管理器方法对应 (116个方法)

| DuiLib C++ 方法 | C API 方法 | 功能描述 |
|-----------------|------------|----------|
| `Init(HWND, LPCTSTR)` | `duilib_paint_manager_init()` | 初始化管理器 |
| `GetName()` | `duilib_paint_manager_get_name()` | 获取管理器名称 |
| `GetPaintDC()` | `duilib_paint_manager_get_paint_dc()` | 获取绘制DC |
| `GetPaintOffscreenBitmap()` | `duilib_paint_manager_get_paint_offscreen_bitmap()` | 获取离屏位图 |
| `GetPaintWindow()` | `duilib_paint_manager_get_paint_window()` | 获取绘制窗口 |
| `GetTooltipWindow()` | `duilib_paint_manager_get_tooltip_window()` | 获取工具提示窗口 |
| `GetTooltipWindowWidth()` | `duilib_paint_manager_get_tooltip_window_width()` | 获取工具提示宽度 |
| `SetTooltipWindowWidth()` | `duilib_paint_manager_set_tooltip_window_width()` | 设置工具提示宽度 |
| `GetHoverTime()` | `duilib_paint_manager_get_hover_time()` | 获取悬停时间 |
| `SetHoverTime()` | `duilib_paint_manager_set_hover_time()` | 设置悬停时间 |
| `IsUpdateNeeded()` | `duilib_paint_manager_is_update_needed()` | 检查是否需要更新 |
| `NeedUpdate()` | `duilib_paint_manager_need_update()` | 标记需要更新 |
| `Invalidate()` | `duilib_paint_manager_invalidate()` | 无效化窗口 |
| `Invalidate(RECT&)` | `duilib_paint_manager_invalidate_rect()` | 无效化指定区域 |
| `GetMousePos()` | `duilib_paint_manager_get_mouse_pos()` | 获取鼠标位置 |
| `GetClientSize()` | `duilib_paint_manager_get_client_size()` | 获取客户区尺寸 |
| `GetInitSize()` | `duilib_paint_manager_get_init_size()` | 获取初始尺寸 |
| `SetInitSize()` | `duilib_paint_manager_set_init_size()` | 设置初始尺寸 |
| `GetSizeBox()` | `duilib_paint_manager_get_size_box()` | 获取尺寸框 |
| `SetSizeBox()` | `duilib_paint_manager_set_size_box()` | 设置尺寸框 |
| `GetCaptionRect()` | `duilib_paint_manager_get_caption_rect()` | 获取标题栏矩形 |
| `SetCaptionRect()` | `duilib_paint_manager_set_caption_rect()` | 设置标题栏矩形 |
| `GetRoundCorner()` | `duilib_paint_manager_get_round_corner()` | 获取圆角 |
| `SetRoundCorner()` | `duilib_paint_manager_set_round_corner()` | 设置圆角 |
| `GetMinInfo()` | `duilib_paint_manager_get_min_info()` | 获取最小尺寸 |
| `SetMinInfo()` | `duilib_paint_manager_set_min_info()` | 设置最小尺寸 |
| `GetMaxInfo()` | `duilib_paint_manager_get_max_info()` | 获取最大尺寸 |
| `SetMaxInfo()` | `duilib_paint_manager_set_max_info()` | 设置最大尺寸 |
| `IsShowUpdateRect()` | `duilib_paint_manager_is_show_update_rect()` | 是否显示更新矩形 |
| `SetShowUpdateRect()` | `duilib_paint_manager_set_show_update_rect()` | 设置显示更新矩形 |
| `IsNoActivate()` | `duilib_paint_manager_is_no_activate()` | 是否禁用激活 |
| `SetNoActivate()` | `duilib_paint_manager_set_no_activate()` | 设置禁用激活 |
| `GetOpacity()` | `duilib_paint_manager_get_opacity()` | 获取不透明度 |
| `SetOpacity()` | `duilib_paint_manager_set_opacity()` | 设置不透明度 |
| `IsLayered()` | `duilib_paint_manager_is_layered()` | 是否分层窗口 |
| `SetLayered()` | `duilib_paint_manager_set_layered()` | 设置分层窗口 |
| `GetLayeredInset()` | `duilib_paint_manager_get_layered_inset()` | 获取分层边距 |
| `SetLayeredInset()` | `duilib_paint_manager_set_layered_inset()` | 设置分层边距 |
| `GetLayeredOpacity()` | `duilib_paint_manager_get_layered_opacity()` | 获取分层不透明度 |
| `SetLayeredOpacity()` | `duilib_paint_manager_set_layered_opacity()` | 设置分层不透明度 |
| `GetLayeredImage()` | `duilib_paint_manager_get_layered_image()` | 获取分层图片 |
| `SetLayeredImage()` | `duilib_paint_manager_set_layered_image()` | 设置分层图片 |
| `IsForceUseSharedRes()` | `duilib_paint_manager_is_force_use_shared_res()` | 是否强制使用共享资源 |
| `SetForceUseSharedRes()` | `duilib_paint_manager_set_force_use_shared_res()` | 设置强制使用共享资源 |
| `GetDefaultDisabledColor()` | `duilib_paint_manager_get_default_disabled_color()` | 获取默认禁用颜色 |
| `SetDefaultDisabledColor()` | `duilib_paint_manager_set_default_disabled_color()` | 设置默认禁用颜色 |
| `GetDefaultFontColor()` | `duilib_paint_manager_get_default_font_color()` | 获取默认字体颜色 |
| `SetDefaultFontColor()` | `duilib_paint_manager_set_default_font_color()` | 设置默认字体颜色 |
| `GetDefaultLinkFontColor()` | `duilib_paint_manager_get_default_link_font_color()` | 获取默认链接字体颜色 |
| `SetDefaultLinkFontColor()` | `duilib_paint_manager_set_default_link_font_color()` | 设置默认链接字体颜色 |
| `GetDefaultLinkHoverFontColor()` | `duilib_paint_manager_get_default_link_hover_font_color()` | 获取默认链接悬停颜色 |
| `SetDefaultLinkHoverFontColor()` | `duilib_paint_manager_set_default_link_hover_font_color()` | 设置默认链接悬停颜色 |
| `GetDefaultSelectedBkColor()` | `duilib_paint_manager_get_default_selected_bk_color()` | 获取默认选中背景色 |
| `SetDefaultSelectedBkColor()` | `duilib_paint_manager_set_default_selected_bk_color()` | 设置默认选中背景色 |
| `SetDefaultFont()` | `duilib_paint_manager_set_default_font()` | 设置默认字体 |
| `GetCustomFontCount()` | `duilib_paint_manager_get_custom_font_count()` | 获取自定义字体数量 |
| `AddFont()` | `duilib_paint_manager_add_font()` | 添加字体 |
| `GetFont()` | `duilib_paint_manager_get_font()` | 获取字体 |
| `GetFontIndex()` | `duilib_paint_manager_get_font_index()` | 获取字体索引 |
| `RemoveFont()` | `duilib_paint_manager_remove_font()` | 删除字体 |
| `RemoveAllFonts()` | `duilib_paint_manager_remove_all_fonts()` | 删除所有字体 |
| `AddImage()` | `duilib_paint_manager_add_image()` | 添加图片 |
| `RemoveImage()` | `duilib_paint_manager_remove_image()` | 删除图片 |
| `RemoveAllImages()` | `duilib_paint_manager_remove_all_images()` | 删除所有图片 |
| `ReloadImages()` | `duilib_paint_manager_reload_images()` | 重载图片 |
| `AddDefaultAttributeList()` | `duilib_paint_manager_add_default_attribute_list()` | 添加默认属性列表 |
| `GetDefaultAttributeList()` | `duilib_paint_manager_get_default_attribute_list()` | 获取默认属性列表 |
| `RemoveDefaultAttributeList()` | `duilib_paint_manager_remove_default_attribute_list()` | 删除默认属性列表 |
| `AddWindowCustomAttribute()` | `duilib_paint_manager_add_window_custom_attribute()` | 添加窗口自定义属性 |
| `GetWindowCustomAttribute()` | `duilib_paint_manager_get_window_custom_attribute()` | 获取窗口自定义属性 |
| `RemoveWindowCustomAttribute()` | `duilib_paint_manager_remove_window_custom_attribute()` | 删除窗口自定义属性 |
| `GetWindowAttribute()` | `duilib_paint_manager_get_window_attribute()` | 获取窗口属性 |
| `SetWindowAttribute()` | `duilib_paint_manager_set_window_attribute()` | 设置窗口属性 |
| `GetWindowAttributeList()` | `duilib_paint_manager_get_window_attribute_list()` | 获取窗口属性列表 |
| `SetWindowAttributeList()` | `duilib_paint_manager_set_window_attribute_list()` | 设置窗口属性列表 |
| `AttachDialog()` | `duilib_paint_manager_attach_dialog()` | 附加对话框 |
| `InitControls()` | `duilib_paint_manager_init_controls()` | 初始化控件 |
| `RenameControl()` | `duilib_paint_manager_rename_control()` | 重命名控件 |
| `ReapObjects()` | `duilib_paint_manager_reap_objects()` | 回收对象 |
| `AddOptionGroup()` | `duilib_paint_manager_add_option_group()` | 添加选项组 |
| `RemoveOptionGroup()` | `duilib_paint_manager_remove_option_group()` | 删除选项组 |
| `RemoveAllOptionGroups()` | `duilib_paint_manager_remove_all_option_groups()` | 删除所有选项组 |
| `GetFocus()` | `duilib_paint_manager_get_focus()` | 获取焦点控件 |
| `SetFocus()` | `duilib_paint_manager_set_focus()` | 设置焦点 |
| `SetFocusNeeded()` | `duilib_paint_manager_set_focus_needed()` | 设置需要焦点 |
| `SetNextTabControl()` | `duilib_paint_manager_set_next_tab_control()` | 设置下一个Tab控件 |
| `SetTimer()` | `duilib_paint_manager_set_timer()` | 设置定时器 |
| `KillTimer(CControlUI*, UINT)` | `duilib_paint_manager_kill_timer()` | 删除定时器 |
| `KillTimer(CControlUI*)` | `duilib_paint_manager_kill_all_timers()` | 删除所有定时器 |
| `SetCapture()` | `duilib_paint_manager_set_capture()` | 设置鼠标捕获 |
| `ReleaseCapture()` | `duilib_paint_manager_release_capture()` | 释放鼠标捕获 |
| `IsCaptured()` | `duilib_paint_manager_is_captured()` | 是否捕获鼠标 |
| `IsPainting()` | `duilib_paint_manager_is_painting()` | 是否正在绘制 |
| `SetPainting()` | `duilib_paint_manager_set_painting()` | 设置绘制状态 |
| `GetPostPaintCount()` | `duilib_paint_manager_get_post_paint_count()` | 获取后绘制数量 |
| `AddPostPaint()` | `duilib_paint_manager_add_post_paint()` | 添加后绘制 |
| `RemovePostPaint()` | `duilib_paint_manager_remove_post_paint()` | 删除后绘制 |
| `SetPostPaintIndex()` | `duilib_paint_manager_set_post_paint_index()` | 设置后绘制索引 |
| `GetNativeWindowCount()` | `duilib_paint_manager_get_native_window_count()` | 获取本地窗口数量 |
| `GetNativeWindowRect()` | `duilib_paint_manager_get_native_window_rect()` | 获取本地窗口矩形 |
| `AddNativeWindow()` | `duilib_paint_manager_add_native_window()` | 添加本地窗口 |
| `RemoveNativeWindow()` | `duilib_paint_manager_remove_native_window()` | 删除本地窗口 |
| `AddDelayedCleanup()` | `duilib_paint_manager_add_delayed_cleanup()` | 添加延迟清理 |
| `AddMouseLeaveNeeded()` | `duilib_paint_manager_add_mouse_leave_needed()` | 添加鼠标离开需求 |
| `RemoveMouseLeaveNeeded()` | `duilib_paint_manager_remove_mouse_leave_needed()` | 删除鼠标离开需求 |
| `UsedVirtualWnd()` | `duilib_paint_manager_used_virtual_wnd()` | 使用虚拟窗口 |
| `GetWindowXML()` | `duilib_paint_manager_get_window_xml()` | 获取窗口XML |
| `FindControl(LPCTSTR)` | `duilib_find_control()` | 查找控件 |
| `FindControl(POINT)` | `duilib_find_control_at_point()` | 根据坐标查找控件 |
| `FindSubControlByClass(CControlUI*, LPCTSTR, int)` | `duilib_paint_manager_find_sub_control_by_class()` | 按类名查找子控件 |
| `FindSubControlByName(CControlUI*, LPCTSTR)` | `duilib_paint_manager_find_sub_control_by_name()` | 按名称查找子控件 |
| `FindSubControlByPoint(CControlUI*, POINT)` | `duilib_paint_manager_find_sub_control_by_point()` | 按坐标查找子控件 |
| `GetRoot()` | `duilib_get_root()` | 获取根控件 |
| `SendNotify(CControlUI*, LPCTSTR)` | `duilib_send_notify()` | 发送通知 |

#### CControlUI 基础控件方法对应 (115个方法)

| DuiLib C++ 方法 | C API 方法 | 功能描述 |
|-----------------|------------|----------|
| `GetName()` | `duilib_control_get_name()` | 获取控件名称 |
| `SetName()` | `duilib_control_set_name()` | 设置控件名称 |
| `GetClass()` | `duilib_control_get_class()` | 获取控件类名 |
| `GetText()` | `duilib_control_get_text()` | 获取文本 |
| `SetText()` | `duilib_control_set_text()` | 设置文本 |
| `GetPos()` | `duilib_control_get_pos()` | 获取位置 |
| `SetPos()` | `duilib_control_set_pos()` | 设置位置 |
| `GetRelativePos()` | `duilib_control_get_relative_pos()` | 获取相对位置 |
| `GetClientPos()` | `duilib_control_get_client_pos()` | 获取客户区位置 |
| `Move()` | `duilib_control_move()` | 移动控件 |
| `IsVisible()` | `duilib_control_is_visible()` | 是否可见 |
| `SetVisible()` | `duilib_control_set_visible()` | 设置可见性 |
| `SetInternVisible()` | `duilib_control_set_intern_visible()` | 设置内部可见性 |
| `IsEnabled()` | `duilib_control_is_enabled()` | 是否启用 |
| `SetEnabled()` | `duilib_control_set_enabled()` | 设置启用状态 |
| `IsMouseEnabled()` | `duilib_control_is_mouse_enabled()` | 鼠标是否启用 |
| `SetMouseEnabled()` | `duilib_control_set_mouse_enabled()` | 设置鼠标启用 |
| `IsKeyboardEnabled()` | `duilib_control_is_keyboard_enabled()` | 键盘是否启用 |
| `SetKeyboardEnabled()` | `duilib_control_set_keyboard_enabled()` | 设置键盘启用 |
| `IsFocused()` | `duilib_control_is_focused()` | 是否有焦点 |
| `SetFocus()` | `duilib_control_set_focus()` | 设置焦点 |
| `IsFloat()` | `duilib_control_is_float()` | 是否浮动 |
| `SetFloat()` | `duilib_control_set_float()` | 设置浮动 |
| `GetWidth()` | `duilib_control_get_width()` | 获取宽度 |
| `GetHeight()` | `duilib_control_get_height()` | 获取高度 |
| `GetX()` | `duilib_control_get_x()` | 获取X坐标 |
| `GetY()` | `duilib_control_get_y()` | 获取Y坐标 |
| `GetPadding()` | `duilib_control_get_padding()` | 获取边距 |
| `SetPadding()` | `duilib_control_set_padding()` | 设置边距 |
| `GetFixedXY()` | `duilib_control_get_fixed_xy()` | 获取固定XY |
| `SetFixedXY()` | `duilib_control_set_fixed_xy()` | 设置固定XY |
| `GetFixedWidth()` | `duilib_control_get_fixed_width()` | 获取固定宽度 |
| `SetFixedWidth()` | `duilib_control_set_fixed_width()` | 设置固定宽度 |
| `GetFixedHeight()` | `duilib_control_get_fixed_height()` | 获取固定高度 |
| `SetFixedHeight()` | `duilib_control_set_fixed_height()` | 设置固定高度 |
| `GetMinWidth()` | `duilib_control_get_min_width()` | 获取最小宽度 |
| `SetMinWidth()` | `duilib_control_set_min_width()` | 设置最小宽度 |
| `GetMinHeight()` | `duilib_control_get_min_height()` | 获取最小高度 |
| `SetMinHeight()` | `duilib_control_set_min_height()` | 设置最小高度 |
| `GetMaxWidth()` | `duilib_control_get_max_width()` | 获取最大宽度 |
| `SetMaxWidth()` | `duilib_control_set_max_width()` | 设置最大宽度 |
| `GetMaxHeight()` | `duilib_control_get_max_height()` | 获取最大高度 |
| `SetMaxHeight()` | `duilib_control_set_max_height()` | 设置最大高度 |
| `GetToolTip()` | `duilib_control_get_tooltip()` | 获取工具提示 |
| `SetToolTip()` | `duilib_control_set_tooltip()` | 设置工具提示 |
| `GetToolTipWidth()` | `duilib_control_get_tooltip_width()` | 获取工具提示宽度 |
| `SetToolTipWidth()` | `duilib_control_set_tooltip_width()` | 设置工具提示宽度 |
| `GetUserData()` | `duilib_control_get_user_data()` | 获取用户数据 |
| `SetUserData()` | `duilib_control_set_user_data()` | 设置用户数据 |
| `GetTag()` | `duilib_control_get_tag()` | 获取标签 |
| `SetTag()` | `duilib_control_set_tag()` | 设置标签 |
| `GetShortcut()` | `duilib_control_get_shortcut()` | 获取快捷键 |
| `SetShortcut()` | `duilib_control_set_shortcut()` | 设置快捷键 |
| `IsContextMenuUsed()` | `duilib_control_is_context_menu_used()` | 是否使用上下文菜单 |
| `SetContextMenuUsed()` | `duilib_control_set_context_menu_used()` | 设置使用上下文菜单 |
| `GetBkColor()` | `duilib_control_get_bk_color()` | 获取背景色 |
| `SetBkColor()` | `duilib_control_set_bk_color()` | 设置背景色 |
| `GetBkColor2()` | `duilib_control_get_bk_color2()` | 获取背景色2 |
| `SetBkColor2()` | `duilib_control_set_bk_color2()` | 设置背景色2 |
| `GetBkColor3()` | `duilib_control_get_bk_color3()` | 获取背景色3 |
| `SetBkColor3()` | `duilib_control_set_bk_color3()` | 设置背景色3 |
| `GetBkImage()` | `duilib_control_get_bk_image()` | 获取背景图片 |
| `SetBkImage()` | `duilib_control_set_bk_image()` | 设置背景图片 |
| `GetBorderColor()` | `duilib_control_get_border_color()` | 获取边框颜色 |
| `SetBorderColor()` | `duilib_control_set_border_color()` | 设置边框颜色 |
| `GetFocusBorderColor()` | `duilib_control_get_focus_border_color()` | 获取焦点边框颜色 |
| `SetFocusBorderColor()` | `duilib_control_set_focus_border_color()` | 设置焦点边框颜色 |
| `GetBorderSize()` | `duilib_control_get_border_size()` | 获取边框尺寸 |
| `SetBorderSize(RECT)` | `duilib_control_set_border_size_rect()` | 设置边框尺寸(矩形) |
| `SetBorderSize(int)` | `duilib_control_set_border_size()` | 设置边框尺寸(整数) |
| `GetBorderStyle()` | `duilib_control_get_border_style()` | 获取边框样式 |
| `SetBorderStyle()` | `duilib_control_set_border_style()` | 设置边框样式 |
| `GetBorderRound()` | `duilib_control_get_border_round()` | 获取边框圆角 |
| `SetBorderRound()` | `duilib_control_set_border_round()` | 设置边框圆角 |
| `IsColorHSL()` | `duilib_control_is_color_hsl()` | 是否HSL颜色 |
| `SetColorHSL()` | `duilib_control_set_color_hsl()` | 设置HSL颜色 |
| `GetParent()` | `duilib_control_get_parent()` | 获取父控件 |
| `GetCover()` | `duilib_control_get_cover()` | 获取覆盖控件 |
| `SetCover()` | `duilib_control_set_cover()` | 设置覆盖控件 |
| `GetNativeWindow()` | `duilib_control_get_native_window()` | 获取本地窗口 |
| `GetVirtualWnd()` | `duilib_control_get_virtual_wnd()` | 获取虚拟窗口 |
| `SetVirtualWnd()` | `duilib_control_set_virtual_wnd()` | 设置虚拟窗口 |
| `Activate()` | `duilib_control_activate()` | 激活控件 |
| `GetManager()` | `duilib_control_get_manager()` | 获取管理器 |
| `SetManager()` | `duilib_control_set_manager()` | 设置管理器 |
| `Invalidate()` | `duilib_control_invalidate()` | 无效化控件 |
| `IsUpdateNeeded()` | `duilib_control_is_update_needed()` | 是否需要更新 |
| `NeedUpdate()` | `duilib_control_need_update()` | 标记需要更新 |
| `NeedParentUpdate()` | `duilib_control_need_parent_update()` | 标记父控件需要更新 |
| `GetAdjustColor()` | `duilib_control_get_adjust_color()` | 获取调整颜色 |
| `Init()` | `duilib_control_init()` | 初始化控件 |
| `DoInit()` | `duilib_control_do_init()` | 执行初始化 |
| `GetAttribute()` | `duilib_control_get_attribute()` | 获取属性 |
| `SetAttribute()` | `duilib_control_set_attribute()` | 设置属性 |
| `GetAttributeList()` | `duilib_control_get_attribute_list()` | 获取属性列表 |
| `SetAttributeList()` | `duilib_control_set_attribute_list()` | 设置属性列表 |
| `EstimateSize()` | `duilib_control_estimate_size()` | 估算尺寸 |
| `GetFloatPercent()` | `duilib_control_get_float_percent()` | 获取浮动百分比 |
| `SetFloatPercent()` | `duilib_control_set_float_percent()` | 设置浮动百分比 |
| `AddCustomAttribute()` | `duilib_control_add_custom_attribute()` | 添加自定义属性 |
| `GetCustomAttribute()` | `duilib_control_get_custom_attribute()` | 获取自定义属性 |
| `RemoveCustomAttribute()` | `duilib_control_remove_custom_attribute()` | 删除自定义属性 |
| `RemoveAllCustomAttribute()` | `duilib_control_remove_all_custom_attributes()` | 删除所有自定义属性 |
| `Paint()` | `duilib_control_paint()` | 绘制控件 |
| `DoPaint()` | `duilib_control_do_paint()` | 执行绘制 |
| `PaintBkColor()` | `duilib_control_paint_bk_color()` | 绘制背景色 |
| `PaintBkImage()` | `duilib_control_paint_bk_image()` | 绘制背景图片 |
| `PaintStatusImage()` | `duilib_control_paint_status_image()` | 绘制状态图片 |
| `PaintText()` | `duilib_control_paint_text()` | 绘制文本 |
| `PaintBorder()` | `duilib_control_paint_border()` | 绘制边框 |
| `DoPostPaint()` | `duilib_control_do_post_paint()` | 执行后绘制 |
| `DrawImage()` | `duilib_control_draw_image()` | 绘制图片 |

#### CContainerUI 容器方法对应 (52个方法)

| DuiLib C++ 方法 | C API 方法 | 功能描述 |
|-----------------|------------|----------|
| `GetItemAt()` | `duilib_container_get_item_at()` | 获取指定索引项 |
| `GetItemIndex()` | `duilib_container_get_item_index()` | 获取项索引 |
| `SetItemIndex()` | `duilib_container_set_item_index()` | 设置项索引 |
| `SetMultiItemIndex()` | `duilib_container_set_multi_item_index()` | 设置多项索引 |
| `GetCount()` | `duilib_container_get_count()` | 获取项数量 |
| `Add()` | `duilib_container_add()` | 添加子控件 |
| `AddAt()` | `duilib_container_add_at()` | 在指定位置添加 |
| `Remove()` | `duilib_container_remove()` | 删除子控件 |
| `RemoveAt()` | `duilib_container_remove_at()` | 删除指定位置项 |
| `RemoveAll()` | `duilib_container_remove_all()` | 删除所有项 |
| `GetInset()` | `duilib_container_get_inset()` | 获取内边距 |
| `SetInset()` | `duilib_container_set_inset()` | 设置内边距 |
| `GetChildPadding()` | `duilib_container_get_child_padding()` | 获取子控件间距 |
| `SetChildPadding()` | `duilib_container_set_child_padding()` | 设置子控件间距 |
| *(省略其他38个方法...)*| | |

#### CButtonUI 按钮方法对应 (26个方法)

| DuiLib C++ 方法 | C API 方法 | 功能描述 |
|-----------------|------------|----------|
| `Activate()` | `duilib_button_activate()` | 激活按钮 |
| `GetNormalImage()` | `duilib_button_get_normal_image()` | 获取正常状态图片 |
| `SetNormalImage()` | `duilib_button_set_normal_image()` | 设置正常状态图片 |
| `GetHotImage()` | `duilib_button_get_hot_image()` | 获取热点状态图片 |
| `SetHotImage()` | `duilib_button_set_hot_image()` | 设置热点状态图片 |
| `GetPushedImage()` | `duilib_button_get_pushed_image()` | 获取按下状态图片 |
| `SetPushedImage()` | `duilib_button_set_pushed_image()` | 设置按下状态图片 |
| `GetFocusedImage()` | `duilib_button_get_focused_image()` | 获取焦点状态图片 |
| `SetFocusedImage()` | `duilib_button_set_focused_image()` | 设置焦点状态图片 |
| `GetDisabledImage()` | `duilib_button_get_disabled_image()` | 获取禁用状态图片 |
| `SetDisabledImage()` | `duilib_button_set_disabled_image()` | 设置禁用状态图片 |
| `GetForeImage()` | `duilib_button_get_fore_image()` | 获取前景图片 |
| `SetForeImage()` | `duilib_button_set_fore_image()` | 设置前景图片 |
| `GetHotForeImage()` | `duilib_button_get_hot_fore_image()` | 获取热点前景图片 |
| `SetHotForeImage()` | `duilib_button_set_hot_fore_image()` | 设置热点前景图片 |
| `SetFiveStatusImage()` | `duilib_button_set_five_status_image()` | 设置五状态图片 |
| `SetFadeAlphaDelta()` | `duilib_button_set_fade_alpha_delta()` | 设置淡化透明度增量 |
| `GetFadeAlphaDelta()` | `duilib_button_get_fade_alpha_delta()` | 获取淡化透明度增量 |
| `SetHotBkColor()` | `duilib_button_set_hot_bk_color()` | 设置热点背景色 |
| `GetHotBkColor()` | `duilib_button_get_hot_bk_color()` | 获取热点背景色 |
| `SetHotTextColor()` | `duilib_button_set_hot_text_color()` | 设置热点文本色 |
| `GetHotTextColor()` | `duilib_button_get_hot_text_color()` | 获取热点文本色 |
| `SetPushedTextColor()` | `duilib_button_set_pushed_text_color()` | 设置按下文本色 |
| `GetPushedTextColor()` | `duilib_button_get_pushed_text_color()` | 获取按下文本色 |
| `SetFocusedTextColor()` | `duilib_button_set_focused_text_color()` | 设置焦点文本色 |
| `GetFocusedTextColor()` | `duilib_button_get_focused_text_color()` | 获取焦点文本色 |

#### CEditUI 编辑框方法对应 (27个方法)

| DuiLib C++ 方法 | C API 方法 | 功能描述 |
|-----------------|------------|----------|
| `SetMaxChar()` | `duilib_edit_set_max_char()` | 设置最大字符数 |
| `GetMaxChar()` | `duilib_edit_get_max_char()` | 获取最大字符数 |
| `SetReadOnly()` | `duilib_edit_set_readonly()` | 设置只读 |
| `IsReadOnly()` | `duilib_edit_is_readonly()` | 是否只读 |
| `SetPasswordMode()` | `duilib_edit_set_password_mode()` | 设置密码模式 |
| `IsPasswordMode()` | `duilib_edit_is_password_mode()` | 是否密码模式 |
| `SetPasswordChar()` | `duilib_edit_set_password_char()` | 设置密码字符 |
| `GetPasswordChar()` | `duilib_edit_get_password_char()` | 获取密码字符 |
| `SetNumberOnly()` | `duilib_edit_set_number_only()` | 设置只能输入数字 |
| `IsNumberOnly()` | `duilib_edit_is_number_only()` | 是否只能输入数字 |
| `SetAutoSelAll()` | `duilib_edit_set_auto_sel_all()` | 设置自动全选 |
| `IsAutoSelAll()` | `duilib_edit_is_auto_sel_all()` | 是否自动全选 |
| `SetSel()` | `duilib_edit_set_sel()` | 设置选择范围 |
| `SetSelAll()` | `duilib_edit_set_sel_all()` | 全选 |
| `SetReplaceSel()` | `duilib_edit_replace_sel()` | 替换选择内容 |
| `GetNormalImage()` | `duilib_edit_get_normal_image()` | 获取正常状态图片 |
| `SetNormalImage()` | `duilib_edit_set_normal_image()` | 设置正常状态图片 |
| `GetHotImage()` | `duilib_edit_get_hot_image()` | 获取热点状态图片 |
| `SetHotImage()` | `duilib_edit_set_hot_image()` | 设置热点状态图片 |
| `GetFocusedImage()` | `duilib_edit_get_focused_image()` | 获取焦点状态图片 |
| `SetFocusedImage()` | `duilib_edit_set_focused_image()` | 设置焦点状态图片 |
| `GetDisabledImage()` | `duilib_edit_get_disabled_image()` | 获取禁用状态图片 |
| `SetDisabledImage()` | `duilib_edit_set_disabled_image()` | 设置禁用状态图片 |
| `SetNativeEditBkColor()` | `duilib_edit_set_native_bk_color()` | 设置原生编辑框背景色 |
| `GetNativeEditBkColor()` | `duilib_edit_get_native_bk_color()` | 获取原生编辑框背景色 |
| `GetWindowStyls()` | `duilib_edit_get_window_styles()` | 获取窗口样式 |
| `GetNativeEditHWND()` | `duilib_edit_get_native_hwnd()` | 获取原生编辑框句柄 |

#### CLabelUI 标签方法对应 (38个方法)

| DuiLib C++ 方法 | C API 方法 | 功能描述 |
|-----------------|------------|----------|
| `SetTextStyle()` | `duilib_label_set_text_style()` | 设置文本样式 |
| `GetTextStyle()` | `duilib_label_get_text_style()` | 获取文本样式 |
| `IsMultiLine()` | `duilib_label_is_multiline()` | 是否多行 |
| `SetMultiLine()` | `duilib_label_set_multiline()` | 设置多行 |
| `SetTextColor()` | `duilib_label_set_text_color()` | 设置文本颜色 |
| `GetTextColor()` | `duilib_label_get_text_color()` | 获取文本颜色 |
| `SetDisabledTextColor()` | `duilib_label_set_disabled_text_color()` | 设置禁用文本颜色 |
| `GetDisabledTextColor()` | `duilib_label_get_disabled_text_color()` | 获取禁用文本颜色 |
| `SetFont()` | `duilib_label_set_font()` | 设置字体 |
| `GetFont()` | `duilib_label_get_font()` | 获取字体 |
| `GetTextPadding()` | `duilib_label_get_text_padding()` | 获取文本边距 |
| `SetTextPadding()` | `duilib_label_set_text_padding()` | 设置文本边距 |
| `IsShowHtml()` | `duilib_label_is_show_html()` | 是否显示HTML |
| `SetShowHtml()` | `duilib_label_set_show_html()` | 设置显示HTML |
| `SetEnabledEffect()` | `duilib_label_set_enabled_effect()` | 设置启用特效 |
| `GetEnabledEffect()` | `duilib_label_get_enabled_effect()` | 获取启用特效 |
| `SetEnabledLuminous()` | `duilib_label_set_enabled_luminous()` | 设置启用发光 |
| `GetEnabledLuminous()` | `duilib_label_get_enabled_luminous()` | 获取启用发光 |
| `SetLuminousFuzzy()` | `duilib_label_set_luminous_fuzzy()` | 设置发光模糊度 |
| `GetLuminousFuzzy()` | `duilib_label_get_luminous_fuzzy()` | 获取发光模糊度 |
| `SetGradientLength()` | `duilib_label_set_gradient_length()` | 设置渐变长度 |
| `GetGradientLength()` | `duilib_label_get_gradient_length()` | 获取渐变长度 |
| `SetGradientAngle()` | `duilib_label_set_gradient_angle()` | 设置渐变角度 |
| `GetGradientAngle()` | `duilib_label_get_gradient_angle()` | 获取渐变角度 |
| `SetShadowOffset()` | `duilib_label_set_shadow_offset()` | 设置阴影偏移 |
| `GetShadowOffset()` | `duilib_label_get_shadow_offset()` | 获取阴影偏移 |
| `SetTextColor1()` | `duilib_label_set_text_color1()` | 设置文本颜色1 |
| `GetTextColor1()` | `duilib_label_get_text_color1()` | 获取文本颜色1 |
| `SetTextShadowColorA()` | `duilib_label_set_text_shadow_color_a()` | 设置文本阴影颜色A |
| `GetTextShadowColorA()` | `duilib_label_get_text_shadow_color_a()` | 获取文本阴影颜色A |
| `SetTextShadowColorB()` | `duilib_label_set_text_shadow_color_b()` | 设置文本阴影颜色B |
| `GetTextShadowColorB()` | `duilib_label_get_text_shadow_color_b()` | 获取文本阴影颜色B |
| `SetStrokeColor()` | `duilib_label_set_stroke_color()` | 设置描边颜色 |
| `GetStrokeColor()` | `duilib_label_get_stroke_color()` | 获取描边颜色 |
| `SetEnabledStroke()` | `duilib_label_set_enabled_stroke()` | 设置启用描边 |
| `GetEnabledStroke()` | `duilib_label_get_enabled_stroke()` | 获取启用描边 |
| `SetEnabledShadow()` | `duilib_label_set_enabled_shadow()` | 设置启用阴影 |
| `GetEnabledShadow()` | `duilib_label_get_enabled_shadow()` | 获取启用阴影 |

## 📋 函数命名规范和设计模式

### 🎯 命名规范
所有API函数都遵循统一的命名模式：
```
duilib_[模块名]_[操作动词]_[对象/属性]
```

### 📊 操作类型分布
- **设置类操作 (set)：** 约280个函数 (40%)
- **获取类操作 (get)：** 约250个函数 (36%)
- **判断类操作 (is)：** 约80个函数 (11%)
- **动作类操作：** 约90个函数 (13%)

### 2. 简化的主要控件对应关系

#### Control模块主要控件 (300个函数总计)

**常用控件API示例：**

| 控件类型 | 主要API函数示例 | 功能说明 |
|----------|-----------------|----------|
| **Button (26函数)** | `duilib_button_set_normal_image()` | 设置按钮各状态图片 |
| **Edit (27函数)** | `duilib_edit_set_password_mode()` | 密码输入和文本验证 |
| **Label (38函数)** | `duilib_label_set_text_style()` | 丰富文本格式和效果 |
| **CheckBox (2函数)** | `duilib_checkbox_set_check()` | 简单的选中状态控制 |
| **Option (23函数)** | `duilib_option_set_group()` | 单选按钮分组管理 |
| **Progress (11函数)** | `duilib_progress_set_value()` | 进度显示和控制 |
| **Slider (18函数)** | `duilib_slider_set_thumb_image()` | 滑块外观和行为 |
| **TreeView (26函数)** | `duilib_treeview_expand_item()` | 树形数据展示 |
| **List (11函数)** | `duilib_list_get_cur_sel()` | 列表选择和滚动 |
| **Combo (24函数)** | `duilib_combo_select_item()` | 下拉选择功能 |

### 3. Layout和Utils模块对应

#### Layout模块 (21个函数)

| 布局类型 | API函数示例 | 功能说明 |
|----------|-------------|----------|
| **VerticalLayout (5函数)** | `duilib_vertical_layout_set_sep_height()` | 垂直排列，设置分隔高度 |
| **HorizontalLayout (5函数)** | `duilib_horizontal_layout_set_sep_width()` | 水平排列，设置分隔宽度 |
| **TabLayout (3函数)** | `duilib_tab_layout_select_item()` | 标签页切换 |
| **TileLayout (4函数)** | `duilib_tile_layout_set_columns()` | 瓦片布局，设置列数 |
| **ChildLayout (4函数)** | `duilib_child_layout_set_xml_file()` | 子窗口布局 |

#### Utils模块 (39个函数)

| 工具类 | API函数示例 | 功能说明 |
|--------|-------------|----------|
| **Utils (13函数)** | `duilib_set_resource_path()` | 资源路径和文件管理 |
| **WndShadow (16函数)** | `duilib_wndshadow_set_size()` | 窗口阴影效果配置 |
| **WinImpl (6函数)** | `duilib_window_create()` | 窗口创建和管理 |
| **Delegate (4函数)** | `duilib_add_notify_handler()` | 事件处理和委托 |

## 🚀 版本信息

- **当前版本**: 5.0.0 (模块化重构版)
- **发布日期**: 2025-08
- **API 总数**: 700个函数
- **架构**: 模块化设计 (Core/Control/Layout/Utils)
- **对应完整度**: 100% (与原生DuiLib 1:1对应)
- **文件组织**: 68个文件 (34个头文件 + 34个实现文件)

## 💡 使用示例

### 基础窗口创建

```c
#include "duilib_c.h"  // 包含所有模块

int main() {
    // 初始化库 (core/duilib_c_base)
    duilib_init();
    
    // 设置资源路径 (utils/duilib_c_utils)
    duilib_set_resource_path("./skin");
    
    // 创建管理器 (core/duilib_c_manager)
    duilib_manager_t manager = duilib_create_manager(hwnd, "MainWindow");
    
    // 创建按钮 (control/duilib_c_button)
    duilib_control_t button = duilib_create_control("Button");
    duilib_control_set_text(button, "点击我");  // core/duilib_c_control
    duilib_button_set_normal_image(button, "button_normal.png");
    
    // 添加到垂直布局 (layout/duilib_c_vertical_layout)
    duilib_control_t layout = duilib_create_control("VerticalLayout");
    duilib_container_add(layout, button);  // core/duilib_c_container
    
    // 设置为根控件
    duilib_set_root(manager, layout);
    
    // 运行消息循环
    return duilib_message_loop();
}
```

### 模块化使用

```c
// 只包含需要的模块
#include "core/duilib_c_manager.h"
#include "control/duilib_c_button.h"
#include "layout/duilib_c_vertical_layout.h"
#include "utils/duilib_c_utils.h"
```

## ⚠️ 注意事项

1. **内存管理**：所有控件由DuiLib内部管理，无需手动释放
2. **线程安全**：API调用应在UI线程中执行
3. **字符编码**：所有字符串参数使用UTF-8编码
4. **错误处理**：检查返回值，使用`duilib_result_t`枚举
5. **方法对应**：所有C++方法都有对应的C API函数

## 🔄 模块化重构亮点

### 架构优势
1. **清晰的模块分离**：每个模块职责单一，便于维护和理解
2. **按需包含**：可以只包含需要的模块头文件，减少编译时间
3. **1:1目录对应**：与原生DuiLib目录结构完全一致
4. **标准C命名**：遵循C语言函数命名规范

### 构建系统
- 使用CMake管理所有68个文件
- 支持静态库和动态库构建
- 模块化安装规则，头文件按目录分类安装

### 兼容性
- 向后兼容旧版API
- 主头文件`duilib_c.h`包含所有模块
- 保持原有的C ABI稳定性

---

**DuiLib C API v5.0 - 模块化架构，700个函数，完整1:1对应！** 🎉