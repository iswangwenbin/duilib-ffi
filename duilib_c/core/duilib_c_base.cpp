#include "../duilib_c_internal.h"

// 全局状态管理
bool g_initialized = false;
std::map<duilib_manager_t, CPaintManagerUI*> g_managers;
duilib_event_callback_t g_event_callback = nullptr;

// 字符串缓存（用于返回const char*）
thread_local std::string g_string_buffer;

// 事件通知处理对象
CNotifyHandler g_notify_handler;

//=============================================================================
// 内部辅助函数实现
//=============================================================================

// 辅助函数：将CDuiString转换为const char*
const char* to_cstring(const CDuiString& str) {
#ifdef UNICODE
    // 将Unicode字符串转换为UTF-8
    int len = WideCharToMultiByte(CP_UTF8, 0, str.GetData(), -1, nullptr, 0, nullptr, nullptr);
    if (len > 0) {
        g_string_buffer.resize(len - 1);
        WideCharToMultiByte(CP_UTF8, 0, str.GetData(), -1, &g_string_buffer[0], len, nullptr, nullptr);
    } else {
        g_string_buffer.clear();
    }
#else
    g_string_buffer = str.GetData();
#endif
    return g_string_buffer.c_str();
}

// 辅助函数：将const char*转换为CDuiString
CDuiString from_cstring(const char* str) {
    if (!str) return CDuiString();
#ifdef UNICODE
    int len = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
    if (len > 0) {
        std::wstring wstr(len - 1, 0);
        MultiByteToWideChar(CP_UTF8, 0, str, -1, &wstr[0], len);
        return CDuiString(wstr.c_str());
    }
    return CDuiString();
#else
    return CDuiString(str);
#endif
}

// 事件通知处理类实现
void CNotifyHandler::Notify(TNotifyUI& msg) {
    if (!g_event_callback) return;

    duilib_event_t event = {0};
    event.sender = reinterpret_cast<duilib_control_t>(new duilib_control{msg.pSender});
    
    // 转换事件类型
    CDuiString sType = msg.sType;
    if (sType == DUI_MSGTYPE_CLICK) {
        event.type = DUILIB_EVENT_CLICK;
    } else if (sType == DUI_MSGTYPE_BUTTONDOWN) {
        event.type = DUILIB_EVENT_BUTTON_DOWN;
    } else if (sType == DUI_MSGTYPE_BUTTONUP) {
        event.type = DUILIB_EVENT_BUTTON_UP;
    } else if (sType == DUI_MSGTYPE_MOUSEENTER) {
        event.type = DUILIB_EVENT_MOUSE_ENTER;
    } else if (sType == DUI_MSGTYPE_MOUSELEAVE) {
        event.type = DUILIB_EVENT_MOUSE_LEAVE;
    } else if (sType == DUI_MSGTYPE_KEYDOWN) {
        event.type = DUILIB_EVENT_KEY_DOWN;
    } else if (sType == DUI_MSGTYPE_KEYUP) {
        event.type = DUILIB_EVENT_KEY_UP;
    } else if (sType == DUI_MSGTYPE_TEXTCHANGED) {
        event.type = DUILIB_EVENT_TEXT_CHANGED;
    } else if (sType == DUI_MSGTYPE_VALUECHANGED) {
        event.type = DUILIB_EVENT_VALUE_CHANGED;
    } else if (sType == DUI_MSGTYPE_WINDOWCLOSE) {
        event.type = DUILIB_EVENT_WINDOW_CLOSE;
    }
    
    // 填充鼠标位置信息
    event.data.mouse.x = msg.ptMouse.x;
    event.data.mouse.y = msg.ptMouse.y;
    
    // 调用回调函数
    g_event_callback(&event);
    
    // 清理临时控件包装器
    delete reinterpret_cast<duilib_control*>(event.sender);
}

//=============================================================================
// 核心初始化API实现
//=============================================================================

DUILIB_C_API duilib_result_t duilib_init(void) {
    if (g_initialized) {
        return DUILIB_OK;
    }
    
    try {
        // 初始化COM
        ::CoInitialize(nullptr);
        
        g_initialized = true;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API void duilib_cleanup(void) {
    if (!g_initialized) {
        return;
    }
    
    // 清理所有管理器
    g_managers.clear();
    g_event_callback = nullptr;
    
    // 清理COM
    ::CoUninitialize();
    
    g_initialized = false;
}

//=============================================================================
// 消息循环API实现
//=============================================================================

DUILIB_C_API int duilib_message_loop(void) {
    return CPaintManagerUI::MessageLoop();
}

DUILIB_C_API bool duilib_translate_message(MSG* msg) {
    return CPaintManagerUI::TranslateMessage(msg);
}

DUILIB_C_API void duilib_quit_message_loop(int exit_code) {
    ::PostQuitMessage(exit_code);
}

//=============================================================================
// 内存管理API实现
//=============================================================================

DUILIB_C_API void duilib_control_destroy(duilib_control_t control) {
    if (control) {
        delete control;
    }
}

//=============================================================================
// 工具函数API实现
//=============================================================================

DUILIB_C_API duilib_result_t duilib_set_resource_path(const char* path) {
    if (!path) return DUILIB_ERROR_INVALID_PARAM;
    
    try {
        CPaintManagerUI::SetResourcePath(from_cstring(path));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_set_resource_zip(const char* zip_file) {
    if (!zip_file) return DUILIB_ERROR_INVALID_PARAM;
    
    try {
        CPaintManagerUI::SetResourceZip(from_cstring(zip_file));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

// 全局静态方法实现
DUILIB_C_API void* duilib_get_instance(void) {
    return CPaintManagerUI::GetInstance();
}

DUILIB_C_API const char* duilib_get_instance_path(void) {
    return to_cstring(CPaintManagerUI::GetInstancePath());
}

DUILIB_C_API const char* duilib_get_current_path(void) {
    return to_cstring(CPaintManagerUI::GetCurrentPath());
}

DUILIB_C_API void* duilib_get_resource_dll(void) {
    return CPaintManagerUI::GetResourceDll();
}

DUILIB_C_API const char* duilib_get_resource_zip(void) {
    return to_cstring(CPaintManagerUI::GetResourceZip());
}

DUILIB_C_API bool duilib_is_cached_resource_zip(void) {
    return CPaintManagerUI::IsCachedResourceZip();
}

DUILIB_C_API void* duilib_get_resource_zip_handle(void) {
    return CPaintManagerUI::GetResourceZipHandle();
}

DUILIB_C_API duilib_result_t duilib_set_instance(void* hinst) {
    try {
        CPaintManagerUI::SetInstance(static_cast<HINSTANCE>(hinst));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_set_current_path(const char* path) {
    if (!path) return DUILIB_ERROR_INVALID_PARAM;
    
    try {
        CPaintManagerUI::SetCurrentPath(from_cstring(path));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_set_resource_dll(void* hinst) {
    try {
        CPaintManagerUI::SetResourceDll(static_cast<HINSTANCE>(hinst));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_get_hsl(short* h, short* s, short* l) {
    if (!h || !s || !l) return DUILIB_ERROR_INVALID_PARAM;
    
    try {
        CPaintManagerUI::GetHSL(h, s, l);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_set_hsl(bool use_hsl, short h, short s, short l) {
    try {
        CPaintManagerUI::SetHSL(use_hsl, h, s, l);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_reload_skin(void) {
    try {
        CPaintManagerUI::ReloadSkin();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_manager_t duilib_get_paint_manager(const char* name) {
    if (!name) return nullptr;
    
    try {
        CPaintManagerUI* manager = CPaintManagerUI::GetPaintManager(from_cstring(name));
        if (!manager) return nullptr;
        
        // 查找现有的manager包装器
        for (auto& pair : g_managers) {
            if (pair.second == manager) {
                return pair.first;
            }
        }
        
        return nullptr;
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_load_plugin(const char* module_name) {
    if (!module_name) return DUILIB_ERROR_INVALID_PARAM;
    
    try {
        CPaintManagerUI::LoadPlugin(from_cstring(module_name));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

// 多语言支持实现
DUILIB_C_API duilib_result_t duilib_add_multi_language_string(int id, const char* text) {
    if (!text) return DUILIB_ERROR_INVALID_PARAM;
    
    try {
        CPaintManagerUI::AddMultiLanguageString(id, from_cstring(text));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API const char* duilib_get_multi_language_string(int id) {
    try {
        return to_cstring(CPaintManagerUI::GetMultiLanguageString(id));
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_remove_multi_language_string(int id) {
    try {
        CPaintManagerUI::RemoveMultiLanguageString(id);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_remove_all_multi_language_strings(void) {
    try {
        CPaintManagerUI::RemoveAllMultiLanguageString();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}