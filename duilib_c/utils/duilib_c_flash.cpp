#include "duilib_c_flash.h"
#include "../../duilib/DuiLib/Utils/FlashEventHandler.h"
#include <new>
#include <map>
#include <sstream>

using namespace DuiLib;

//=============================================================================
// Internal wrapper structures
//=============================================================================

class CFlashEventWrapper : public CFlashEventHandler {
public:
    CFlashEventWrapper(const duilib_flash_config_t* config);
    virtual ~CFlashEventWrapper();

    // CFlashEventHandler overrides
    virtual HRESULT OnReadyStateChange(long newState) override;
    virtual HRESULT OnProgress(long percentDone) override;
    virtual HRESULT FSCommand(BSTR command, BSTR args) override;
    virtual HRESULT OnFlashCall(BSTR request) override;

    // Configuration management
    void SetReadyStateCallback(duilib_flash_ready_state_callback_t callback, void* user_data);
    void SetProgressCallback(duilib_flash_progress_callback_t callback, void* user_data);
    void SetFSCommandCallback(duilib_flash_fscommand_callback_t callback, void* user_data);
    void SetFlashCallCallback(duilib_flash_call_callback_t callback, void* user_data);
    void SetUserData(void* user_data);
    void* GetUserData() const;

private:
    duilib_flash_ready_state_callback_t ready_state_callback_;
    duilib_flash_progress_callback_t progress_callback_;
    duilib_flash_fscommand_callback_t fscommand_callback_;
    duilib_flash_call_callback_t call_callback_;
    void* user_data_;
    
    void ConvertBSTRToUTF8(BSTR bstr, char* buffer, size_t buffer_size);
    BSTR ConvertUTF8ToBSTR(const char* utf8_str);
};

struct duilib_flashevent {
    CFlashEventWrapper* impl;
    
    duilib_flashevent(const duilib_flash_config_t* config) {
        impl = new(std::nothrow) CFlashEventWrapper(config);
    }
    
    ~duilib_flashevent() {
        delete impl;
    }
};

struct duilib_flash_manager {
    std::map<std::string, duilib_flashevent_t> handlers;
};

// Global flash manager instance
static duilib_flash_manager* g_global_flash_manager = nullptr;

//=============================================================================
// CFlashEventWrapper implementation
//=============================================================================

CFlashEventWrapper::CFlashEventWrapper(const duilib_flash_config_t* config)
    : ready_state_callback_(nullptr)
    , progress_callback_(nullptr)
    , fscommand_callback_(nullptr)
    , call_callback_(nullptr)
    , user_data_(nullptr)
{
    if (config) {
        ready_state_callback_ = config->ready_state_callback;
        progress_callback_ = config->progress_callback;
        fscommand_callback_ = config->fscommand_callback;
        call_callback_ = config->call_callback;
        user_data_ = config->user_data;
    }
}

CFlashEventWrapper::~CFlashEventWrapper() {
}

HRESULT CFlashEventWrapper::OnReadyStateChange(long newState) {
    if (ready_state_callback_) {
        long result = ready_state_callback_(newState, user_data_);
        return result == 0 ? S_OK : E_FAIL;
    }
    return S_OK;
}

HRESULT CFlashEventWrapper::OnProgress(long percentDone) {
    if (progress_callback_) {
        long result = progress_callback_(percentDone, user_data_);
        return result == 0 ? S_OK : E_FAIL;
    }
    return S_OK;
}

HRESULT CFlashEventWrapper::FSCommand(BSTR command, BSTR args) {
    if (fscommand_callback_) {
        char command_buffer[512] = {0};
        char args_buffer[1024] = {0};
        
        ConvertBSTRToUTF8(command, command_buffer, sizeof(command_buffer));
        ConvertBSTRToUTF8(args, args_buffer, sizeof(args_buffer));
        
        long result = fscommand_callback_(command_buffer, args_buffer, user_data_);
        return result == 0 ? S_OK : E_FAIL;
    }
    return S_OK;
}

HRESULT CFlashEventWrapper::OnFlashCall(BSTR request) {
    if (call_callback_) {
        char request_buffer[2048] = {0};
        ConvertBSTRToUTF8(request, request_buffer, sizeof(request_buffer));
        
        long result = call_callback_(request_buffer, user_data_);
        return result == 0 ? S_OK : E_FAIL;
    }
    return S_OK;
}

void CFlashEventWrapper::SetReadyStateCallback(duilib_flash_ready_state_callback_t callback, void* user_data) {
    ready_state_callback_ = callback;
    user_data_ = user_data;
}

void CFlashEventWrapper::SetProgressCallback(duilib_flash_progress_callback_t callback, void* user_data) {
    progress_callback_ = callback;
    user_data_ = user_data;
}

void CFlashEventWrapper::SetFSCommandCallback(duilib_flash_fscommand_callback_t callback, void* user_data) {
    fscommand_callback_ = callback;
    user_data_ = user_data;
}

void CFlashEventWrapper::SetFlashCallCallback(duilib_flash_call_callback_t callback, void* user_data) {
    call_callback_ = callback;
    user_data_ = user_data;
}

void CFlashEventWrapper::SetUserData(void* user_data) {
    user_data_ = user_data;
}

void* CFlashEventWrapper::GetUserData() const {
    return user_data_;
}

void CFlashEventWrapper::ConvertBSTRToUTF8(BSTR bstr, char* buffer, size_t buffer_size) {
    if (!bstr || !buffer || buffer_size == 0) return;
    
    WideCharToMultiByte(CP_UTF8, 0, bstr, -1, buffer, (int)buffer_size, nullptr, nullptr);
}

BSTR CFlashEventWrapper::ConvertUTF8ToBSTR(const char* utf8_str) {
    if (!utf8_str) return nullptr;
    
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8_str, -1, nullptr, 0);
    if (len <= 0) return nullptr;
    
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, utf8_str, -1, wstr, len);
    
    BSTR result = SysAllocString(wstr);
    delete[] wstr;
    return result;
}

//=============================================================================
// Flash event handler basic API implementation
//=============================================================================

DUILIB_C_API duilib_flashevent_t duilib_flashevent_create(const duilib_flash_config_t* config) {
    if (!config) return nullptr;
    return new(std::nothrow) duilib_flashevent(config);
}

DUILIB_C_API void duilib_flashevent_destroy(duilib_flashevent_t handler) {
    delete handler;
}

DUILIB_C_API bool duilib_flashevent_is_valid(duilib_flashevent_t handler) {
    return handler && handler->impl;
}

//=============================================================================
// Flash event handling methods
//=============================================================================

DUILIB_C_API long duilib_flashevent_on_ready_state_change(duilib_flashevent_t handler, long new_state) {
    if (!handler || !handler->impl) return E_FAIL;
    
    HRESULT hr = handler->impl->OnReadyStateChange(new_state);
    return SUCCEEDED(hr) ? 0 : -1;
}

DUILIB_C_API long duilib_flashevent_on_progress(duilib_flashevent_t handler, long percent_done) {
    if (!handler || !handler->impl) return E_FAIL;
    
    HRESULT hr = handler->impl->OnProgress(percent_done);
    return SUCCEEDED(hr) ? 0 : -1;
}

DUILIB_C_API long duilib_flashevent_on_fscommand(duilib_flashevent_t handler, const char* command, const char* args) {
    if (!handler || !handler->impl || !command || !args) return E_FAIL;
    
    // Convert to BSTR
    BSTR bstr_command = SysAllocStringLen(nullptr, 0);
    BSTR bstr_args = SysAllocStringLen(nullptr, 0);
    
    int cmd_len = MultiByteToWideChar(CP_UTF8, 0, command, -1, nullptr, 0);
    int args_len = MultiByteToWideChar(CP_UTF8, 0, args, -1, nullptr, 0);
    
    if (cmd_len > 0) {
        SysFreeString(bstr_command);
        bstr_command = SysAllocStringLen(nullptr, cmd_len);
        MultiByteToWideChar(CP_UTF8, 0, command, -1, bstr_command, cmd_len);
    }
    
    if (args_len > 0) {
        SysFreeString(bstr_args);
        bstr_args = SysAllocStringLen(nullptr, args_len);
        MultiByteToWideChar(CP_UTF8, 0, args, -1, bstr_args, args_len);
    }
    
    HRESULT hr = handler->impl->FSCommand(bstr_command, bstr_args);
    
    SysFreeString(bstr_command);
    SysFreeString(bstr_args);
    
    return SUCCEEDED(hr) ? 0 : -1;
}

DUILIB_C_API long duilib_flashevent_on_flash_call(duilib_flashevent_t handler, const char* request) {
    if (!handler || !handler->impl || !request) return E_FAIL;
    
    // Convert to BSTR
    int len = MultiByteToWideChar(CP_UTF8, 0, request, -1, nullptr, 0);
    if (len <= 0) return E_FAIL;
    
    BSTR bstr_request = SysAllocStringLen(nullptr, len);
    MultiByteToWideChar(CP_UTF8, 0, request, -1, bstr_request, len);
    
    HRESULT hr = handler->impl->OnFlashCall(bstr_request);
    
    SysFreeString(bstr_request);
    
    return SUCCEEDED(hr) ? 0 : -1;
}

//=============================================================================
// Flash event handler configuration management
//=============================================================================

DUILIB_C_API duilib_result_t duilib_flashevent_set_ready_state_callback(duilib_flashevent_t handler, duilib_flash_ready_state_callback_t callback, void* user_data) {
    if (!handler || !handler->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    handler->impl->SetReadyStateCallback(callback, user_data);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API duilib_result_t duilib_flashevent_set_progress_callback(duilib_flashevent_t handler, duilib_flash_progress_callback_t callback, void* user_data) {
    if (!handler || !handler->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    handler->impl->SetProgressCallback(callback, user_data);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API duilib_result_t duilib_flashevent_set_fscommand_callback(duilib_flashevent_t handler, duilib_flash_fscommand_callback_t callback, void* user_data) {
    if (!handler || !handler->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    handler->impl->SetFSCommandCallback(callback, user_data);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API duilib_result_t duilib_flashevent_set_call_callback(duilib_flashevent_t handler, duilib_flash_call_callback_t callback, void* user_data) {
    if (!handler || !handler->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    handler->impl->SetFlashCallCallback(callback, user_data);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API void* duilib_flashevent_get_user_data(duilib_flashevent_t handler) {
    if (!handler || !handler->impl) return nullptr;
    return handler->impl->GetUserData();
}

DUILIB_C_API duilib_result_t duilib_flashevent_set_user_data(duilib_flashevent_t handler, void* user_data) {
    if (!handler || !handler->impl) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    handler->impl->SetUserData(user_data);
    return DUILIB_RESULT_OK;
}

//=============================================================================
// Flash helper functions
//=============================================================================

DUILIB_C_API duilib_flash_config_t duilib_flash_config_default(void) {
    duilib_flash_config_t config;
    memset(&config, 0, sizeof(config));
    return config;
}

DUILIB_C_API const char* duilib_flash_get_ready_state_name(long state) {
    switch (state) {
        case DUILIB_FLASH_READYSTATE_UNINITIALIZED:
            return "Uninitialized";
        case DUILIB_FLASH_READYSTATE_LOADING:
            return "Loading";
        case DUILIB_FLASH_READYSTATE_LOADED:
            return "Loaded";
        case DUILIB_FLASH_READYSTATE_INTERACTIVE:
            return "Interactive";
        case DUILIB_FLASH_READYSTATE_COMPLETE:
            return "Complete";
        default:
            return "Unknown";
    }
}

DUILIB_C_API duilib_result_t duilib_flash_parse_call_request(const char* request, char* method, int method_size, char* params, int params_size) {
    if (!request || !method || !params || method_size <= 0 || params_size <= 0) {
        return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    }
    
    // Initialize output buffers
    method[0] = '\0';
    params[0] = '\0';
    
    try {
        // Parse request format: <invoke name="method" returntype="xml"><arguments><arguments>params</arguments></arguments></invoke>
        std::string req_str(request);
        
        // Find method name
        size_t name_pos = req_str.find("name=\"");
        if (name_pos != std::string::npos) {
            name_pos += 6; // Skip 'name="'
            size_t name_end = req_str.find("\"", name_pos);
            if (name_end != std::string::npos) {
                std::string method_str = req_str.substr(name_pos, name_end - name_pos);
                strncpy_s(method, method_size, method_str.c_str(), _TRUNCATE);
            }
        }
        
        // Find parameters
        size_t args_pos = req_str.find("<arguments>");
        if (args_pos != std::string::npos) {
            args_pos += 11; // Skip '<arguments>'
            size_t args_end = req_str.find("</arguments>", args_pos);
            if (args_end != std::string::npos) {
                std::string params_str = req_str.substr(args_pos, args_end - args_pos);
                strncpy_s(params, params_size, params_str.c_str(), _TRUNCATE);
            }
        }
        
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API const char* duilib_flash_build_call_response(const char* result, const char* error) {
    static thread_local char response_buffer[4096];
    
    if (error && strlen(error) > 0) {
        // Build error response
        _snprintf_s(response_buffer, sizeof(response_buffer), _TRUNCATE,
            "<error>%s</error>", error);
    } else if (result && strlen(result) > 0) {
        // Build success response
        _snprintf_s(response_buffer, sizeof(response_buffer), _TRUNCATE,
            "<result>%s</result>", result);
    } else {
        // Build empty success response
        strcpy_s(response_buffer, sizeof(response_buffer), "<result></result>");
    }
    
    return response_buffer;
}

//=============================================================================
// Flash event manager implementation
//=============================================================================

DUILIB_C_API duilib_flash_manager_t duilib_flash_manager_create(void) {
    return new(std::nothrow) duilib_flash_manager();
}

DUILIB_C_API void duilib_flash_manager_destroy(duilib_flash_manager_t manager) {
    if (manager == g_global_flash_manager) {
        g_global_flash_manager = nullptr;
    }
    
    if (manager) {
        // Clean up all handlers
        for (auto& pair : manager->handlers) {
            duilib_flashevent_destroy(pair.second);
        }
        manager->handlers.clear();
        delete manager;
    }
}

DUILIB_C_API duilib_result_t duilib_flash_manager_register(duilib_flash_manager_t manager, const char* name, duilib_flashevent_t handler) {
    if (!manager || !name || !handler) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        std::string key(name);
        
        // Remove existing handler if present
        auto it = manager->handlers.find(key);
        if (it != manager->handlers.end()) {
            duilib_flashevent_destroy(it->second);
        }
        
        manager->handlers[key] = handler;
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR_OUT_OF_MEMORY;
    }
}

DUILIB_C_API duilib_result_t duilib_flash_manager_unregister(duilib_flash_manager_t manager, const char* name) {
    if (!manager || !name) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        std::string key(name);
        auto it = manager->handlers.find(key);
        if (it != manager->handlers.end()) {
            duilib_flashevent_destroy(it->second);
            manager->handlers.erase(it);
            return DUILIB_RESULT_OK;
        }
        
        return DUILIB_RESULT_ERROR_NOT_FOUND;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_flashevent_t duilib_flash_manager_get_handler(duilib_flash_manager_t manager, const char* name) {
    if (!manager || !name) return nullptr;
    
    std::string key(name);
    auto it = manager->handlers.find(key);
    return it != manager->handlers.end() ? it->second : nullptr;
}

DUILIB_C_API duilib_result_t duilib_flash_manager_broadcast_ready_state(duilib_flash_manager_t manager, long new_state) {
    if (!manager) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        for (auto& pair : manager->handlers) {
            duilib_flashevent_on_ready_state_change(pair.second, new_state);
        }
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_result_t duilib_flash_manager_broadcast_progress(duilib_flash_manager_t manager, long percent_done) {
    if (!manager) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        for (auto& pair : manager->handlers) {
            duilib_flashevent_on_progress(pair.second, percent_done);
        }
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_flash_manager_t duilib_get_global_flash_manager(void) {
    if (!g_global_flash_manager) {
        g_global_flash_manager = new(std::nothrow) duilib_flash_manager();
    }
    return g_global_flash_manager;
}