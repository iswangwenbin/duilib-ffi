#ifndef __DUILIB_C_CHECKBOX_H__
#define __DUILIB_C_CHECKBOX_H__

#include "../core/duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 复选框控件API - 对应 CCheckBoxUI
//=============================================================================

// 复选框控件句柄
typedef struct duilib_checkbox* duilib_checkbox_t;

//=============================================================================
// 复选框控件基础API
//=============================================================================

// 创建和销毁复选框控件
DUILIB_C_API duilib_checkbox_t duilib_checkbox_create(void);
DUILIB_C_API void duilib_checkbox_destroy(duilib_checkbox_t checkbox);

// 获取控件基类接口
DUILIB_C_API duilib_control_t duilib_checkbox_to_control(duilib_checkbox_t checkbox);
DUILIB_C_API duilib_checkbox_t duilib_control_to_checkbox(duilib_control_t control);

// 获取选项接口（继承关系）
DUILIB_C_API duilib_option_t duilib_checkbox_to_option(duilib_checkbox_t checkbox);
DUILIB_C_API duilib_checkbox_t duilib_option_to_checkbox(duilib_option_t option);

// 类型检查
DUILIB_C_API bool duilib_checkbox_is_valid(duilib_checkbox_t checkbox);

//=============================================================================
// CCheckBoxUI 核心方法 - 对应原始接口
//=============================================================================

// 类信息
DUILIB_C_API const char* duilib_checkbox_get_class(duilib_checkbox_t checkbox);
DUILIB_C_API void* duilib_checkbox_get_interface(duilib_checkbox_t checkbox, const char* name);

//=============================================================================
// 复选框状态管理 - 对应 CCheckBoxUI 状态方法
//=============================================================================

// 选中状态 - 对应 SetCheck/GetCheck
DUILIB_C_API duilib_result_t duilib_checkbox_set_check(duilib_checkbox_t checkbox, bool checked, bool trigger_event);
DUILIB_C_API bool duilib_checkbox_get_check(duilib_checkbox_t checkbox);

//=============================================================================
// 继承自 COptionUI 的方法访问
//=============================================================================

// 从复选框获取选项接口进行选项操作
DUILIB_C_API const char* duilib_checkbox_get_text(duilib_checkbox_t checkbox);
DUILIB_C_API duilib_result_t duilib_checkbox_set_text(duilib_checkbox_t checkbox, const char* text);

// 分组管理
DUILIB_C_API const char* duilib_checkbox_get_group(duilib_checkbox_t checkbox);
DUILIB_C_API duilib_result_t duilib_checkbox_set_group(duilib_checkbox_t checkbox, const char* group_name);

// 选择状态
DUILIB_C_API bool duilib_checkbox_is_selected(duilib_checkbox_t checkbox);
DUILIB_C_API duilib_result_t duilib_checkbox_selected(duilib_checkbox_t checkbox, bool selected, bool trigger_event);

// 激活
DUILIB_C_API bool duilib_checkbox_activate(duilib_checkbox_t checkbox);

// 状态控制
DUILIB_C_API duilib_result_t duilib_checkbox_set_enabled(duilib_checkbox_t checkbox, bool enabled);

// 图片管理
DUILIB_C_API const char* duilib_checkbox_get_normal_image(duilib_checkbox_t checkbox);
DUILIB_C_API duilib_result_t duilib_checkbox_set_normal_image(duilib_checkbox_t checkbox, const char* image);

DUILIB_C_API const char* duilib_checkbox_get_hot_image(duilib_checkbox_t checkbox);
DUILIB_C_API duilib_result_t duilib_checkbox_set_hot_image(duilib_checkbox_t checkbox, const char* image);

DUILIB_C_API const char* duilib_checkbox_get_pushed_image(duilib_checkbox_t checkbox);
DUILIB_C_API duilib_result_t duilib_checkbox_set_pushed_image(duilib_checkbox_t checkbox, const char* image);

DUILIB_C_API const char* duilib_checkbox_get_focused_image(duilib_checkbox_t checkbox);
DUILIB_C_API duilib_result_t duilib_checkbox_set_focused_image(duilib_checkbox_t checkbox, const char* image);

DUILIB_C_API const char* duilib_checkbox_get_disabled_image(duilib_checkbox_t checkbox);
DUILIB_C_API duilib_result_t duilib_checkbox_set_disabled_image(duilib_checkbox_t checkbox, const char* image);

DUILIB_C_API const char* duilib_checkbox_get_selected_image(duilib_checkbox_t checkbox);
DUILIB_C_API duilib_result_t duilib_checkbox_set_selected_image(duilib_checkbox_t checkbox, const char* image);

DUILIB_C_API const char* duilib_checkbox_get_selected_hot_image(duilib_checkbox_t checkbox);
DUILIB_C_API duilib_result_t duilib_checkbox_set_selected_hot_image(duilib_checkbox_t checkbox, const char* image);

// 颜色管理
DUILIB_C_API duilib_color_t duilib_checkbox_get_text_color(duilib_checkbox_t checkbox);
DUILIB_C_API duilib_result_t duilib_checkbox_set_text_color(duilib_checkbox_t checkbox, duilib_color_t color);

DUILIB_C_API duilib_color_t duilib_checkbox_get_selected_text_color(duilib_checkbox_t checkbox);
DUILIB_C_API duilib_result_t duilib_checkbox_set_selected_text_color(duilib_checkbox_t checkbox, duilib_color_t color);

DUILIB_C_API duilib_color_t duilib_checkbox_get_selected_bk_color(duilib_checkbox_t checkbox);
DUILIB_C_API duilib_result_t duilib_checkbox_set_selected_bk_color(duilib_checkbox_t checkbox, duilib_color_t color);

// 布局和绘制
DUILIB_C_API duilib_size_t duilib_checkbox_estimate_size(duilib_checkbox_t checkbox, duilib_size_t available);
DUILIB_C_API duilib_result_t duilib_checkbox_set_attribute(duilib_checkbox_t checkbox, const char* name, const char* value);
DUILIB_C_API duilib_result_t duilib_checkbox_paint_status_image(duilib_checkbox_t checkbox, void* hdc);
DUILIB_C_API duilib_result_t duilib_checkbox_paint_text(duilib_checkbox_t checkbox, void* hdc);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_CHECKBOX_H__