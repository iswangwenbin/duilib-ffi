#ifndef __DUILIB_C_CONTROLS_H__
#define __DUILIB_C_CONTROLS_H__

//=============================================================================
// DuiLib C API - 控件模块汇总头文件
// 包含所有控件类的C API声明
//=============================================================================

#include "../core/duilib_c_base.h"

// 基础控件
#include "duilib_c_label.h"
#include "duilib_c_text.h"
#include "duilib_c_button.h"
#include "duilib_c_edit.h"

// 选择控件
#include "duilib_c_option.h"
#include "duilib_c_checkbox.h"

// 进度和滑块控件
#include "duilib_c_progress.h"
#include "duilib_c_slider.h"
#include "duilib_c_scrollbar.h"

// 组合框和日期时间控件
#include "duilib_c_combo.h"
#include "duilib_c_datetime.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 控件模块初始化和清理
//=============================================================================

// 初始化控件模块
DUILIB_C_API duilib_result_t duilib_controls_initialize(void);

// 清理控件模块
DUILIB_C_API duilib_result_t duilib_controls_cleanup(void);

//=============================================================================
// 控件工厂方法 - 通用控件创建
//=============================================================================

// 通过类名创建控件
DUILIB_C_API duilib_control_t duilib_create_control_by_class(const char* class_name);

// 控件类型枚举
typedef enum {
    DUILIB_CONTROL_TYPE_UNKNOWN = 0,
    DUILIB_CONTROL_TYPE_CONTROL,
    DUILIB_CONTROL_TYPE_LABEL,
    DUILIB_CONTROL_TYPE_TEXT,
    DUILIB_CONTROL_TYPE_BUTTON,
    DUILIB_CONTROL_TYPE_EDIT,
    DUILIB_CONTROL_TYPE_OPTION,
    DUILIB_CONTROL_TYPE_CHECKBOX,
    DUILIB_CONTROL_TYPE_PROGRESS,
    DUILIB_CONTROL_TYPE_SLIDER,
    DUILIB_CONTROL_TYPE_SCROLLBAR,
    DUILIB_CONTROL_TYPE_COMBO,
    DUILIB_CONTROL_TYPE_DATETIME
} duilib_control_type_t;

// 获取控件类型
DUILIB_C_API duilib_control_type_t duilib_get_control_type(duilib_control_t control);

// 检查控件类型
DUILIB_C_API bool duilib_is_control_type(duilib_control_t control, duilib_control_type_t type);

//=============================================================================
// 控件转换辅助函数 - 安全类型转换
//=============================================================================

// 安全转换到具体控件类型（失败返回NULL）
DUILIB_C_API duilib_label_t duilib_safe_cast_to_label(duilib_control_t control);
DUILIB_C_API duilib_text_t duilib_safe_cast_to_text(duilib_control_t control);
DUILIB_C_API duilib_button_t duilib_safe_cast_to_button(duilib_control_t control);
DUILIB_C_API duilib_edit_t duilib_safe_cast_to_edit(duilib_control_t control);
DUILIB_C_API duilib_option_t duilib_safe_cast_to_option(duilib_control_t control);
DUILIB_C_API duilib_checkbox_t duilib_safe_cast_to_checkbox(duilib_control_t control);
DUILIB_C_API duilib_progress_t duilib_safe_cast_to_progress(duilib_control_t control);
DUILIB_C_API duilib_slider_t duilib_safe_cast_to_slider(duilib_control_t control);
DUILIB_C_API duilib_scrollbar_t duilib_safe_cast_to_scrollbar(duilib_control_t control);
DUILIB_C_API duilib_combo_t duilib_safe_cast_to_combo(duilib_control_t control);
DUILIB_C_API duilib_datetime_t duilib_safe_cast_to_datetime(duilib_control_t control);

//=============================================================================
// 控件事件回调类型定义
//=============================================================================

// 控件通用事件回调
typedef void (*duilib_control_event_callback_t)(duilib_control_t control, const duilib_ui_event_t* event, void* user_data);

// 按钮点击事件回调
typedef void (*duilib_button_click_callback_t)(duilib_button_t button, void* user_data);

// 编辑框文本改变回调
typedef void (*duilib_edit_text_changed_callback_t)(duilib_edit_t edit, const char* new_text, void* user_data);

// 选项选择改变回调
typedef void (*duilib_option_select_callback_t)(duilib_option_t option, bool selected, void* user_data);

// 复选框状态改变回调
typedef void (*duilib_checkbox_check_callback_t)(duilib_checkbox_t checkbox, bool checked, void* user_data);

// 滑块值改变回调
typedef void (*duilib_slider_value_callback_t)(duilib_slider_t slider, int value, void* user_data);

// 组合框选择改变回调
typedef void (*duilib_combo_select_callback_t)(duilib_combo_t combo, int index, void* user_data);

//=============================================================================
// 控件事件回调注册
//=============================================================================

// 注册控件通用事件回调
DUILIB_C_API duilib_result_t duilib_control_set_event_callback(duilib_control_t control, duilib_control_event_callback_t callback, void* user_data);

// 注册按钮点击回调
DUILIB_C_API duilib_result_t duilib_button_set_click_callback(duilib_button_t button, duilib_button_click_callback_t callback, void* user_data);

// 注册编辑框文本改变回调
DUILIB_C_API duilib_result_t duilib_edit_set_text_changed_callback(duilib_edit_t edit, duilib_edit_text_changed_callback_t callback, void* user_data);

// 注册选项选择回调
DUILIB_C_API duilib_result_t duilib_option_set_select_callback(duilib_option_t option, duilib_option_select_callback_t callback, void* user_data);

// 注册复选框状态回调
DUILIB_C_API duilib_result_t duilib_checkbox_set_check_callback(duilib_checkbox_t checkbox, duilib_checkbox_check_callback_t callback, void* user_data);

// 注册滑块值改变回调
DUILIB_C_API duilib_result_t duilib_slider_set_value_callback(duilib_slider_t slider, duilib_slider_value_callback_t callback, void* user_data);

// 注册组合框选择回调
DUILIB_C_API duilib_result_t duilib_combo_set_select_callback(duilib_combo_t combo, duilib_combo_select_callback_t callback, void* user_data);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_CONTROLS_H__