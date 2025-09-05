#ifndef __DUILIB_C_INTERNAL_H__
#define __DUILIB_C_INTERNAL_H__

#include "duilib_c.h"
#include "../duilib/DuiLib/UIlib.h"
#include <map>
#include <string>
#include <vector>
#include <cstring>
#include <tchar.h>

#ifdef UNICODE
    #define _T_CSTR(s) L##s
    typedef std::wstring native_string_t;
#else
    #define _T_CSTR(s) s
    typedef std::string native_string_t;
#endif

using namespace DuiLib;

// 全局状态管理（声明）
extern bool g_initialized;
extern std::map<duilib_manager_t, CPaintManagerUI*> g_managers;
extern duilib_event_callback_t g_event_callback;

// 包装器结构体
struct duilib_manager {
    CPaintManagerUI* paint_manager;
    HWND hwnd;
    std::string name;
};

struct duilib_control {
    CControlUI* control;
};

// 字符串缓存（用于返回const char*）
extern thread_local std::string g_string_buffer;

// 控件类型检查辅助函数
template<typename T>
T* safe_control_cast(duilib_control_t control, const char* expected_class = nullptr) {
    if (!control || !control->control) return nullptr;
    
    if (expected_class) {
        CDuiString class_name = control->control->GetClass();
        std::string actual_class = to_cstring(class_name);
        if (actual_class != expected_class) return nullptr;
    }
    
    return static_cast<T*>(control->control);
}

// 辅助函数声明
const char* to_cstring(const CDuiString& str);
CDuiString from_cstring(const char* str);

// 事件通知处理类
class CNotifyHandler : public INotifyUI {
public:
    void Notify(TNotifyUI& msg) override;
};

extern CNotifyHandler g_notify_handler;

#endif // __DUILIB_C_INTERNAL_H__