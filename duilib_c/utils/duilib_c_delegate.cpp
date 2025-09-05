#include "duilib_c_delegate.h"
#include "../../duilib/DuiLib/Utils/UIDelegate.h"
#include <new>
#include <map>
#include <vector>
#include <algorithm>

using namespace DuiLib;

//=============================================================================
// Internal wrapper structures
//=============================================================================

struct duilib_delegatebase {
    CDelegateBase* impl;
    duilib_delegatebase(CDelegateBase* delegate) : impl(delegate) {}
    ~duilib_delegatebase() { delete impl; }
};

// C callback wrapper for CDelegateStatic
class CCallbackDelegate : public CDelegateBase {
public:
    CCallbackDelegate(duilib_delegate_callback_t callback, void* user_data)
        : callback_(callback), user_data_(user_data) {}
    
    virtual CDelegateBase* Copy() override {
        return new CCallbackDelegate(callback_, user_data_);
    }
    
    virtual bool Invoke(void* param) override {
        return callback_ ? callback_(param, user_data_) : false;
    }
    
    virtual bool Equals(const CDelegateBase* pDelegate) const override {
        const CCallbackDelegate* other = dynamic_cast<const CCallbackDelegate*>(pDelegate);
        return other && other->callback_ == callback_ && other->user_data_ == user_data_;
    }

private:
    duilib_delegate_callback_t callback_;
    void* user_data_;
};

struct duilib_delegatestatic {
    CDelegateStatic impl;
    duilib_delegatestatic(duilib_delegate_callback_t callback, void* user_data) 
        : impl(new CCallbackDelegate(callback, user_data)) {}
};

struct duilib_eventsource {
    CEventSource impl;
};

struct duilib_multicast_delegate {
    std::vector<std::pair<duilib_delegate_callback_t, void*>> callbacks;
};

// Event handler wrapper
struct EventHandlerWrapper {
    duilib_event_handler_t handler;
    void* user_data;
    
    EventHandlerWrapper(duilib_event_handler_t h, void* data) : handler(h), user_data(data) {}
};

struct duilib_event_manager {
    std::map<duilib_event_type_t, std::vector<EventHandlerWrapper>> event_handlers;
};

// Global event manager instance
static duilib_event_manager* g_global_event_manager = nullptr;

//=============================================================================
// CDelegateBase implementation
//=============================================================================

DUILIB_C_API void duilib_delegatebase_destroy(duilib_delegatebase_t delegate) {
    delete delegate;
}

DUILIB_C_API bool duilib_delegatebase_equals(duilib_delegatebase_t delegate, duilib_delegatebase_t other) {
    if (!delegate || !other) return false;
    return delegate->impl->Equals(other->impl);
}

DUILIB_C_API bool duilib_delegatebase_invoke(duilib_delegatebase_t delegate, void* param) {
    if (!delegate) return false;
    return delegate->impl->Invoke(param);
}

//=============================================================================
// CDelegateStatic implementation  
//=============================================================================

DUILIB_C_API duilib_delegatestatic_t duilib_delegatestatic_create(duilib_delegate_callback_t callback, void* user_data) {
    if (!callback) return nullptr;
    return new(std::nothrow) duilib_delegatestatic(callback, user_data);
}

DUILIB_C_API void duilib_delegatestatic_destroy(duilib_delegatestatic_t delegate) {
    delete delegate;
}

DUILIB_C_API duilib_delegatebase_t duilib_delegatestatic_to_base(duilib_delegatestatic_t delegate) {
    if (!delegate) return nullptr;
    
    CDelegateBase* copy = delegate->impl.Copy();
    if (!copy) return nullptr;
    
    return new(std::nothrow) duilib_delegatebase(copy);
}

//=============================================================================
// CEventSource implementation
//=============================================================================

DUILIB_C_API duilib_eventsource_t duilib_eventsource_create(void) {
    return new(std::nothrow) duilib_eventsource();
}

DUILIB_C_API void duilib_eventsource_destroy(duilib_eventsource_t event_source) {
    delete event_source;
}

DUILIB_C_API bool duilib_eventsource_has_handlers(duilib_eventsource_t event_source) {
    return event_source ? !event_source->impl.IsEmpty() : false;
}

DUILIB_C_API bool duilib_eventsource_invoke(duilib_eventsource_t event_source, void* param) {
    if (!event_source) return false;
    return event_source->impl(param);
}

DUILIB_C_API duilib_result_t duilib_eventsource_add_delegate(duilib_eventsource_t event_source, duilib_delegatebase_t delegate) {
    if (!event_source || !delegate) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        event_source->impl += delegate->impl->Copy();
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR_OUT_OF_MEMORY;
    }
}

DUILIB_C_API duilib_result_t duilib_eventsource_add_callback(duilib_eventsource_t event_source, duilib_delegate_callback_t callback, void* user_data) {
    if (!event_source || !callback) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        CDelegateBase* delegate = new CCallbackDelegate(callback, user_data);
        event_source->impl += delegate;
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR_OUT_OF_MEMORY;
    }
}

DUILIB_C_API duilib_result_t duilib_eventsource_remove_delegate(duilib_eventsource_t event_source, duilib_delegatebase_t delegate) {
    if (!event_source || !delegate) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        event_source->impl -= delegate->impl;
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_result_t duilib_eventsource_remove_callback(duilib_eventsource_t event_source, duilib_delegate_callback_t callback, void* user_data) {
    if (!event_source || !callback) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        CCallbackDelegate temp_delegate(callback, user_data);
        event_source->impl -= &temp_delegate;
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

//=============================================================================
// Helper functions
//=============================================================================

DUILIB_C_API duilib_delegatebase_t duilib_make_delegate(duilib_delegate_callback_t callback, void* user_data) {
    if (!callback) return nullptr;
    
    try {
        CDelegateBase* delegate = new CCallbackDelegate(callback, user_data);
        return new(std::nothrow) duilib_delegatebase(delegate);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_delegatebase_t duilib_delegate_copy(duilib_delegatebase_t delegate) {
    if (!delegate) return nullptr;
    
    try {
        CDelegateBase* copy = delegate->impl->Copy();
        if (!copy) return nullptr;
        return new(std::nothrow) duilib_delegatebase(copy);
    } catch (...) {
        return nullptr;
    }
}

//=============================================================================
// Multicast delegate implementation
//=============================================================================

DUILIB_C_API duilib_multicast_delegate_t duilib_multicast_delegate_create(void) {
    return new(std::nothrow) duilib_multicast_delegate();
}

DUILIB_C_API void duilib_multicast_delegate_destroy(duilib_multicast_delegate_t delegate) {
    delete delegate;
}

DUILIB_C_API duilib_result_t duilib_multicast_delegate_add(duilib_multicast_delegate_t delegate, duilib_delegate_callback_t callback, void* user_data) {
    if (!delegate || !callback) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        delegate->callbacks.emplace_back(callback, user_data);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR_OUT_OF_MEMORY;
    }
}

DUILIB_C_API duilib_result_t duilib_multicast_delegate_remove(duilib_multicast_delegate_t delegate, duilib_delegate_callback_t callback, void* user_data) {
    if (!delegate || !callback) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        auto it = std::find_if(delegate->callbacks.begin(), delegate->callbacks.end(),
            [callback, user_data](const std::pair<duilib_delegate_callback_t, void*>& pair) {
                return pair.first == callback && pair.second == user_data;
            });
        
        if (it != delegate->callbacks.end()) {
            delegate->callbacks.erase(it);
            return DUILIB_RESULT_OK;
        }
        
        return DUILIB_RESULT_ERROR_NOT_FOUND;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_result_t duilib_multicast_delegate_clear(duilib_multicast_delegate_t delegate) {
    if (!delegate) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        delegate->callbacks.clear();
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API bool duilib_multicast_delegate_invoke(duilib_multicast_delegate_t delegate, void* param) {
    if (!delegate) return false;
    
    bool result = true;
    for (const auto& callback_pair : delegate->callbacks) {
        try {
            if (callback_pair.first) {
                bool callback_result = callback_pair.first(param, callback_pair.second);
                result = result && callback_result;
            }
        } catch (...) {
            result = false;
        }
    }
    
    return result;
}

DUILIB_C_API int duilib_multicast_delegate_get_count(duilib_multicast_delegate_t delegate) {
    return delegate ? static_cast<int>(delegate->callbacks.size()) : 0;
}

DUILIB_C_API bool duilib_multicast_delegate_is_empty(duilib_multicast_delegate_t delegate) {
    return delegate ? delegate->callbacks.empty() : true;
}

//=============================================================================
// Event manager implementation
//=============================================================================

DUILIB_C_API duilib_event_manager_t duilib_event_manager_create(void) {
    return new(std::nothrow) duilib_event_manager();
}

DUILIB_C_API void duilib_event_manager_destroy(duilib_event_manager_t manager) {
    if (manager == g_global_event_manager) {
        g_global_event_manager = nullptr;
    }
    delete manager;
}

DUILIB_C_API duilib_result_t duilib_event_manager_subscribe(duilib_event_manager_t manager, duilib_event_type_t event_type, duilib_event_handler_t handler, void* user_data) {
    if (!manager || !handler) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        manager->event_handlers[event_type].emplace_back(handler, user_data);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR_OUT_OF_MEMORY;
    }
}

DUILIB_C_API duilib_result_t duilib_event_manager_unsubscribe(duilib_event_manager_t manager, duilib_event_type_t event_type, duilib_event_handler_t handler, void* user_data) {
    if (!manager || !handler) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        auto it = manager->event_handlers.find(event_type);
        if (it != manager->event_handlers.end()) {
            auto& handlers = it->second;
            
            handlers.erase(
                std::remove_if(handlers.begin(), handlers.end(),
                    [handler, user_data](const EventHandlerWrapper& wrapper) {
                        return wrapper.handler == handler && wrapper.user_data == user_data;
                    }),
                handlers.end()
            );
            
            if (handlers.empty()) {
                manager->event_handlers.erase(it);
            }
        }
        
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API bool duilib_event_manager_fire_event(duilib_event_manager_t manager, duilib_event_type_t event_type, const duilib_event_args_t* args) {
    if (!manager || !args) return false;
    
    try {
        auto it = manager->event_handlers.find(event_type);
        if (it == manager->event_handlers.end()) {
            return true; // No handlers, considered successful
        }
        
        bool all_handled = true;
        duilib_event_args_t mutable_args = *args; // Make a copy we can modify
        
        for (const auto& wrapper : it->second) {
            try {
                if (wrapper.handler) {
                    // Set user_data if not already set
                    if (!mutable_args.user_data) {
                        mutable_args.user_data = wrapper.user_data;
                    }
                    
                    bool handled = wrapper.handler(&mutable_args);
                    all_handled = all_handled && handled;
                    
                    // If the event was marked as handled, we can stop processing
                    if (mutable_args.handled) {
                        break;
                    }
                }
            } catch (...) {
                all_handled = false;
            }
        }
        
        return all_handled;
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_event_manager_t duilib_get_global_event_manager(void) {
    if (!g_global_event_manager) {
        g_global_event_manager = new(std::nothrow) duilib_event_manager();
    }
    return g_global_event_manager;
}