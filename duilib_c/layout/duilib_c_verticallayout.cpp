#include "duilib_c_verticallayout.h"
#include "../duilib_c_internal.h"

using namespace DuiLib;

//=============================================================================
// 垂直布局控件包装结构
//=============================================================================

struct duilib_verticallayout {
    CVerticalLayoutUI* layout_ui;
};

//=============================================================================
// 垂直布局控件基础API实现
//=============================================================================

DUILIB_C_API duilib_verticallayout_t duilib_verticallayout_create(void) {
    if (!g_initialized) return nullptr;
    
    try {
        duilib_verticallayout_t layout = new duilib_verticallayout();
        layout->layout_ui = new CVerticalLayoutUI();
        return layout;
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API void duilib_verticallayout_destroy(duilib_verticallayout_t layout) {
    if (!layout) return;
    
    try {
        if (layout->layout_ui) {
            delete layout->layout_ui;
        }
        delete layout;
    } catch (...) {
        // 忽略异常
    }
}

DUILIB_C_API duilib_control_t duilib_verticallayout_to_control(duilib_verticallayout_t layout) {
    if (!layout || !layout->layout_ui) return nullptr;
    
    duilib_control_t control = new duilib_control();
    control->control = static_cast<CControlUI*>(layout->layout_ui);
    return control;
}

DUILIB_C_API duilib_verticallayout_t duilib_control_to_verticallayout(duilib_control_t control) {
    if (!control || !control->control) return nullptr;
    
    CVerticalLayoutUI* layout_ui = dynamic_cast<CVerticalLayoutUI*>(control->control);
    if (!layout_ui) return nullptr;
    
    duilib_verticallayout_t layout = new duilib_verticallayout();
    layout->layout_ui = layout_ui;
    return layout;
}

DUILIB_C_API duilib_container_t duilib_verticallayout_to_container(duilib_verticallayout_t layout) {
    if (!layout || !layout->layout_ui) return nullptr;
    
    duilib_container_t container = new duilib_container();
    container->container = static_cast<CContainerUI*>(layout->layout_ui);
    return container;
}

DUILIB_C_API duilib_verticallayout_t duilib_container_to_verticallayout(duilib_container_t container) {
    if (!container || !container->container) return nullptr;
    
    CVerticalLayoutUI* layout_ui = dynamic_cast<CVerticalLayoutUI*>(container->container);
    if (!layout_ui) return nullptr;
    
    duilib_verticallayout_t layout = new duilib_verticallayout();
    layout->layout_ui = layout_ui;
    return layout;
}

DUILIB_C_API bool duilib_verticallayout_is_valid(duilib_verticallayout_t layout) {
    return layout && layout->layout_ui;
}

//=============================================================================
// CVerticalLayoutUI 核心方法实现
//=============================================================================

DUILIB_C_API const char* duilib_verticallayout_get_class(duilib_verticallayout_t layout) {
    if (!duilib_verticallayout_is_valid(layout)) return nullptr;
    
    try {
        CDuiString class_name = layout->layout_ui->GetClass();
        return to_cstring(class_name);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API void* duilib_verticallayout_get_interface(duilib_verticallayout_t layout, const char* name) {
    if (!duilib_verticallayout_is_valid(layout) || !name) return nullptr;
    
    try {
        CDuiString interface_name = from_cstring(name);
        return layout->layout_ui->GetInterface(interface_name);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API uint32_t duilib_verticallayout_get_control_flags(duilib_verticallayout_t layout) {
    if (!duilib_verticallayout_is_valid(layout)) return 0;
    
    try {
        return layout->layout_ui->GetControlFlags();
    } catch (...) {
        return 0;
    }
}

//=============================================================================
// 垂直布局分隔器管理实现
//=============================================================================

DUILIB_C_API duilib_result_t duilib_verticallayout_set_sep_height(duilib_verticallayout_t layout, int height) {
    if (!duilib_verticallayout_is_valid(layout)) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        layout->layout_ui->SetSepHeight(height);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API int duilib_verticallayout_get_sep_height(duilib_verticallayout_t layout) {
    if (!duilib_verticallayout_is_valid(layout)) return 0;
    
    try {
        return layout->layout_ui->GetSepHeight();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_verticallayout_set_sep_imm_mode(duilib_verticallayout_t layout, bool immediate) {
    if (!duilib_verticallayout_is_valid(layout)) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        layout->layout_ui->SetSepImmMode(immediate);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API bool duilib_verticallayout_is_sep_imm_mode(duilib_verticallayout_t layout) {
    if (!duilib_verticallayout_is_valid(layout)) return false;
    
    try {
        return layout->layout_ui->IsSepImmMode();
    } catch (...) {
        return false;
    }
}

//=============================================================================
// 垂直布局属性和事件实现
//=============================================================================

DUILIB_C_API duilib_result_t duilib_verticallayout_set_attribute(duilib_verticallayout_t layout, const char* name, const char* value) {
    if (!duilib_verticallayout_is_valid(layout) || !name || !value) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        CDuiString attr_name = from_cstring(name);
        CDuiString attr_value = from_cstring(value);
        layout->layout_ui->SetAttribute(attr_name, attr_value);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_verticallayout_do_event(duilib_verticallayout_t layout, const duilib_ui_event_t* event) {
    if (!duilib_verticallayout_is_valid(layout) || !event) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        TEventUI ui_event;
        ui_event.Type = static_cast<UINT>(event->type);
        ui_event.pSender = reinterpret_cast<CControlUI*>(event->sender);
        ui_event.dwTimestamp = event->timestamp;
        ui_event.ptMouse.x = event->mouse_pos.x;
        ui_event.ptMouse.y = event->mouse_pos.y;
        ui_event.chKey = event->key;
        ui_event.wKeyState = event->key_state;
        ui_event.lParam = event->lparam;
        ui_event.wParam = event->wparam;
        
        layout->layout_ui->DoEvent(ui_event);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

//=============================================================================
// 垂直布局位置和绘制实现
//=============================================================================

DUILIB_C_API duilib_result_t duilib_verticallayout_set_pos(duilib_verticallayout_t layout, duilib_rect_t rect, bool need_invalidate) {
    if (!duilib_verticallayout_is_valid(layout)) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        RECT rc;
        rc.left = rect.left;
        rc.top = rect.top;
        rc.right = rect.right;
        rc.bottom = rect.bottom;
        layout->layout_ui->SetPos(rc, need_invalidate);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_verticallayout_do_post_paint(duilib_verticallayout_t layout, void* hdc, duilib_rect_t paint_rect) {
    if (!duilib_verticallayout_is_valid(layout) || !hdc) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        RECT rc;
        rc.left = paint_rect.left;
        rc.top = paint_rect.top;
        rc.right = paint_rect.right;
        rc.bottom = paint_rect.bottom;
        layout->layout_ui->DoPostPaint(static_cast<HDC>(hdc), rc);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_rect_t duilib_verticallayout_get_thumb_rect(duilib_verticallayout_t layout, bool use_new) {
    duilib_rect_t rect = {0, 0, 0, 0};
    
    if (!duilib_verticallayout_is_valid(layout)) return rect;
    
    try {
        RECT rc = layout->layout_ui->GetThumbRect(use_new);
        rect.left = rc.left;
        rect.top = rc.top;
        rect.right = rc.right;
        rect.bottom = rc.bottom;
        return rect;
    } catch (...) {
        return rect;
    }
}

//=============================================================================
// 继承自 CContainerUI 的方法实现 - 基础容器操作
//=============================================================================

DUILIB_C_API bool duilib_verticallayout_add(duilib_verticallayout_t layout, duilib_control_t control) {
    if (!duilib_verticallayout_is_valid(layout) || !control || !control->control) return false;
    
    try {
        return layout->layout_ui->Add(control->control);
    } catch (...) {
        return false;
    }
}

DUILIB_C_API bool duilib_verticallayout_add_at(duilib_verticallayout_t layout, duilib_control_t control, int index) {
    if (!duilib_verticallayout_is_valid(layout) || !control || !control->control) return false;
    
    try {
        return layout->layout_ui->AddAt(control->control, index);
    } catch (...) {
        return false;
    }
}

DUILIB_C_API bool duilib_verticallayout_remove(duilib_verticallayout_t layout, duilib_control_t control, bool do_not_destroy) {
    if (!duilib_verticallayout_is_valid(layout) || !control || !control->control) return false;
    
    try {
        return layout->layout_ui->Remove(control->control, do_not_destroy);
    } catch (...) {
        return false;
    }
}

DUILIB_C_API bool duilib_verticallayout_remove_at(duilib_verticallayout_t layout, int index, bool do_not_destroy) {
    if (!duilib_verticallayout_is_valid(layout)) return false;
    
    try {
        return layout->layout_ui->RemoveAt(index, do_not_destroy);
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_verticallayout_remove_all(duilib_verticallayout_t layout) {
    if (!duilib_verticallayout_is_valid(layout)) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        layout->layout_ui->RemoveAll();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API int duilib_verticallayout_get_count(duilib_verticallayout_t layout) {
    if (!duilib_verticallayout_is_valid(layout)) return 0;
    
    try {
        return layout->layout_ui->GetCount();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_control_t duilib_verticallayout_get_item_at(duilib_verticallayout_t layout, int index) {
    if (!duilib_verticallayout_is_valid(layout)) return nullptr;
    
    try {
        CControlUI* control_ui = layout->layout_ui->GetItemAt(index);
        if (!control_ui) return nullptr;
        
        duilib_control_t control = new duilib_control();
        control->control = control_ui;
        return control;
    } catch (...) {
        return nullptr;
    }
}