#ifndef __DUILIB_C_MANAGER_H__
#define __DUILIB_C_MANAGER_H__

#include "duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 核心管理器API
//=============================================================================

// 创建并初始化窗口管理器
DUILIB_C_API duilib_manager_t duilib_paint_manager_init(HWND hwnd, const char* name);

// 销毁窗口管理器
DUILIB_C_API void duilib_destroy_manager(duilib_manager_t manager);

// 从XML文件加载界面
DUILIB_C_API duilib_result_t duilib_load_layout(duilib_manager_t manager, const char* xml_file);

// 从XML字符串加载界面
DUILIB_C_API duilib_result_t duilib_load_layout_from_string(duilib_manager_t manager, const char* xml_string);

// 获取根控件
DUILIB_C_API duilib_control_t duilib_get_root(duilib_manager_t manager);

//=============================================================================
// 事件处理API
//=============================================================================

// 设置事件回调
DUILIB_C_API duilib_result_t duilib_set_event_callback(duilib_manager_t manager, duilib_event_callback_t callback);

// 发送自定义消息
DUILIB_C_API duilib_result_t duilib_send_notify(duilib_manager_t manager, duilib_control_t control, const char* message);

//=============================================================================
// 管理器扩展API
//=============================================================================

// 查找控件扩展
DUILIB_C_API duilib_control_t duilib_paint_manager_find_sub_control_by_class(duilib_manager_t manager, duilib_control_t parent, const char* class_name, int index);
DUILIB_C_API duilib_control_t duilib_paint_manager_find_sub_control_by_name(duilib_manager_t manager, duilib_control_t parent, const char* name);
DUILIB_C_API duilib_control_t duilib_paint_manager_find_sub_control_by_point(duilib_manager_t manager, duilib_control_t parent, int x, int y);

// 焦点管理
DUILIB_C_API duilib_control_t duilib_paint_manager_get_focus(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_focus(duilib_manager_t manager, duilib_control_t control, bool focus_wnd);
DUILIB_C_API bool duilib_paint_manager_set_next_tab_control(duilib_manager_t manager, bool forward);

// 定时器管理
DUILIB_C_API bool duilib_paint_manager_set_timer(duilib_manager_t manager, duilib_control_t control, uint32_t timer_id, uint32_t elapse);
DUILIB_C_API bool duilib_paint_manager_kill_timer(duilib_manager_t manager, duilib_control_t control, uint32_t timer_id);
DUILIB_C_API duilib_result_t duilib_paint_manager_kill_all_timers(duilib_manager_t manager, duilib_control_t control);

// 鼠标捕获
DUILIB_C_API duilib_result_t duilib_paint_manager_set_capture(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_release_capture(duilib_manager_t manager);
DUILIB_C_API bool duilib_paint_manager_is_captured(duilib_manager_t manager);

// 窗口属性
DUILIB_C_API duilib_size_t duilib_paint_manager_get_client_size(duilib_manager_t manager);
DUILIB_C_API duilib_size_t duilib_paint_manager_get_init_size(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_init_size(duilib_manager_t manager, int width, int height);

//=============================================================================
// 字体管理API
//=============================================================================

// 默认字体
DUILIB_C_API duilib_result_t duilib_paint_manager_set_default_font(duilib_manager_t manager, const char* font_name, int size, bool bold, bool underline, bool italic);
DUILIB_C_API uint32_t duilib_paint_manager_get_custom_font_count(duilib_manager_t manager);

// 字体添加和管理
DUILIB_C_API int duilib_paint_manager_add_font(duilib_manager_t manager, int id, const char* font_name, int size, bool bold, bool underline, bool italic);
DUILIB_C_API void* duilib_paint_manager_get_font(duilib_manager_t manager, int id);
DUILIB_C_API int duilib_paint_manager_get_font_index(duilib_manager_t manager, const char* font_name, int size, bool bold, bool underline, bool italic);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_font(duilib_manager_t manager, int id);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_all_fonts(duilib_manager_t manager);

//=============================================================================
// 图片资源管理API
//=============================================================================

// 图片添加和管理
DUILIB_C_API duilib_result_t duilib_paint_manager_add_image(duilib_manager_t manager, const char* bitmap_name, const char* type, uint32_t mask, bool use_hsl);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_image(duilib_manager_t manager, const char* bitmap_name);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_all_images(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_reload_images(duilib_manager_t manager);

//=============================================================================
// 默认属性管理API
//=============================================================================

// 默认属性列表
DUILIB_C_API duilib_result_t duilib_paint_manager_add_default_attribute_list(duilib_manager_t manager, const char* control_name, const char* attr_list);
DUILIB_C_API const char* duilib_paint_manager_get_default_attribute_list(duilib_manager_t manager, const char* control_name);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_default_attribute_list(duilib_manager_t manager, const char* control_name);

// 窗口自定义属性
DUILIB_C_API duilib_result_t duilib_paint_manager_add_window_custom_attribute(duilib_manager_t manager, const char* name, const char* attr);
DUILIB_C_API const char* duilib_paint_manager_get_window_custom_attribute(duilib_manager_t manager, const char* name);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_window_custom_attribute(duilib_manager_t manager, const char* name);

// 窗口属性
DUILIB_C_API const char* duilib_paint_manager_get_window_attribute(duilib_manager_t manager, const char* name);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_window_attribute(duilib_manager_t manager, const char* name, const char* value);
DUILIB_C_API const char* duilib_paint_manager_get_window_attribute_list(duilib_manager_t manager, bool ignore_default);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_window_attribute_list(duilib_manager_t manager, const char* attr_list);

//=============================================================================
// 选项组管理API
//=============================================================================

// 选项组管理
DUILIB_C_API duilib_result_t duilib_paint_manager_add_option_group(duilib_manager_t manager, const char* group_name, duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_option_group(duilib_manager_t manager, const char* group_name, duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_all_option_groups(duilib_manager_t manager);

//=============================================================================
// CPaintManagerUI 缺失方法补充
//=============================================================================

// 管理器基础属性
DUILIB_C_API const char* duilib_paint_manager_get_name(duilib_manager_t manager);
DUILIB_C_API void* duilib_paint_manager_get_paint_dc(duilib_manager_t manager);
DUILIB_C_API void* duilib_paint_manager_get_paint_offscreen_bitmap(duilib_manager_t manager);
DUILIB_C_API void* duilib_paint_manager_get_paint_window(duilib_manager_t manager);
DUILIB_C_API void* duilib_paint_manager_get_tooltip_window(duilib_manager_t manager);
DUILIB_C_API int duilib_paint_manager_get_tooltip_window_width(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_tooltip_window_width(duilib_manager_t manager, int width);
DUILIB_C_API int duilib_paint_manager_get_hover_time(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_hover_time(duilib_manager_t manager, int time);

// 更新和无效化
DUILIB_C_API bool duilib_paint_manager_is_update_needed(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_need_update(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_invalidate(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_invalidate_rect(duilib_manager_t manager, duilib_rect_t rect);

// 鼠标和窗口几何
DUILIB_C_API duilib_point_t duilib_paint_manager_get_mouse_pos(duilib_manager_t manager);
DUILIB_C_API duilib_rect_t duilib_paint_manager_get_size_box(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_size_box(duilib_manager_t manager, duilib_rect_t rect);
DUILIB_C_API duilib_rect_t duilib_paint_manager_get_caption_rect(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_caption_rect(duilib_manager_t manager, duilib_rect_t rect);
DUILIB_C_API duilib_size_t duilib_paint_manager_get_round_corner(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_round_corner(duilib_manager_t manager, int cx, int cy);
DUILIB_C_API duilib_size_t duilib_paint_manager_get_min_info(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_min_info(duilib_manager_t manager, int cx, int cy);
DUILIB_C_API duilib_size_t duilib_paint_manager_get_max_info(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_max_info(duilib_manager_t manager, int cx, int cy);
DUILIB_C_API bool duilib_paint_manager_is_show_update_rect(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_show_update_rect(duilib_manager_t manager, bool show);
DUILIB_C_API bool duilib_paint_manager_is_no_activate(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_no_activate(duilib_manager_t manager, bool no_activate);

// 透明度和分层窗口
DUILIB_C_API uint8_t duilib_paint_manager_get_opacity(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_opacity(duilib_manager_t manager, uint8_t opacity);
DUILIB_C_API bool duilib_paint_manager_is_layered(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_layered(duilib_manager_t manager, bool layered);
DUILIB_C_API duilib_rect_t duilib_paint_manager_get_layered_inset(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_layered_inset(duilib_manager_t manager, duilib_rect_t inset);
DUILIB_C_API uint8_t duilib_paint_manager_get_layered_opacity(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_layered_opacity(duilib_manager_t manager, uint8_t opacity);
DUILIB_C_API const char* duilib_paint_manager_get_layered_image(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_layered_image(duilib_manager_t manager, const char* image);

// 共享资源管理
DUILIB_C_API bool duilib_paint_manager_is_force_use_shared_res(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_force_use_shared_res(duilib_manager_t manager, bool force);

// 默认颜色管理
DUILIB_C_API uint32_t duilib_paint_manager_get_default_disabled_color(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_default_disabled_color(duilib_manager_t manager, uint32_t color);
DUILIB_C_API uint32_t duilib_paint_manager_get_default_font_color(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_default_font_color(duilib_manager_t manager, uint32_t color);
DUILIB_C_API uint32_t duilib_paint_manager_get_default_link_font_color(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_default_link_font_color(duilib_manager_t manager, uint32_t color);
DUILIB_C_API uint32_t duilib_paint_manager_get_default_link_hover_font_color(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_default_link_hover_font_color(duilib_manager_t manager, uint32_t color);
DUILIB_C_API uint32_t duilib_paint_manager_get_default_selected_bk_color(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_default_selected_bk_color(duilib_manager_t manager, uint32_t color);

// 控件管理高级功能
DUILIB_C_API duilib_result_t duilib_paint_manager_attach_dialog(duilib_manager_t manager, duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_paint_manager_init_controls(duilib_manager_t manager, duilib_control_t control, duilib_control_t parent);
DUILIB_C_API duilib_result_t duilib_paint_manager_rename_control(duilib_manager_t manager, duilib_control_t control, const char* name);
DUILIB_C_API duilib_result_t duilib_paint_manager_reap_objects(duilib_manager_t manager, duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_focus_needed(duilib_manager_t manager, duilib_control_t control);

// 绘制状态管理
DUILIB_C_API bool duilib_paint_manager_is_painting(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_painting(duilib_manager_t manager, bool painting);

// 后绘制管理
DUILIB_C_API int duilib_paint_manager_get_post_paint_count(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_add_post_paint(duilib_manager_t manager, duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_post_paint(duilib_manager_t manager, duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_post_paint_index(duilib_manager_t manager, duilib_control_t control, int index);

// 本地窗口管理
DUILIB_C_API int duilib_paint_manager_get_native_window_count(duilib_manager_t manager);
DUILIB_C_API duilib_rect_t duilib_paint_manager_get_native_window_rect(duilib_manager_t manager, void* child_wnd);
DUILIB_C_API duilib_result_t duilib_paint_manager_add_native_window(duilib_manager_t manager, duilib_control_t control, void* child_wnd);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_native_window(duilib_manager_t manager, void* child_wnd);

// 延迟清理和鼠标离开管理
DUILIB_C_API duilib_result_t duilib_paint_manager_add_delayed_cleanup(duilib_manager_t manager, duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_paint_manager_add_mouse_leave_needed(duilib_manager_t manager, duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_mouse_leave_needed(duilib_manager_t manager, duilib_control_t control);

// 消息处理高级功能
DUILIB_C_API duilib_result_t duilib_paint_manager_used_virtual_wnd(duilib_manager_t manager, bool used);

// XML支持
DUILIB_C_API const char* duilib_paint_manager_get_window_xml(duilib_manager_t manager);

//=============================================================================
// CPaintManagerUI 缺失方法补充
//=============================================================================

// 消息过滤器接口类型定义
typedef struct duilib_message_filter* duilib_message_filter_t;
typedef struct duilib_notify_ui* duilib_notify_ui_t;
typedef struct duilib_translate_accelerator* duilib_translate_accelerator_t;

// 消息过滤器回调
typedef intptr_t (*duilib_message_filter_callback_t)(uint32_t msg, uintptr_t wparam, intptr_t lparam, bool* handled);
typedef intptr_t (*duilib_translate_accelerator_callback_t)(void* msg);
typedef void (*duilib_notify_ui_callback_t)(const duilib_event_t* msg);

// 消息过滤器管理
DUILIB_C_API duilib_result_t duilib_paint_manager_add_pre_message_filter(duilib_manager_t manager, duilib_message_filter_callback_t filter);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_pre_message_filter(duilib_manager_t manager, duilib_message_filter_callback_t filter);
DUILIB_C_API duilib_result_t duilib_paint_manager_add_message_filter(duilib_manager_t manager, duilib_message_filter_callback_t filter);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_message_filter(duilib_manager_t manager, duilib_message_filter_callback_t filter);

// 通知器管理
DUILIB_C_API duilib_result_t duilib_paint_manager_add_notifier(duilib_manager_t manager, duilib_notify_ui_callback_t notifier);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_notifier(duilib_manager_t manager, duilib_notify_ui_callback_t notifier);
DUILIB_C_API duilib_result_t duilib_paint_manager_send_notify(duilib_manager_t manager, const duilib_event_t* msg, bool async, bool enable_repeat);
DUILIB_C_API duilib_result_t duilib_paint_manager_send_notify_control(duilib_manager_t manager, duilib_control_t control, const char* message, uintptr_t wparam, intptr_t lparam, bool async, bool enable_repeat);

// 加速器管理
DUILIB_C_API duilib_result_t duilib_paint_manager_add_translate_accelerator(duilib_manager_t manager, duilib_translate_accelerator_callback_t accelerator);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_translate_accelerator(duilib_manager_t manager, duilib_translate_accelerator_callback_t accelerator);
DUILIB_C_API bool duilib_paint_manager_translate_accelerator(duilib_manager_t manager, void* msg);

// 静态管理方法
DUILIB_C_API int duilib_paint_manager_message_loop(void);
DUILIB_C_API bool duilib_paint_manager_translate_message(const void* msg);
DUILIB_C_API duilib_result_t duilib_paint_manager_term(void);

// 消息处理
DUILIB_C_API bool duilib_paint_manager_message_handler(duilib_manager_t manager, uint32_t msg, uintptr_t wparam, intptr_t lparam, intptr_t* result);
DUILIB_C_API bool duilib_paint_manager_pre_message_handler(duilib_manager_t manager, uint32_t msg, uintptr_t wparam, intptr_t lparam, intptr_t* result);

// 高级查找功能列表
typedef struct duilib_ptr_array* duilib_ptr_array_t;

DUILIB_C_API duilib_ptr_array_t duilib_paint_manager_find_sub_controls_by_class(duilib_manager_t manager, duilib_control_t parent, const char* class_name);

// 获取所有管理器和插件列表
DUILIB_C_API duilib_ptr_array_t duilib_paint_manager_get_paint_managers(void);
DUILIB_C_API duilib_ptr_array_t duilib_paint_manager_get_plugins(void);

// 共享资源重新加载
DUILIB_C_API duilib_result_t duilib_paint_manager_reload_shared_images(void);

// 管理器清理和定时器
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_all_timers(duilib_manager_t manager);

// 字体信息结构和管理
typedef struct {
    void* font;          // HFONT
    char font_name[256]; // 字体名称
    int size;           // 字体大小
    bool bold;          // 粗体
    bool underline;     // 下划线
    bool italic;        // 斜体
    // TEXTMETRIC tm;   // Windows TEXTMETRIC 结构
} duilib_font_info_t;

DUILIB_C_API const duilib_font_info_t* duilib_paint_manager_get_default_font_info(duilib_manager_t manager);
DUILIB_C_API const duilib_font_info_t* duilib_paint_manager_get_font_info(duilib_manager_t manager, int id);
DUILIB_C_API const duilib_font_info_t* duilib_paint_manager_get_font_info_by_font(duilib_manager_t manager, void* font);

// 图像信息结构
typedef struct {
    void* bitmap;           // HBITMAP
    void* bits;             // 像素数据
    void* src_bits;         // 源像素数据
    int x, y;              // 尺寸
    bool alpha;            // 是否有alpha通道
    bool use_hsl;          // 是否使用HSL
    char res_type[64];     // 资源类型
    uint32_t mask;         // 颜色掩码
} duilib_image_info_t;

DUILIB_C_API const duilib_image_info_t* duilib_paint_manager_get_image(duilib_manager_t manager, const char* bitmap);
DUILIB_C_API const duilib_image_info_t* duilib_paint_manager_get_image_ex(duilib_manager_t manager, const char* bitmap, const char* type, uint32_t mask, bool use_hsl);
DUILIB_C_API const duilib_image_info_t* duilib_paint_manager_add_image_from_bitmap(duilib_manager_t manager, const char* bitmap, void* hbitmap, int width, int height, bool alpha);

// 选项组高级管理
DUILIB_C_API duilib_ptr_array_t duilib_paint_manager_get_option_group(duilib_manager_t manager, const char* group_name);

//=============================================================================
// CPaintManagerUI 剩余缺失方法补充 - 完整1:1对应
//=============================================================================

// 静态资源管理的共享版本参数支持
DUILIB_C_API duilib_result_t duilib_paint_manager_set_default_font_shared(duilib_manager_t manager, const char* font_name, int size, bool bold, bool underline, bool italic, bool shared);
DUILIB_C_API void* duilib_paint_manager_add_font_shared(duilib_manager_t manager, int id, const char* font_name, int size, bool bold, bool underline, bool italic, bool shared);
DUILIB_C_API void* duilib_paint_manager_get_font_by_name(duilib_manager_t manager, const char* font_name, int size, bool bold, bool underline, bool italic);
DUILIB_C_API int duilib_paint_manager_get_font_index_by_font(duilib_manager_t manager, void* font, bool shared);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_font_by_font(duilib_manager_t manager, void* font, bool shared);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_font_shared(duilib_manager_t manager, int id, bool shared);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_all_fonts_shared(duilib_manager_t manager, bool shared);

// 图片管理的完整API
DUILIB_C_API const duilib_image_info_t* duilib_paint_manager_add_image_shared(duilib_manager_t manager, const char* bitmap, const char* type, uint32_t mask, bool use_hsl, bool shared);
DUILIB_C_API const duilib_image_info_t* duilib_paint_manager_add_image_from_bitmap_shared(duilib_manager_t manager, const char* bitmap, void* hbitmap, int width, int height, bool alpha, bool shared);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_image_shared(duilib_manager_t manager, const char* bitmap, bool shared);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_all_images_shared(duilib_manager_t manager, bool shared);

// 默认属性的shared参数版本
DUILIB_C_API duilib_result_t duilib_paint_manager_add_default_attribute_list_shared(duilib_manager_t manager, const char* control_name, const char* attr_list, bool shared);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_default_attribute_list_shared(duilib_manager_t manager, const char* control_name, bool shared);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_all_default_attribute_list(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_all_default_attribute_list_shared(duilib_manager_t manager, bool shared);

// 颜色管理的shared参数版本
DUILIB_C_API duilib_result_t duilib_paint_manager_set_default_disabled_color_shared(duilib_manager_t manager, uint32_t color, bool shared);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_default_font_color_shared(duilib_manager_t manager, uint32_t color, bool shared);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_default_link_font_color_shared(duilib_manager_t manager, uint32_t color, bool shared);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_default_link_hover_font_color_shared(duilib_manager_t manager, uint32_t color, bool shared);
DUILIB_C_API duilib_result_t duilib_paint_manager_set_default_selected_bk_color_shared(duilib_manager_t manager, uint32_t color, bool shared);

// 窗口属性管理完整API
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_all_window_custom_attribute(duilib_manager_t manager);
DUILIB_C_API duilib_result_t duilib_paint_manager_remove_window_attribute(duilib_manager_t manager, const char* name);

// 找控件的完整回调支持
typedef struct {
    int count;
    int index;
} duilib_find_control_data_t;

DUILIB_C_API duilib_result_t duilib_paint_manager_remove_all_timers_control(duilib_manager_t manager, duilib_control_t control);

// 字体统计信息
DUILIB_C_API uint32_t duilib_paint_manager_get_custom_font_count_shared(duilib_manager_t manager, bool shared);

// HSL调整所有图片的方法补充
DUILIB_C_API duilib_result_t duilib_paint_manager_adjust_images_hsl(duilib_manager_t manager);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_MANAGER_H__