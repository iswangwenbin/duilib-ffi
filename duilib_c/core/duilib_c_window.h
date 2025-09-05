#ifndef __DUILIB_C_WINDOW_H__
#define __DUILIB_C_WINDOW_H__

#include "duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 窗口类 API - 对应 CWindowWnd
//=============================================================================

// 窗口消息处理回调函数类型
typedef int (*duilib_window_message_handler_t)(duilib_window_t window, uint32_t msg, uintptr_t wparam, intptr_t lparam, intptr_t* result);

// 创建和销毁窗口
DUILIB_C_API duilib_window_t duilib_window_create(void);
DUILIB_C_API void duilib_window_destroy(duilib_window_t window);

// 获取窗口句柄
DUILIB_C_API void* duilib_window_get_hwnd(duilib_window_t window);

// 窗口类注册
DUILIB_C_API bool duilib_window_register_window_class(duilib_window_t window);
DUILIB_C_API bool duilib_window_register_superclass(duilib_window_t window);

// 窗口创建 - 基本版本
DUILIB_C_API void* duilib_window_create_window(duilib_window_t window, void* parent_hwnd, const char* name, uint32_t style, uint32_t ex_style, duilib_rect_t rect, void* menu);

// 窗口创建 - 坐标版本  
DUILIB_C_API void* duilib_window_create_window_ex(duilib_window_t window, void* parent_hwnd, const char* name, uint32_t style, uint32_t ex_style, int x, int y, int cx, int cy, void* menu);

// 窗口创建 - DUI窗口版本
DUILIB_C_API void* duilib_window_create_dui_window(duilib_window_t window, void* parent_hwnd, const char* window_name, uint32_t style, uint32_t ex_style);

// 子类化
DUILIB_C_API void* duilib_window_subclass(duilib_window_t window, void* hwnd);
DUILIB_C_API duilib_result_t duilib_window_unsubclass(duilib_window_t window);

// 窗口显示和控制
DUILIB_C_API duilib_result_t duilib_window_show_window(duilib_window_t window, bool show, bool take_focus);
DUILIB_C_API uint32_t duilib_window_show_modal(duilib_window_t window);
DUILIB_C_API duilib_result_t duilib_window_close(duilib_window_t window, uint32_t result);
DUILIB_C_API duilib_result_t duilib_window_center_window(duilib_window_t window);
DUILIB_C_API duilib_result_t duilib_window_set_icon(duilib_window_t window, uint32_t resource_id);

// 消息发送
DUILIB_C_API intptr_t duilib_window_send_message(duilib_window_t window, uint32_t msg, uintptr_t wparam, intptr_t lparam);
DUILIB_C_API intptr_t duilib_window_post_message(duilib_window_t window, uint32_t msg, uintptr_t wparam, intptr_t lparam);

// 客户区尺寸调整
DUILIB_C_API duilib_result_t duilib_window_resize_client(duilib_window_t window, int cx, int cy);

// 窗口类属性设置
DUILIB_C_API duilib_result_t duilib_window_set_window_class_name(duilib_window_t window, const char* class_name);
DUILIB_C_API const char* duilib_window_get_window_class_name(duilib_window_t window);
DUILIB_C_API duilib_result_t duilib_window_set_super_class_name(duilib_window_t window, const char* super_class_name);
DUILIB_C_API const char* duilib_window_get_super_class_name(duilib_window_t window);
DUILIB_C_API duilib_result_t duilib_window_set_class_style(duilib_window_t window, uint32_t class_style);
DUILIB_C_API uint32_t duilib_window_get_class_style(duilib_window_t window);

// 消息处理
DUILIB_C_API duilib_result_t duilib_window_set_message_handler(duilib_window_t window, duilib_window_message_handler_t handler);
DUILIB_C_API intptr_t duilib_window_handle_message(duilib_window_t window, uint32_t msg, uintptr_t wparam, intptr_t lparam);

// 最终消息处理
DUILIB_C_API duilib_result_t duilib_window_on_final_message(duilib_window_t window, void* hwnd);

//=============================================================================
// 辅助函数和工具方法
//=============================================================================

// 窗口状态查询
DUILIB_C_API bool duilib_window_is_window(duilib_window_t window);
DUILIB_C_API bool duilib_window_is_visible(duilib_window_t window);
DUILIB_C_API bool duilib_window_is_enabled(duilib_window_t window);
DUILIB_C_API bool duilib_window_is_subclassed(duilib_window_t window);

// 窗口几何
DUILIB_C_API duilib_rect_t duilib_window_get_window_rect(duilib_window_t window);
DUILIB_C_API duilib_rect_t duilib_window_get_client_rect(duilib_window_t window);
DUILIB_C_API duilib_result_t duilib_window_set_window_pos(duilib_window_t window, void* hwnd_insert_after, int x, int y, int cx, int cy, uint32_t flags);

// 窗口标题
DUILIB_C_API duilib_result_t duilib_window_set_window_text(duilib_window_t window, const char* text);
DUILIB_C_API const char* duilib_window_get_window_text(duilib_window_t window);

// 父子关系
DUILIB_C_API void* duilib_window_get_parent(duilib_window_t window);
DUILIB_C_API duilib_result_t duilib_window_set_parent(duilib_window_t window, void* parent_hwnd);

// 焦点相关
DUILIB_C_API duilib_result_t duilib_window_set_focus(duilib_window_t window);
DUILIB_C_API bool duilib_window_has_focus(duilib_window_t window);

// 激活相关
DUILIB_C_API duilib_result_t duilib_window_set_active_window(duilib_window_t window);
DUILIB_C_API bool duilib_window_is_active(duilib_window_t window);

// 窗口样式
DUILIB_C_API uint32_t duilib_window_get_style(duilib_window_t window);
DUILIB_C_API duilib_result_t duilib_window_set_style(duilib_window_t window, uint32_t style);
DUILIB_C_API uint32_t duilib_window_get_ex_style(duilib_window_t window);
DUILIB_C_API duilib_result_t duilib_window_set_ex_style(duilib_window_t window, uint32_t ex_style);

// 窗口属性
DUILIB_C_API intptr_t duilib_window_get_window_long_ptr(duilib_window_t window, int index);
DUILIB_C_API intptr_t duilib_window_set_window_long_ptr(duilib_window_t window, int index, intptr_t new_long);

// Z序相关
DUILIB_C_API duilib_result_t duilib_window_bring_to_top(duilib_window_t window);
DUILIB_C_API duilib_result_t duilib_window_send_to_back(duilib_window_t window);

// 透明度和层叠
DUILIB_C_API duilib_result_t duilib_window_set_layered_window_attributes(duilib_window_t window, uint32_t color_key, uint8_t alpha, uint32_t flags);
DUILIB_C_API duilib_result_t duilib_window_update_layered_window(duilib_window_t window, void* hdc_dst, duilib_point_t* dst_pt, duilib_size_t* size, void* hdc_src, duilib_point_t* src_pt, uint32_t color_key, void* blend_func, uint32_t flags);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_WINDOW_H__