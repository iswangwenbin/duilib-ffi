#ifndef __DUILIB_C_SCROLLBAR_H__
#define __DUILIB_C_SCROLLBAR_H__

#include "../core/duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 滚动条控件API - 对应 CScrollBarUI
//=============================================================================

// 滚动条控件句柄
typedef struct duilib_scrollbar* duilib_scrollbar_t;

//=============================================================================
// 滚动条控件基础API
//=============================================================================

// 创建和销毁滚动条控件
DUILIB_C_API duilib_scrollbar_t duilib_scrollbar_create(void);
DUILIB_C_API void duilib_scrollbar_destroy(duilib_scrollbar_t scrollbar);

// 获取控件基类接口
DUILIB_C_API duilib_control_t duilib_scrollbar_to_control(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_scrollbar_t duilib_control_to_scrollbar(duilib_control_t control);

// 类型检查
DUILIB_C_API bool duilib_scrollbar_is_valid(duilib_scrollbar_t scrollbar);

//=============================================================================
// CScrollBarUI 核心方法 - 对应原始接口
//=============================================================================

// 类信息
DUILIB_C_API const char* duilib_scrollbar_get_class(duilib_scrollbar_t scrollbar);
DUILIB_C_API void* duilib_scrollbar_get_interface(duilib_scrollbar_t scrollbar, const char* name);

//=============================================================================
// 滚动条拥有者和状态管理 - 对应 CScrollBarUI 拥有者和状态方法
//=============================================================================

// 拥有者管理
DUILIB_C_API duilib_control_t duilib_scrollbar_get_owner(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_owner(duilib_scrollbar_t scrollbar, duilib_control_t owner);

// 可见性和启用状态
DUILIB_C_API duilib_result_t duilib_scrollbar_set_visible(duilib_scrollbar_t scrollbar, bool visible);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_enabled(duilib_scrollbar_t scrollbar, bool enabled);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_focus(duilib_scrollbar_t scrollbar);

//=============================================================================
// 滚动条方向和范围管理 - 对应 CScrollBarUI 方向和范围方法
//=============================================================================

// 水平/垂直方向
DUILIB_C_API bool duilib_scrollbar_is_horizontal(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_horizontal(duilib_scrollbar_t scrollbar, bool horizontal);

// 滚动范围
DUILIB_C_API int duilib_scrollbar_get_scroll_range(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_scroll_range(duilib_scrollbar_t scrollbar, int range);

// 滚动位置
DUILIB_C_API int duilib_scrollbar_get_scroll_pos(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_scroll_pos(duilib_scrollbar_t scrollbar, int pos, bool trigger_event);

// 行尺寸
DUILIB_C_API int duilib_scrollbar_get_line_size(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_line_size(duilib_scrollbar_t scrollbar, int size);

// 滚动单位
DUILIB_C_API int duilib_scrollbar_get_scroll_unit(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_scroll_unit(duilib_scrollbar_t scrollbar, int unit);

//=============================================================================
// 按钮1管理 - 对应 CScrollBarUI 按钮1方法
//=============================================================================

// 显示按钮1
DUILIB_C_API bool duilib_scrollbar_get_show_button1(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_show_button1(duilib_scrollbar_t scrollbar, bool show);

// 按钮1颜色
DUILIB_C_API duilib_color_t duilib_scrollbar_get_button1_color(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_button1_color(duilib_scrollbar_t scrollbar, duilib_color_t color);

// 按钮1图片
DUILIB_C_API const char* duilib_scrollbar_get_button1_normal_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_button1_normal_image(duilib_scrollbar_t scrollbar, const char* image);

DUILIB_C_API const char* duilib_scrollbar_get_button1_hot_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_button1_hot_image(duilib_scrollbar_t scrollbar, const char* image);

DUILIB_C_API const char* duilib_scrollbar_get_button1_pushed_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_button1_pushed_image(duilib_scrollbar_t scrollbar, const char* image);

DUILIB_C_API const char* duilib_scrollbar_get_button1_disabled_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_button1_disabled_image(duilib_scrollbar_t scrollbar, const char* image);

//=============================================================================
// 按钮2管理 - 对应 CScrollBarUI 按钮2方法
//=============================================================================

// 显示按钮2
DUILIB_C_API bool duilib_scrollbar_get_show_button2(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_show_button2(duilib_scrollbar_t scrollbar, bool show);

// 按钮2颜色
DUILIB_C_API duilib_color_t duilib_scrollbar_get_button2_color(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_button2_color(duilib_scrollbar_t scrollbar, duilib_color_t color);

// 按钮2图片
DUILIB_C_API const char* duilib_scrollbar_get_button2_normal_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_button2_normal_image(duilib_scrollbar_t scrollbar, const char* image);

DUILIB_C_API const char* duilib_scrollbar_get_button2_hot_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_button2_hot_image(duilib_scrollbar_t scrollbar, const char* image);

DUILIB_C_API const char* duilib_scrollbar_get_button2_pushed_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_button2_pushed_image(duilib_scrollbar_t scrollbar, const char* image);

DUILIB_C_API const char* duilib_scrollbar_get_button2_disabled_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_button2_disabled_image(duilib_scrollbar_t scrollbar, const char* image);

//=============================================================================
// 滑块管理 - 对应 CScrollBarUI 滑块方法
//=============================================================================

// 滑块颜色
DUILIB_C_API duilib_color_t duilib_scrollbar_get_thumb_color(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_thumb_color(duilib_scrollbar_t scrollbar, duilib_color_t color);

// 滑块图片
DUILIB_C_API const char* duilib_scrollbar_get_thumb_normal_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_thumb_normal_image(duilib_scrollbar_t scrollbar, const char* image);

DUILIB_C_API const char* duilib_scrollbar_get_thumb_hot_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_thumb_hot_image(duilib_scrollbar_t scrollbar, const char* image);

DUILIB_C_API const char* duilib_scrollbar_get_thumb_pushed_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_thumb_pushed_image(duilib_scrollbar_t scrollbar, const char* image);

DUILIB_C_API const char* duilib_scrollbar_get_thumb_disabled_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_thumb_disabled_image(duilib_scrollbar_t scrollbar, const char* image);

//=============================================================================
// 导轨管理 - 对应 CScrollBarUI 导轨方法
//=============================================================================

// 导轨图片
DUILIB_C_API const char* duilib_scrollbar_get_rail_normal_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_rail_normal_image(duilib_scrollbar_t scrollbar, const char* image);

DUILIB_C_API const char* duilib_scrollbar_get_rail_hot_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_rail_hot_image(duilib_scrollbar_t scrollbar, const char* image);

DUILIB_C_API const char* duilib_scrollbar_get_rail_pushed_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_rail_pushed_image(duilib_scrollbar_t scrollbar, const char* image);

DUILIB_C_API const char* duilib_scrollbar_get_rail_disabled_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_rail_disabled_image(duilib_scrollbar_t scrollbar, const char* image);

//=============================================================================
// 背景管理 - 对应 CScrollBarUI 背景方法
//=============================================================================

// 背景图片
DUILIB_C_API const char* duilib_scrollbar_get_bk_normal_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_bk_normal_image(duilib_scrollbar_t scrollbar, const char* image);

DUILIB_C_API const char* duilib_scrollbar_get_bk_hot_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_bk_hot_image(duilib_scrollbar_t scrollbar, const char* image);

DUILIB_C_API const char* duilib_scrollbar_get_bk_pushed_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_bk_pushed_image(duilib_scrollbar_t scrollbar, const char* image);

DUILIB_C_API const char* duilib_scrollbar_get_bk_disabled_image(duilib_scrollbar_t scrollbar);
DUILIB_C_API duilib_result_t duilib_scrollbar_set_bk_disabled_image(duilib_scrollbar_t scrollbar, const char* image);

//=============================================================================
// 滚动条位置和事件 - 对应 CScrollBarUI 位置和事件方法
//=============================================================================

// 位置设置
DUILIB_C_API duilib_result_t duilib_scrollbar_set_pos(duilib_scrollbar_t scrollbar, duilib_rect_t rect, bool need_invalidate);

// 事件处理
DUILIB_C_API duilib_result_t duilib_scrollbar_do_event(duilib_scrollbar_t scrollbar, const duilib_ui_event_t* event);

// 设置属性
DUILIB_C_API duilib_result_t duilib_scrollbar_set_attribute(duilib_scrollbar_t scrollbar, const char* name, const char* value);

//=============================================================================
// 滚动条绘制方法 - 对应 CScrollBarUI 绘制方法
//=============================================================================

// 绘制
DUILIB_C_API bool duilib_scrollbar_do_paint(duilib_scrollbar_t scrollbar, void* hdc, duilib_rect_t paint_rect, duilib_control_t stop_control);

// 绘制背景
DUILIB_C_API duilib_result_t duilib_scrollbar_paint_bk(duilib_scrollbar_t scrollbar, void* hdc);

// 绘制按钮1
DUILIB_C_API duilib_result_t duilib_scrollbar_paint_button1(duilib_scrollbar_t scrollbar, void* hdc);

// 绘制按钮2
DUILIB_C_API duilib_result_t duilib_scrollbar_paint_button2(duilib_scrollbar_t scrollbar, void* hdc);

// 绘制滑块
DUILIB_C_API duilib_result_t duilib_scrollbar_paint_thumb(duilib_scrollbar_t scrollbar, void* hdc);

// 绘制导轨
DUILIB_C_API duilib_result_t duilib_scrollbar_paint_rail(duilib_scrollbar_t scrollbar, void* hdc);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_SCROLLBAR_H__