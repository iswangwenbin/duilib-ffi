#ifndef __DUILIB_C_FLASH_H__
#define __DUILIB_C_FLASH_H__

#include "../core/duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// Flash事件处理API - 对应 FlashEventHandler.h
//=============================================================================

// Flash事件处理器句柄
typedef struct duilib_flashevent* duilib_flashevent_t;

//=============================================================================
// Flash事件处理回调函数类型定义
//=============================================================================

// Flash就绪状态改变回调
typedef long (*duilib_flash_ready_state_callback_t)(long new_state, void* user_data);

// Flash进度回调
typedef long (*duilib_flash_progress_callback_t)(long percent_done, void* user_data);

// Flash命令回调
typedef long (*duilib_flash_fscommand_callback_t)(const char* command, const char* args, void* user_data);

// Flash调用回调
typedef long (*duilib_flash_call_callback_t)(const char* request, void* user_data);

//=============================================================================
// Flash事件处理器配置结构
//=============================================================================

typedef struct {
    duilib_flash_ready_state_callback_t ready_state_callback;
    duilib_flash_progress_callback_t progress_callback;
    duilib_flash_fscommand_callback_t fscommand_callback;
    duilib_flash_call_callback_t call_callback;
    void* user_data;
} duilib_flash_config_t;

//=============================================================================
// Flash事件处理器基础API
//=============================================================================

// 创建和销毁Flash事件处理器
DUILIB_C_API duilib_flashevent_t duilib_flashevent_create(const duilib_flash_config_t* config);
DUILIB_C_API void duilib_flashevent_destroy(duilib_flashevent_t handler);

// 类型检查
DUILIB_C_API bool duilib_flashevent_is_valid(duilib_flashevent_t handler);

//=============================================================================
// Flash事件处理方法
//=============================================================================

// 处理就绪状态改变事件
DUILIB_C_API long duilib_flashevent_on_ready_state_change(duilib_flashevent_t handler, long new_state);

// 处理进度事件
DUILIB_C_API long duilib_flashevent_on_progress(duilib_flashevent_t handler, long percent_done);

// 处理FS命令事件
DUILIB_C_API long duilib_flashevent_on_fscommand(duilib_flashevent_t handler, const char* command, const char* args);

// 处理Flash调用事件
DUILIB_C_API long duilib_flashevent_on_flash_call(duilib_flashevent_t handler, const char* request);

//=============================================================================
// Flash事件处理器配置管理
//=============================================================================

// 设置回调函数
DUILIB_C_API duilib_result_t duilib_flashevent_set_ready_state_callback(duilib_flashevent_t handler, duilib_flash_ready_state_callback_t callback, void* user_data);
DUILIB_C_API duilib_result_t duilib_flashevent_set_progress_callback(duilib_flashevent_t handler, duilib_flash_progress_callback_t callback, void* user_data);
DUILIB_C_API duilib_result_t duilib_flashevent_set_fscommand_callback(duilib_flashevent_t handler, duilib_flash_fscommand_callback_t callback, void* user_data);
DUILIB_C_API duilib_result_t duilib_flashevent_set_call_callback(duilib_flashevent_t handler, duilib_flash_call_callback_t callback, void* user_data);

// 获取用户数据
DUILIB_C_API void* duilib_flashevent_get_user_data(duilib_flashevent_t handler);
DUILIB_C_API duilib_result_t duilib_flashevent_set_user_data(duilib_flashevent_t handler, void* user_data);

//=============================================================================
// Flash状态常量
//=============================================================================

// Flash就绪状态常量
#define DUILIB_FLASH_READYSTATE_UNINITIALIZED  0
#define DUILIB_FLASH_READYSTATE_LOADING         1
#define DUILIB_FLASH_READYSTATE_LOADED          2
#define DUILIB_FLASH_READYSTATE_INTERACTIVE     3
#define DUILIB_FLASH_READYSTATE_COMPLETE        4

//=============================================================================
// Flash辅助功能
//=============================================================================

// 创建默认配置
DUILIB_C_API duilib_flash_config_t duilib_flash_config_default(void);

// 获取就绪状态名称
DUILIB_C_API const char* duilib_flash_get_ready_state_name(long state);

// 解析Flash调用请求
DUILIB_C_API duilib_result_t duilib_flash_parse_call_request(const char* request, char* method, int method_size, char* params, int params_size);

// 构建Flash调用响应
DUILIB_C_API const char* duilib_flash_build_call_response(const char* result, const char* error);

//=============================================================================
// Flash事件管理器 - 集中管理多个Flash控件的事件
//=============================================================================

// Flash事件管理器句柄
typedef struct duilib_flash_manager* duilib_flash_manager_t;

// 创建和销毁Flash事件管理器
DUILIB_C_API duilib_flash_manager_t duilib_flash_manager_create(void);
DUILIB_C_API void duilib_flash_manager_destroy(duilib_flash_manager_t manager);

// 注册Flash控件
DUILIB_C_API duilib_result_t duilib_flash_manager_register(duilib_flash_manager_t manager, const char* name, duilib_flashevent_t handler);

// 注销Flash控件
DUILIB_C_API duilib_result_t duilib_flash_manager_unregister(duilib_flash_manager_t manager, const char* name);

// 获取Flash事件处理器
DUILIB_C_API duilib_flashevent_t duilib_flash_manager_get_handler(duilib_flash_manager_t manager, const char* name);

// 广播事件到所有注册的Flash控件
DUILIB_C_API duilib_result_t duilib_flash_manager_broadcast_ready_state(duilib_flash_manager_t manager, long new_state);
DUILIB_C_API duilib_result_t duilib_flash_manager_broadcast_progress(duilib_flash_manager_t manager, long percent_done);

// 获取全局Flash事件管理器
DUILIB_C_API duilib_flash_manager_t duilib_get_global_flash_manager(void);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_FLASH_H__