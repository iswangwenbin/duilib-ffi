#ifndef __DUILIB_C_LABEL_H__
#define __DUILIB_C_LABEL_H__

#include "../core/duilib_c_base.h"
#include "../duilib_c_types.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 标签控件API - 对应 CLabelUI
//=============================================================================

//=============================================================================
// 标签控件基础API
//=============================================================================

// 创建和销毁标签控件
DUILIB_C_API duilib_label_t duilib_label_create(void);
DUILIB_C_API void duilib_label_destroy(duilib_label_t label);

// 获取控件基类接口
DUILIB_C_API duilib_control_t duilib_label_to_control(duilib_label_t label);
DUILIB_C_API duilib_label_t duilib_control_to_label(duilib_control_t control);

// 类型检查
DUILIB_C_API bool duilib_label_is_valid(duilib_label_t label);

//=============================================================================
// CLabelUI 核心方法 - 对应原始接口
//=============================================================================

// 类信息
DUILIB_C_API const char* duilib_label_get_class(duilib_label_t label);
DUILIB_C_API void* duilib_label_get_interface(duilib_label_t label, const char* name);

// 固定尺寸设置
DUILIB_C_API duilib_result_t duilib_label_set_fixed_width(duilib_label_t label, int cx);
DUILIB_C_API duilib_result_t duilib_label_set_fixed_height(duilib_label_t label, int cy);

//=============================================================================
// 标签文本管理 - 对应 CLabelUI 文本方法
//=============================================================================

// 文本内容
DUILIB_C_API const char* duilib_label_get_text(duilib_label_t label);
DUILIB_C_API duilib_result_t duilib_label_set_text(duilib_label_t label, const char* text);

// 文本样式
DUILIB_C_API uint32_t duilib_label_get_text_style(duilib_label_t label);
DUILIB_C_API duilib_result_t duilib_label_set_text_style(duilib_label_t label, uint32_t style);

// 多行文本支持
DUILIB_C_API bool duilib_label_is_multiline(duilib_label_t label);
DUILIB_C_API duilib_result_t duilib_label_set_multiline(duilib_label_t label, bool multiline);

//=============================================================================
// 标签颜色管理 - 对应 CLabelUI 颜色方法
//=============================================================================

// 文本颜色
DUILIB_C_API duilib_color_t duilib_label_get_text_color(duilib_label_t label);
DUILIB_C_API duilib_result_t duilib_label_set_text_color(duilib_label_t label, duilib_color_t color);

// 禁用文本颜色
DUILIB_C_API duilib_color_t duilib_label_get_disabled_text_color(duilib_label_t label);
DUILIB_C_API duilib_result_t duilib_label_set_disabled_text_color(duilib_label_t label, duilib_color_t color);

//=============================================================================
// 标签字体管理 - 对应 CLabelUI 字体方法
//=============================================================================

// 字体
DUILIB_C_API int duilib_label_get_font(duilib_label_t label);
DUILIB_C_API duilib_result_t duilib_label_set_font(duilib_label_t label, int font_index);

// 文本边距
DUILIB_C_API duilib_rect_t duilib_label_get_text_padding(duilib_label_t label);
DUILIB_C_API duilib_result_t duilib_label_set_text_padding(duilib_label_t label, duilib_rect_t padding);

//=============================================================================
// HTML文本支持 - 对应 CLabelUI HTML方法
//=============================================================================

// HTML文本支持
DUILIB_C_API bool duilib_label_is_show_html(duilib_label_t label);
DUILIB_C_API duilib_result_t duilib_label_set_show_html(duilib_label_t label, bool show_html);

//=============================================================================
// 标签尺寸和布局 - 对应 CLabelUI 布局方法
//=============================================================================

// 估算尺寸 - 对应 EstimateSize
DUILIB_C_API duilib_size_t duilib_label_estimate_size(duilib_label_t label, duilib_size_t available);

// 事件处理
DUILIB_C_API duilib_result_t duilib_label_do_event(duilib_label_t label, const duilib_ui_event_t* event);

//=============================================================================
// 标签属性管理 - 对应 CLabelUI 属性方法
//=============================================================================

// 设置属性 - 对应 SetAttribute
DUILIB_C_API duilib_result_t duilib_label_set_attribute(duilib_label_t label, const char* name, const char* value);

//=============================================================================
// 标签绘制方法 - 对应 CLabelUI 绘制方法
//=============================================================================

// 绘制文本 - 对应 PaintText
DUILIB_C_API duilib_result_t duilib_label_paint_text(duilib_label_t label, void* hdc);

//=============================================================================
// GDI+ 效果支持 - 对应 CLabelUI 的 _USE_GDIPLUS 功能
//=============================================================================

// 启用效果
DUILIB_C_API duilib_result_t duilib_label_set_enabled_effect(duilib_label_t label, bool enabled);
DUILIB_C_API bool duilib_label_get_enabled_effect(duilib_label_t label);

// 发光效果
DUILIB_C_API duilib_result_t duilib_label_set_enabled_luminous(duilib_label_t label, bool enabled);
DUILIB_C_API bool duilib_label_get_enabled_luminous(duilib_label_t label);

// 发光模糊度
DUILIB_C_API duilib_result_t duilib_label_set_luminous_fuzzy(duilib_label_t label, float fuzzy);
DUILIB_C_API float duilib_label_get_luminous_fuzzy(duilib_label_t label);

// 渐变长度
DUILIB_C_API duilib_result_t duilib_label_set_gradient_length(duilib_label_t label, int length);
DUILIB_C_API int duilib_label_get_gradient_length(duilib_label_t label);

// 阴影偏移
DUILIB_C_API duilib_result_t duilib_label_set_shadow_offset(duilib_label_t label, int offset, int angle);
DUILIB_C_API duilib_point_t duilib_label_get_shadow_offset(duilib_label_t label);

// 渐变颜色
DUILIB_C_API duilib_result_t duilib_label_set_text_color1(duilib_label_t label, duilib_color_t color);
DUILIB_C_API duilib_color_t duilib_label_get_text_color1(duilib_label_t label);

// 阴影颜色A
DUILIB_C_API duilib_result_t duilib_label_set_text_shadow_color_a(duilib_label_t label, duilib_color_t color);
DUILIB_C_API duilib_color_t duilib_label_get_text_shadow_color_a(duilib_label_t label);

// 阴影颜色B
DUILIB_C_API duilib_result_t duilib_label_set_text_shadow_color_b(duilib_label_t label, duilib_color_t color);
DUILIB_C_API duilib_color_t duilib_label_get_text_shadow_color_b(duilib_label_t label);

// 描边颜色
DUILIB_C_API duilib_result_t duilib_label_set_stroke_color(duilib_label_t label, duilib_color_t color);
DUILIB_C_API duilib_color_t duilib_label_get_stroke_color(duilib_label_t label);

// 渐变角度
DUILIB_C_API duilib_result_t duilib_label_set_gradient_angle(duilib_label_t label, int angle);
DUILIB_C_API int duilib_label_get_gradient_angle(duilib_label_t label);

// 启用描边
DUILIB_C_API duilib_result_t duilib_label_set_enabled_stroke(duilib_label_t label, bool enabled);
DUILIB_C_API bool duilib_label_get_enabled_stroke(duilib_label_t label);

// 启用阴影
DUILIB_C_API duilib_result_t duilib_label_set_enabled_shadow(duilib_label_t label, bool enabled);
DUILIB_C_API bool duilib_label_get_enabled_shadow(duilib_label_t label);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_LABEL_H__