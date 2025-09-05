#ifndef __DUILIB_C_CONTAINER_H__
#define __DUILIB_C_CONTAINER_H__

#include "duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 容器控件操作
//=============================================================================

// 添加子控件
DUILIB_C_API duilib_result_t duilib_container_add(duilib_control_t container, duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_container_add_at(duilib_control_t container, duilib_control_t control, int index);

// 移除子控件
DUILIB_C_API duilib_result_t duilib_container_remove(duilib_control_t container, duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_container_remove_at(duilib_control_t container, int index);
DUILIB_C_API duilib_result_t duilib_container_remove_all(duilib_control_t container);

// 子控件管理
DUILIB_C_API int duilib_container_get_count(duilib_control_t container);
DUILIB_C_API duilib_control_t duilib_container_get_item_at(duilib_control_t container, int index);

//=============================================================================
// 容器特殊方法
//=============================================================================

// 内边距
DUILIB_C_API duilib_rect_t duilib_container_get_inset(duilib_control_t container);
DUILIB_C_API duilib_result_t duilib_container_set_inset(duilib_control_t container, duilib_rect_t inset);

// 子控件间距
DUILIB_C_API int duilib_container_get_child_padding(duilib_control_t container);
DUILIB_C_API duilib_result_t duilib_container_set_child_padding(duilib_control_t container, int padding);

// 子控件对齐
DUILIB_C_API uint32_t duilib_container_get_child_align(duilib_control_t container);
DUILIB_C_API duilib_result_t duilib_container_set_child_align(duilib_control_t container, uint32_t align);
DUILIB_C_API uint32_t duilib_container_get_child_valign(duilib_control_t container);
DUILIB_C_API duilib_result_t duilib_container_set_child_valign(duilib_control_t container, uint32_t valign);

// 自动销毁
DUILIB_C_API bool duilib_container_is_auto_destroy(duilib_control_t container);
DUILIB_C_API duilib_result_t duilib_container_set_auto_destroy(duilib_control_t container, bool auto_destroy);

// 鼠标子控件支持
DUILIB_C_API bool duilib_container_is_mouse_child_enabled(duilib_control_t container);
DUILIB_C_API duilib_result_t duilib_container_set_mouse_child_enabled(duilib_control_t container, bool enabled);

//=============================================================================
// 子控件操作辅助方法
//=============================================================================

// 子控件文本操作
DUILIB_C_API duilib_result_t duilib_container_set_sub_control_text(duilib_control_t container, const char* sub_name, const char* text);
DUILIB_C_API const char* duilib_container_get_sub_control_text(duilib_control_t container, const char* sub_name);

// 子控件查找
DUILIB_C_API duilib_control_t duilib_container_find_sub_control(duilib_control_t container, const char* sub_name);

//=============================================================================
// 滚动条相关
//=============================================================================

// 滚动位置和范围
DUILIB_C_API duilib_size_t duilib_container_get_scroll_pos(duilib_control_t container);
DUILIB_C_API duilib_size_t duilib_container_get_scroll_range(duilib_control_t container);
DUILIB_C_API duilib_result_t duilib_container_set_scroll_pos(duilib_control_t container, duilib_size_t pos);

// 启用滚动条
DUILIB_C_API duilib_result_t duilib_container_enable_scroll_bar(duilib_control_t container, bool vertical, bool horizontal);

//=============================================================================
// 滚动操作
//=============================================================================

// 垂直滚动
DUILIB_C_API duilib_result_t duilib_container_line_up(duilib_control_t container);
DUILIB_C_API duilib_result_t duilib_container_line_down(duilib_control_t container);
DUILIB_C_API duilib_result_t duilib_container_page_up(duilib_control_t container);
DUILIB_C_API duilib_result_t duilib_container_page_down(duilib_control_t container);
DUILIB_C_API duilib_result_t duilib_container_home_up(duilib_control_t container);
DUILIB_C_API duilib_result_t duilib_container_end_down(duilib_control_t container);

// 水平滚动
DUILIB_C_API duilib_result_t duilib_container_line_left(duilib_control_t container);
DUILIB_C_API duilib_result_t duilib_container_line_right(duilib_control_t container);
DUILIB_C_API duilib_result_t duilib_container_page_left(duilib_control_t container);
DUILIB_C_API duilib_result_t duilib_container_page_right(duilib_control_t container);
DUILIB_C_API duilib_result_t duilib_container_home_left(duilib_control_t container);
DUILIB_C_API duilib_result_t duilib_container_end_right(duilib_control_t container);

//=============================================================================
// CContainerUI 缺失方法补充
//=============================================================================

// 项目索引管理
DUILIB_C_API int duilib_container_get_item_index(duilib_control_t container, duilib_control_t control);
DUILIB_C_API duilib_result_t duilib_container_set_item_index(duilib_control_t container, duilib_control_t control, int new_index);
DUILIB_C_API duilib_result_t duilib_container_set_multi_item_index(duilib_control_t container, duilib_control_t start_control, int count, int new_start_index);

// 延迟销毁
DUILIB_C_API bool duilib_container_is_delayed_destroy(duilib_control_t container);
DUILIB_C_API duilib_result_t duilib_container_set_delayed_destroy(duilib_control_t container, bool delayed);

// 选择导航
DUILIB_C_API int duilib_container_find_selectable(duilib_control_t container, int index, bool forward);

// 子控件完整属性管理
DUILIB_C_API duilib_result_t duilib_container_set_sub_control_fixed_height(duilib_control_t container, const char* sub_name, int height);
DUILIB_C_API int duilib_container_get_sub_control_fixed_height(duilib_control_t container, const char* sub_name);
DUILIB_C_API duilib_result_t duilib_container_set_sub_control_fixed_width(duilib_control_t container, const char* sub_name, int width);
DUILIB_C_API int duilib_container_get_sub_control_fixed_width(duilib_control_t container, const char* sub_name);
DUILIB_C_API duilib_result_t duilib_container_set_sub_control_user_data(duilib_control_t container, const char* sub_name, const char* user_data);
DUILIB_C_API const char* duilib_container_get_sub_control_user_data(duilib_control_t container, const char* sub_name);

// 滚动条访问
DUILIB_C_API duilib_control_t duilib_container_get_vertical_scroll_bar(duilib_control_t container);
DUILIB_C_API duilib_control_t duilib_container_get_horizontal_scroll_bar(duilib_control_t container);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_CONTAINER_H__