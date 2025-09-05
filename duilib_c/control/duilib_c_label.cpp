#include "duilib_c_label.h"
#include "../duilib_c_internal.h"

using namespace DuiLib;

//=============================================================================
// 标签控件包装结构
//=============================================================================

struct duilib_label {
    CLabelUI* label_ui;
};

//=============================================================================
// 标签控件基础API实现
//=============================================================================

DUILIB_C_API duilib_label_t duilib_label_create(void) {
    if (!g_initialized) return nullptr;
    
    try {
        duilib_label_t label = new duilib_label();
        label->label_ui = new CLabelUI();
        return label;
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API void duilib_label_destroy(duilib_label_t label) {
    if (!label) return;
    
    try {
        if (label->label_ui) {
            delete label->label_ui;
        }
        delete label;
    } catch (...) {
        // 忽略异常
    }
}

DUILIB_C_API duilib_control_t duilib_label_to_control(duilib_label_t label) {
    if (!label || !label->label_ui) return nullptr;
    
    duilib_control_t control = new duilib_control();
    control->control = static_cast<CControlUI*>(label->label_ui);
    return control;
}

DUILIB_C_API duilib_label_t duilib_control_to_label(duilib_control_t control) {
    if (!control || !control->control) return nullptr;
    
    CLabelUI* label_ui = dynamic_cast<CLabelUI*>(control->control);
    if (!label_ui) return nullptr;
    
    duilib_label_t label = new duilib_label();
    label->label_ui = label_ui;
    return label;
}

DUILIB_C_API bool duilib_label_is_valid(duilib_label_t label) {
    return label && label->label_ui;
}

//=============================================================================
// CLabelUI 核心方法实现
//=============================================================================

DUILIB_C_API const char* duilib_label_get_class(duilib_label_t label) {
    if (!duilib_label_is_valid(label)) return nullptr;
    
    try {
        CDuiString class_name = label->label_ui->GetClass();
        return to_cstring(class_name);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API void* duilib_label_get_interface(duilib_label_t label, const char* name) {
    if (!duilib_label_is_valid(label) || !name) return nullptr;
    
    try {
        CDuiString interface_name = from_cstring(name);
        return label->label_ui->GetInterface(interface_name);
    } catch (...) {
        return nullptr;
    }
}

//=============================================================================
// 标签文本管理实现
//=============================================================================

DUILIB_C_API const char* duilib_label_get_text(duilib_label_t label) {
    if (!duilib_label_is_valid(label)) return nullptr;
    
    try {
        CDuiString text = label->label_ui->GetText();
        return to_cstring(text);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_label_set_text(duilib_label_t label, const char* text) {
    if (!duilib_label_is_valid(label) || !text) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        CDuiString text_str = from_cstring(text);
        label->label_ui->SetText(text_str);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API uint32_t duilib_label_get_text_style(duilib_label_t label) {
    if (!duilib_label_is_valid(label)) return 0;
    
    try {
        return label->label_ui->GetTextStyle();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_label_set_text_style(duilib_label_t label, uint32_t style) {
    if (!duilib_label_is_valid(label)) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        label->label_ui->SetTextStyle(style);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API bool duilib_label_is_multiline(duilib_label_t label) {
    if (!duilib_label_is_valid(label)) return false;
    
    try {
        return label->label_ui->IsMultiLine();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_label_set_multiline(duilib_label_t label, bool multiline) {
    if (!duilib_label_is_valid(label)) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        label->label_ui->SetMultiLine(multiline);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

//=============================================================================
// 标签颜色管理实现
//=============================================================================

DUILIB_C_API duilib_color_t duilib_label_get_text_color(duilib_label_t label) {
    if (!duilib_label_is_valid(label)) return 0;
    
    try {
        return label->label_ui->GetTextColor();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_label_set_text_color(duilib_label_t label, duilib_color_t color) {
    if (!duilib_label_is_valid(label)) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        label->label_ui->SetTextColor(color);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_color_t duilib_label_get_disabled_text_color(duilib_label_t label) {
    if (!duilib_label_is_valid(label)) return 0;
    
    try {
        return label->label_ui->GetDisabledTextColor();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_label_set_disabled_text_color(duilib_label_t label, duilib_color_t color) {
    if (!duilib_label_is_valid(label)) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        label->label_ui->SetDisabledTextColor(color);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

//=============================================================================
// 标签字体管理实现
//=============================================================================

DUILIB_C_API int duilib_label_get_font(duilib_label_t label) {
    if (!duilib_label_is_valid(label)) return -1;
    
    try {
        return label->label_ui->GetFont();
    } catch (...) {
        return -1;
    }
}

DUILIB_C_API duilib_result_t duilib_label_set_font(duilib_label_t label, int font_index) {
    if (!duilib_label_is_valid(label)) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        label->label_ui->SetFont(font_index);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_rect_t duilib_label_get_text_padding(duilib_label_t label) {
    duilib_rect_t padding = {0, 0, 0, 0};
    
    if (!duilib_label_is_valid(label)) return padding;
    
    try {
        RECT rc = label->label_ui->GetTextPadding();
        padding.left = rc.left;
        padding.top = rc.top;
        padding.right = rc.right;
        padding.bottom = rc.bottom;
        return padding;
    } catch (...) {
        return padding;
    }
}

DUILIB_C_API duilib_result_t duilib_label_set_text_padding(duilib_label_t label, duilib_rect_t padding) {
    if (!duilib_label_is_valid(label)) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        RECT rc;
        rc.left = padding.left;
        rc.top = padding.top;
        rc.right = padding.right;
        rc.bottom = padding.bottom;
        label->label_ui->SetTextPadding(rc);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

//=============================================================================
// HTML文本支持实现
//=============================================================================

DUILIB_C_API bool duilib_label_is_show_html(duilib_label_t label) {
    if (!duilib_label_is_valid(label)) return false;
    
    try {
        return label->label_ui->IsShowHtml();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_label_set_show_html(duilib_label_t label, bool show_html) {
    if (!duilib_label_is_valid(label)) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        label->label_ui->SetShowHtml(show_html);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

//=============================================================================
// 标签尺寸和布局实现
//=============================================================================

DUILIB_C_API duilib_size_t duilib_label_estimate_size(duilib_label_t label, duilib_size_t available) {
    duilib_size_t size = {0, 0};
    
    if (!duilib_label_is_valid(label)) return size;
    
    try {
        SIZE sz_available;
        sz_available.cx = available.cx;
        sz_available.cy = available.cy;
        
        SIZE sz_result = label->label_ui->EstimateSize(sz_available);
        size.cx = sz_result.cx;
        size.cy = sz_result.cy;
        return size;
    } catch (...) {
        return size;
    }
}

DUILIB_C_API duilib_result_t duilib_label_do_event(duilib_label_t label, const duilib_ui_event_t* event) {
    if (!duilib_label_is_valid(label) || !event) return DUILIB_ERROR_INVALID_PARAMETER;
    
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
        
        label->label_ui->DoEvent(ui_event);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_label_set_attribute(duilib_label_t label, const char* name, const char* value) {
    if (!duilib_label_is_valid(label) || !name || !value) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        CDuiString attr_name = from_cstring(name);
        CDuiString attr_value = from_cstring(value);
        label->label_ui->SetAttribute(attr_name, attr_value);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_label_paint_text(duilib_label_t label, void* hdc) {
    if (!duilib_label_is_valid(label) || !hdc) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        label->label_ui->PaintText(static_cast<HDC>(hdc));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}