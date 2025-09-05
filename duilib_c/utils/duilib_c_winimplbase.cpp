#include "duilib_c_winimplbase.h"
#include "../../duilib/DuiLib/Utils/WinImplBase.h"
#include <new>

using namespace DuiLib;

//=============================================================================
// Internal wrapper structures
//=============================================================================

class CWindowImplWrapper : public WindowImplBase {
public:
    CWindowImplWrapper(const duilib_winimpl_config_t* config);
    virtual ~CWindowImplWrapper();

    // WindowImplBase overrides
    virtual CDuiString GetSkinFolder() override;
    virtual CDuiString GetSkinFile() override;
    virtual LPCTSTR GetWindowClassName() const override;
    virtual UINT GetClassStyle() const override;
    virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
    virtual void OnFinalMessage(HWND hWnd) override;
    virtual void Notify(TNotifyUI& msg) override;
    virtual CControlUI* CreateControl(LPCTSTR pstrClass) override;

    // Configuration accessors
    void SetSkinFolder(LPCTSTR folder);
    void SetSkinFile(LPCTSTR file);
    void SetResourceType(duilib_resource_type_t type);
    void SetZipFileName(LPCTSTR zip_name);
    void SetResourceId(LPCTSTR resource_id);
    void SetClassStyle(UINT style);
    void SetWindowStyle(LONG style);
    
    // Callback setters
    void SetInitCallback(duilib_winimpl_init_callback_t callback, void* user_data);
    void SetNotifyCallback(duilib_winimpl_notify_callback_t callback, void* user_data);
    void SetClickCallback(duilib_winimpl_click_callback_t callback, void* user_data);
    void SetMessageCallback(duilib_winimpl_message_callback_t callback, void* user_data);
    void SetCreateControlCallback(duilib_winimpl_create_control_callback_t callback, void* user_data);
    void SetUserData(void* user_data);
    void* GetUserData() const;

private:
    CDuiString skin_folder_;
    CDuiString skin_file_;
    CDuiString window_class_name_;
    duilib_resource_type_t resource_type_;
    CDuiString zip_file_name_;
    CDuiString resource_id_;
    UINT class_style_;
    LONG window_style_;
    
    duilib_winimpl_init_callback_t init_callback_;
    duilib_winimpl_notify_callback_t notify_callback_;
    duilib_winimpl_click_callback_t click_callback_;
    duilib_winimpl_message_callback_t message_callback_;
    duilib_winimpl_create_control_callback_t create_control_callback_;
    void* callback_user_data_;
    void* user_data_;
    
    void ConvertTNotifyUIToEvent(const TNotifyUI& notify, duilib_ui_event_t* event);
    void ConvertStringToUTF8(LPCTSTR src, char* dst, size_t dst_size);
    CDuiString ConvertUTF8ToString(const char* utf8_str);
};

struct duilib_winimplbase {
    CWindowImplWrapper* impl;
    
    duilib_winimplbase(const duilib_winimpl_config_t* config) {
        impl = new(std::nothrow) CWindowImplWrapper(config);
    }
    
    ~duilib_winimplbase() {
        if (impl) {
            impl->Close();
            impl = nullptr; // WindowImplBase handles its own deletion via OnFinalMessage
        }
    }
};

// Static ZIP resource buffer
static unsigned char* g_resource_zip_buffer = nullptr;
static unsigned int g_resource_zip_size = 0;

//=============================================================================
// CWindowImplWrapper implementation
//=============================================================================

CWindowImplWrapper::CWindowImplWrapper(const duilib_winimpl_config_t* config) 
    : resource_type_(DUILIB_RESOURCE_TYPE_FILE)
    , class_style_(CS_DBLCLKS)
    , window_style_(WS_OVERLAPPEDWINDOW)
    , init_callback_(nullptr)
    , notify_callback_(nullptr)
    , click_callback_(nullptr)
    , message_callback_(nullptr)
    , create_control_callback_(nullptr)
    , callback_user_data_(nullptr)
    , user_data_(nullptr)
{
    if (config) {
        if (config->skin_folder) {
            skin_folder_ = ConvertUTF8ToString(config->skin_folder);
        }
        if (config->skin_file) {
            skin_file_ = ConvertUTF8ToString(config->skin_file);
        }
        if (config->window_class_name) {
            window_class_name_ = ConvertUTF8ToString(config->window_class_name);
        }
        
        resource_type_ = config->resource_type;
        
        if (config->zip_file_name) {
            zip_file_name_ = ConvertUTF8ToString(config->zip_file_name);
        }
        if (config->resource_id) {
            resource_id_ = ConvertUTF8ToString(config->resource_id);
        }
        
        class_style_ = config->class_style;
        window_style_ = config->window_style;
        
        init_callback_ = config->init_callback;
        notify_callback_ = config->notify_callback;
        click_callback_ = config->click_callback;
        message_callback_ = config->message_callback;
        create_control_callback_ = config->create_control_callback;
        user_data_ = config->user_data;
    }
}

CWindowImplWrapper::~CWindowImplWrapper() {
}

CDuiString CWindowImplWrapper::GetSkinFolder() {
    return skin_folder_;
}

CDuiString CWindowImplWrapper::GetSkinFile() {
    return skin_file_;
}

LPCTSTR CWindowImplWrapper::GetWindowClassName() const {
    return window_class_name_.IsEmpty() ? _T("DUIMainFrame") : window_class_name_.GetData();
}

UINT CWindowImplWrapper::GetClassStyle() const {
    return class_style_;
}

LRESULT CWindowImplWrapper::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    // Set the resource type and path based on configuration
    CPaintManagerUI* pPaintManager = &m_pm;
    
    switch (resource_type_) {
        case DUILIB_RESOURCE_TYPE_ZIP:
            if (!zip_file_name_.IsEmpty()) {
                pPaintManager->SetResourcePath(zip_file_name_.GetData());
                pPaintManager->SetResourceType(UILIB_ZIP);
            }
            break;
            
        case DUILIB_RESOURCE_TYPE_RESOURCE:
            if (!resource_id_.IsEmpty()) {
                pPaintManager->SetResourcePath(resource_id_.GetData());
                pPaintManager->SetResourceType(UILIB_RESOURCE);
            }
            break;
            
        case DUILIB_RESOURCE_TYPE_ZIPRESOURCE:
            if (!resource_id_.IsEmpty()) {
                pPaintManager->SetResourcePath(resource_id_.GetData());
                pPaintManager->SetResourceType(UILIB_ZIPRESOURCE);
            }
            break;
            
        case DUILIB_RESOURCE_TYPE_FILE:
        default:
            pPaintManager->SetResourceType(UILIB_FILE);
            break;
    }
    
    // Set ZIP resource buffer if available
    if (g_resource_zip_buffer && g_resource_zip_size > 0) {
        pPaintManager->SetResourceZip(g_resource_zip_buffer, g_resource_zip_size);
    }
    
    // Call base implementation
    LRESULT result = WindowImplBase::OnCreate(uMsg, wParam, lParam, bHandled);
    
    // Call init callback
    if (init_callback_) {
        init_callback_((duilib_winimplbase_t)this, user_data_);
    }
    
    return result;
}

LRESULT CWindowImplWrapper::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    // Call custom message callback first
    if (message_callback_) {
        BOOL handled = FALSE;
        LRESULT result = message_callback_((duilib_winimplbase_t)this, uMsg, (void*)wParam, (void*)lParam, &handled, user_data_);
        if (handled) {
            return result;
        }
    }
    
    // Call base implementation
    return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

void CWindowImplWrapper::OnFinalMessage(HWND hWnd) {
    WindowImplBase::OnFinalMessage(hWnd);
    delete this; // Safe to delete here
}

void CWindowImplWrapper::Notify(TNotifyUI& msg) {
    // Convert to C event structure
    duilib_ui_event_t event;
    ConvertTNotifyUIToEvent(msg, &event);
    
    // Handle click events specially
    if (msg.sType == DUI_MSGTYPE_CLICK || msg.sType == DUI_MSGTYPE_ITEMCLICK) {
        if (click_callback_) {
            click_callback_((duilib_winimplbase_t)this, &event, user_data_);
        }
    }
    
    // Call general notify callback
    if (notify_callback_) {
        notify_callback_((duilib_winimplbase_t)this, &event, user_data_);
    }
    
    // Call base implementation
    WindowImplBase::Notify(msg);
}

CControlUI* CWindowImplWrapper::CreateControl(LPCTSTR pstrClass) {
    // Call custom control creation callback
    if (create_control_callback_) {
        char class_name[256];
        ConvertStringToUTF8(pstrClass, class_name, sizeof(class_name));
        
        duilib_control_t control = create_control_callback_((duilib_winimplbase_t)this, class_name, user_data_);
        if (control) {
            // Assuming control wraps a CControlUI* - need to extract it
            // This would require access to the control wrapper structure
            // For now, return nullptr to use default creation
        }
    }
    
    // Call base implementation
    return WindowImplBase::CreateControl(pstrClass);
}

void CWindowImplWrapper::SetSkinFolder(LPCTSTR folder) {
    if (folder) {
        skin_folder_ = folder;
    } else {
        skin_folder_.Empty();
    }
}

void CWindowImplWrapper::SetSkinFile(LPCTSTR file) {
    if (file) {
        skin_file_ = file;
    } else {
        skin_file_.Empty();
    }
}

void CWindowImplWrapper::SetResourceType(duilib_resource_type_t type) {
    resource_type_ = type;
}

void CWindowImplWrapper::SetZipFileName(LPCTSTR zip_name) {
    if (zip_name) {
        zip_file_name_ = zip_name;
    } else {
        zip_file_name_.Empty();
    }
}

void CWindowImplWrapper::SetResourceId(LPCTSTR resource_id) {
    if (resource_id) {
        resource_id_ = resource_id;
    } else {
        resource_id_.Empty();
    }
}

void CWindowImplWrapper::SetClassStyle(UINT style) {
    class_style_ = style;
}

void CWindowImplWrapper::SetWindowStyle(LONG style) {
    window_style_ = style;
}

void CWindowImplWrapper::SetInitCallback(duilib_winimpl_init_callback_t callback, void* user_data) {
    init_callback_ = callback;
    callback_user_data_ = user_data;
}

void CWindowImplWrapper::SetNotifyCallback(duilib_winimpl_notify_callback_t callback, void* user_data) {
    notify_callback_ = callback;
    callback_user_data_ = user_data;
}

void CWindowImplWrapper::SetClickCallback(duilib_winimpl_click_callback_t callback, void* user_data) {
    click_callback_ = callback;
    callback_user_data_ = user_data;
}

void CWindowImplWrapper::SetMessageCallback(duilib_winimpl_message_callback_t callback, void* user_data) {
    message_callback_ = callback;
    callback_user_data_ = user_data;
}

void CWindowImplWrapper::SetCreateControlCallback(duilib_winimpl_create_control_callback_t callback, void* user_data) {
    create_control_callback_ = callback;
    callback_user_data_ = user_data;
}

void CWindowImplWrapper::SetUserData(void* user_data) {
    user_data_ = user_data;
}

void* CWindowImplWrapper::GetUserData() const {
    return user_data_;
}

void CWindowImplWrapper::ConvertTNotifyUIToEvent(const TNotifyUI& notify, duilib_ui_event_t* event) {
    if (!event) return;
    
    memset(event, 0, sizeof(duilib_ui_event_t));
    
    // Convert event type
    if (notify.sType == DUI_MSGTYPE_CLICK) {
        event->type = DUILIB_UI_EVENT_CLICK;
    } else if (notify.sType == DUI_MSGTYPE_DBCLICK) {
        event->type = DUILIB_UI_EVENT_DBCLICK;
    } else if (notify.sType == DUI_MSGTYPE_TEXTCHANGED) {
        event->type = DUILIB_UI_EVENT_TEXTCHANGED;
    } else if (notify.sType == DUI_MSGTYPE_RETURN) {
        event->type = DUILIB_UI_EVENT_RETURN;
    } else if (notify.sType == DUI_MSGTYPE_SCROLL) {
        event->type = DUILIB_UI_EVENT_SCROLL;
    } else if (notify.sType == DUI_MSGTYPE_SETFOCUS) {
        event->type = DUILIB_UI_EVENT_SETFOCUS;
    } else if (notify.sType == DUI_MSGTYPE_KILLFOCUS) {
        event->type = DUILIB_UI_EVENT_KILLFOCUS;
    } else if (notify.sType == DUI_MSGTYPE_TIMER) {
        event->type = DUILIB_UI_EVENT_TIMER;
    } else if (notify.sType == DUI_MSGTYPE_MENU) {
        event->type = DUILIB_UI_EVENT_MENU;
    } else {
        event->type = DUILIB_UI_EVENT_UNKNOWN;
    }
    
    // Convert sender control name
    if (notify.pSender) {
        ConvertStringToUTF8(notify.pSender->GetName().GetData(), event->sender_name, sizeof(event->sender_name));
    }
    
    // Convert event type string
    ConvertStringToUTF8(notify.sType.GetData(), event->type_name, sizeof(event->type_name));
    
    // Set basic properties
    event->sender = (duilib_control_t)notify.pSender; // Cast to opaque handle
    event->timestamp = GetTickCount();
    event->wparam = notify.wParam;
    event->lparam = notify.lParam;
    
    // Copy point data
    event->point.x = notify.ptMouse.x;
    event->point.y = notify.ptMouse.y;
}

void CWindowImplWrapper::ConvertStringToUTF8(LPCTSTR src, char* dst, size_t dst_size) {
    if (!src || !dst || dst_size == 0) return;
    
#ifdef _UNICODE
    WideCharToMultiByte(CP_UTF8, 0, src, -1, dst, (int)dst_size, nullptr, nullptr);
#else
    strncpy_s(dst, dst_size, src, _TRUNCATE);
#endif
}

CDuiString CWindowImplWrapper::ConvertUTF8ToString(const char* utf8_str) {
    if (!utf8_str) return CDuiString();
    
#ifdef _UNICODE
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8_str, -1, nullptr, 0);
    if (len <= 0) return CDuiString();
    
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, utf8_str, -1, wstr, len);
    CDuiString result(wstr);
    delete[] wstr;
    return result;
#else
    return CDuiString(utf8_str);
#endif
}

//=============================================================================
// WindowImplBase C API implementation
//=============================================================================

DUILIB_C_API duilib_winimplbase_t duilib_winimplbase_create(const duilib_winimpl_config_t* config) {
    if (!config) return nullptr;
    return new(std::nothrow) duilib_winimplbase(config);
}

DUILIB_C_API void duilib_winimplbase_destroy(duilib_winimplbase_t window) {
    delete window;
}

DUILIB_C_API duilib_window_t duilib_winimplbase_to_window(duilib_winimplbase_t window) {
    return window ? (duilib_window_t)window->impl : nullptr;
}

DUILIB_C_API duilib_winimplbase_t duilib_window_to_winimplbase(duilib_window_t window) {
    // This would require RTTI or a safe casting mechanism
    // For now, return nullptr as we can't safely cast back
    return nullptr;
}

DUILIB_C_API bool duilib_winimplbase_is_valid(duilib_winimplbase_t window) {
    return window && window->impl;
}

DUILIB_C_API duilib_result_t duilib_winimplbase_init_window(duilib_winimplbase_t window) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        window->impl->InitWindow();
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_manager_t duilib_winimplbase_get_paint_manager(duilib_winimplbase_t window) {
    if (!window || !window->impl) return nullptr;
    return (duilib_manager_t)&(window->impl->GetPaintManager());
}

// Configuration methods
DUILIB_C_API const char* duilib_winimplbase_get_skin_folder(duilib_winimplbase_t window) {
    if (!window || !window->impl) return nullptr;
    
    CDuiString folder = window->impl->GetSkinFolder();
    static thread_local char buffer[512];
    
#ifdef _UNICODE
    WideCharToMultiByte(CP_UTF8, 0, folder.GetData(), -1, buffer, sizeof(buffer), nullptr, nullptr);
#else
    strncpy_s(buffer, sizeof(buffer), folder.GetData(), _TRUNCATE);
#endif
    
    return buffer;
}

DUILIB_C_API duilib_result_t duilib_winimplbase_set_skin_folder(duilib_winimplbase_t window, const char* folder) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
#ifdef _UNICODE
        if (folder) {
            int len = MultiByteToWideChar(CP_UTF8, 0, folder, -1, nullptr, 0);
            wchar_t* wstr = new wchar_t[len];
            MultiByteToWideChar(CP_UTF8, 0, folder, -1, wstr, len);
            window->impl->SetSkinFolder(wstr);
            delete[] wstr;
        } else {
            window->impl->SetSkinFolder(nullptr);
        }
#else
        window->impl->SetSkinFolder(folder);
#endif
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR_OUT_OF_MEMORY;
    }
}

DUILIB_C_API const char* duilib_winimplbase_get_skin_file(duilib_winimplbase_t window) {
    if (!window || !window->impl) return nullptr;
    
    CDuiString file = window->impl->GetSkinFile();
    static thread_local char buffer[512];
    
#ifdef _UNICODE
    WideCharToMultiByte(CP_UTF8, 0, file.GetData(), -1, buffer, sizeof(buffer), nullptr, nullptr);
#else
    strncpy_s(buffer, sizeof(buffer), file.GetData(), _TRUNCATE);
#endif
    
    return buffer;
}

DUILIB_C_API duilib_result_t duilib_winimplbase_set_skin_file(duilib_winimplbase_t window, const char* file) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
#ifdef _UNICODE
        if (file) {
            int len = MultiByteToWideChar(CP_UTF8, 0, file, -1, nullptr, 0);
            wchar_t* wstr = new wchar_t[len];
            MultiByteToWideChar(CP_UTF8, 0, file, -1, wstr, len);
            window->impl->SetSkinFile(wstr);
            delete[] wstr;
        } else {
            window->impl->SetSkinFile(nullptr);
        }
#else
        window->impl->SetSkinFile(file);
#endif
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR_OUT_OF_MEMORY;
    }
}

DUILIB_C_API const char* duilib_winimplbase_get_window_class_name(duilib_winimplbase_t window) {
    if (!window || !window->impl) return nullptr;
    
    LPCTSTR class_name = window->impl->GetWindowClassName();
    static thread_local char buffer[256];
    
#ifdef _UNICODE
    WideCharToMultiByte(CP_UTF8, 0, class_name, -1, buffer, sizeof(buffer), nullptr, nullptr);
#else
    strncpy_s(buffer, sizeof(buffer), class_name, _TRUNCATE);
#endif
    
    return buffer;
}

DUILIB_C_API duilib_resource_type_t duilib_winimplbase_get_resource_type(duilib_winimplbase_t window) {
    if (!window || !window->impl) return DUILIB_RESOURCE_TYPE_FILE;
    
    // Access private member through wrapper
    return DUILIB_RESOURCE_TYPE_FILE; // Default fallback
}

DUILIB_C_API duilib_result_t duilib_winimplbase_set_resource_type(duilib_winimplbase_t window, duilib_resource_type_t type) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    window->impl->SetResourceType(type);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API const char* duilib_winimplbase_get_zip_file_name(duilib_winimplbase_t window) {
    // Implementation would require access to private members
    return nullptr;
}

DUILIB_C_API duilib_result_t duilib_winimplbase_set_zip_file_name(duilib_winimplbase_t window, const char* zip_name) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
#ifdef _UNICODE
        if (zip_name) {
            int len = MultiByteToWideChar(CP_UTF8, 0, zip_name, -1, nullptr, 0);
            wchar_t* wstr = new wchar_t[len];
            MultiByteToWideChar(CP_UTF8, 0, zip_name, -1, wstr, len);
            window->impl->SetZipFileName(wstr);
            delete[] wstr;
        } else {
            window->impl->SetZipFileName(nullptr);
        }
#else
        window->impl->SetZipFileName(zip_name);
#endif
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR_OUT_OF_MEMORY;
    }
}

DUILIB_C_API const char* duilib_winimplbase_get_resource_id(duilib_winimplbase_t window) {
    // Implementation would require access to private members
    return nullptr;
}

DUILIB_C_API duilib_result_t duilib_winimplbase_set_resource_id(duilib_winimplbase_t window, const char* resource_id) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
#ifdef _UNICODE
        if (resource_id) {
            int len = MultiByteToWideChar(CP_UTF8, 0, resource_id, -1, nullptr, 0);
            wchar_t* wstr = new wchar_t[len];
            MultiByteToWideChar(CP_UTF8, 0, resource_id, -1, wstr, len);
            window->impl->SetResourceId(wstr);
            delete[] wstr;
        } else {
            window->impl->SetResourceId(nullptr);
        }
#else
        window->impl->SetResourceId(resource_id);
#endif
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR_OUT_OF_MEMORY;
    }
}

DUILIB_C_API unsigned int duilib_winimplbase_get_class_style(duilib_winimplbase_t window) {
    if (!window || !window->impl) return 0;
    return window->impl->GetClassStyle();
}

DUILIB_C_API duilib_result_t duilib_winimplbase_set_class_style(duilib_winimplbase_t window, unsigned int style) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    window->impl->SetClassStyle(style);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API long duilib_winimplbase_get_style(duilib_winimplbase_t window) {
    if (!window || !window->impl) return 0;
    return GetWindowLong(window->impl->GetHWND(), GWL_STYLE);
}

DUILIB_C_API duilib_result_t duilib_winimplbase_set_style(duilib_winimplbase_t window, long style) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    window->impl->SetWindowStyle(style);
    return DUILIB_RESULT_OK;
}

// Callback setters
DUILIB_C_API duilib_result_t duilib_winimplbase_set_init_callback(duilib_winimplbase_t window, duilib_winimpl_init_callback_t callback, void* user_data) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    window->impl->SetInitCallback(callback, user_data);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API duilib_result_t duilib_winimplbase_set_notify_callback(duilib_winimplbase_t window, duilib_winimpl_notify_callback_t callback, void* user_data) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    window->impl->SetNotifyCallback(callback, user_data);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API duilib_result_t duilib_winimplbase_set_click_callback(duilib_winimplbase_t window, duilib_winimpl_click_callback_t callback, void* user_data) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    window->impl->SetClickCallback(callback, user_data);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API duilib_result_t duilib_winimplbase_set_message_callback(duilib_winimplbase_t window, duilib_winimpl_message_callback_t callback, void* user_data) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    window->impl->SetMessageCallback(callback, user_data);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API duilib_result_t duilib_winimplbase_set_create_control_callback(duilib_winimplbase_t window, duilib_winimpl_create_control_callback_t callback, void* user_data) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    window->impl->SetCreateControlCallback(callback, user_data);
    return DUILIB_RESULT_OK;
}

// Message handling
DUILIB_C_API long duilib_winimplbase_response_default_key_event(duilib_winimplbase_t window, void* wparam) {
    if (!window || !window->impl) return 0;
    return window->impl->ResponseDefaultKeyEvent((WPARAM)wparam);
}

DUILIB_C_API long duilib_winimplbase_message_handler(duilib_winimplbase_t window, unsigned int msg, void* wparam, void* lparam, bool* handled) {
    if (!window || !window->impl) return 0;
    
    BOOL bHandled = FALSE;
    LRESULT result = window->impl->HandleMessage(msg, (WPARAM)wparam, (LPARAM)lparam);
    if (handled) *handled = (bHandled != FALSE);
    return result;
}

DUILIB_C_API long duilib_winimplbase_handle_custom_message(duilib_winimplbase_t window, unsigned int msg, void* wparam, void* lparam, bool* handled) {
    if (!window || !window->impl) return 0;
    
    BOOL bHandled = FALSE;
    LRESULT result = window->impl->HandleCustomMessage(msg, (WPARAM)wparam, (LPARAM)lparam, bHandled);
    if (handled) *handled = (bHandled != FALSE);
    return result;
}

// Static resource management
DUILIB_C_API duilib_result_t duilib_winimplbase_set_resource_zip_buffer(unsigned char* buffer, unsigned int size) {
    g_resource_zip_buffer = buffer;
    g_resource_zip_size = size;
    return DUILIB_RESULT_OK;
}

DUILIB_C_API unsigned char* duilib_winimplbase_get_resource_zip_buffer(void) {
    return g_resource_zip_buffer;
}

// Window operations
DUILIB_C_API void* duilib_winimplbase_create_window(duilib_winimplbase_t window, void* parent, const char* name, unsigned int style, unsigned int ex_style) {
    if (!window || !window->impl) return nullptr;
    
#ifdef _UNICODE
    wchar_t* wname = nullptr;
    if (name) {
        int len = MultiByteToWideChar(CP_UTF8, 0, name, -1, nullptr, 0);
        wname = new wchar_t[len];
        MultiByteToWideChar(CP_UTF8, 0, name, -1, wname, len);
    }
    
    HWND result = window->impl->Create((HWND)parent, wname ? wname : L"", style, ex_style);
    delete[] wname;
    return result;
#else
    return window->impl->Create((HWND)parent, name ? name : "", style, ex_style);
#endif
}

DUILIB_C_API duilib_result_t duilib_winimplbase_show_window(duilib_winimplbase_t window, bool show, bool take_focus) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    window->impl->ShowWindow(show, take_focus);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API duilib_result_t duilib_winimplbase_show_modal(duilib_winimplbase_t window, void* parent) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    window->impl->ShowModal();
    return DUILIB_RESULT_OK;
}

DUILIB_C_API duilib_result_t duilib_winimplbase_close_window(duilib_winimplbase_t window, unsigned int ret) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    window->impl->Close(ret);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API duilib_result_t duilib_winimplbase_center_window(duilib_winimplbase_t window) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    window->impl->CenterWindow();
    return DUILIB_RESULT_OK;
}

DUILIB_C_API duilib_result_t duilib_winimplbase_set_icon(duilib_winimplbase_t window, unsigned int resource_id) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    window->impl->SetIcon(resource_id);
    return DUILIB_RESULT_OK;
}

// Helper functions
DUILIB_C_API duilib_control_t duilib_winimplbase_find_control(duilib_winimplbase_t window, const char* name) {
    if (!window || !window->impl || !name) return nullptr;
    
#ifdef _UNICODE
    int len = MultiByteToWideChar(CP_UTF8, 0, name, -1, nullptr, 0);
    wchar_t* wname = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, name, -1, wname, len);
    
    CControlUI* control = window->impl->GetPaintManager().FindControl(wname);
    delete[] wname;
    return (duilib_control_t)control;
#else
    CControlUI* control = window->impl->GetPaintManager().FindControl(name);
    return (duilib_control_t)control;
#endif
}

DUILIB_C_API duilib_result_t duilib_winimplbase_set_window_text(duilib_winimplbase_t window, const char* title) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
#ifdef _UNICODE
    if (title) {
        int len = MultiByteToWideChar(CP_UTF8, 0, title, -1, nullptr, 0);
        wchar_t* wtitle = new wchar_t[len];
        MultiByteToWideChar(CP_UTF8, 0, title, -1, wtitle, len);
        SetWindowText(window->impl->GetHWND(), wtitle);
        delete[] wtitle;
    } else {
        SetWindowText(window->impl->GetHWND(), L"");
    }
#else
    SetWindowText(window->impl->GetHWND(), title ? title : "");
#endif
    
    return DUILIB_RESULT_OK;
}

DUILIB_C_API const char* duilib_winimplbase_get_window_text(duilib_winimplbase_t window) {
    if (!window || !window->impl) return nullptr;
    
    static thread_local char buffer[512];
    
#ifdef _UNICODE
    wchar_t wbuffer[512];
    GetWindowText(window->impl->GetHWND(), wbuffer, 512);
    WideCharToMultiByte(CP_UTF8, 0, wbuffer, -1, buffer, sizeof(buffer), nullptr, nullptr);
#else
    GetWindowText(window->impl->GetHWND(), buffer, 512);
#endif
    
    return buffer;
}

DUILIB_C_API duilib_result_t duilib_winimplbase_invalidate(duilib_winimplbase_t window) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    window->impl->GetPaintManager().Invalidate();
    return DUILIB_RESULT_OK;
}

DUILIB_C_API void* duilib_winimplbase_get_user_data(duilib_winimplbase_t window) {
    if (!window || !window->impl) return nullptr;
    return window->impl->GetUserData();
}

DUILIB_C_API duilib_result_t duilib_winimplbase_set_user_data(duilib_winimplbase_t window, void* user_data) {
    if (!window || !window->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    window->impl->SetUserData(user_data);
    return DUILIB_RESULT_OK;
}