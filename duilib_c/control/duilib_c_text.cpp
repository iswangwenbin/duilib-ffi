#include "duilib_c_text.h"
#include "../duilib_c_internal.h"
#include "../../duilib/DuiLib/Control/UIText.h"
#include <cstring>

using namespace DuiLib;

// Text control wrapper structure
struct duilib_text_impl {
    CTextUI* text_ui;
    
    explicit duilib_text_impl(CTextUI* ui = nullptr) : text_ui(ui) {}
};

// Create and destroy functions
DUILIB_C_API duilib_text_t duilib_text_create() {
    try {
        CTextUI* text_ui = new CTextUI();
        if (!text_ui) return nullptr;
        
        duilib_text_impl* impl = new duilib_text_impl(text_ui);
        return reinterpret_cast<duilib_text_t>(impl);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_text_destroy(duilib_text_t text) {
    if (!text) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (impl->text_ui) {
            delete impl->text_ui;
        }
        delete impl;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

// Control UI interface functions
DUILIB_C_API duilib_control_t duilib_text_to_control(duilib_text_t text) {
    if (!text) return nullptr;
    
    duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
    return reinterpret_cast<duilib_control_t>(impl->text_ui);
}

DUILIB_C_API duilib_label_t duilib_text_to_label(duilib_text_t text) {
    if (!text) return nullptr;
    
    duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
    return reinterpret_cast<duilib_label_t>(impl->text_ui);
}

DUILIB_C_API duilib_text_t duilib_text_from_control(duilib_control_t control) {
    if (!control) return nullptr;
    
    CControlUI* ctrl = reinterpret_cast<CControlUI*>(control);
    CTextUI* text_ui = dynamic_cast<CTextUI*>(ctrl);
    if (!text_ui) return nullptr;
    
    try {
        duilib_text_impl* impl = new duilib_text_impl(text_ui);
        return reinterpret_cast<duilib_text_t>(impl);
    } catch (...) {
        return nullptr;
    }
}

// CTextUI specific methods
DUILIB_C_API const char* duilib_text_get_class(duilib_text_t text) {
    if (!text) return nullptr;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return nullptr;
        
        LPCTSTR class_name = impl->text_ui->GetClass();
        return duilib_wchar_to_utf8(class_name);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API unsigned int duilib_text_get_control_flags(duilib_text_t text) {
    if (!text) return 0;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return 0;
        
        return impl->text_ui->GetControlFlags();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API void* duilib_text_get_interface(duilib_text_t text, const char* name) {
    if (!text || !name) return nullptr;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return nullptr;
        
        wchar_t* wide_name = duilib_utf8_to_wchar(name);
        if (!wide_name) return nullptr;
        
        void* result = impl->text_ui->GetInterface(wide_name);
        delete[] wide_name;
        return result;
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API char* duilib_text_get_link_content(duilib_text_t text, int index) {
    if (!text || index < 0) return nullptr;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return nullptr;
        
        CDuiString* link_content = impl->text_ui->GetLinkContent(index);
        if (!link_content) return nullptr;
        
        return duilib_wchar_to_utf8(link_content->GetData());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_text_do_event(duilib_text_t text, duilib_event_t event) {
    if (!text) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return DUILIB_ERROR;
        
        TEventUI* event_ui = reinterpret_cast<TEventUI*>(event);
        if (!event_ui) return DUILIB_INVALID_PARAM;
        
        impl->text_ui->DoEvent(*event_ui);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API duilib_result_t duilib_text_paint_text(duilib_text_t text, void* hdc) {
    if (!text || !hdc) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return DUILIB_ERROR;
        
        impl->text_ui->PaintText(reinterpret_cast<HDC>(hdc));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

// Inherited CLabelUI methods
DUILIB_C_API duilib_result_t duilib_text_set_text_style(duilib_text_t text, unsigned int style) {
    if (!text) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return DUILIB_ERROR;
        
        impl->text_ui->SetTextStyle(style);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API unsigned int duilib_text_get_text_style(duilib_text_t text) {
    if (!text) return 0;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return 0;
        
        return impl->text_ui->GetTextStyle();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API bool duilib_text_is_multi_line(duilib_text_t text) {
    if (!text) return false;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return false;
        
        return impl->text_ui->IsMultiLine();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_text_set_multi_line(duilib_text_t text, bool multi_line) {
    if (!text) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return DUILIB_ERROR;
        
        impl->text_ui->SetMultiLine(multi_line);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API duilib_result_t duilib_text_set_text_color(duilib_text_t text, unsigned long color) {
    if (!text) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return DUILIB_ERROR;
        
        impl->text_ui->SetTextColor(color);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API unsigned long duilib_text_get_text_color(duilib_text_t text) {
    if (!text) return 0;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return 0;
        
        return impl->text_ui->GetTextColor();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_text_set_disabled_text_color(duilib_text_t text, unsigned long color) {
    if (!text) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return DUILIB_ERROR;
        
        impl->text_ui->SetDisabledTextColor(color);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API unsigned long duilib_text_get_disabled_text_color(duilib_text_t text) {
    if (!text) return 0;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return 0;
        
        return impl->text_ui->GetDisabledTextColor();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_text_set_font(duilib_text_t text, int index) {
    if (!text) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return DUILIB_ERROR;
        
        impl->text_ui->SetFont(index);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API int duilib_text_get_font(duilib_text_t text) {
    if (!text) return -1;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return -1;
        
        return impl->text_ui->GetFont();
    } catch (...) {
        return -1;
    }
}

DUILIB_C_API duilib_rect_t duilib_text_get_text_padding(duilib_text_t text) {
    duilib_rect_t result = {0, 0, 0, 0};
    if (!text) return result;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return result;
        
        RECT padding = impl->text_ui->GetTextPadding();
        result.left = padding.left;
        result.top = padding.top;
        result.right = padding.right;
        result.bottom = padding.bottom;
        return result;
    } catch (...) {
        return result;
    }
}

DUILIB_C_API duilib_result_t duilib_text_set_text_padding(duilib_text_t text, duilib_rect_t padding) {
    if (!text) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return DUILIB_ERROR;
        
        RECT rc = {padding.left, padding.top, padding.right, padding.bottom};
        impl->text_ui->SetTextPadding(rc);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API bool duilib_text_is_show_html(duilib_text_t text) {
    if (!text) return false;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return false;
        
        return impl->text_ui->IsShowHtml();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_text_set_show_html(duilib_text_t text, bool show_html) {
    if (!text) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return DUILIB_ERROR;
        
        impl->text_ui->SetShowHtml(show_html);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

// Inherited CControlUI methods
DUILIB_C_API char* duilib_text_get_name(duilib_text_t text) {
    if (!text) return nullptr;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return nullptr;
        
        CDuiString name = impl->text_ui->GetName();
        return duilib_wchar_to_utf8(name.GetData());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_text_set_name(duilib_text_t text, const char* name) {
    if (!text || !name) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return DUILIB_ERROR;
        
        wchar_t* wide_name = duilib_utf8_to_wchar(name);
        if (!wide_name) return DUILIB_ERROR;
        
        impl->text_ui->SetName(wide_name);
        delete[] wide_name;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API char* duilib_text_get_text(duilib_text_t text) {
    if (!text) return nullptr;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return nullptr;
        
        CDuiString text_content = impl->text_ui->GetText();
        return duilib_wchar_to_utf8(text_content.GetData());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_text_set_text(duilib_text_t text, const char* text_content) {
    if (!text) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return DUILIB_ERROR;
        
        if (!text_content) {
            impl->text_ui->SetText(L"");
            return DUILIB_OK;
        }
        
        wchar_t* wide_text = duilib_utf8_to_wchar(text_content);
        if (!wide_text) return DUILIB_ERROR;
        
        impl->text_ui->SetText(wide_text);
        delete[] wide_text;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API bool duilib_text_is_visible(duilib_text_t text) {
    if (!text) return false;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return false;
        
        return impl->text_ui->IsVisible();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_text_set_visible(duilib_text_t text, bool visible) {
    if (!text) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return DUILIB_ERROR;
        
        impl->text_ui->SetVisible(visible);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API bool duilib_text_is_enabled(duilib_text_t text) {
    if (!text) return false;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return false;
        
        return impl->text_ui->IsEnabled();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_text_set_enabled(duilib_text_t text, bool enabled) {
    if (!text) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return DUILIB_ERROR;
        
        impl->text_ui->SetEnabled(enabled);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API duilib_rect_t duilib_text_get_pos(duilib_text_t text) {
    duilib_rect_t result = {0, 0, 0, 0};
    if (!text) return result;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return result;
        
        const RECT& pos = impl->text_ui->GetPos();
        result.left = pos.left;
        result.top = pos.top;
        result.right = pos.right;
        result.bottom = pos.bottom;
        return result;
    } catch (...) {
        return result;
    }
}

DUILIB_C_API duilib_result_t duilib_text_set_pos(duilib_text_t text, duilib_rect_t pos, bool need_invalidate) {
    if (!text) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return DUILIB_ERROR;
        
        RECT rc = {pos.left, pos.top, pos.right, pos.bottom};
        impl->text_ui->SetPos(rc, need_invalidate);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API duilib_size_t duilib_text_estimate_size(duilib_text_t text, duilib_size_t available) {
    duilib_size_t result = {0, 0};
    if (!text) return result;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return result;
        
        SIZE sz = {available.cx, available.cy};
        SIZE estimated = impl->text_ui->EstimateSize(sz);
        result.cx = estimated.cx;
        result.cy = estimated.cy;
        return result;
    } catch (...) {
        return result;
    }
}

DUILIB_C_API char* duilib_text_get_attribute(duilib_text_t text, const char* name) {
    if (!text || !name) return nullptr;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return nullptr;
        
        wchar_t* wide_name = duilib_utf8_to_wchar(name);
        if (!wide_name) return nullptr;
        
        CDuiString attr = impl->text_ui->GetAttribute(wide_name);
        delete[] wide_name;
        
        return duilib_wchar_to_utf8(attr.GetData());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_text_set_attribute(duilib_text_t text, const char* name, const char* value) {
    if (!text || !name) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_text_impl* impl = reinterpret_cast<duilib_text_impl*>(text);
        if (!impl->text_ui) return DUILIB_ERROR;
        
        wchar_t* wide_name = duilib_utf8_to_wchar(name);
        if (!wide_name) return DUILIB_ERROR;
        
        wchar_t* wide_value = nullptr;
        if (value) {
            wide_value = duilib_utf8_to_wchar(value);
            if (!wide_value) {
                delete[] wide_name;
                return DUILIB_ERROR;
            }
        }
        
        impl->text_ui->SetAttribute(wide_name, wide_value);
        
        delete[] wide_name;
        if (wide_value) delete[] wide_value;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}