#ifndef __DUILIB_C_EDIT_H__
#define __DUILIB_C_EDIT_H__

#include "../core/duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 编辑框控件API - 对应 CEditUI
//=============================================================================

// 编辑框控件句柄
typedef struct duilib_edit* duilib_edit_t;

//=============================================================================
// 编辑框控件基础API
//=============================================================================

// 创建和销毁编辑框控件
DUILIB_C_API duilib_edit_t duilib_edit_create(void);
DUILIB_C_API void duilib_edit_destroy(duilib_edit_t edit);

// 获取控件基类接口
DUILIB_C_API duilib_control_t duilib_edit_to_control(duilib_edit_t edit);
DUILIB_C_API duilib_edit_t duilib_control_to_edit(duilib_control_t control);

// 获取标签接口（继承关系）
DUILIB_C_API duilib_label_t duilib_edit_to_label(duilib_edit_t edit);
DUILIB_C_API duilib_edit_t duilib_label_to_edit(duilib_label_t label);

// 类型检查
DUILIB_C_API bool duilib_edit_is_valid(duilib_edit_t edit);

//=============================================================================
// CEditUI 核心方法 - 对应原始接口
//=============================================================================

// 类信息
DUILIB_C_API const char* duilib_edit_get_class(duilib_edit_t edit);
DUILIB_C_API void* duilib_edit_get_interface(duilib_edit_t edit, const char* name);
DUILIB_C_API uint32_t duilib_edit_get_control_flags(duilib_edit_t edit);

// 原生窗口句柄
DUILIB_C_API void* duilib_edit_get_native_window(duilib_edit_t edit);
DUILIB_C_API void* duilib_edit_get_native_edit_hwnd(duilib_edit_t edit);

//=============================================================================
// 编辑框状态管理 - 对应 CEditUI 状态方法
//=============================================================================

// 启用状态
DUILIB_C_API duilib_result_t duilib_edit_set_enabled(duilib_edit_t edit, bool enabled);

// 文本内容
DUILIB_C_API duilib_result_t duilib_edit_set_text(duilib_edit_t edit, const char* text);

// 最大字符数
DUILIB_C_API duilib_result_t duilib_edit_set_max_char(duilib_edit_t edit, uint32_t max_char);
DUILIB_C_API uint32_t duilib_edit_get_max_char(duilib_edit_t edit);

// 只读模式
DUILIB_C_API duilib_result_t duilib_edit_set_readonly(duilib_edit_t edit, bool readonly);
DUILIB_C_API bool duilib_edit_is_readonly(duilib_edit_t edit);

// 密码模式
DUILIB_C_API duilib_result_t duilib_edit_set_password_mode(duilib_edit_t edit, bool password_mode);
DUILIB_C_API bool duilib_edit_is_password_mode(duilib_edit_t edit);

// 密码字符
DUILIB_C_API duilib_result_t duilib_edit_set_password_char(duilib_edit_t edit, char password_char);
DUILIB_C_API char duilib_edit_get_password_char(duilib_edit_t edit);

// 自动全选
DUILIB_C_API bool duilib_edit_is_auto_sel_all(duilib_edit_t edit);
DUILIB_C_API duilib_result_t duilib_edit_set_auto_sel_all(duilib_edit_t edit, bool auto_sel_all);

// 数字专用模式
DUILIB_C_API duilib_result_t duilib_edit_set_number_only(duilib_edit_t edit, bool number_only);
DUILIB_C_API bool duilib_edit_is_number_only(duilib_edit_t edit);

// 窗口样式
DUILIB_C_API int duilib_edit_get_window_styles(duilib_edit_t edit);

//=============================================================================
// 编辑框图片状态管理 - 对应 CEditUI 图片方法
//=============================================================================

// 普通状态图片
DUILIB_C_API const char* duilib_edit_get_normal_image(duilib_edit_t edit);
DUILIB_C_API duilib_result_t duilib_edit_set_normal_image(duilib_edit_t edit, const char* image);

// 热点状态图片
DUILIB_C_API const char* duilib_edit_get_hot_image(duilib_edit_t edit);
DUILIB_C_API duilib_result_t duilib_edit_set_hot_image(duilib_edit_t edit, const char* image);

// 焦点状态图片
DUILIB_C_API const char* duilib_edit_get_focused_image(duilib_edit_t edit);
DUILIB_C_API duilib_result_t duilib_edit_set_focused_image(duilib_edit_t edit, const char* image);

// 禁用状态图片
DUILIB_C_API const char* duilib_edit_get_disabled_image(duilib_edit_t edit);
DUILIB_C_API duilib_result_t duilib_edit_set_disabled_image(duilib_edit_t edit, const char* image);

// 原生编辑框背景颜色
DUILIB_C_API duilib_result_t duilib_edit_set_native_edit_bk_color(duilib_edit_t edit, duilib_color_t color);
DUILIB_C_API duilib_color_t duilib_edit_get_native_edit_bk_color(duilib_edit_t edit);

//=============================================================================
// 编辑框文本选择和操作 - 对应 CEditUI 文本操作方法
//=============================================================================

// 文本选择
DUILIB_C_API duilib_result_t duilib_edit_set_sel(duilib_edit_t edit, long start_char, long end_char);
DUILIB_C_API duilib_result_t duilib_edit_set_sel_all(duilib_edit_t edit);

// 替换选择的文本
DUILIB_C_API duilib_result_t duilib_edit_set_replace_sel(duilib_edit_t edit, const char* replace_text);

//=============================================================================
// 编辑框位置和布局 - 对应 CEditUI 布局方法
//=============================================================================

// 位置设置
DUILIB_C_API duilib_result_t duilib_edit_set_pos(duilib_edit_t edit, duilib_rect_t rect, bool need_invalidate);

// 移动
DUILIB_C_API duilib_result_t duilib_edit_move(duilib_edit_t edit, duilib_size_t offset, bool need_invalidate);

// 可见性
DUILIB_C_API duilib_result_t duilib_edit_set_visible(duilib_edit_t edit, bool visible);
DUILIB_C_API duilib_result_t duilib_edit_set_intern_visible(duilib_edit_t edit, bool visible);

// 估算尺寸
DUILIB_C_API duilib_size_t duilib_edit_estimate_size(duilib_edit_t edit, duilib_size_t available);

//=============================================================================
// 编辑框事件处理 - 对应 CEditUI 事件方法
//=============================================================================

// 事件处理
DUILIB_C_API duilib_result_t duilib_edit_do_event(duilib_edit_t edit, const duilib_ui_event_t* event);

//=============================================================================
// 编辑框属性管理 - 对应 CEditUI 属性方法
//=============================================================================

// 设置属性 - 对应 SetAttribute
DUILIB_C_API duilib_result_t duilib_edit_set_attribute(duilib_edit_t edit, const char* name, const char* value);

//=============================================================================
// 编辑框绘制方法 - 对应 CEditUI 绘制方法
//=============================================================================

// 绘制状态图片 - 对应 PaintStatusImage
DUILIB_C_API duilib_result_t duilib_edit_paint_status_image(duilib_edit_t edit, void* hdc);

// 绘制文本 - 对应 PaintText
DUILIB_C_API duilib_result_t duilib_edit_paint_text(duilib_edit_t edit, void* hdc);

//=============================================================================
// 继承自 CLabelUI 的方法访问
//=============================================================================

// 从编辑框获取标签接口进行文本操作
DUILIB_C_API const char* duilib_edit_get_text(duilib_edit_t edit);

// 文本样式
DUILIB_C_API uint32_t duilib_edit_get_text_style(duilib_edit_t edit);
DUILIB_C_API duilib_result_t duilib_edit_set_text_style(duilib_edit_t edit, uint32_t style);

// 文本颜色
DUILIB_C_API duilib_color_t duilib_edit_get_text_color(duilib_edit_t edit);
DUILIB_C_API duilib_result_t duilib_edit_set_text_color(duilib_edit_t edit, duilib_color_t color);

// 禁用文本颜色
DUILIB_C_API duilib_color_t duilib_edit_get_disabled_text_color(duilib_edit_t edit);
DUILIB_C_API duilib_result_t duilib_edit_set_disabled_text_color(duilib_edit_t edit, duilib_color_t color);

// 字体
DUILIB_C_API int duilib_edit_get_font(duilib_edit_t edit);
DUILIB_C_API duilib_result_t duilib_edit_set_font(duilib_edit_t edit, int font_index);

// 文本边距
DUILIB_C_API duilib_rect_t duilib_edit_get_text_padding(duilib_edit_t edit);
DUILIB_C_API duilib_result_t duilib_edit_set_text_padding(duilib_edit_t edit, duilib_rect_t padding);

// 多行文本支持
DUILIB_C_API bool duilib_edit_is_multiline(duilib_edit_t edit);
DUILIB_C_API duilib_result_t duilib_edit_set_multiline(duilib_edit_t edit, bool multiline);

// HTML文本支持
DUILIB_C_API bool duilib_edit_is_show_html(duilib_edit_t edit);
DUILIB_C_API duilib_result_t duilib_edit_set_show_html(duilib_edit_t edit, bool show_html);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_EDIT_H__