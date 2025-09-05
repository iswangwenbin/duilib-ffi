#ifndef __DUILIB_C_WINIMPLBASE_H__
#define __DUILIB_C_WINIMPLBASE_H__

#include "../core/duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 窗口实现基类API - 对应 WinImplBase.h
//=============================================================================

// 资源类型枚举
typedef enum {
    DUILIB_RESOURCE_TYPE_FILE = 1,          // 资源来自文件
    DUILIB_RESOURCE_TYPE_ZIP,               // 资源来自ZIP压缩包
    DUILIB_RESOURCE_TYPE_RESOURCE,          // 资源来自资源
    DUILIB_RESOURCE_TYPE_ZIPRESOURCE        // 资源来自资源中的ZIP压缩包
} duilib_resource_type_t;

// WindowImplBase句柄
typedef struct duilib_winimplbase* duilib_winimplbase_t;

//=============================================================================
// 窗口实现基类回调函数类型定义
//=============================================================================

// 窗口初始化回调
typedef void (*duilib_winimpl_init_callback_t)(duilib_winimplbase_t window, void* user_data);

// 通知消息回调
typedef void (*duilib_winimpl_notify_callback_t)(duilib_winimplbase_t window, const duilib_ui_event_t* msg, void* user_data);

// 点击事件回调
typedef void (*duilib_winimpl_click_callback_t)(duilib_winimplbase_t window, const duilib_ui_event_t* msg, void* user_data);

// 消息处理回调
typedef long (*duilib_winimpl_message_callback_t)(duilib_winimplbase_t window, unsigned int msg, void* wparam, void* lparam, bool* handled, void* user_data);

// 控件创建回调
typedef duilib_control_t (*duilib_winimpl_create_control_callback_t)(duilib_winimplbase_t window, const char* class_name, void* user_data);

//=============================================================================
// WindowImplBase创建配置结构
//=============================================================================

typedef struct {
    // 皮肤配置
    const char* skin_folder;           // 皮肤文件夹
    const char* skin_file;             // 皮肤文件名
    const char* window_class_name;     // 窗口类名
    
    // 资源配置
    duilib_resource_type_t resource_type;  // 资源类型
    const char* zip_file_name;         // ZIP文件名
    const char* resource_id;           // 资源ID
    
    // 窗口样式
    unsigned int class_style;          // 窗口类样式
    long window_style;                 // 窗口样式
    
    // 回调函数
    duilib_winimpl_init_callback_t init_callback;
    duilib_winimpl_notify_callback_t notify_callback;  
    duilib_winimpl_click_callback_t click_callback;
    duilib_winimpl_message_callback_t message_callback;
    duilib_winimpl_create_control_callback_t create_control_callback;
    
    void* user_data;                   // 用户数据
} duilib_winimpl_config_t;

//=============================================================================
// WindowImplBase基础API
//=============================================================================

// 创建和销毁WindowImplBase
DUILIB_C_API duilib_winimplbase_t duilib_winimplbase_create(const duilib_winimpl_config_t* config);
DUILIB_C_API void duilib_winimplbase_destroy(duilib_winimplbase_t window);

// 获取窗口基类接口
DUILIB_C_API duilib_window_t duilib_winimplbase_to_window(duilib_winimplbase_t window);
DUILIB_C_API duilib_winimplbase_t duilib_window_to_winimplbase(duilib_window_t window);

// 类型检查
DUILIB_C_API bool duilib_winimplbase_is_valid(duilib_winimplbase_t window);

//=============================================================================
// WindowImplBase核心方法
//=============================================================================

// 窗口初始化
DUILIB_C_API duilib_result_t duilib_winimplbase_init_window(duilib_winimplbase_t window);

// 获取绘制管理器
DUILIB_C_API duilib_manager_t duilib_winimplbase_get_paint_manager(duilib_winimplbase_t window);

//=============================================================================
// WindowImplBase配置方法
//=============================================================================

// 皮肤配置
DUILIB_C_API const char* duilib_winimplbase_get_skin_folder(duilib_winimplbase_t window);
DUILIB_C_API duilib_result_t duilib_winimplbase_set_skin_folder(duilib_winimplbase_t window, const char* folder);

DUILIB_C_API const char* duilib_winimplbase_get_skin_file(duilib_winimplbase_t window);
DUILIB_C_API duilib_result_t duilib_winimplbase_set_skin_file(duilib_winimplbase_t window, const char* file);

DUILIB_C_API const char* duilib_winimplbase_get_window_class_name(duilib_winimplbase_t window);

// 资源配置
DUILIB_C_API duilib_resource_type_t duilib_winimplbase_get_resource_type(duilib_winimplbase_t window);
DUILIB_C_API duilib_result_t duilib_winimplbase_set_resource_type(duilib_winimplbase_t window, duilib_resource_type_t type);

DUILIB_C_API const char* duilib_winimplbase_get_zip_file_name(duilib_winimplbase_t window);
DUILIB_C_API duilib_result_t duilib_winimplbase_set_zip_file_name(duilib_winimplbase_t window, const char* zip_name);

DUILIB_C_API const char* duilib_winimplbase_get_resource_id(duilib_winimplbase_t window);
DUILIB_C_API duilib_result_t duilib_winimplbase_set_resource_id(duilib_winimplbase_t window, const char* resource_id);

//=============================================================================
// WindowImplBase样式方法
//=============================================================================

// 窗口类样式
DUILIB_C_API unsigned int duilib_winimplbase_get_class_style(duilib_winimplbase_t window);
DUILIB_C_API duilib_result_t duilib_winimplbase_set_class_style(duilib_winimplbase_t window, unsigned int style);

// 窗口样式
DUILIB_C_API long duilib_winimplbase_get_style(duilib_winimplbase_t window);
DUILIB_C_API duilib_result_t duilib_winimplbase_set_style(duilib_winimplbase_t window, long style);

//=============================================================================
// WindowImplBase回调设置
//=============================================================================

// 设置回调函数
DUILIB_C_API duilib_result_t duilib_winimplbase_set_init_callback(duilib_winimplbase_t window, duilib_winimpl_init_callback_t callback, void* user_data);
DUILIB_C_API duilib_result_t duilib_winimplbase_set_notify_callback(duilib_winimplbase_t window, duilib_winimpl_notify_callback_t callback, void* user_data);
DUILIB_C_API duilib_result_t duilib_winimplbase_set_click_callback(duilib_winimplbase_t window, duilib_winimpl_click_callback_t callback, void* user_data);
DUILIB_C_API duilib_result_t duilib_winimplbase_set_message_callback(duilib_winimplbase_t window, duilib_winimpl_message_callback_t callback, void* user_data);
DUILIB_C_API duilib_result_t duilib_winimplbase_set_create_control_callback(duilib_winimplbase_t window, duilib_winimpl_create_control_callback_t callback, void* user_data);

//=============================================================================
// WindowImplBase消息处理方法
//=============================================================================

// 默认按键响应
DUILIB_C_API long duilib_winimplbase_response_default_key_event(duilib_winimplbase_t window, void* wparam);

// 消息处理器
DUILIB_C_API long duilib_winimplbase_message_handler(duilib_winimplbase_t window, unsigned int msg, void* wparam, void* lparam, bool* handled);

// 自定义消息处理
DUILIB_C_API long duilib_winimplbase_handle_custom_message(duilib_winimplbase_t window, unsigned int msg, void* wparam, void* lparam, bool* handled);

//=============================================================================
// WindowImplBase静态资源管理
//=============================================================================

// ZIP资源缓冲区管理
DUILIB_C_API duilib_result_t duilib_winimplbase_set_resource_zip_buffer(unsigned char* buffer, unsigned int size);
DUILIB_C_API unsigned char* duilib_winimplbase_get_resource_zip_buffer(void);

//=============================================================================
// WindowImplBase窗口操作
//=============================================================================

// 创建窗口
DUILIB_C_API void* duilib_winimplbase_create_window(duilib_winimplbase_t window, void* parent, const char* name, unsigned int style, unsigned int ex_style);

// 显示窗口
DUILIB_C_API duilib_result_t duilib_winimplbase_show_window(duilib_winimplbase_t window, bool show, bool take_focus);
DUILIB_C_API duilib_result_t duilib_winimplbase_show_modal(duilib_winimplbase_t window, void* parent);

// 关闭窗口
DUILIB_C_API duilib_result_t duilib_winimplbase_close_window(duilib_winimplbase_t window, unsigned int ret);

// 居中显示
DUILIB_C_API duilib_result_t duilib_winimplbase_center_window(duilib_winimplbase_t window);

// 设置图标
DUILIB_C_API duilib_result_t duilib_winimplbase_set_icon(duilib_winimplbase_t window, unsigned int resource_id);

//=============================================================================
// WindowImplBase辅助功能
//=============================================================================

// 查找控件
DUILIB_C_API duilib_control_t duilib_winimplbase_find_control(duilib_winimplbase_t window, const char* name);

// 设置窗口标题
DUILIB_C_API duilib_result_t duilib_winimplbase_set_window_text(duilib_winimplbase_t window, const char* title);
DUILIB_C_API const char* duilib_winimplbase_get_window_text(duilib_winimplbase_t window);

// 重绘窗口
DUILIB_C_API duilib_result_t duilib_winimplbase_invalidate(duilib_winimplbase_t window);

// 获取用户数据
DUILIB_C_API void* duilib_winimplbase_get_user_data(duilib_winimplbase_t window);
DUILIB_C_API duilib_result_t duilib_winimplbase_set_user_data(duilib_winimplbase_t window, void* user_data);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_WINIMPLBASE_H__