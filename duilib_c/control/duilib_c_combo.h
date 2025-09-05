#ifndef __DUILIB_C_COMBO_H__
#define __DUILIB_C_COMBO_H__

#include "../core/duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 组合框控件API - 对应 CComboUI
//=============================================================================

// 组合框控件句柄
typedef struct duilib_combo* duilib_combo_t;

//=============================================================================
// 组合框控件基础API
//=============================================================================

// 创建和销毁组合框控件
DUILIB_C_API duilib_combo_t duilib_combo_create(void);
DUILIB_C_API void duilib_combo_destroy(duilib_combo_t combo);

// 获取控件基类接口
DUILIB_C_API duilib_control_t duilib_combo_to_control(duilib_combo_t combo);
DUILIB_C_API duilib_combo_t duilib_control_to_combo(duilib_control_t control);

// 类型检查
DUILIB_C_API bool duilib_combo_is_valid(duilib_combo_t combo);

//=============================================================================
// CComboUI 核心方法 - 对应原始接口
//=============================================================================

// 类信息
DUILIB_C_API const char* duilib_combo_get_class(duilib_combo_t combo);
DUILIB_C_API void* duilib_combo_get_interface(duilib_combo_t combo, const char* name);
DUILIB_C_API uint32_t duilib_combo_get_control_flags(duilib_combo_t combo);

// 初始化和状态
DUILIB_C_API duilib_result_t duilib_combo_do_init(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_enabled(duilib_combo_t combo, bool enabled);
DUILIB_C_API bool duilib_combo_activate(duilib_combo_t combo);

//=============================================================================
// 组合框文本和内容管理 - 对应 CComboUI 文本方法
//=============================================================================

// 文本内容
DUILIB_C_API const char* duilib_combo_get_text(duilib_combo_t combo);

// 显示文本标志
DUILIB_C_API bool duilib_combo_get_show_text(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_show_text(duilib_combo_t combo, bool show_text);

// 文本边距
DUILIB_C_API duilib_rect_t duilib_combo_get_text_padding(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_text_padding(duilib_combo_t combo, duilib_rect_t padding);

//=============================================================================
// 下拉框管理 - 对应 CComboUI 下拉框方法
//=============================================================================

// 下拉框属性
DUILIB_C_API const char* duilib_combo_get_drop_box_attribute_list(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_drop_box_attribute_list(duilib_combo_t combo, const char* attribute_list);

// 下拉框尺寸
DUILIB_C_API duilib_size_t duilib_combo_get_drop_box_size(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_drop_box_size(duilib_combo_t combo, duilib_size_t size);

//=============================================================================
// 选择管理 - 对应 CComboUI 选择方法
//=============================================================================

// 当前选择
DUILIB_C_API int duilib_combo_get_cur_sel(duilib_combo_t combo);

// 选择关闭标志
DUILIB_C_API bool duilib_combo_get_select_close_flag(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_select_close_flag(duilib_combo_t combo, bool flag);

// 选择项目
DUILIB_C_API bool duilib_combo_select_item(duilib_combo_t combo, int index, bool take_focus, bool trigger_event);

// 展开项目
DUILIB_C_API bool duilib_combo_expand_item(duilib_combo_t combo, int index, bool expand);
DUILIB_C_API int duilib_combo_get_expanded_item(duilib_combo_t combo);

//=============================================================================
// 项目管理 - 对应 CComboUI 项目管理方法
//=============================================================================

// 设置项目索引
DUILIB_C_API bool duilib_combo_set_item_index(duilib_combo_t combo, duilib_control_t control, int new_index);
DUILIB_C_API bool duilib_combo_set_multi_item_index(duilib_combo_t combo, duilib_control_t start_control, int count, int new_start_index);

// 添加项目
DUILIB_C_API bool duilib_combo_add(duilib_combo_t combo, duilib_control_t control);
DUILIB_C_API bool duilib_combo_add_at(duilib_combo_t combo, duilib_control_t control, int index);

// 移除项目
DUILIB_C_API bool duilib_combo_remove(duilib_combo_t combo, duilib_control_t control, bool do_not_destroy);
DUILIB_C_API bool duilib_combo_remove_at(duilib_combo_t combo, int index, bool do_not_destroy);
DUILIB_C_API duilib_result_t duilib_combo_remove_all(duilib_combo_t combo);

//=============================================================================
// 组合框图片状态管理 - 对应 CComboUI 图片方法
//=============================================================================

// 普通状态图片
DUILIB_C_API const char* duilib_combo_get_normal_image(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_normal_image(duilib_combo_t combo, const char* image);

// 热点状态图片
DUILIB_C_API const char* duilib_combo_get_hot_image(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_hot_image(duilib_combo_t combo, const char* image);

// 按下状态图片
DUILIB_C_API const char* duilib_combo_get_pushed_image(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_pushed_image(duilib_combo_t combo, const char* image);

// 焦点状态图片
DUILIB_C_API const char* duilib_combo_get_focused_image(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_focused_image(duilib_combo_t combo, const char* image);

// 禁用状态图片
DUILIB_C_API const char* duilib_combo_get_disabled_image(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_disabled_image(duilib_combo_t combo, const char* image);

//=============================================================================
// 列表信息和项目样式 - 对应 CComboUI 列表信息方法
//=============================================================================

// 项目固定高度
DUILIB_C_API uint32_t duilib_combo_get_item_fixed_height(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_item_fixed_height(duilib_combo_t combo, uint32_t height);

// 项目字体
DUILIB_C_API int duilib_combo_get_item_font(duilib_combo_t combo, int index);
DUILIB_C_API duilib_result_t duilib_combo_set_item_font(duilib_combo_t combo, int index);

// 项目文本样式
DUILIB_C_API uint32_t duilib_combo_get_item_text_style(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_item_text_style(duilib_combo_t combo, uint32_t style);

// 项目文本边距
DUILIB_C_API duilib_rect_t duilib_combo_get_item_text_padding(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_item_text_padding(duilib_combo_t combo, duilib_rect_t padding);

// 项目文本颜色
DUILIB_C_API duilib_color_t duilib_combo_get_item_text_color(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_item_text_color(duilib_combo_t combo, duilib_color_t color);

// 项目背景颜色
DUILIB_C_API duilib_color_t duilib_combo_get_item_bk_color(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_item_bk_color(duilib_combo_t combo, duilib_color_t color);

// 项目背景图片
DUILIB_C_API const char* duilib_combo_get_item_bk_image(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_item_bk_image(duilib_combo_t combo, const char* image);

// 交替背景
DUILIB_C_API bool duilib_combo_is_alternate_bk(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_alternate_bk(duilib_combo_t combo, bool alternate_bk);

//=============================================================================
// 选择项样式 - 对应 CComboUI 选择项样式方法
//=============================================================================

// 选择项文本颜色
DUILIB_C_API duilib_color_t duilib_combo_get_selected_item_text_color(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_selected_item_text_color(duilib_combo_t combo, duilib_color_t color);

// 选择项背景颜色
DUILIB_C_API duilib_color_t duilib_combo_get_selected_item_bk_color(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_selected_item_bk_color(duilib_combo_t combo, duilib_color_t color);

// 选择项图片
DUILIB_C_API const char* duilib_combo_get_selected_item_image(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_selected_item_image(duilib_combo_t combo, const char* image);

//=============================================================================
// 热点项样式 - 对应 CComboUI 热点项样式方法
//=============================================================================

// 热点项文本颜色
DUILIB_C_API duilib_color_t duilib_combo_get_hot_item_text_color(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_hot_item_text_color(duilib_combo_t combo, duilib_color_t color);

// 热点项背景颜色
DUILIB_C_API duilib_color_t duilib_combo_get_hot_item_bk_color(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_hot_item_bk_color(duilib_combo_t combo, duilib_color_t color);

// 热点项图片
DUILIB_C_API const char* duilib_combo_get_hot_item_image(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_hot_item_image(duilib_combo_t combo, const char* image);

//=============================================================================
// 禁用项样式 - 对应 CComboUI 禁用项样式方法
//=============================================================================

// 禁用项文本颜色
DUILIB_C_API duilib_color_t duilib_combo_get_disabled_item_text_color(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_disabled_item_text_color(duilib_combo_t combo, duilib_color_t color);

// 禁用项背景颜色
DUILIB_C_API duilib_color_t duilib_combo_get_disabled_item_bk_color(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_disabled_item_bk_color(duilib_combo_t combo, duilib_color_t color);

// 禁用项图片
DUILIB_C_API const char* duilib_combo_get_disabled_item_image(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_disabled_item_image(duilib_combo_t combo, const char* image);

//=============================================================================
// 分隔线样式 - 对应 CComboUI 分隔线方法
//=============================================================================

// 水平分隔线
DUILIB_C_API int duilib_combo_get_item_h_line_size(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_item_h_line_size(duilib_combo_t combo, int size);

DUILIB_C_API duilib_color_t duilib_combo_get_item_h_line_color(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_item_h_line_color(duilib_combo_t combo, duilib_color_t color);

// 垂直分隔线
DUILIB_C_API int duilib_combo_get_item_v_line_size(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_item_v_line_size(duilib_combo_t combo, int size);

DUILIB_C_API duilib_color_t duilib_combo_get_item_v_line_color(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_item_v_line_color(duilib_combo_t combo, duilib_color_t color);

// HTML支持
DUILIB_C_API bool duilib_combo_is_item_show_html(duilib_combo_t combo);
DUILIB_C_API duilib_result_t duilib_combo_set_item_show_html(duilib_combo_t combo, bool show_html);

//=============================================================================
// 组合框布局和事件 - 对应 CComboUI 布局和事件方法
//=============================================================================

// 估算尺寸
DUILIB_C_API duilib_size_t duilib_combo_estimate_size(duilib_combo_t combo, duilib_size_t available);

// 位置设置
DUILIB_C_API duilib_result_t duilib_combo_set_pos(duilib_combo_t combo, duilib_rect_t rect, bool need_invalidate);

// 移动
DUILIB_C_API duilib_result_t duilib_combo_move(duilib_combo_t combo, duilib_size_t offset, bool need_invalidate);

// 事件处理
DUILIB_C_API duilib_result_t duilib_combo_do_event(duilib_combo_t combo, const duilib_ui_event_t* event);

// 属性设置
DUILIB_C_API duilib_result_t duilib_combo_set_attribute(duilib_combo_t combo, const char* name, const char* value);

//=============================================================================
// 组合框绘制方法 - 对应 CComboUI 绘制方法
//=============================================================================

// 绘制
DUILIB_C_API bool duilib_combo_do_paint(duilib_combo_t combo, void* hdc, duilib_rect_t paint_rect, duilib_control_t stop_control);

// 绘制文本
DUILIB_C_API duilib_result_t duilib_combo_paint_text(duilib_combo_t combo, void* hdc);

// 绘制状态图片
DUILIB_C_API duilib_result_t duilib_combo_paint_status_image(duilib_combo_t combo, void* hdc);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_COMBO_H__