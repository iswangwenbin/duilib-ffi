#include "duilib_c_button.h"
#include "../duilib_c_internal.h"

using namespace DuiLib;

//=============================================================================
// 按钮控件包装结构
//=============================================================================

struct duilib_button {
    CButtonUI* button_ui;
};

//=============================================================================
// 按钮控件基础API实现
//=============================================================================

DUILIB_C_API duilib_button_t duilib_button_create(void) {
    if (!g_initialized) return nullptr;
    
    try {
        duilib_button_t button = new duilib_button();
        button->button_ui = new CButtonUI();
        return button;
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API void duilib_button_destroy(duilib_button_t button) {
    if (!button) return;
    
    try {
        if (button->button_ui) {
            delete button->button_ui;
        }
        delete button;
    } catch (...) {
        // 忽略异常
    }
}

DUILIB_C_API duilib_control_t duilib_button_to_control(duilib_button_t button) {
    if (!button || !button->button_ui) return nullptr;
    
    duilib_control_t control = new duilib_control();
    control->control = static_cast<CControlUI*>(button->button_ui);
    return control;
}

DUILIB_C_API duilib_button_t duilib_control_to_button(duilib_control_t control) {
    if (!control || !control->control) return nullptr;
    
    CButtonUI* button_ui = dynamic_cast<CButtonUI*>(control->control);
    if (!button_ui) return nullptr;
    
    duilib_button_t button = new duilib_button();
    button->button_ui = button_ui;
    return button;
}

DUILIB_C_API bool duilib_button_is_valid(duilib_button_t button) {
    return button && button->button_ui;
}

//=============================================================================
// CButtonUI 核心方法实现
//=============================================================================

DUILIB_C_API const char* duilib_button_get_class(duilib_button_t button) {
    if (!duilib_button_is_valid(button)) return nullptr;
    
    try {
        CDuiString class_name = button->button_ui->GetClass();
        return to_cstring(class_name);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API void* duilib_button_get_interface(duilib_button_t button, const char* name) {
    if (!duilib_button_is_valid(button) || !name) return nullptr;
    
    try {
        CDuiString interface_name = from_cstring(name);
        return button->button_ui->GetInterface(interface_name);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API uint32_t duilib_button_get_control_flags(duilib_button_t button) {
    if (!duilib_button_is_valid(button)) return 0;
    
    try {
        return button->button_ui->GetControlFlags();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API bool duilib_button_activate(duilib_button_t button) {
    if (!duilib_button_is_valid(button)) return false;
    
    try {
        return button->button_ui->Activate();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_button_set_enabled(duilib_button_t button, bool enabled) {
    if (!duilib_button_is_valid(button)) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        button->button_ui->SetEnabled(enabled);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_button_do_event(duilib_button_t button, const duilib_ui_event_t* event) {
    if (!duilib_button_is_valid(button) || !event) return DUILIB_ERROR_INVALID_PARAMETER;
    
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
        
        button->button_ui->DoEvent(ui_event);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

//=============================================================================
// 按钮图片状态管理实现
//=============================================================================

DUILIB_C_API const char* duilib_button_get_normal_image(duilib_button_t button) {
    if (!duilib_button_is_valid(button)) return nullptr;
    
    try {
        CDuiString image = button->button_ui->GetNormalImage();
        return to_cstring(image);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_button_set_normal_image(duilib_button_t button, const char* image) {
    if (!duilib_button_is_valid(button) || !image) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        CDuiString image_str = from_cstring(image);
        button->button_ui->SetNormalImage(image_str);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API const char* duilib_button_get_hot_image(duilib_button_t button) {
    if (!duilib_button_is_valid(button)) return nullptr;
    
    try {
        CDuiString image = button->button_ui->GetHotImage();
        return to_cstring(image);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_button_set_hot_image(duilib_button_t button, const char* image) {
    if (!duilib_button_is_valid(button) || !image) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        CDuiString image_str = from_cstring(image);
        button->button_ui->SetHotImage(image_str);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API const char* duilib_button_get_pushed_image(duilib_button_t button) {
    if (!duilib_button_is_valid(button)) return nullptr;
    
    try {
        CDuiString image = button->button_ui->GetPushedImage();
        return to_cstring(image);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_button_set_pushed_image(duilib_button_t button, const char* image) {
    if (!duilib_button_is_valid(button) || !image) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        CDuiString image_str = from_cstring(image);
        button->button_ui->SetPushedImage(image_str);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

//=============================================================================
// 按钮颜色状态管理实现
//=============================================================================

DUILIB_C_API duilib_result_t duilib_button_set_hot_bk_color(duilib_button_t button, duilib_color_t color) {
    if (!duilib_button_is_valid(button)) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        button->button_ui->SetHotBkColor(color);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_color_t duilib_button_get_hot_bk_color(duilib_button_t button) {
    if (!duilib_button_is_valid(button)) return 0;
    
    try {
        return button->button_ui->GetHotBkColor();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_button_set_hot_text_color(duilib_button_t button, duilib_color_t color) {
    if (!duilib_button_is_valid(button)) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        button->button_ui->SetHotTextColor(color);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_color_t duilib_button_get_hot_text_color(duilib_button_t button) {
    if (!duilib_button_is_valid(button)) return 0;
    
    try {
        return button->button_ui->GetHotTextColor();
    } catch (...) {
        return 0;
    }
}

//=============================================================================
// 按钮属性和绘制实现
//=============================================================================

DUILIB_C_API duilib_result_t duilib_button_set_attribute(duilib_button_t button, const char* name, const char* value) {
    if (!duilib_button_is_valid(button) || !name || !value) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        CDuiString attr_name = from_cstring(name);
        CDuiString attr_value = from_cstring(value);
        button->button_ui->SetAttribute(attr_name, attr_value);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_button_paint_text(duilib_button_t button, void* hdc) {
    if (!duilib_button_is_valid(button) || !hdc) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        button->button_ui->PaintText(static_cast<HDC>(hdc));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_button_paint_status_image(duilib_button_t button, void* hdc) {
    if (!duilib_button_is_valid(button) || !hdc) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        button->button_ui->PaintStatusImage(static_cast<HDC>(hdc));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

//=============================================================================
// 继承自 CLabelUI 的方法实现
//=============================================================================

DUILIB_C_API const char* duilib_button_get_text(duilib_button_t button) {
    if (!duilib_button_is_valid(button)) return nullptr;
    
    try {
        CDuiString text = button->button_ui->GetText();
        return to_cstring(text);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_button_set_text(duilib_button_t button, const char* text) {
    if (!duilib_button_is_valid(button) || !text) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        CDuiString text_str = from_cstring(text);
        button->button_ui->SetText(text_str);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}