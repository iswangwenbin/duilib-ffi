#ifndef __DUILIB_C_CONTROL_H__
#define __DUILIB_C_CONTROL_H__

#include "duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 控件查找API
//=============================================================================

// 通过名称查找控件
DUILIB_C_API duilib_control_t duilib_find_control(duilib_manager_t manager, const char* name);

// 通过类名查找控件
DUILIB_C_API duilib_control_t duilib_find_control_by_class(duilib_manager_t manager, const char* class_name);

// 通过坐标查找控件
DUILIB_C_API duilib_control_t duilib_find_control_at_point(duilib_manager_t manager, int x, int y);

//=============================================================================
// 控件属性API
//=============================================================================

// 获取控件名称
DUILIB_C_API const char* duilib_control_get_name(duilib_control_t control);

// 设置控件名称
DUILIB_C_API duilib_result_t duilib_control_set_name(duilib_control_t control, const char* name);

// 获取控件文本
DUILIB_C_API const char* duilib_control_get_text(duilib_control_t control);

// 设置控件文本
DUILIB_C_API duilib_result_t duilib_control_set_text(duilib_control_t control, const char* text);

// 获取控件位置
DUILIB_C_API duilib_rect_t duilib_control_get_pos(duilib_control_t control);

// 设置控件位置
DUILIB_C_API duilib_result_t duilib_control_set_pos(duilib_control_t control, duilib_rect_t rect);

// 获取控件可见性
DUILIB_C_API bool duilib_control_is_visible(duilib_control_t control);

// 设置控件可见性
DUILIB_C_API duilib_result_t duilib_control_set_visible(duilib_control_t control, bool visible);

// 获取控件启用状态
DUILIB_C_API bool duilib_control_is_enabled(duilib_control_t control);

// 设置控件启用状态
DUILIB_C_API duilib_result_t duilib_control_set_enabled(duilib_control_t control, bool enabled);

// 获取控件宽高
DUILIB_C_API int duilib_control_get_width(duilib_control_t control);
DUILIB_C_API int duilib_control_get_height(duilib_control_t control);

// 获取控件坐标
DUILIB_C_API int duilib_control_get_x(duilib_control_t control);
DUILIB_C_API int duilib_control_get_y(duilib_control_t control);

// 获取设置内边距
DUILIB_C_API duilib_rect_t duilib_control_get_padding(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_padding(duilib_control_t control, duilib_rect_t padding);

// 工具提示
DUILIB_C_API const char* duilib_control_get_tooltip(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_tooltip(duilib_control_t control, const char* tooltip);

// 用户数据
DUILIB_C_API const char* duilib_control_get_user_data(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_user_data(duilib_control_t control, const char* user_data);

// 标签指针
DUILIB_C_API uintptr_t duilib_control_get_tag(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_tag(duilib_control_t control, uintptr_t tag);

//=============================================================================
// 控件样式API
//=============================================================================

// 设置背景色
DUILIB_C_API duilib_result_t duilib_control_set_bk_color(duilib_control_t control, duilib_color_t color);

// 设置背景图片
DUILIB_C_API duilib_result_t duilib_control_set_bk_image(duilib_control_t control, const char* image_path);

// 设置边框色
DUILIB_C_API duilib_result_t duilib_control_set_border_color(duilib_control_t control, duilib_color_t color);

// 设置边框大小
DUILIB_C_API duilib_result_t duilib_control_set_border_size(duilib_control_t control, int size);
DUILIB_C_API duilib_result_t duilib_control_set_border_size_rect(duilib_control_t control, duilib_rect_t rect);
DUILIB_C_API duilib_rect_t duilib_control_get_border_size(duilib_control_t control);

//=============================================================================
// 通用属性API
//=============================================================================

// 设置控件属性（对应duilib的SetAttribute）
DUILIB_C_API duilib_result_t duilib_control_set_attribute(duilib_control_t control, const char* name, const char* value);
DUILIB_C_API const char* duilib_control_get_attribute(duilib_control_t control, const char* name);

// 获取控件类名
DUILIB_C_API const char* duilib_control_get_class(duilib_control_t control);

// 控件状态
DUILIB_C_API bool duilib_control_is_focused(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_focus(duilib_control_t control);
DUILIB_C_API bool duilib_control_is_float(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_float(duilib_control_t control, bool is_float);

// 控件管理
DUILIB_C_API duilib_control_t duilib_control_get_parent(duilib_control_t control);

// 控件尺寸
DUILIB_C_API int duilib_control_get_fixed_width(duilib_control_t control);
DUILIB_C_API int duilib_control_get_fixed_height(duilib_control_t control);
DUILIB_C_API int duilib_control_get_min_width(duilib_control_t control);
DUILIB_C_API int duilib_control_get_min_height(duilib_control_t control);
DUILIB_C_API int duilib_control_get_max_width(duilib_control_t control);
DUILIB_C_API int duilib_control_get_max_height(duilib_control_t control);

// 颜色属性
DUILIB_C_API duilib_color_t duilib_control_get_bk_color(duilib_control_t control);
DUILIB_C_API duilib_color_t duilib_control_get_bk_color2(duilib_control_t control);
DUILIB_C_API duilib_color_t duilib_control_get_bk_color3(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_bk_color2(duilib_control_t control, duilib_color_t color);
DUILIB_C_API duilib_result_t duilib_control_set_bk_color3(duilib_control_t control, duilib_color_t color);
DUILIB_C_API const char* duilib_control_get_bk_image(duilib_control_t control);
DUILIB_C_API duilib_color_t duilib_control_get_border_color(duilib_control_t control);
DUILIB_C_API duilib_color_t duilib_control_get_focus_border_color(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_focus_border_color(duilib_control_t control, duilib_color_t color);

// 鼠标和键盘支持
DUILIB_C_API bool duilib_control_is_mouse_enabled(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_mouse_enabled(duilib_control_t control, bool enabled);
DUILIB_C_API bool duilib_control_is_keyboard_enabled(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_keyboard_enabled(duilib_control_t control, bool enabled);

// 快捷键和右键菜单
DUILIB_C_API char duilib_control_get_shortcut(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_shortcut(duilib_control_t control, char shortcut);
DUILIB_C_API bool duilib_control_is_context_menu_used(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_context_menu_used(duilib_control_t control, bool used);

// 控件更新
DUILIB_C_API duilib_result_t duilib_control_invalidate(duilib_control_t control);
DUILIB_C_API bool duilib_control_is_update_needed(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_need_update(duilib_control_t control);

// 工具提示宽度
DUILIB_C_API int duilib_control_get_tooltip_width(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_tooltip_width(duilib_control_t control, int width);

// 控件位置和尺寸扩展
DUILIB_C_API duilib_size_t duilib_control_get_fixed_xy(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_fixed_xy(duilib_control_t control, duilib_size_t xy);
DUILIB_C_API duilib_rect_t duilib_control_get_relative_pos(duilib_control_t control);
DUILIB_C_API duilib_rect_t duilib_control_get_client_pos(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_move(duilib_control_t control, duilib_size_t offset);

// 覆盖控件
DUILIB_C_API duilib_control_t duilib_control_get_cover(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_cover(duilib_control_t control, duilib_control_t cover);

// 原生窗口
DUILIB_C_API void* duilib_control_get_native_window(duilib_control_t control);

// 边框圆角
DUILIB_C_API duilib_size_t duilib_control_get_border_round(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_border_round(duilib_control_t control, duilib_size_t round);

// 边框样式
DUILIB_C_API int duilib_control_get_border_style(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_border_style(duilib_control_t control, int style);

// 控件尺寸估算
DUILIB_C_API duilib_size_t duilib_control_estimate_size(duilib_control_t control, duilib_size_t available);

// 自定义属性管理
DUILIB_C_API duilib_result_t duilib_control_add_custom_attribute(duilib_control_t control, const char* name, const char* value);
DUILIB_C_API const char* duilib_control_get_custom_attribute(duilib_control_t control, const char* name);
DUILIB_C_API duilib_result_t duilib_control_remove_custom_attribute(duilib_control_t control, const char* name);
DUILIB_C_API duilib_result_t duilib_control_remove_all_custom_attributes(duilib_control_t control);

// 颜色HSL支持
DUILIB_C_API bool duilib_control_is_color_hsl(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_color_hsl(duilib_control_t control, bool hsl);

// 虚拟窗口支持
DUILIB_C_API const char* duilib_control_get_virtual_wnd(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_virtual_wnd(duilib_control_t control, const char* virtual_wnd);

// 控件激活
DUILIB_C_API bool duilib_control_activate(duilib_control_t control);

// 控件初始化
DUILIB_C_API duilib_result_t duilib_control_init(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_do_init(duilib_control_t control);

// 属性列表操作
DUILIB_C_API const char* duilib_control_get_attribute_list(duilib_control_t control, bool ignore_default);
DUILIB_C_API duilib_result_t duilib_control_set_attribute_list(duilib_control_t control, const char* attr_list);

//=============================================================================
// CControlUI 缺失方法补充
//=============================================================================

// 管理器相关
DUILIB_C_API duilib_manager_t duilib_control_get_manager(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_manager(duilib_control_t control, duilib_manager_t manager, duilib_control_t parent, bool init);

// 内部可见性和更新
DUILIB_C_API duilib_result_t duilib_control_set_intern_visible(duilib_control_t control, bool visible);
DUILIB_C_API duilib_result_t duilib_control_need_parent_update(duilib_control_t control);
DUILIB_C_API uint32_t duilib_control_get_adjust_color(duilib_control_t control, uint32_t color);

// 浮动百分比
DUILIB_C_API duilib_float_percent_t duilib_control_get_float_percent(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_float_percent(duilib_control_t control, duilib_float_percent_t percent);

// 绘制相关方法
DUILIB_C_API duilib_result_t duilib_control_paint(duilib_control_t control, void* hdc, duilib_rect_t paint_rect, duilib_control_t stop_control);
DUILIB_C_API duilib_result_t duilib_control_do_paint(duilib_control_t control, void* hdc, duilib_rect_t paint_rect, duilib_control_t stop_control);
DUILIB_C_API duilib_result_t duilib_control_paint_bk_color(duilib_control_t control, void* hdc);
DUILIB_C_API duilib_result_t duilib_control_paint_bk_image(duilib_control_t control, void* hdc);
DUILIB_C_API duilib_result_t duilib_control_paint_status_image(duilib_control_t control, void* hdc);
DUILIB_C_API duilib_result_t duilib_control_paint_text(duilib_control_t control, void* hdc);
DUILIB_C_API duilib_result_t duilib_control_paint_border(duilib_control_t control, void* hdc);
DUILIB_C_API duilib_result_t duilib_control_do_post_paint(duilib_control_t control, void* hdc, duilib_rect_t paint_rect);
DUILIB_C_API duilib_result_t duilib_control_draw_image(duilib_control_t control, void* hdc, const char* image_name);

// 布局属性设置
DUILIB_C_API duilib_result_t duilib_control_set_fixed_width(duilib_control_t control, int width);
DUILIB_C_API duilib_result_t duilib_control_set_fixed_height(duilib_control_t control, int height);
DUILIB_C_API duilib_result_t duilib_control_set_min_width(duilib_control_t control, int min_width);
DUILIB_C_API duilib_result_t duilib_control_set_min_height(duilib_control_t control, int min_height);
DUILIB_C_API duilib_result_t duilib_control_set_max_width(duilib_control_t control, int max_width);
DUILIB_C_API duilib_result_t duilib_control_set_max_height(duilib_control_t control, int max_height);

//=============================================================================
// CControlUI 缺失方法补充
//=============================================================================

// 控件查找回调函数类型 - 对应 FINDCONTROLPROC
typedef duilib_control_t (*duilib_find_control_proc_t)(duilib_control_t control, void* data);

// 事件处理结构体
typedef struct {
    int type;                    // 事件类型 - 对应 EVENTTYPE_UI
    duilib_control_t sender;     // 发送控件
    uint32_t timestamp;          // 时间戳
    duilib_point_t mouse;        // 鼠标位置
    int key;                     // 按键
    uint16_t key_state;          // 按键状态
    uintptr_t wparam;            // WPARAM
    intptr_t lparam;             // LPARAM
} duilib_ui_event_t;

// 高级事件处理
DUILIB_C_API duilib_result_t duilib_control_event(duilib_control_t control, const duilib_ui_event_t* event);
DUILIB_C_API duilib_result_t duilib_control_do_event(duilib_control_t control, const duilib_ui_event_t* event);

// 控件查找功能
DUILIB_C_API duilib_control_t duilib_control_find_control(duilib_control_t control, duilib_find_control_proc_t proc, void* data, uint32_t flags);

// 接口获取
DUILIB_C_API void* duilib_control_get_interface(duilib_control_t control, const char* name);
DUILIB_C_API uint32_t duilib_control_get_control_flags(duilib_control_t control);

// 删除方法
DUILIB_C_API duilib_result_t duilib_control_delete(duilib_control_t control);

// 事件源支持 - 对应原生的事件源
typedef void (*duilib_event_source_callback_t)(duilib_control_t sender, void* user_data);

DUILIB_C_API duilib_result_t duilib_control_on_init_add_handler(duilib_control_t control, duilib_event_source_callback_t callback, void* user_data);
DUILIB_C_API duilib_result_t duilib_control_on_destroy_add_handler(duilib_control_t control, duilib_event_source_callback_t callback, void* user_data);
DUILIB_C_API duilib_result_t duilib_control_on_size_add_handler(duilib_control_t control, duilib_event_source_callback_t callback, void* user_data);
DUILIB_C_API duilib_result_t duilib_control_on_event_add_handler(duilib_control_t control, duilib_event_source_callback_t callback, void* user_data);
DUILIB_C_API duilib_result_t duilib_control_on_notify_add_handler(duilib_control_t control, duilib_event_source_callback_t callback, void* user_data);
DUILIB_C_API duilib_result_t duilib_control_on_paint_add_handler(duilib_control_t control, duilib_event_source_callback_t callback, void* user_data);
DUILIB_C_API duilib_result_t duilib_control_on_post_paint_add_handler(duilib_control_t control, duilib_event_source_callback_t callback, void* user_data);

// 事件源移除处理器
DUILIB_C_API duilib_result_t duilib_control_on_init_remove_handler(duilib_control_t control, duilib_event_source_callback_t callback);
DUILIB_C_API duilib_result_t duilib_control_on_destroy_remove_handler(duilib_control_t control, duilib_event_source_callback_t callback);
DUILIB_C_API duilib_result_t duilib_control_on_size_remove_handler(duilib_control_t control, duilib_event_source_callback_t callback);
DUILIB_C_API duilib_result_t duilib_control_on_event_remove_handler(duilib_control_t control, duilib_event_source_callback_t callback);
DUILIB_C_API duilib_result_t duilib_control_on_notify_remove_handler(duilib_control_t control, duilib_event_source_callback_t callback);
DUILIB_C_API duilib_result_t duilib_control_on_paint_remove_handler(duilib_control_t control, duilib_event_source_callback_t callback);
DUILIB_C_API duilib_result_t duilib_control_on_post_paint_remove_handler(duilib_control_t control, duilib_event_source_callback_t callback);

//=============================================================================
// CControlUI 剩余缺失方法补充 - 完整1:1对应
//=============================================================================

// 绘制信息结构 - 对应 TDrawInfo
typedef struct {
    char draw_string[512];   // 绘制字符串
    char image_name[256];    // 图像名称
    bool loaded;             // 是否已加载
    const duilib_image_info_t* image_info; // 图像信息
    duilib_rect_t dest_offset;  // 目标偏移
    duilib_rect_t bmp_part;     // 位图部分
    duilib_rect_t scale9;       // 九宫格缩放
    uint8_t fade;              // 淡入淡出
    bool hole;                 // 镂空
    bool tiled_x;              // X方向平铺
    bool tiled_y;              // Y方向平铺
} duilib_draw_info_t;

// TDrawInfo相关方法
DUILIB_C_API duilib_result_t duilib_draw_info_clear(duilib_draw_info_t* draw_info);
DUILIB_C_API duilib_result_t duilib_draw_info_init(duilib_draw_info_t* draw_info, const char* draw_string);

// 控件绘制信息获取
DUILIB_C_API duilib_result_t duilib_control_get_background_draw_info(duilib_control_t control, duilib_draw_info_t* draw_info);
DUILIB_C_API duilib_result_t duilib_control_get_foreground_draw_info(duilib_control_t control, duilib_draw_info_t* draw_info);

// 高级绘制方法 - 对应DrawImage的TDrawInfo版本
DUILIB_C_API bool duilib_control_draw_image_with_draw_info(duilib_control_t control, void* hdc, duilib_draw_info_t* draw_info);

// 异步通知支持
DUILIB_C_API bool duilib_control_is_async_notify(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_async_notify(duilib_control_t control, bool async);

// 位置设置标志 - 防止SetPos循环调用
DUILIB_C_API bool duilib_control_is_set_pos(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_set_pos(duilib_control_t control, bool set_pos);

// 控件的绘制区域
DUILIB_C_API duilib_rect_t duilib_control_get_paint_rect(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_paint_rect(duilib_control_t control, duilib_rect_t rect);

// operator重载对应的方法
DUILIB_C_API bool duilib_control_equals(duilib_control_t control1, duilib_control_t control2);

// 控件状态的完整支持
DUILIB_C_API bool duilib_control_is_internal_visible(duilib_control_t control);

// 前景绘制相关
DUILIB_C_API const char* duilib_control_get_foreground_image(duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_control_set_foreground_image(duilib_control_t control, const char* image);

// 控件完整性验证方法
DUILIB_C_API bool duilib_control_is_valid(duilib_control_t control);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_CONTROL_H__