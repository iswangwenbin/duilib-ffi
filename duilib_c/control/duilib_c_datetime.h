#ifndef __DUILIB_C_DATETIME_H__
#define __DUILIB_C_DATETIME_H__

#include "../core/duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 日期时间控件API - 对应 CDateTimeUI
//=============================================================================

// 日期时间控件句柄
typedef struct duilib_datetime* duilib_datetime_t;

// 系统时间结构 - 对应 SYSTEMTIME
typedef struct {
    uint16_t year;
    uint16_t month;
    uint16_t day_of_week;
    uint16_t day;
    uint16_t hour;
    uint16_t minute;
    uint16_t second;
    uint16_t milliseconds;
} duilib_systemtime_t;

//=============================================================================
// 日期时间控件基础API
//=============================================================================

// 创建和销毁日期时间控件
DUILIB_C_API duilib_datetime_t duilib_datetime_create(void);
DUILIB_C_API void duilib_datetime_destroy(duilib_datetime_t datetime);

// 获取控件基类接口
DUILIB_C_API duilib_control_t duilib_datetime_to_control(duilib_datetime_t datetime);
DUILIB_C_API duilib_datetime_t duilib_control_to_datetime(duilib_control_t control);

// 获取标签接口（继承关系）
DUILIB_C_API duilib_label_t duilib_datetime_to_label(duilib_datetime_t datetime);
DUILIB_C_API duilib_datetime_t duilib_label_to_datetime(duilib_label_t label);

// 类型检查
DUILIB_C_API bool duilib_datetime_is_valid(duilib_datetime_t datetime);

//=============================================================================
// CDateTimeUI 核心方法 - 对应原始接口
//=============================================================================

// 类信息
DUILIB_C_API const char* duilib_datetime_get_class(duilib_datetime_t datetime);
DUILIB_C_API void* duilib_datetime_get_interface(duilib_datetime_t datetime, const char* name);
DUILIB_C_API uint32_t duilib_datetime_get_control_flags(duilib_datetime_t datetime);

// 原生窗口句柄
DUILIB_C_API void* duilib_datetime_get_native_window(duilib_datetime_t datetime);

//=============================================================================
// 日期时间管理 - 对应 CDateTimeUI 时间方法
//=============================================================================

// 时间获取和设置
DUILIB_C_API duilib_result_t duilib_datetime_get_time(duilib_datetime_t datetime, duilib_systemtime_t* time);
DUILIB_C_API duilib_result_t duilib_datetime_set_time(duilib_datetime_t datetime, const duilib_systemtime_t* time);

// 只读状态
DUILIB_C_API duilib_result_t duilib_datetime_set_readonly(duilib_datetime_t datetime, bool readonly);
DUILIB_C_API bool duilib_datetime_is_readonly(duilib_datetime_t datetime);

// 更新文本显示
DUILIB_C_API duilib_result_t duilib_datetime_update_text(duilib_datetime_t datetime);

//=============================================================================
// 日期时间位置和事件 - 对应 CDateTimeUI 位置和事件方法
//=============================================================================

// 位置设置
DUILIB_C_API duilib_result_t duilib_datetime_set_pos(duilib_datetime_t datetime, duilib_rect_t rect, bool need_invalidate);

// 移动
DUILIB_C_API duilib_result_t duilib_datetime_move(duilib_datetime_t datetime, duilib_size_t offset, bool need_invalidate);

// 事件处理
DUILIB_C_API duilib_result_t duilib_datetime_do_event(duilib_datetime_t datetime, const duilib_ui_event_t* event);

//=============================================================================
// 继承自 CLabelUI 的方法访问
//=============================================================================

// 从日期时间获取标签接口进行文本操作
DUILIB_C_API const char* duilib_datetime_get_text(duilib_datetime_t datetime);
DUILIB_C_API duilib_result_t duilib_datetime_set_text(duilib_datetime_t datetime, const char* text);

// 文本样式
DUILIB_C_API uint32_t duilib_datetime_get_text_style(duilib_datetime_t datetime);
DUILIB_C_API duilib_result_t duilib_datetime_set_text_style(duilib_datetime_t datetime, uint32_t style);

// 文本颜色
DUILIB_C_API duilib_color_t duilib_datetime_get_text_color(duilib_datetime_t datetime);
DUILIB_C_API duilib_result_t duilib_datetime_set_text_color(duilib_datetime_t datetime, duilib_color_t color);

// 禁用文本颜色
DUILIB_C_API duilib_color_t duilib_datetime_get_disabled_text_color(duilib_datetime_t datetime);
DUILIB_C_API duilib_result_t duilib_datetime_set_disabled_text_color(duilib_datetime_t datetime, duilib_color_t color);

// 字体
DUILIB_C_API int duilib_datetime_get_font(duilib_datetime_t datetime);
DUILIB_C_API duilib_result_t duilib_datetime_set_font(duilib_datetime_t datetime, int font_index);

// 文本边距
DUILIB_C_API duilib_rect_t duilib_datetime_get_text_padding(duilib_datetime_t datetime);
DUILIB_C_API duilib_result_t duilib_datetime_set_text_padding(duilib_datetime_t datetime, duilib_rect_t padding);

// HTML文本支持
DUILIB_C_API bool duilib_datetime_is_show_html(duilib_datetime_t datetime);
DUILIB_C_API duilib_result_t duilib_datetime_set_show_html(duilib_datetime_t datetime, bool show_html);

// 布局
DUILIB_C_API duilib_size_t duilib_datetime_estimate_size(duilib_datetime_t datetime, duilib_size_t available);
DUILIB_C_API duilib_result_t duilib_datetime_set_attribute(duilib_datetime_t datetime, const char* name, const char* value);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_DATETIME_H__