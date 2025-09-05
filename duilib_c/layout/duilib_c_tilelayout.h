#ifndef __DUILIB_C_TILELAYOUT_H__
#define __DUILIB_C_TILELAYOUT_H__

#include "../core/duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 平铺布局控件API - 对应 CTileLayoutUI
//=============================================================================

// 平铺布局控件句柄
typedef struct duilib_tilelayout* duilib_tilelayout_t;

//=============================================================================
// 平铺布局控件基础API
//=============================================================================

// 创建和销毁平铺布局控件
DUILIB_C_API duilib_tilelayout_t duilib_tilelayout_create(void);
DUILIB_C_API void duilib_tilelayout_destroy(duilib_tilelayout_t layout);

// 获取控件基类接口
DUILIB_C_API duilib_control_t duilib_tilelayout_to_control(duilib_tilelayout_t layout);
DUILIB_C_API duilib_tilelayout_t duilib_control_to_tilelayout(duilib_control_t control);

// 获取容器接口（继承关系）
DUILIB_C_API duilib_container_t duilib_tilelayout_to_container(duilib_tilelayout_t layout);
DUILIB_C_API duilib_tilelayout_t duilib_container_to_tilelayout(duilib_container_t container);

// 类型检查
DUILIB_C_API bool duilib_tilelayout_is_valid(duilib_tilelayout_t layout);

//=============================================================================
// CTileLayoutUI 核心方法 - 对应原始接口
//=============================================================================

// 类信息
DUILIB_C_API const char* duilib_tilelayout_get_class(duilib_tilelayout_t layout);
DUILIB_C_API void* duilib_tilelayout_get_interface(duilib_tilelayout_t layout, const char* name);

//=============================================================================
// 平铺布局位置设置 - 对应 CTileLayoutUI 位置方法
//=============================================================================

// 位置设置
DUILIB_C_API duilib_result_t duilib_tilelayout_set_pos(duilib_tilelayout_t layout, duilib_rect_t rect, bool need_invalidate);

//=============================================================================
// 平铺布局列管理 - 对应 CTileLayoutUI 列管理方法
//=============================================================================

// 固定列数
DUILIB_C_API int duilib_tilelayout_get_fixed_columns(duilib_tilelayout_t layout);
DUILIB_C_API duilib_result_t duilib_tilelayout_set_fixed_columns(duilib_tilelayout_t layout, int columns);

// 子控件垂直边距
DUILIB_C_API int duilib_tilelayout_get_child_v_padding(duilib_tilelayout_t layout);
DUILIB_C_API duilib_result_t duilib_tilelayout_set_child_v_padding(duilib_tilelayout_t layout, int padding);

//=============================================================================
// 平铺布局项目尺寸管理 - 对应 CTileLayoutUI 项目尺寸方法
//=============================================================================

// 项目尺寸
DUILIB_C_API duilib_size_t duilib_tilelayout_get_item_size(duilib_tilelayout_t layout);
DUILIB_C_API duilib_result_t duilib_tilelayout_set_item_size(duilib_tilelayout_t layout, duilib_size_t size);

// 获取当前布局信息
DUILIB_C_API int duilib_tilelayout_get_columns(duilib_tilelayout_t layout);
DUILIB_C_API int duilib_tilelayout_get_rows(duilib_tilelayout_t layout);

//=============================================================================
// 平铺布局属性 - 对应 CTileLayoutUI 属性方法
//=============================================================================

// 设置属性
DUILIB_C_API duilib_result_t duilib_tilelayout_set_attribute(duilib_tilelayout_t layout, const char* name, const char* value);

//=============================================================================
// 继承自 CContainerUI 的方法访问
//=============================================================================

// 从平铺布局获取容器接口进行容器操作
DUILIB_C_API bool duilib_tilelayout_add(duilib_tilelayout_t layout, duilib_control_t control);
DUILIB_C_API bool duilib_tilelayout_add_at(duilib_tilelayout_t layout, duilib_control_t control, int index);
DUILIB_C_API bool duilib_tilelayout_remove(duilib_tilelayout_t layout, duilib_control_t control, bool do_not_destroy);
DUILIB_C_API bool duilib_tilelayout_remove_at(duilib_tilelayout_t layout, int index, bool do_not_destroy);
DUILIB_C_API duilib_result_t duilib_tilelayout_remove_all(duilib_tilelayout_t layout);

// 子控件管理
DUILIB_C_API int duilib_tilelayout_get_count(duilib_tilelayout_t layout);
DUILIB_C_API duilib_control_t duilib_tilelayout_get_item_at(duilib_tilelayout_t layout, int index);
DUILIB_C_API int duilib_tilelayout_get_item_index(duilib_tilelayout_t layout, duilib_control_t control);
DUILIB_C_API bool duilib_tilelayout_set_item_index(duilib_tilelayout_t layout, duilib_control_t control, int new_index);

// 内边距管理
DUILIB_C_API duilib_rect_t duilib_tilelayout_get_inset(duilib_tilelayout_t layout);
DUILIB_C_API duilib_result_t duilib_tilelayout_set_inset(duilib_tilelayout_t layout, duilib_rect_t inset);

// 子控件边距
DUILIB_C_API int duilib_tilelayout_get_child_padding(duilib_tilelayout_t layout);
DUILIB_C_API duilib_result_t duilib_tilelayout_set_child_padding(duilib_tilelayout_t layout, int padding);

// 鼠标子控件启用
DUILIB_C_API bool duilib_tilelayout_is_mouse_child_enabled(duilib_tilelayout_t layout);
DUILIB_C_API duilib_result_t duilib_tilelayout_set_mouse_child_enabled(duilib_tilelayout_t layout, bool enabled);

// 滚动条管理
DUILIB_C_API duilib_scrollbar_t duilib_tilelayout_get_vertical_scrollbar(duilib_tilelayout_t layout);
DUILIB_C_API duilib_scrollbar_t duilib_tilelayout_get_horizontal_scrollbar(duilib_tilelayout_t layout);

// 可见性管理
DUILIB_C_API duilib_result_t duilib_tilelayout_set_visible(duilib_tilelayout_t layout, bool visible);
DUILIB_C_API duilib_result_t duilib_tilelayout_set_intern_visible(duilib_tilelayout_t layout, bool visible);

// 启用状态
DUILIB_C_API duilib_result_t duilib_tilelayout_set_enabled(duilib_tilelayout_t layout, bool enabled);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_TILELAYOUT_H__