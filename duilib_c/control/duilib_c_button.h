#ifndef __DUILIB_C_BUTTON_H__
#define __DUILIB_C_BUTTON_H__

#include "../core/duilib_c_base.h"
#include "../duilib_c_types.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 按钮控件API - 对应 CButtonUI
//=============================================================================

// 按钮状态枚举
typedef enum {
    DUILIB_BUTTON_STATE_NORMAL = 0,
    DUILIB_BUTTON_STATE_HOT,
    DUILIB_BUTTON_STATE_PUSHED,
    DUILIB_BUTTON_STATE_FOCUSED,
    DUILIB_BUTTON_STATE_DISABLED
} duilib_button_state_t;

//=============================================================================
// 按钮控件基础API
//=============================================================================

// 创建和销毁按钮控件
DUILIB_C_API duilib_button_t duilib_button_create(void);
DUILIB_C_API void duilib_button_destroy(duilib_button_t button);

// 获取控件基类接口
DUILIB_C_API duilib_control_t duilib_button_to_control(duilib_button_t button);
DUILIB_C_API duilib_button_t duilib_control_to_button(duilib_control_t control);

// 类型检查
DUILIB_C_API bool duilib_button_is_valid(duilib_button_t button);

//=============================================================================
// CButtonUI 核心方法 - 对应原始接口
//=============================================================================

// 类信息
DUILIB_C_API const char* duilib_button_get_class(duilib_button_t button);
DUILIB_C_API void* duilib_button_get_interface(duilib_button_t button, const char* name);
DUILIB_C_API uint32_t duilib_button_get_control_flags(duilib_button_t button);

// 激活和状态
DUILIB_C_API bool duilib_button_activate(duilib_button_t button);
DUILIB_C_API duilib_result_t duilib_button_set_enabled(duilib_button_t button, bool enabled);

// 事件处理
DUILIB_C_API duilib_result_t duilib_button_do_event(duilib_button_t button, const duilib_ui_event_t* event);

//=============================================================================
// 按钮图片状态管理 - 对应 CButtonUI 图片方法
//=============================================================================

// 普通状态图片
DUILIB_C_API const char* duilib_button_get_normal_image(duilib_button_t button);
DUILIB_C_API duilib_result_t duilib_button_set_normal_image(duilib_button_t button, const char* image);

// 热点状态图片
DUILIB_C_API const char* duilib_button_get_hot_image(duilib_button_t button);
DUILIB_C_API duilib_result_t duilib_button_set_hot_image(duilib_button_t button, const char* image);

// 按下状态图片
DUILIB_C_API const char* duilib_button_get_pushed_image(duilib_button_t button);
DUILIB_C_API duilib_result_t duilib_button_set_pushed_image(duilib_button_t button, const char* image);

// 焦点状态图片
DUILIB_C_API const char* duilib_button_get_focused_image(duilib_button_t button);
DUILIB_C_API duilib_result_t duilib_button_set_focused_image(duilib_button_t button, const char* image);

// 禁用状态图片
DUILIB_C_API const char* duilib_button_get_disabled_image(duilib_button_t button);
DUILIB_C_API duilib_result_t duilib_button_set_disabled_image(duilib_button_t button, const char* image);

// 前景图片
DUILIB_C_API const char* duilib_button_get_fore_image(duilib_button_t button);
DUILIB_C_API duilib_result_t duilib_button_set_fore_image(duilib_button_t button, const char* image);

// 热点前景图片
DUILIB_C_API const char* duilib_button_get_hot_fore_image(duilib_button_t button);
DUILIB_C_API duilib_result_t duilib_button_set_hot_fore_image(duilib_button_t button, const char* image);

//=============================================================================
// 五状态图片和淡入淡出效果
//=============================================================================

// 五状态图片 - 对应 SetFiveStatusImage
DUILIB_C_API duilib_result_t duilib_button_set_five_status_image(duilib_button_t button, const char* image);

// 淡入淡出效果 - 对应 SetFadeAlphaDelta/GetFadeAlphaDelta
DUILIB_C_API duilib_result_t duilib_button_set_fade_alpha_delta(duilib_button_t button, uint8_t delta);
DUILIB_C_API uint8_t duilib_button_get_fade_alpha_delta(duilib_button_t button);

//=============================================================================
// 按钮颜色状态管理 - 对应 CButtonUI 颜色方法
//=============================================================================

// 热点背景颜色
DUILIB_C_API duilib_result_t duilib_button_set_hot_bk_color(duilib_button_t button, duilib_color_t color);
DUILIB_C_API duilib_color_t duilib_button_get_hot_bk_color(duilib_button_t button);

// 热点文本颜色
DUILIB_C_API duilib_result_t duilib_button_set_hot_text_color(duilib_button_t button, duilib_color_t color);
DUILIB_C_API duilib_color_t duilib_button_get_hot_text_color(duilib_button_t button);

// 按下文本颜色
DUILIB_C_API duilib_result_t duilib_button_set_pushed_text_color(duilib_button_t button, duilib_color_t color);
DUILIB_C_API duilib_color_t duilib_button_get_pushed_text_color(duilib_button_t button);

// 焦点文本颜色
DUILIB_C_API duilib_result_t duilib_button_set_focused_text_color(duilib_button_t button, duilib_color_t color);
DUILIB_C_API duilib_color_t duilib_button_get_focused_text_color(duilib_button_t button);

//=============================================================================
// 按钮尺寸和布局 - 对应 CButtonUI 布局方法
//=============================================================================

// 估算尺寸 - 对应 EstimateSize
DUILIB_C_API duilib_size_t duilib_button_estimate_size(duilib_button_t button, duilib_size_t available);

//=============================================================================
// 按钮属性管理 - 对应 CButtonUI 属性方法
//=============================================================================

// 设置属性 - 对应 SetAttribute
DUILIB_C_API duilib_result_t duilib_button_set_attribute(duilib_button_t button, const char* name, const char* value);

//=============================================================================
// 按钮绘制方法 - 对应 CButtonUI 绘制方法
//=============================================================================

// 绘制文本 - 对应 PaintText
DUILIB_C_API duilib_result_t duilib_button_paint_text(duilib_button_t button, void* hdc);

// 绘制状态图片 - 对应 PaintStatusImage
DUILIB_C_API duilib_result_t duilib_button_paint_status_image(duilib_button_t button, void* hdc);

//=============================================================================
// 按钮状态查询和管理
//=============================================================================

// 获取当前按钮状态
DUILIB_C_API duilib_button_state_t duilib_button_get_button_state(duilib_button_t button);
DUILIB_C_API duilib_result_t duilib_button_set_button_state(duilib_button_t button, duilib_button_state_t state);

// 检查按钮状态
DUILIB_C_API bool duilib_button_is_hot(duilib_button_t button);
DUILIB_C_API bool duilib_button_is_pushed(duilib_button_t button);
DUILIB_C_API bool duilib_button_is_focused(duilib_button_t button);

//=============================================================================
// 继承自 CLabelUI 的方法访问
//=============================================================================

// 从按钮获取标签接口进行文本操作
DUILIB_C_API const char* duilib_button_get_text(duilib_button_t button);
DUILIB_C_API duilib_result_t duilib_button_set_text(duilib_button_t button, const char* text);

// 文本样式
DUILIB_C_API uint32_t duilib_button_get_text_style(duilib_button_t button);
DUILIB_C_API duilib_result_t duilib_button_set_text_style(duilib_button_t button, uint32_t style);

// 文本颜色
DUILIB_C_API duilib_color_t duilib_button_get_text_color(duilib_button_t button);
DUILIB_C_API duilib_result_t duilib_button_set_text_color(duilib_button_t button, duilib_color_t color);

// 禁用文本颜色
DUILIB_C_API duilib_color_t duilib_button_get_disabled_text_color(duilib_button_t button);
DUILIB_C_API duilib_result_t duilib_button_set_disabled_text_color(duilib_button_t button, duilib_color_t color);

// 字体
DUILIB_C_API int duilib_button_get_font(duilib_button_t button);
DUILIB_C_API duilib_result_t duilib_button_set_font(duilib_button_t button, int font_index);

// 文本边距
DUILIB_C_API duilib_rect_t duilib_button_get_text_padding(duilib_button_t button);
DUILIB_C_API duilib_result_t duilib_button_set_text_padding(duilib_button_t button, duilib_rect_t padding);

// 多行文本支持
DUILIB_C_API bool duilib_button_is_multiline(duilib_button_t button);
DUILIB_C_API duilib_result_t duilib_button_set_multiline(duilib_button_t button, bool multiline);

// HTML文本支持
DUILIB_C_API bool duilib_button_is_show_html(duilib_button_t button);
DUILIB_C_API duilib_result_t duilib_button_set_show_html(duilib_button_t button, bool show_html);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_BUTTON_H__