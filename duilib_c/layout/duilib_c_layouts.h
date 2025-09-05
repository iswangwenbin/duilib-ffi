#ifndef __DUILIB_C_LAYOUTS_H__
#define __DUILIB_C_LAYOUTS_H__

//=============================================================================
// DuiLib C API - 布局模块汇总头文件
// 包含所有布局类的C API声明
//=============================================================================

#include "../core/duilib_c_base.h"

// 各种布局控件
#include "duilib_c_verticallayout.h"
#include "duilib_c_horizontallayout.h"
#include "duilib_c_tablayout.h"
#include "duilib_c_tilelayout.h"
#include "duilib_c_childlayout.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 布局模块初始化和清理
//=============================================================================

// 初始化布局模块
DUILIB_C_API duilib_result_t duilib_layouts_initialize(void);

// 清理布局模块
DUILIB_C_API duilib_result_t duilib_layouts_cleanup(void);

//=============================================================================
// 布局工厂方法 - 通用布局创建
//=============================================================================

// 通过类名创建布局控件
DUILIB_C_API duilib_control_t duilib_create_layout_by_class(const char* class_name);

// 布局类型枚举
typedef enum {
    DUILIB_LAYOUT_TYPE_UNKNOWN = 0,
    DUILIB_LAYOUT_TYPE_CONTAINER,
    DUILIB_LAYOUT_TYPE_VERTICAL,
    DUILIB_LAYOUT_TYPE_HORIZONTAL,
    DUILIB_LAYOUT_TYPE_TAB,
    DUILIB_LAYOUT_TYPE_TILE,
    DUILIB_LAYOUT_TYPE_CHILD
} duilib_layout_type_t;

// 获取布局类型
DUILIB_C_API duilib_layout_type_t duilib_get_layout_type(duilib_control_t control);

// 检查布局类型
DUILIB_C_API bool duilib_is_layout_type(duilib_control_t control, duilib_layout_type_t type);

//=============================================================================
// 布局转换辅助函数 - 安全类型转换
//=============================================================================

// 安全转换到具体布局类型（失败返回NULL）
DUILIB_C_API duilib_verticallayout_t duilib_safe_cast_to_verticallayout(duilib_control_t control);
DUILIB_C_API duilib_horizontallayout_t duilib_safe_cast_to_horizontallayout(duilib_control_t control);
DUILIB_C_API duilib_tablayout_t duilib_safe_cast_to_tablayout(duilib_control_t control);
DUILIB_C_API duilib_tilelayout_t duilib_safe_cast_to_tilelayout(duilib_control_t control);
DUILIB_C_API duilib_childlayout_t duilib_safe_cast_to_childlayout(duilib_control_t control);

//=============================================================================
// 布局通用操作 - 适用于所有布局控件
//=============================================================================

// 布局通用属性设置
DUILIB_C_API duilib_result_t duilib_layout_set_inset(duilib_control_t layout, duilib_rect_t inset);
DUILIB_C_API duilib_rect_t duilib_layout_get_inset(duilib_control_t layout);

DUILIB_C_API duilib_result_t duilib_layout_set_child_padding(duilib_control_t layout, int padding);
DUILIB_C_API int duilib_layout_get_child_padding(duilib_control_t layout);

// 布局通用子控件管理
DUILIB_C_API bool duilib_layout_add_control(duilib_control_t layout, duilib_control_t control);
DUILIB_C_API bool duilib_layout_add_control_at(duilib_control_t layout, duilib_control_t control, int index);
DUILIB_C_API bool duilib_layout_remove_control(duilib_control_t layout, duilib_control_t control, bool do_not_destroy);
DUILIB_C_API bool duilib_layout_remove_control_at(duilib_control_t layout, int index, bool do_not_destroy);
DUILIB_C_API duilib_result_t duilib_layout_remove_all_controls(duilib_control_t layout);

DUILIB_C_API int duilib_layout_get_control_count(duilib_control_t layout);
DUILIB_C_API duilib_control_t duilib_layout_get_control_at(duilib_control_t layout, int index);
DUILIB_C_API int duilib_layout_get_control_index(duilib_control_t layout, duilib_control_t control);

//=============================================================================
// 布局事件回调类型定义
//=============================================================================

// 布局通用事件回调
typedef void (*duilib_layout_event_callback_t)(duilib_control_t layout, const duilib_ui_event_t* event, void* user_data);

// 标签页选择改变回调
typedef void (*duilib_tablayout_select_callback_t)(duilib_tablayout_t layout, int old_index, int new_index, void* user_data);

// 布局尺寸改变回调
typedef void (*duilib_layout_size_callback_t)(duilib_control_t layout, duilib_size_t old_size, duilib_size_t new_size, void* user_data);

//=============================================================================
// 布局事件回调注册
//=============================================================================

// 注册布局通用事件回调
DUILIB_C_API duilib_result_t duilib_layout_set_event_callback(duilib_control_t layout, duilib_layout_event_callback_t callback, void* user_data);

// 注册标签页选择回调
DUILIB_C_API duilib_result_t duilib_tablayout_set_select_callback(duilib_tablayout_t layout, duilib_tablayout_select_callback_t callback, void* user_data);

// 注册布局尺寸改变回调
DUILIB_C_API duilib_result_t duilib_layout_set_size_callback(duilib_control_t layout, duilib_layout_size_callback_t callback, void* user_data);

//=============================================================================
// 布局辅助功能
//=============================================================================

// 自动调整布局尺寸
DUILIB_C_API duilib_result_t duilib_layout_auto_size(duilib_control_t layout);

// 刷新布局
DUILIB_C_API duilib_result_t duilib_layout_need_update(duilib_control_t layout);

// 获取布局建议尺寸
DUILIB_C_API duilib_size_t duilib_layout_get_suggested_size(duilib_control_t layout, duilib_size_t available);

// 检查布局是否需要滚动条
DUILIB_C_API bool duilib_layout_needs_scrollbar(duilib_control_t layout, bool vertical);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_LAYOUTS_H__