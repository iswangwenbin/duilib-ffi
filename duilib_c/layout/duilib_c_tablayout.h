#ifndef __DUILIB_C_TABLAYOUT_H__
#define __DUILIB_C_TABLAYOUT_H__

#include "../core/duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 标签页布局控件API - 对应 CTabLayoutUI
//=============================================================================

// 标签页布局控件句柄
typedef struct duilib_tablayout* duilib_tablayout_t;

//=============================================================================
// 标签页布局控件基础API
//=============================================================================

// 创建和销毁标签页布局控件
DUILIB_C_API duilib_tablayout_t duilib_tablayout_create(void);
DUILIB_C_API void duilib_tablayout_destroy(duilib_tablayout_t layout);

// 获取控件基类接口
DUILIB_C_API duilib_control_t duilib_tablayout_to_control(duilib_tablayout_t layout);
DUILIB_C_API duilib_tablayout_t duilib_control_to_tablayout(duilib_control_t control);

// 获取容器接口（继承关系）
DUILIB_C_API duilib_container_t duilib_tablayout_to_container(duilib_tablayout_t layout);
DUILIB_C_API duilib_tablayout_t duilib_container_to_tablayout(duilib_container_t container);

// 类型检查
DUILIB_C_API bool duilib_tablayout_is_valid(duilib_tablayout_t layout);

//=============================================================================
// CTabLayoutUI 核心方法 - 对应原始接口
//=============================================================================

// 类信息
DUILIB_C_API const char* duilib_tablayout_get_class(duilib_tablayout_t layout);
DUILIB_C_API void* duilib_tablayout_get_interface(duilib_tablayout_t layout, const char* name);

//=============================================================================
// 标签页项目管理 - 对应 CTabLayoutUI 项目管理方法
//=============================================================================

// 添加控件
DUILIB_C_API bool duilib_tablayout_add(duilib_tablayout_t layout, duilib_control_t control);
DUILIB_C_API bool duilib_tablayout_add_at(duilib_tablayout_t layout, duilib_control_t control, int index);

// 移除控件
DUILIB_C_API bool duilib_tablayout_remove(duilib_tablayout_t layout, duilib_control_t control, bool do_not_destroy);
DUILIB_C_API duilib_result_t duilib_tablayout_remove_all(duilib_tablayout_t layout);

//=============================================================================
// 标签页选择管理 - 对应 CTabLayoutUI 选择方法
//=============================================================================

// 当前选择
DUILIB_C_API int duilib_tablayout_get_cur_sel(duilib_tablayout_t layout);

// 选择项目 - 通过索引
DUILIB_C_API bool duilib_tablayout_select_item(duilib_tablayout_t layout, int index, bool trigger_event);

// 选择项目 - 通过控件
DUILIB_C_API bool duilib_tablayout_select_control(duilib_tablayout_t layout, duilib_control_t control, bool trigger_event);

//=============================================================================
// 标签页位置和属性 - 对应 CTabLayoutUI 位置和属性方法
//=============================================================================

// 位置设置
DUILIB_C_API duilib_result_t duilib_tablayout_set_pos(duilib_tablayout_t layout, duilib_rect_t rect, bool need_invalidate);

// 设置属性
DUILIB_C_API duilib_result_t duilib_tablayout_set_attribute(duilib_tablayout_t layout, const char* name, const char* value);

//=============================================================================
// 继承自 CContainerUI 的方法访问
//=============================================================================

// 从标签页布局获取容器接口进行容器操作
DUILIB_C_API int duilib_tablayout_get_count(duilib_tablayout_t layout);
DUILIB_C_API duilib_control_t duilib_tablayout_get_item_at(duilib_tablayout_t layout, int index);
DUILIB_C_API int duilib_tablayout_get_item_index(duilib_tablayout_t layout, duilib_control_t control);
DUILIB_C_API bool duilib_tablayout_set_item_index(duilib_tablayout_t layout, duilib_control_t control, int new_index);

// 内边距管理
DUILIB_C_API duilib_rect_t duilib_tablayout_get_inset(duilib_tablayout_t layout);
DUILIB_C_API duilib_result_t duilib_tablayout_set_inset(duilib_tablayout_t layout, duilib_rect_t inset);

// 子控件边距
DUILIB_C_API int duilib_tablayout_get_child_padding(duilib_tablayout_t layout);
DUILIB_C_API duilib_result_t duilib_tablayout_set_child_padding(duilib_tablayout_t layout, int padding);

// 鼠标子控件启用
DUILIB_C_API bool duilib_tablayout_is_mouse_child_enabled(duilib_tablayout_t layout);
DUILIB_C_API duilib_result_t duilib_tablayout_set_mouse_child_enabled(duilib_tablayout_t layout, bool enabled);

// 滚动条管理
DUILIB_C_API duilib_scrollbar_t duilib_tablayout_get_vertical_scrollbar(duilib_tablayout_t layout);
DUILIB_C_API duilib_scrollbar_t duilib_tablayout_get_horizontal_scrollbar(duilib_tablayout_t layout);

// 可见性管理
DUILIB_C_API duilib_result_t duilib_tablayout_set_visible(duilib_tablayout_t layout, bool visible);
DUILIB_C_API duilib_result_t duilib_tablayout_set_intern_visible(duilib_tablayout_t layout, bool visible);

// 启用状态
DUILIB_C_API duilib_result_t duilib_tablayout_set_enabled(duilib_tablayout_t layout, bool enabled);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_TABLAYOUT_H__