#ifndef __DUILIB_C_SLIDER_H__
#define __DUILIB_C_SLIDER_H__

#include "../core/duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 滑块控件API - 对应 CSliderUI
//=============================================================================

// 滑块控件句柄
typedef struct duilib_slider* duilib_slider_t;

//=============================================================================
// 滑块控件基础API
//=============================================================================

// 创建和销毁滑块控件
DUILIB_C_API duilib_slider_t duilib_slider_create(void);
DUILIB_C_API void duilib_slider_destroy(duilib_slider_t slider);

// 获取控件基类接口
DUILIB_C_API duilib_control_t duilib_slider_to_control(duilib_slider_t slider);
DUILIB_C_API duilib_slider_t duilib_control_to_slider(duilib_control_t control);

// 获取进度条接口（继承关系）
DUILIB_C_API duilib_progress_t duilib_slider_to_progress(duilib_slider_t slider);
DUILIB_C_API duilib_slider_t duilib_progress_to_slider(duilib_progress_t progress);

// 类型检查
DUILIB_C_API bool duilib_slider_is_valid(duilib_slider_t slider);

//=============================================================================
// CSliderUI 核心方法 - 对应原始接口
//=============================================================================

// 类信息
DUILIB_C_API const char* duilib_slider_get_class(duilib_slider_t slider);
DUILIB_C_API uint32_t duilib_slider_get_control_flags(duilib_slider_t slider);
DUILIB_C_API void* duilib_slider_get_interface(duilib_slider_t slider, const char* name);

// 启用状态
DUILIB_C_API duilib_result_t duilib_slider_set_enabled(duilib_slider_t slider, bool enabled);

//=============================================================================
// 滑块步长和滑块管理 - 对应 CSliderUI 滑块方法
//=============================================================================

// 改变步长
DUILIB_C_API int duilib_slider_get_change_step(duilib_slider_t slider);
DUILIB_C_API duilib_result_t duilib_slider_set_change_step(duilib_slider_t slider, int step);

// 滑块尺寸
DUILIB_C_API duilib_result_t duilib_slider_set_thumb_size(duilib_slider_t slider, duilib_size_t size);

// 滑块矩形区域
DUILIB_C_API duilib_rect_t duilib_slider_get_thumb_rect(duilib_slider_t slider);

// 即时模式
DUILIB_C_API bool duilib_slider_is_imm_mode(duilib_slider_t slider);
DUILIB_C_API duilib_result_t duilib_slider_set_imm_mode(duilib_slider_t slider, bool imm_mode);

//=============================================================================
// 滑块图片状态管理 - 对应 CSliderUI 滑块图片方法
//=============================================================================

// 滑块普通状态图片
DUILIB_C_API const char* duilib_slider_get_thumb_image(duilib_slider_t slider);
DUILIB_C_API duilib_result_t duilib_slider_set_thumb_image(duilib_slider_t slider, const char* image);

// 滑块热点状态图片
DUILIB_C_API const char* duilib_slider_get_thumb_hot_image(duilib_slider_t slider);
DUILIB_C_API duilib_result_t duilib_slider_set_thumb_hot_image(duilib_slider_t slider, const char* image);

// 滑块按下状态图片
DUILIB_C_API const char* duilib_slider_get_thumb_pushed_image(duilib_slider_t slider);
DUILIB_C_API duilib_result_t duilib_slider_set_thumb_pushed_image(duilib_slider_t slider, const char* image);

//=============================================================================
// 滑块事件和绘制 - 对应 CSliderUI 事件和绘制方法
//=============================================================================

// 事件处理
DUILIB_C_API duilib_result_t duilib_slider_do_event(duilib_slider_t slider, const duilib_ui_event_t* event);

// 设置属性
DUILIB_C_API duilib_result_t duilib_slider_set_attribute(duilib_slider_t slider, const char* name, const char* value);

// 绘制状态图片
DUILIB_C_API duilib_result_t duilib_slider_paint_status_image(duilib_slider_t slider, void* hdc);

//=============================================================================
// 继承自 CProgressUI 的方法访问
//=============================================================================

// 从滑块获取进度条接口进行进度条操作
DUILIB_C_API const char* duilib_slider_get_text(duilib_slider_t slider);
DUILIB_C_API duilib_result_t duilib_slider_set_text(duilib_slider_t slider, const char* text);

// 方向控制
DUILIB_C_API bool duilib_slider_is_horizontal(duilib_slider_t slider);
DUILIB_C_API duilib_result_t duilib_slider_set_horizontal(duilib_slider_t slider, bool horizontal);

// 值管理
DUILIB_C_API int duilib_slider_get_min_value(duilib_slider_t slider);
DUILIB_C_API duilib_result_t duilib_slider_set_min_value(duilib_slider_t slider, int min_value);

DUILIB_C_API int duilib_slider_get_max_value(duilib_slider_t slider);
DUILIB_C_API duilib_result_t duilib_slider_set_max_value(duilib_slider_t slider, int max_value);

DUILIB_C_API int duilib_slider_get_value(duilib_slider_t slider);
DUILIB_C_API duilib_result_t duilib_slider_set_value(duilib_slider_t slider, int value);

// 前景图片
DUILIB_C_API const char* duilib_slider_get_fore_image(duilib_slider_t slider);
DUILIB_C_API duilib_result_t duilib_slider_set_fore_image(duilib_slider_t slider, const char* image);

// 文本样式
DUILIB_C_API uint32_t duilib_slider_get_text_style(duilib_slider_t slider);
DUILIB_C_API duilib_result_t duilib_slider_set_text_style(duilib_slider_t slider, uint32_t style);

// 文本颜色
DUILIB_C_API duilib_color_t duilib_slider_get_text_color(duilib_slider_t slider);
DUILIB_C_API duilib_result_t duilib_slider_set_text_color(duilib_slider_t slider, duilib_color_t color);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_SLIDER_H__