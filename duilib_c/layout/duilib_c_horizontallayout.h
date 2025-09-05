#ifndef __DUILIB_C_HORIZONTALLAYOUT_H__
#define __DUILIB_C_HORIZONTALLAYOUT_H__

#include "../core/duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 水平布局控件API - 对应 CHorizontalLayoutUI
//=============================================================================

// 水平布局控件句柄
typedef struct duilib_horizontallayout* duilib_horizontallayout_t;

//=============================================================================
// 水平布局控件基础API
//=============================================================================

// 创建和销毁水平布局控件
DUILIB_C_API duilib_horizontallayout_t duilib_horizontallayout_create(void);
DUILIB_C_API void duilib_horizontallayout_destroy(duilib_horizontallayout_t layout);

// 获取控件基类接口
DUILIB_C_API duilib_control_t duilib_horizontallayout_to_control(duilib_horizontallayout_t layout);
DUILIB_C_API duilib_horizontallayout_t duilib_control_to_horizontallayout(duilib_control_t control);

// 获取容器接口（继承关系）
DUILIB_C_API duilib_container_t duilib_horizontallayout_to_container(duilib_horizontallayout_t layout);
DUILIB_C_API duilib_horizontallayout_t duilib_container_to_horizontallayout(duilib_container_t container);

// 类型检查
DUILIB_C_API bool duilib_horizontallayout_is_valid(duilib_horizontallayout_t layout);

//=============================================================================
// CHorizontalLayoutUI 核心方法 - 对应原始接口
//=============================================================================

// 类信息
DUILIB_C_API const char* duilib_horizontallayout_get_class(duilib_horizontallayout_t layout);
DUILIB_C_API void* duilib_horizontallayout_get_interface(duilib_horizontallayout_t layout, const char* name);
DUILIB_C_API uint32_t duilib_horizontallayout_get_control_flags(duilib_horizontallayout_t layout);

//=============================================================================
// 水平布局分隔器管理 - 对应 CHorizontalLayoutUI 分隔器方法
//=============================================================================

// 分隔器宽度
DUILIB_C_API duilib_result_t duilib_horizontallayout_set_sep_width(duilib_horizontallayout_t layout, int width);
DUILIB_C_API int duilib_horizontallayout_get_sep_width(duilib_horizontallayout_t layout);

// 即时模式 - 分隔器立即调整
DUILIB_C_API duilib_result_t duilib_horizontallayout_set_sep_imm_mode(duilib_horizontallayout_t layout, bool immediate);
DUILIB_C_API bool duilib_horizontallayout_is_sep_imm_mode(duilib_horizontallayout_t layout);

//=============================================================================
// 水平布局属性和事件 - 对应 CHorizontalLayoutUI 属性和事件方法
//=============================================================================

// 设置属性
DUILIB_C_API duilib_result_t duilib_horizontallayout_set_attribute(duilib_horizontallayout_t layout, const char* name, const char* value);

// 事件处理
DUILIB_C_API duilib_result_t duilib_horizontallayout_do_event(duilib_horizontallayout_t layout, const duilib_ui_event_t* event);

//=============================================================================
// 水平布局位置和绘制 - 对应 CHorizontalLayoutUI 位置和绘制方法
//=============================================================================

// 位置设置
DUILIB_C_API duilib_result_t duilib_horizontallayout_set_pos(duilib_horizontallayout_t layout, duilib_rect_t rect, bool need_invalidate);

// 后绘制处理
DUILIB_C_API duilib_result_t duilib_horizontallayout_do_post_paint(duilib_horizontallayout_t layout, void* hdc, duilib_rect_t paint_rect);

// 获取缩略图矩形区域
DUILIB_C_API duilib_rect_t duilib_horizontallayout_get_thumb_rect(duilib_horizontallayout_t layout, bool use_new);

//=============================================================================
// 继承自 CContainerUI 的方法访问
//=============================================================================

// 从水平布局获取容器接口进行容器操作
DUILIB_C_API bool duilib_horizontallayout_add(duilib_horizontallayout_t layout, duilib_control_t control);
DUILIB_C_API bool duilib_horizontallayout_add_at(duilib_horizontallayout_t layout, duilib_control_t control, int index);
DUILIB_C_API bool duilib_horizontallayout_remove(duilib_horizontallayout_t layout, duilib_control_t control, bool do_not_destroy);
DUILIB_C_API bool duilib_horizontallayout_remove_at(duilib_horizontallayout_t layout, int index, bool do_not_destroy);
DUILIB_C_API duilib_result_t duilib_horizontallayout_remove_all(duilib_horizontallayout_t layout);

// 子控件管理
DUILIB_C_API int duilib_horizontallayout_get_count(duilib_horizontallayout_t layout);
DUILIB_C_API duilib_control_t duilib_horizontallayout_get_item_at(duilib_horizontallayout_t layout, int index);
DUILIB_C_API int duilib_horizontallayout_get_item_index(duilib_horizontallayout_t layout, duilib_control_t control);
DUILIB_C_API bool duilib_horizontallayout_set_item_index(duilib_horizontallayout_t layout, duilib_control_t control, int new_index);

// 内边距管理
DUILIB_C_API duilib_rect_t duilib_horizontallayout_get_inset(duilib_horizontallayout_t layout);
DUILIB_C_API duilib_result_t duilib_horizontallayout_set_inset(duilib_horizontallayout_t layout, duilib_rect_t inset);

// 子控件边距
DUILIB_C_API int duilib_horizontallayout_get_child_padding(duilib_horizontallayout_t layout);
DUILIB_C_API duilib_result_t duilib_horizontallayout_set_child_padding(duilib_horizontallayout_t layout, int padding);

// 鼠标子控件启用
DUILIB_C_API bool duilib_horizontallayout_is_mouse_child_enabled(duilib_horizontallayout_t layout);
DUILIB_C_API duilib_result_t duilib_horizontallayout_set_mouse_child_enabled(duilib_horizontallayout_t layout, bool enabled);

// 滚动条管理
DUILIB_C_API duilib_scrollbar_t duilib_horizontallayout_get_vertical_scrollbar(duilib_horizontallayout_t layout);
DUILIB_C_API duilib_scrollbar_t duilib_horizontallayout_get_horizontal_scrollbar(duilib_horizontallayout_t layout);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_HORIZONTALLAYOUT_H__