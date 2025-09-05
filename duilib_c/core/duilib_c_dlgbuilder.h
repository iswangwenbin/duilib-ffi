#ifndef __DUILIB_C_DLGBUILDER_H__
#define __DUILIB_C_DLGBUILDER_H__

#include "duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 对话框构建器API - 对应 CDlgBuilder
//=============================================================================

// 对话框构建器句柄
typedef struct duilib_dlgbuilder* duilib_dlgbuilder_t;

// 对话框构建器回调函数类型 - 对应 IDialogBuilderCallback
typedef duilib_control_t (*duilib_dialog_builder_callback_t)(const char* class_name, void* user_data);

// 创建和销毁对话框构建器
DUILIB_C_API duilib_dlgbuilder_t duilib_dlgbuilder_create(void);
DUILIB_C_API void duilib_dlgbuilder_destroy(duilib_dlgbuilder_t builder);

// 从文件构建 - 原版本（使用事件回调）
DUILIB_C_API duilib_control_t duilib_dlgbuilder_create_from_file(duilib_dlgbuilder_t builder, const char* xml_file, const char* type, duilib_event_callback_t callback, duilib_manager_t manager, duilib_control_t parent);

// 从字符串构建 - 原版本（使用事件回调） 
DUILIB_C_API duilib_control_t duilib_dlgbuilder_create_from_string(duilib_dlgbuilder_t builder, const char* xml_string, const char* type, duilib_event_callback_t callback, duilib_manager_t manager, duilib_control_t parent);

//=============================================================================
// CDialogBuilder 完整 API - 对应原始接口
//=============================================================================

// 完整的创建方法 - 对应 CDialogBuilder::Create
DUILIB_C_API duilib_control_t duilib_dlgbuilder_create_complete(duilib_dlgbuilder_t builder, const char* xml_resource, const char* type, duilib_dialog_builder_callback_t callback, void* callback_user_data, duilib_manager_t manager, duilib_control_t parent);

// 简化创建方法 - 对应 CDialogBuilder::Create 重载
DUILIB_C_API duilib_control_t duilib_dlgbuilder_create_simple(duilib_dlgbuilder_t builder, duilib_dialog_builder_callback_t callback, void* callback_user_data, duilib_manager_t manager, duilib_control_t parent);

// 获取标记解析器
DUILIB_C_API duilib_markup_t duilib_dlgbuilder_get_markup(duilib_dlgbuilder_t builder);

// 错误信息获取 - 对应原始方法
DUILIB_C_API duilib_result_t duilib_dlgbuilder_get_last_error_message(duilib_dlgbuilder_t builder, char* message, size_t max_chars);
DUILIB_C_API duilib_result_t duilib_dlgbuilder_get_last_error_location(duilib_dlgbuilder_t builder, char* source, size_t max_chars);

//=============================================================================
// 便捷方法 - 直接从资源构建
//=============================================================================

// 从XML文件直接构建（静态方法风格）
DUILIB_C_API duilib_control_t duilib_dlgbuilder_create_from_xml_file(const char* xml_file, const char* type, duilib_dialog_builder_callback_t callback, void* callback_user_data, duilib_manager_t manager, duilib_control_t parent);

// 从XML字符串直接构建（静态方法风格）
DUILIB_C_API duilib_control_t duilib_dlgbuilder_create_from_xml_string(const char* xml_string, const char* type, duilib_dialog_builder_callback_t callback, void* callback_user_data, duilib_manager_t manager, duilib_control_t parent);

//=============================================================================
// IDialogBuilderCallback 接口补充
//=============================================================================

// 预定义的控件创建回调 - 用于标准控件
DUILIB_C_API duilib_control_t duilib_dlgbuilder_default_control_callback(const char* class_name, void* user_data);

// 注册自定义控件类型
typedef struct {
    const char* class_name;                                         // 控件类名
    duilib_control_t (*create_func)(void* user_data);              // 创建函数
    void* user_data;                                               // 用户数据
} duilib_custom_control_info_t;

DUILIB_C_API duilib_result_t duilib_dlgbuilder_register_custom_control(const char* class_name, duilib_control_t (*create_func)(void*), void* user_data);
DUILIB_C_API duilib_result_t duilib_dlgbuilder_unregister_custom_control(const char* class_name);

// 带自定义控件支持的回调
DUILIB_C_API duilib_control_t duilib_dlgbuilder_custom_control_callback(const char* class_name, void* user_data);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_DLGBUILDER_H__