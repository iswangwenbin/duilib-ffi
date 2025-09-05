#include "../duilib_c_internal.h"
#include "duilib_c_dlgbuilder.h"

// 对话框构建器包装结构体
struct duilib_dlgbuilder {
    CDialogBuilder* builder;
};

//=============================================================================
// 对话框构建器API实现 - 对应 CDialogBuilder
//=============================================================================

DUILIB_C_API duilib_dlgbuilder_t duilib_dlgbuilder_create(void) {
    try {
        duilib_dlgbuilder_t builder = new duilib_dlgbuilder;
        builder->builder = new CDialogBuilder();
        return builder;
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API void duilib_dlgbuilder_destroy(duilib_dlgbuilder_t builder) {
    if (builder) {
        if (builder->builder) {
            delete builder->builder;
        }
        delete builder;
    }
}

DUILIB_C_API duilib_control_t duilib_dlgbuilder_create_from_file(duilib_dlgbuilder_t builder, const char* xml_file, const char* type, duilib_event_callback_t callback, duilib_manager_t manager, duilib_control_t parent) {
    if (!builder || !builder->builder || !xml_file) return nullptr;

    try {
        CPaintManagerUI* paint_manager = nullptr;
        if (manager && g_managers.find(manager) != g_managers.end()) {
            paint_manager = g_managers[manager];
        }

        // 设置回调函数
        if (callback) {
            g_event_callback = callback;
        }

        CControlUI* parent_control = nullptr;
        if (parent && parent->control) {
            parent_control = parent->control;
        }

        CControlUI* control = builder->builder->Create(from_cstring(xml_file), 
                                                      type ? from_cstring(type) : CDuiString(),
                                                      callback ? &g_notify_handler : nullptr,
                                                      paint_manager, 
                                                      parent_control);
        
        if (!control) return nullptr;
        
        return new duilib_control{control};
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_control_t duilib_dlgbuilder_create_from_string(duilib_dlgbuilder_t builder, const char* xml_string, const char* type, duilib_event_callback_t callback, duilib_manager_t manager, duilib_control_t parent) {
    if (!builder || !builder->builder || !xml_string) return nullptr;

    try {
        CPaintManagerUI* paint_manager = nullptr;
        if (manager && g_managers.find(manager) != g_managers.end()) {
            paint_manager = g_managers[manager];
        }

        // 设置回调函数
        if (callback) {
            g_event_callback = callback;
        }

        CControlUI* parent_control = nullptr;
        if (parent && parent->control) {
            parent_control = parent->control;
        }

        // 注意：这里需要从字符串创建，可能需要先保存为临时文件或使用内存流
        // 实际实现可能需要适配DuiLib具体的接口
        CControlUI* control = builder->builder->Create(from_cstring(xml_string),
                                                      type ? from_cstring(type) : CDuiString(),
                                                      callback ? &g_notify_handler : nullptr,
                                                      paint_manager,
                                                      parent_control);
        
        if (!control) return nullptr;
        
        return new duilib_control{control};
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API void* duilib_dlgbuilder_get_markup(duilib_dlgbuilder_t builder) {
    if (!builder || !builder->builder) return nullptr;

    try {
        return builder->builder->GetMarkup();
    } catch (...) {
        return nullptr;
    }
}