#ifndef __DUILIB_C_DELEGATE_H__
#define __DUILIB_C_DELEGATE_H__

#include "../core/duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// DuiLib委托系统API - 对应 UIDelegate.h
//=============================================================================

// 委托回调函数类型定义
typedef bool (*duilib_delegate_callback_t)(void* param, void* user_data);

//=============================================================================
// CDelegateBase - 委托基类
//=============================================================================

// CDelegateBase句柄
typedef struct duilib_delegatebase* duilib_delegatebase_t;

// 创建和销毁CDelegateBase
DUILIB_C_API void duilib_delegatebase_destroy(duilib_delegatebase_t delegate);

// CDelegateBase操作
DUILIB_C_API bool duilib_delegatebase_equals(duilib_delegatebase_t delegate, duilib_delegatebase_t other);
DUILIB_C_API bool duilib_delegatebase_invoke(duilib_delegatebase_t delegate, void* param);

//=============================================================================
// CDelegateStatic - 静态委托
//=============================================================================

// CDelegateStatic句柄
typedef struct duilib_delegatestatic* duilib_delegatestatic_t;

// 创建和销毁CDelegateStatic
DUILIB_C_API duilib_delegatestatic_t duilib_delegatestatic_create(duilib_delegate_callback_t callback, void* user_data);
DUILIB_C_API void duilib_delegatestatic_destroy(duilib_delegatestatic_t delegate);

// 转换到基类
DUILIB_C_API duilib_delegatebase_t duilib_delegatestatic_to_base(duilib_delegatestatic_t delegate);

//=============================================================================
// CEventSource - 事件源
//=============================================================================

// CEventSource句柄
typedef struct duilib_eventsource* duilib_eventsource_t;

// 创建和销毁CEventSource
DUILIB_C_API duilib_eventsource_t duilib_eventsource_create(void);
DUILIB_C_API void duilib_eventsource_destroy(duilib_eventsource_t event_source);

// CEventSource操作
DUILIB_C_API bool duilib_eventsource_has_handlers(duilib_eventsource_t event_source);
DUILIB_C_API bool duilib_eventsource_invoke(duilib_eventsource_t event_source, void* param);

// 添加和移除委托
DUILIB_C_API duilib_result_t duilib_eventsource_add_delegate(duilib_eventsource_t event_source, duilib_delegatebase_t delegate);
DUILIB_C_API duilib_result_t duilib_eventsource_add_callback(duilib_eventsource_t event_source, duilib_delegate_callback_t callback, void* user_data);
DUILIB_C_API duilib_result_t duilib_eventsource_remove_delegate(duilib_eventsource_t event_source, duilib_delegatebase_t delegate);
DUILIB_C_API duilib_result_t duilib_eventsource_remove_callback(duilib_eventsource_t event_source, duilib_delegate_callback_t callback, void* user_data);

//=============================================================================
// 委托辅助函数
//=============================================================================

// 创建简单的回调委托
DUILIB_C_API duilib_delegatebase_t duilib_make_delegate(duilib_delegate_callback_t callback, void* user_data);

// 委托链接管理
DUILIB_C_API duilib_delegatebase_t duilib_delegate_copy(duilib_delegatebase_t delegate);

//=============================================================================
// 多播委托 - 支持多个回调
//=============================================================================

// 多播委托句柄
typedef struct duilib_multicast_delegate* duilib_multicast_delegate_t;

// 创建和销毁多播委托
DUILIB_C_API duilib_multicast_delegate_t duilib_multicast_delegate_create(void);
DUILIB_C_API void duilib_multicast_delegate_destroy(duilib_multicast_delegate_t delegate);

// 多播委托操作
DUILIB_C_API duilib_result_t duilib_multicast_delegate_add(duilib_multicast_delegate_t delegate, duilib_delegate_callback_t callback, void* user_data);
DUILIB_C_API duilib_result_t duilib_multicast_delegate_remove(duilib_multicast_delegate_t delegate, duilib_delegate_callback_t callback, void* user_data);
DUILIB_C_API duilib_result_t duilib_multicast_delegate_clear(duilib_multicast_delegate_t delegate);
DUILIB_C_API bool duilib_multicast_delegate_invoke(duilib_multicast_delegate_t delegate, void* param);
DUILIB_C_API int duilib_multicast_delegate_get_count(duilib_multicast_delegate_t delegate);
DUILIB_C_API bool duilib_multicast_delegate_is_empty(duilib_multicast_delegate_t delegate);

//=============================================================================
// 事件参数结构定义
//=============================================================================

// 通用事件参数
typedef struct {
    void* sender;           // 事件发送者
    void* data;            // 事件数据
    int event_type;        // 事件类型
    bool handled;          // 是否已处理
    void* user_data;       // 用户数据
} duilib_event_args_t;

// 事件处理回调类型
typedef bool (*duilib_event_handler_t)(const duilib_event_args_t* args);

//=============================================================================
// 事件管理器 - 集中管理所有事件
//=============================================================================

// 事件管理器句柄
typedef struct duilib_event_manager* duilib_event_manager_t;

// 事件类型定义
typedef enum {
    DUILIB_EVENT_UNKNOWN = 0,
    DUILIB_EVENT_CLICK,
    DUILIB_EVENT_DBCLICK,
    DUILIB_EVENT_RETURN,
    DUILIB_EVENT_SCROLL,
    DUILIB_EVENT_PREDROPDOWN,
    DUILIB_EVENT_DROPDOWN,
    DUILIB_EVENT_SETFOCUS,
    DUILIB_EVENT_KILLFOCUS,
    DUILIB_EVENT_TIMER,
    DUILIB_EVENT_CARRET,
    DUILIB_EVENT_COPY,
    DUILIB_EVENT_CUT,
    DUILIB_EVENT_PASTE,
    DUILIB_EVENT_SELECTALL,
    DUILIB_EVENT_TEXTCHANGED,
    DUILIB_EVENT_HEADERCLICK,
    DUILIB_EVENT_ITEMSELECT,
    DUILIB_EVENT_ITEMACTIVATE,
    DUILIB_EVENT_TABSELECT,
    DUILIB_EVENT_MENU,
    DUILIB_EVENT_LINK,
    DUILIB_EVENT_ITEMCLICK,
    DUILIB_EVENT_ITEMDBCLICK,
    DUILIB_EVENT_SHOWACTIVEX,
    DUILIB_EVENT_ITEMCOLLAPSE,
    DUILIB_EVENT_ITEMEXPAND,
    DUILIB_EVENT_WINDOWINIT,
    DUILIB_EVENT_BUTTONDOWN,
    DUILIB_EVENT_MOUSEMOVE,
    DUILIB_EVENT_MOUSELEAVE,
    DUILIB_EVENT_TEXTROLLEND,
    DUILIB_EVENT_SCROLLWHEEL,
    DUILIB_EVENT_ITEMCHECKCLICK,
    DUILIB_EVENT_TREEITEMDBCLICK,
    DUILIB_EVENT_CHECKCLICK,
    DUILIB_EVENT_COLORCHANGED,
    DUILIB_EVENT_LISTITEMSELECT,
    DUILIB_EVENT_LISTITEMCLICK,
    DUILIB_EVENT_COMBOITEMSELECT,
    DUILIB_EVENT_LISTHEADERCLICK,
    DUILIB_EVENT_LISTITEMDBCLICK,
    DUILIB_EVENT_SHOWACTIVEX2,
    DUILIB_EVENT_ITEMRCLICK,
    DUILIB_EVENT_TABCLOSE,
    DUILIB_EVENT_TABMOVE,
    DUILIB_EVENT_VALUECHANGED,
    DUILIB_EVENT_VALUECHANGED_MOVE,
    DUILIB_EVENT_CUSTOM_START = 1000
} duilib_event_type_t;

// 创建和销毁事件管理器
DUILIB_C_API duilib_event_manager_t duilib_event_manager_create(void);
DUILIB_C_API void duilib_event_manager_destroy(duilib_event_manager_t manager);

// 事件处理器注册
DUILIB_C_API duilib_result_t duilib_event_manager_subscribe(duilib_event_manager_t manager, duilib_event_type_t event_type, duilib_event_handler_t handler, void* user_data);
DUILIB_C_API duilib_result_t duilib_event_manager_unsubscribe(duilib_event_manager_t manager, duilib_event_type_t event_type, duilib_event_handler_t handler, void* user_data);

// 事件触发
DUILIB_C_API bool duilib_event_manager_fire_event(duilib_event_manager_t manager, duilib_event_type_t event_type, const duilib_event_args_t* args);

// 获取全局事件管理器
DUILIB_C_API duilib_event_manager_t duilib_get_global_event_manager(void);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_DELEGATE_H__