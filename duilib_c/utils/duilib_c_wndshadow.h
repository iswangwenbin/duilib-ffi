#ifndef __DUILIB_C_WNDSHADOW_H__
#define __DUILIB_C_WNDSHADOW_H__

#include "../core/duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 窗口阴影API - 对应 WndShadow.h
//=============================================================================

// 窗口阴影句柄
typedef struct duilib_wndshadow* duilib_wndshadow_t;

// 阴影状态枚举
typedef enum {
    DUILIB_SHADOW_STATUS_ENABLED = 1,           // 阴影启用
    DUILIB_SHADOW_STATUS_VISIBLE = 2,           // 阴影窗口可见
    DUILIB_SHADOW_STATUS_PARENT_VISIBLE = 4     // 父窗口可见
} duilib_shadow_status_t;

//=============================================================================
// 窗口阴影基础API
//=============================================================================

// 创建和销毁窗口阴影
DUILIB_C_API duilib_wndshadow_t duilib_wndshadow_create(void);
DUILIB_C_API void duilib_wndshadow_destroy(duilib_wndshadow_t shadow);

// 类型检查
DUILIB_C_API bool duilib_wndshadow_is_valid(duilib_wndshadow_t shadow);

//=============================================================================
// 窗口阴影静态初始化
//=============================================================================

// 初始化阴影系统（必须在使用前调用）
DUILIB_C_API bool duilib_wndshadow_initialize(void* hinstance);

//=============================================================================
// 窗口阴影核心方法
//=============================================================================

// 获取阴影窗口句柄
DUILIB_C_API void* duilib_wndshadow_get_hwnd(duilib_wndshadow_t shadow);

// 创建阴影窗口
DUILIB_C_API duilib_result_t duilib_wndshadow_create_shadow(duilib_wndshadow_t shadow, void* parent_hwnd);

//=============================================================================
// 窗口阴影图片配置 - 使用图片绘制阴影
//=============================================================================

// 设置阴影图片
DUILIB_C_API bool duilib_wndshadow_set_image(duilib_wndshadow_t shadow, const char* image, duilib_rect_t corner, duilib_rect_t hole_offset);

//=============================================================================
// 窗口阴影颜色配置 - 使用颜色绘制阴影
//=============================================================================

// 设置阴影尺寸
DUILIB_C_API bool duilib_wndshadow_set_size(duilib_wndshadow_t shadow, int size);

// 设置阴影锐度（模糊边框宽度）
DUILIB_C_API bool duilib_wndshadow_set_sharpness(duilib_wndshadow_t shadow, unsigned int sharpness);

// 设置阴影暗度（透明度）
DUILIB_C_API bool duilib_wndshadow_set_darkness(duilib_wndshadow_t shadow, unsigned int darkness);

// 设置阴影位置偏移
DUILIB_C_API bool duilib_wndshadow_set_position(duilib_wndshadow_t shadow, int x_offset, int y_offset);

// 设置阴影颜色
DUILIB_C_API bool duilib_wndshadow_set_color(duilib_wndshadow_t shadow, duilib_color_t color);

//=============================================================================
// 窗口阴影状态管理
//=============================================================================

// 获取阴影状态
DUILIB_C_API unsigned char duilib_wndshadow_get_status(duilib_wndshadow_t shadow);

// 检查特定状态
DUILIB_C_API bool duilib_wndshadow_is_enabled(duilib_wndshadow_t shadow);
DUILIB_C_API bool duilib_wndshadow_is_visible(duilib_wndshadow_t shadow);
DUILIB_C_API bool duilib_wndshadow_is_parent_visible(duilib_wndshadow_t shadow);

// 设置阴影启用状态
DUILIB_C_API duilib_result_t duilib_wndshadow_set_enabled(duilib_wndshadow_t shadow, bool enabled);

//=============================================================================
// 窗口阴影属性获取
//=============================================================================

// 获取阴影属性
DUILIB_C_API int duilib_wndshadow_get_size(duilib_wndshadow_t shadow);
DUILIB_C_API unsigned int duilib_wndshadow_get_sharpness(duilib_wndshadow_t shadow);
DUILIB_C_API unsigned int duilib_wndshadow_get_darkness(duilib_wndshadow_t shadow);
DUILIB_C_API duilib_point_t duilib_wndshadow_get_position(duilib_wndshadow_t shadow);
DUILIB_C_API duilib_color_t duilib_wndshadow_get_color(duilib_wndshadow_t shadow);

//=============================================================================
// 窗口阴影更新和绘制
//=============================================================================

// 更新阴影（当窗口大小改变或阴影属性改变时调用）
DUILIB_C_API duilib_result_t duilib_wndshadow_update(duilib_wndshadow_t shadow, void* parent_hwnd);

// 强制重绘阴影
DUILIB_C_API duilib_result_t duilib_wndshadow_invalidate(duilib_wndshadow_t shadow);

//=============================================================================
// 窗口阴影辅助功能
//=============================================================================

// 显示/隐藏阴影
DUILIB_C_API duilib_result_t duilib_wndshadow_show(duilib_wndshadow_t shadow, bool show);

// 移动阴影窗口
DUILIB_C_API duilib_result_t duilib_wndshadow_move_window(duilib_wndshadow_t shadow, duilib_rect_t rect, bool repaint);

// 设置阴影窗口层次
DUILIB_C_API duilib_result_t duilib_wndshadow_set_window_pos(duilib_wndshadow_t shadow, void* hwnd_insert_after, duilib_rect_t rect, unsigned int flags);

//=============================================================================
// 预设阴影配置
//=============================================================================

// 预设阴影配置结构
typedef struct {
    int size;                  // 阴影大小
    unsigned int sharpness;    // 锐度
    unsigned int darkness;     // 暗度
    int x_offset;             // X偏移
    int y_offset;             // Y偏移
    duilib_color_t color;     // 阴影颜色
    const char* image;        // 阴影图片（可选）
    duilib_rect_t corner;     // 图片九宫格角点
    duilib_rect_t hole_offset; // 图片挖空偏移
} duilib_shadow_config_t;

// 应用预设配置
DUILIB_C_API duilib_result_t duilib_wndshadow_apply_config(duilib_wndshadow_t shadow, const duilib_shadow_config_t* config);

// 获取当前配置
DUILIB_C_API duilib_result_t duilib_wndshadow_get_config(duilib_wndshadow_t shadow, duilib_shadow_config_t* config);

//=============================================================================
// 常用阴影预设
//=============================================================================

// 创建默认阴影配置
DUILIB_C_API duilib_shadow_config_t duilib_shadow_config_default(void);

// 创建简单阴影配置
DUILIB_C_API duilib_shadow_config_t duilib_shadow_config_simple(int size, duilib_color_t color);

// 创建软阴影配置  
DUILIB_C_API duilib_shadow_config_t duilib_shadow_config_soft(int size, unsigned int darkness);

// 创建硬阴影配置
DUILIB_C_API duilib_shadow_config_t duilib_shadow_config_hard(int size, duilib_color_t color, int x_offset, int y_offset);

// 创建图片阴影配置
DUILIB_C_API duilib_shadow_config_t duilib_shadow_config_image(const char* image, duilib_rect_t corner, duilib_rect_t hole_offset);

//=============================================================================
// 窗口阴影管理器 - 批量管理多个阴影
//=============================================================================

// 阴影管理器句柄
typedef struct duilib_shadow_manager* duilib_shadow_manager_t;

// 创建和销毁阴影管理器
DUILIB_C_API duilib_shadow_manager_t duilib_shadow_manager_create(void);
DUILIB_C_API void duilib_shadow_manager_destroy(duilib_shadow_manager_t manager);

// 为窗口添加阴影
DUILIB_C_API duilib_wndshadow_t duilib_shadow_manager_add_shadow(duilib_shadow_manager_t manager, void* hwnd, const duilib_shadow_config_t* config);

// 移除窗口阴影
DUILIB_C_API duilib_result_t duilib_shadow_manager_remove_shadow(duilib_shadow_manager_t manager, void* hwnd);

// 获取窗口阴影
DUILIB_C_API duilib_wndshadow_t duilib_shadow_manager_get_shadow(duilib_shadow_manager_t manager, void* hwnd);

// 更新所有阴影
DUILIB_C_API duilib_result_t duilib_shadow_manager_update_all(duilib_shadow_manager_t manager);

// 显示/隐藏所有阴影
DUILIB_C_API duilib_result_t duilib_shadow_manager_show_all(duilib_shadow_manager_t manager, bool show);

// 获取全局阴影管理器
DUILIB_C_API duilib_shadow_manager_t duilib_get_global_shadow_manager(void);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_WNDSHADOW_H__