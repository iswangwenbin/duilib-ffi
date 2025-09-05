#include "../duilib_c_internal.h"

//=============================================================================
// 外部定义的全局变量（来自 duilib_c_core.cpp）
//=============================================================================
extern bool g_initialized;
extern std::map<duilib_manager_t, CPaintManagerUI*> g_managers;
extern duilib_event_callback_t g_event_callback;
extern CNotifyHandler g_notify_handler;

// 辅助函数声明（来自 duilib_c_core.cpp）
extern const char* to_cstring(const CDuiString& str);
extern CDuiString from_cstring(const char* str);

//=============================================================================
// 核心管理器API实现
//=============================================================================

DUILIB_C_API duilib_manager_t duilib_paint_manager_init(HWND hwnd, const char* name) {
    if (!g_initialized || !hwnd) {
        return nullptr;
    }

    try {
        auto* manager_wrapper = new duilib_manager;
        manager_wrapper->paint_manager = new CPaintManagerUI();
        manager_wrapper->hwnd = hwnd;
        manager_wrapper->name = name ? name : "";

        manager_wrapper->paint_manager->Init(hwnd, name ? from_cstring(name) : CDuiString());
        manager_wrapper->paint_manager->AddNotifier(&g_notify_handler);

        g_managers[manager_wrapper] = manager_wrapper->paint_manager;
        
        return manager_wrapper;
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API void duilib_destroy_manager(duilib_manager_t manager) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return;
    }

    try {
        manager->paint_manager->RemoveNotifier(&g_notify_handler);
        delete manager->paint_manager;
        g_managers.erase(manager);
        delete manager;
    } catch (...) {
        // 忽略清理异常
    }
}

DUILIB_C_API duilib_result_t duilib_load_layout(duilib_manager_t manager, const char* xml_file) {
    if (!manager || !xml_file || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }

    try {
        CDialogBuilder builder;
        CDuiString xml_str = from_cstring(xml_file);
        CControlUI* pRoot = builder.Create(xml_str.GetData(), (UINT)0, nullptr, manager->paint_manager);
        
        if (!pRoot) {
            return DUILIB_ERROR_NOT_FOUND;
        }

        manager->paint_manager->AttachDialog(pRoot);
        manager->paint_manager->AddNotifier(&g_notify_handler);
        
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_load_layout_from_string(duilib_manager_t manager, const char* xml_string) {
    if (!manager || !xml_string || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }

    try {
        CDialogBuilder builder;
        CControlUI* pRoot = builder.Create((LPCTSTR)xml_string, (UINT)0, nullptr, manager->paint_manager);
        
        if (!pRoot) {
            return DUILIB_ERROR_NOT_FOUND;
        }

        manager->paint_manager->AttachDialog(pRoot);
        manager->paint_manager->AddNotifier(&g_notify_handler);
        
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_control_t duilib_get_root(duilib_manager_t manager) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return nullptr;
    }

    try {
        CControlUI* root = manager->paint_manager->GetRoot();
        if (!root) return nullptr;

        return reinterpret_cast<duilib_control_t>(new duilib_control{root});
    } catch (...) {
        return nullptr;
    }
}

//=============================================================================
// 控件查找API实现
//=============================================================================

DUILIB_C_API duilib_control_t duilib_find_control(duilib_manager_t manager, const char* name) {
    if (!manager || !name || g_managers.find(manager) == g_managers.end()) {
        return nullptr;
    }

    try {
        CControlUI* control = manager->paint_manager->FindControl(from_cstring(name));
        if (!control) return nullptr;

        return reinterpret_cast<duilib_control_t>(new duilib_control{control});
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_control_t duilib_find_control_by_class(duilib_manager_t manager, const char* class_name) {
    if (!manager || !class_name || g_managers.find(manager) == g_managers.end()) {
        return nullptr;
    }

    try {
        CControlUI* root = manager->paint_manager->GetRoot();
        if (!root) return nullptr;

        CControlUI* control = manager->paint_manager->FindSubControlByClass(root, from_cstring(class_name));
        if (!control) return nullptr;

        return reinterpret_cast<duilib_control_t>(new duilib_control{control});
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_control_t duilib_find_control_at_point(duilib_manager_t manager, int x, int y) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return nullptr;
    }

    try {
        POINT pt = {x, y};
        CControlUI* control = manager->paint_manager->FindControl(pt);
        if (!control) return nullptr;

        return reinterpret_cast<duilib_control_t>(new duilib_control{control});
    } catch (...) {
        return nullptr;
    }
}

//=============================================================================
// 事件处理API实现
//=============================================================================

DUILIB_C_API duilib_result_t duilib_set_event_callback(duilib_manager_t manager, duilib_event_callback_t callback) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }

    g_event_callback = callback;
    return DUILIB_OK;
}

DUILIB_C_API duilib_result_t duilib_send_notify(duilib_manager_t manager, duilib_control_t control, const char* message) {
    if (!manager || !control || !message || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }

    try {
        TNotifyUI msg;
        msg.pSender = control->control;
        msg.sType = from_cstring(message);
        msg.ptMouse = {0, 0};
        msg.dwTimestamp = ::GetTickCount();
        msg.wParam = 0;
        msg.lParam = 0;
        manager->paint_manager->SendNotify(msg);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

//=============================================================================
// CPaintManagerUI 扩展方法实现
//=============================================================================

// 基础属性访问
DUILIB_C_API const char* duilib_paint_manager_get_name(duilib_manager_t manager) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return nullptr;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        return to_cstring(paint_manager->GetName());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API void* duilib_paint_manager_get_paint_dc(duilib_manager_t manager) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return nullptr;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        return paint_manager->GetPaintDC();
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API void* duilib_paint_manager_get_paint_window(duilib_manager_t manager) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return nullptr;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        return paint_manager->GetPaintWindow();
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_size_t duilib_paint_manager_get_client_size(duilib_manager_t manager) {
    duilib_size_t result = {0, 0};
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return result;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        SIZE size = paint_manager->GetClientSize();
        result.width = size.cx;
        result.height = size.cy;
        return result;
    } catch (...) {
        return result;
    }
}

DUILIB_C_API duilib_size_t duilib_paint_manager_get_init_size(duilib_manager_t manager) {
    duilib_size_t result = {0, 0};
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return result;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        SIZE size = paint_manager->GetInitSize();
        result.width = size.cx;
        result.height = size.cy;
        return result;
    } catch (...) {
        return result;
    }
}

DUILIB_C_API duilib_result_t duilib_paint_manager_set_init_size(duilib_manager_t manager, int width, int height) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        paint_manager->SetInitSize(width, height);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

// 焦点管理
DUILIB_C_API duilib_control_t duilib_paint_manager_get_focus(duilib_manager_t manager) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return nullptr;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        CControlUI* control = paint_manager->GetFocus();
        if (!control) return nullptr;
        
        return new duilib_control{control};
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_paint_manager_set_focus(duilib_manager_t manager, duilib_control_t control, bool focus_wnd) {
    if (!manager || !control || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        paint_manager->SetFocus(control->control, focus_wnd);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

// 定时器管理
DUILIB_C_API bool duilib_paint_manager_set_timer(duilib_manager_t manager, duilib_control_t control, uint32_t timer_id, uint32_t elapse) {
    if (!manager || !control || g_managers.find(manager) == g_managers.end()) {
        return false;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        return paint_manager->SetTimer(control->control, timer_id, elapse);
    } catch (...) {
        return false;
    }
}

DUILIB_C_API bool duilib_paint_manager_kill_timer(duilib_manager_t manager, duilib_control_t control, uint32_t timer_id) {
    if (!manager || !control || g_managers.find(manager) == g_managers.end()) {
        return false;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        return paint_manager->KillTimer(control->control, timer_id);
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_paint_manager_kill_all_timers(duilib_manager_t manager, duilib_control_t control) {
    if (!manager || !control || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        paint_manager->KillTimer(control->control);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

// 鼠标捕获
DUILIB_C_API duilib_result_t duilib_paint_manager_set_capture(duilib_manager_t manager) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        paint_manager->SetCapture();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_paint_manager_release_capture(duilib_manager_t manager) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        paint_manager->ReleaseCapture();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API bool duilib_paint_manager_is_captured(duilib_manager_t manager) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return false;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        return paint_manager->IsCaptured();
    } catch (...) {
        return false;
    }
}

// 窗口几何属性
DUILIB_C_API duilib_point_t duilib_paint_manager_get_mouse_pos(duilib_manager_t manager) {
    duilib_point_t result = {0, 0};
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return result;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        POINT pt = paint_manager->GetMousePos();
        result.x = pt.x;
        result.y = pt.y;
        return result;
    } catch (...) {
        return result;
    }
}

DUILIB_C_API duilib_rect_t duilib_paint_manager_get_size_box(duilib_manager_t manager) {
    duilib_rect_t result = {0, 0, 0, 0};
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return result;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        RECT rc = paint_manager->GetSizeBox();
        result.left = rc.left;
        result.top = rc.top;
        result.right = rc.right;
        result.bottom = rc.bottom;
        return result;
    } catch (...) {
        return result;
    }
}

DUILIB_C_API duilib_result_t duilib_paint_manager_set_size_box(duilib_manager_t manager, duilib_rect_t rect) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        RECT rc = {rect.left, rect.top, rect.right, rect.bottom};
        paint_manager->SetSizeBox(rc);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_rect_t duilib_paint_manager_get_caption_rect(duilib_manager_t manager) {
    duilib_rect_t result = {0, 0, 0, 0};
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return result;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        RECT rc = paint_manager->GetCaptionRect();
        result.left = rc.left;
        result.top = rc.top;
        result.right = rc.right;
        result.bottom = rc.bottom;
        return result;
    } catch (...) {
        return result;
    }
}

DUILIB_C_API duilib_result_t duilib_paint_manager_set_caption_rect(duilib_manager_t manager, duilib_rect_t rect) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        RECT rc = {rect.left, rect.top, rect.right, rect.bottom};
        paint_manager->SetCaptionRect(rc);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_size_t duilib_paint_manager_get_round_corner(duilib_manager_t manager) {
    duilib_size_t result = {0, 0};
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return result;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        SIZE size = paint_manager->GetRoundCorner();
        result.width = size.cx;
        result.height = size.cy;
        return result;
    } catch (...) {
        return result;
    }
}

DUILIB_C_API duilib_result_t duilib_paint_manager_set_round_corner(duilib_manager_t manager, int cx, int cy) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        paint_manager->SetRoundCorner(cx, cy);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_size_t duilib_paint_manager_get_min_info(duilib_manager_t manager) {
    duilib_size_t result = {0, 0};
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return result;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        SIZE size = paint_manager->GetMinInfo();
        result.width = size.cx;
        result.height = size.cy;
        return result;
    } catch (...) {
        return result;
    }
}

DUILIB_C_API duilib_result_t duilib_paint_manager_set_min_info(duilib_manager_t manager, int cx, int cy) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        paint_manager->SetMinInfo(cx, cy);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_size_t duilib_paint_manager_get_max_info(duilib_manager_t manager) {
    duilib_size_t result = {0, 0};
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return result;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        SIZE size = paint_manager->GetMaxInfo();
        result.width = size.cx;
        result.height = size.cy;
        return result;
    } catch (...) {
        return result;
    }
}

DUILIB_C_API duilib_result_t duilib_paint_manager_set_max_info(duilib_manager_t manager, int cx, int cy) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        paint_manager->SetMaxInfo(cx, cy);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

// 更新和绘制管理
DUILIB_C_API bool duilib_paint_manager_is_update_needed(duilib_manager_t manager) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return false;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        return paint_manager->IsUpdateNeeded();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_paint_manager_need_update(duilib_manager_t manager) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        paint_manager->NeedUpdate();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_paint_manager_invalidate(duilib_manager_t manager) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        paint_manager->Invalidate();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_paint_manager_invalidate_rect(duilib_manager_t manager, duilib_rect_t rect) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        RECT rc = {rect.left, rect.top, rect.right, rect.bottom};
        paint_manager->Invalidate(rc);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

// 显示选项
DUILIB_C_API bool duilib_paint_manager_is_show_update_rect(duilib_manager_t manager) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return false;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        return paint_manager->IsShowUpdateRect();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_paint_manager_set_show_update_rect(duilib_manager_t manager, bool show) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        paint_manager->SetShowUpdateRect(show);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

// 激活和透明度管理
DUILIB_C_API bool duilib_paint_manager_is_no_activate(duilib_manager_t manager) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return false;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        return paint_manager->IsNoActivate();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_paint_manager_set_no_activate(duilib_manager_t manager, bool no_activate) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        paint_manager->SetNoActivate(no_activate);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API uint8_t duilib_paint_manager_get_opacity(duilib_manager_t manager) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return 255;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        return paint_manager->GetOpacity();
    } catch (...) {
        return 255;
    }
}

DUILIB_C_API duilib_result_t duilib_paint_manager_set_opacity(duilib_manager_t manager, uint8_t opacity) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        paint_manager->SetOpacity(opacity);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

// 分层窗口功能
DUILIB_C_API bool duilib_paint_manager_is_layered(duilib_manager_t manager) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return false;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        return paint_manager->IsLayered();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_paint_manager_set_layered(duilib_manager_t manager, bool layered) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        paint_manager->SetLayered(layered);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_rect_t duilib_paint_manager_get_layered_inset(duilib_manager_t manager) {
    duilib_rect_t result = {0, 0, 0, 0};
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return result;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        RECT rc = paint_manager->GetLayeredInset();
        result.left = rc.left;
        result.top = rc.top;
        result.right = rc.right;
        result.bottom = rc.bottom;
        return result;
    } catch (...) {
        return result;
    }
}

DUILIB_C_API duilib_result_t duilib_paint_manager_set_layered_inset(duilib_manager_t manager, duilib_rect_t inset) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        RECT rc = {inset.left, inset.top, inset.right, inset.bottom};
        paint_manager->SetLayeredInset(rc);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API uint8_t duilib_paint_manager_get_layered_opacity(duilib_manager_t manager) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return 255;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        return paint_manager->GetLayeredOpacity();
    } catch (...) {
        return 255;
    }
}

DUILIB_C_API duilib_result_t duilib_paint_manager_set_layered_opacity(duilib_manager_t manager, uint8_t opacity) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        paint_manager->SetLayeredOpacity(opacity);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API const char* duilib_paint_manager_get_layered_image(duilib_manager_t manager) {
    if (!manager || g_managers.find(manager) == g_managers.end()) {
        return nullptr;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        return to_cstring(paint_manager->GetLayeredImage());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_paint_manager_set_layered_image(duilib_manager_t manager, const char* image) {
    if (!manager || !image || g_managers.find(manager) == g_managers.end()) {
        return DUILIB_ERROR_INVALID_PARAM;
    }
    
    try {
        CPaintManagerUI* paint_manager = g_managers[manager];
        paint_manager->SetLayeredImage(from_cstring(image));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}