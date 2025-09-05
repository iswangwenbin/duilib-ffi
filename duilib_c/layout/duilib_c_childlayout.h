#ifndef __DUILIB_C_CHILDLAYOUT_H__
#define __DUILIB_C_CHILDLAYOUT_H__

#include "../core/duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 子布局控件API - 对应 CChildLayoutUI
//=============================================================================

// 子布局控件句柄
typedef struct duilib_childlayout* duilib_childlayout_t;

//=============================================================================
// 子布局控件基础API
//=============================================================================

// 创建和销毁子布局控件
DUILIB_C_API duilib_childlayout_t duilib_childlayout_create(void);
DUILIB_C_API void duilib_childlayout_destroy(duilib_childlayout_t layout);

// 获取控件基类接口
DUILIB_C_API duilib_control_t duilib_childlayout_to_control(duilib_childlayout_t layout);
DUILIB_C_API duilib_childlayout_t duilib_control_to_childlayout(duilib_control_t control);

// 获取容器接口（继承关系）
DUILIB_C_API duilib_container_t duilib_childlayout_to_container(duilib_childlayout_t layout);
DUILIB_C_API duilib_childlayout_t duilib_container_to_childlayout(duilib_container_t container);

// 类型检查
DUILIB_C_API bool duilib_childlayout_is_valid(duilib_childlayout_t layout);

//=============================================================================
// CChildLayoutUI 核心方法 - 对应原始接口
//=============================================================================

// 类信息
DUILIB_C_API const char* duilib_childlayout_get_class(duilib_childlayout_t layout);
DUILIB_C_API void* duilib_childlayout_get_interface(duilib_childlayout_t layout, const char* name);

// 初始化
DUILIB_C_API duilib_result_t duilib_childlayout_init(duilib_childlayout_t layout);

//=============================================================================
// 子布局XML管理 - 对应 CChildLayoutUI XML方法
//=============================================================================

// 子布局XML设置和获取
DUILIB_C_API duilib_result_t duilib_childlayout_set_child_layout_xml(duilib_childlayout_t layout, const char* xml);
DUILIB_C_API const char* duilib_childlayout_get_child_layout_xml(duilib_childlayout_t layout);

//=============================================================================
// 子布局属性 - 对应 CChildLayoutUI 属性方法
//=============================================================================

// 设置属性
DUILIB_C_API duilib_result_t duilib_childlayout_set_attribute(duilib_childlayout_t layout, const char* name, const char* value);

//=============================================================================
// 继承自 CContainerUI 的方法访问
//=============================================================================

// 从子布局获取容器接口进行容器操作
DUILIB_C_API bool duilib_childlayout_add(duilib_childlayout_t layout, duilib_control_t control);
DUILIB_C_API bool duilib_childlayout_add_at(duilib_childlayout_t layout, duilib_control_t control, int index);
DUILIB_C_API bool duilib_childlayout_remove(duilib_childlayout_t layout, duilib_control_t control, bool do_not_destroy);
DUILIB_C_API bool duilib_childlayout_remove_at(duilib_childlayout_t layout, int index, bool do_not_destroy);
DUILIB_C_API duilib_result_t duilib_childlayout_remove_all(duilib_childlayout_t layout);

// 子控件管理
DUILIB_C_API int duilib_childlayout_get_count(duilib_childlayout_t layout);
DUILIB_C_API duilib_control_t duilib_childlayout_get_item_at(duilib_childlayout_t layout, int index);
DUILIB_C_API int duilib_childlayout_get_item_index(duilib_childlayout_t layout, duilib_control_t control);
DUILIB_C_API bool duilib_childlayout_set_item_index(duilib_childlayout_t layout, duilib_control_t control, int new_index);

// 内边距管理
DUILIB_C_API duilib_rect_t duilib_childlayout_get_inset(duilib_childlayout_t layout);
DUILIB_C_API duilib_result_t duilib_childlayout_set_inset(duilib_childlayout_t layout, duilib_rect_t inset);

// 子控件边距
DUILIB_C_API int duilib_childlayout_get_child_padding(duilib_childlayout_t layout);
DUILIB_C_API duilib_result_t duilib_childlayout_set_child_padding(duilib_childlayout_t layout, int padding);

// 鼠标子控件启用
DUILIB_C_API bool duilib_childlayout_is_mouse_child_enabled(duilib_childlayout_t layout);
DUILIB_C_API duilib_result_t duilib_childlayout_set_mouse_child_enabled(duilib_childlayout_t layout, bool enabled);

// 滚动条管理
DUILIB_C_API duilib_scrollbar_t duilib_childlayout_get_vertical_scrollbar(duilib_childlayout_t layout);
DUILIB_C_API duilib_scrollbar_t duilib_childlayout_get_horizontal_scrollbar(duilib_childlayout_t layout);

// 可见性管理
DUILIB_C_API duilib_result_t duilib_childlayout_set_visible(duilib_childlayout_t layout, bool visible);
DUILIB_C_API duilib_result_t duilib_childlayout_set_intern_visible(duilib_childlayout_t layout, bool visible);

// 启用状态
DUILIB_C_API duilib_result_t duilib_childlayout_set_enabled(duilib_childlayout_t layout, bool enabled);

// 位置和尺寸
DUILIB_C_API duilib_result_t duilib_childlayout_set_pos(duilib_childlayout_t layout, duilib_rect_t rect, bool need_invalidate);
DUILIB_C_API duilib_size_t duilib_childlayout_estimate_size(duilib_childlayout_t layout, duilib_size_t available);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_CHILDLAYOUT_H__