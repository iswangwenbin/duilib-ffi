#include "duilib_c_option.h"
#include "../duilib_c_internal.h"
#include "../../duilib/DuiLib/Control/UIOption.h"
#include <cstring>

using namespace DuiLib;

// Option control wrapper structure
struct duilib_option_impl {
    COptionUI* option_ui;
    
    explicit duilib_option_impl(COptionUI* ui = nullptr) : option_ui(ui) {}
};

// Create and destroy functions
DUILIB_C_API duilib_option_t duilib_option_create() {
    try {
        COptionUI* option_ui = new COptionUI();
        if (!option_ui) return nullptr;
        
        duilib_option_impl* impl = new duilib_option_impl(option_ui);
        return reinterpret_cast<duilib_option_t>(impl);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_option_destroy(duilib_option_t option) {
    if (!option) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (impl->option_ui) {
            delete impl->option_ui;
        }
        delete impl;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

// Type conversion functions
DUILIB_C_API duilib_control_t duilib_option_to_control(duilib_option_t option) {
    if (!option) return nullptr;
    
    duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
    return reinterpret_cast<duilib_control_t>(impl->option_ui);
}

DUILIB_C_API duilib_button_t duilib_option_to_button(duilib_option_t option) {
    if (!option) return nullptr;
    
    duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
    return reinterpret_cast<duilib_button_t>(impl->option_ui);
}

DUILIB_C_API duilib_option_t duilib_option_from_control(duilib_control_t control) {
    if (!control) return nullptr;
    
    CControlUI* ctrl = reinterpret_cast<CControlUI*>(control);
    COptionUI* option_ui = dynamic_cast<COptionUI*>(ctrl);
    if (!option_ui) return nullptr;
    
    try {
        duilib_option_impl* impl = new duilib_option_impl(option_ui);
        return reinterpret_cast<duilib_option_t>(impl);
    } catch (...) {
        return nullptr;
    }
}

// COptionUI specific methods
DUILIB_C_API const char* duilib_option_get_class(duilib_option_t option) {
    if (!option) return nullptr;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return nullptr;
        
        LPCTSTR class_name = impl->option_ui->GetClass();
        return duilib_wchar_to_utf8(class_name);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API void* duilib_option_get_interface(duilib_option_t option, const char* name) {
    if (!option || !name) return nullptr;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return nullptr;
        
        wchar_t* wide_name = duilib_utf8_to_wchar(name);
        if (!wide_name) return nullptr;
        
        void* result = impl->option_ui->GetInterface(wide_name);
        delete[] wide_name;
        return result;
    } catch (...) {
        return nullptr;
    }
}

// Manager and lifecycle
DUILIB_C_API duilib_result_t duilib_option_set_manager(duilib_option_t option, void* manager, duilib_control_t parent, bool init) {
    if (!option) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return DUILIB_ERROR;
        
        CPaintManagerUI* paint_manager = reinterpret_cast<CPaintManagerUI*>(manager);
        CControlUI* parent_control = reinterpret_cast<CControlUI*>(parent);
        
        impl->option_ui->SetManager(paint_manager, parent_control, init);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

// Activation and state
DUILIB_C_API bool duilib_option_activate(duilib_option_t option) {
    if (!option) return false;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return false;
        
        return impl->option_ui->Activate();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_option_set_enabled(duilib_option_t option, bool enabled) {
    if (!option) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return DUILIB_ERROR;
        
        impl->option_ui->SetEnabled(enabled);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

// Selected state images
DUILIB_C_API char* duilib_option_get_selected_image(duilib_option_t option) {
    if (!option) return nullptr;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return nullptr;
        
        LPCTSTR selected_image = impl->option_ui->GetSelectedImage();
        return duilib_wchar_to_utf8(selected_image);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_option_set_selected_image(duilib_option_t option, const char* image) {
    if (!option) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return DUILIB_ERROR;
        
        if (!image) {
            impl->option_ui->SetSelectedImage(L"");
            return DUILIB_OK;
        }
        
        wchar_t* wide_image = duilib_utf8_to_wchar(image);
        if (!wide_image) return DUILIB_ERROR;
        
        impl->option_ui->SetSelectedImage(wide_image);
        delete[] wide_image;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API char* duilib_option_get_selected_hot_image(duilib_option_t option) {
    if (!option) return nullptr;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return nullptr;
        
        LPCTSTR selected_hot_image = impl->option_ui->GetSelectedHotImage();
        return duilib_wchar_to_utf8(selected_hot_image);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_option_set_selected_hot_image(duilib_option_t option, const char* image) {
    if (!option) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return DUILIB_ERROR;
        
        if (!image) {
            impl->option_ui->SetSelectedHotImage(L"");
            return DUILIB_OK;
        }
        
        wchar_t* wide_image = duilib_utf8_to_wchar(image);
        if (!wide_image) return DUILIB_ERROR;
        
        impl->option_ui->SetSelectedHotImage(wide_image);
        delete[] wide_image;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

// Selected state colors
DUILIB_C_API duilib_result_t duilib_option_set_selected_text_color(duilib_option_t option, unsigned long color) {
    if (!option) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return DUILIB_ERROR;
        
        impl->option_ui->SetSelectedTextColor(color);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API unsigned long duilib_option_get_selected_text_color(duilib_option_t option) {
    if (!option) return 0;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return 0;
        
        return impl->option_ui->GetSelectedTextColor();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_option_set_selected_bk_color(duilib_option_t option, unsigned long color) {
    if (!option) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return DUILIB_ERROR;
        
        impl->option_ui->SetSelectedBkColor(color);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API unsigned long duilib_option_get_selected_bk_color(duilib_option_t option) {
    if (!option) return 0;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return 0;
        
        return impl->option_ui->GetSelectedBkColor();
    } catch (...) {
        return 0;
    }
}

// Foreground image
DUILIB_C_API char* duilib_option_get_fore_image(duilib_option_t option) {
    if (!option) return nullptr;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return nullptr;
        
        LPCTSTR fore_image = impl->option_ui->GetForeImage();
        return duilib_wchar_to_utf8(fore_image);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_option_set_fore_image(duilib_option_t option, const char* image) {
    if (!option) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return DUILIB_ERROR;
        
        if (!image) {
            impl->option_ui->SetForeImage(L"");
            return DUILIB_OK;
        }
        
        wchar_t* wide_image = duilib_utf8_to_wchar(image);
        if (!wide_image) return DUILIB_ERROR;
        
        impl->option_ui->SetForeImage(wide_image);
        delete[] wide_image;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

// Group management
DUILIB_C_API char* duilib_option_get_group(duilib_option_t option) {
    if (!option) return nullptr;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return nullptr;
        
        LPCTSTR group_name = impl->option_ui->GetGroup();
        return duilib_wchar_to_utf8(group_name);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_option_set_group(duilib_option_t option, const char* group_name) {
    if (!option) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return DUILIB_ERROR;
        
        if (!group_name) {
            impl->option_ui->SetGroup(nullptr);
            return DUILIB_OK;
        }
        
        wchar_t* wide_group = duilib_utf8_to_wchar(group_name);
        if (!wide_group) return DUILIB_ERROR;
        
        impl->option_ui->SetGroup(wide_group);
        delete[] wide_group;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

// Selection state
DUILIB_C_API bool duilib_option_is_selected(duilib_option_t option) {
    if (!option) return false;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return false;
        
        return impl->option_ui->IsSelected();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_option_set_selected(duilib_option_t option, bool selected, bool trigger_event) {
    if (!option) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return DUILIB_ERROR;
        
        impl->option_ui->Selected(selected, trigger_event);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

// Layout and rendering
DUILIB_C_API duilib_size_t duilib_option_estimate_size(duilib_option_t option, duilib_size_t available) {
    duilib_size_t result = {0, 0};
    if (!option) return result;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return result;
        
        SIZE sz = {available.cx, available.cy};
        SIZE estimated = impl->option_ui->EstimateSize(sz);
        result.cx = estimated.cx;
        result.cy = estimated.cy;
        return result;
    } catch (...) {
        return result;
    }
}

DUILIB_C_API duilib_result_t duilib_option_paint_status_image(duilib_option_t option, void* hdc) {
    if (!option || !hdc) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return DUILIB_ERROR;
        
        impl->option_ui->PaintStatusImage(reinterpret_cast<HDC>(hdc));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API duilib_result_t duilib_option_paint_text(duilib_option_t option, void* hdc) {
    if (!option || !hdc) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return DUILIB_ERROR;
        
        impl->option_ui->PaintText(reinterpret_cast<HDC>(hdc));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

// Inherited CControlUI methods
DUILIB_C_API char* duilib_option_get_name(duilib_option_t option) {
    if (!option) return nullptr;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return nullptr;
        
        CDuiString name = impl->option_ui->GetName();
        return duilib_wchar_to_utf8(name.GetData());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_option_set_name(duilib_option_t option, const char* name) {
    if (!option || !name) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return DUILIB_ERROR;
        
        wchar_t* wide_name = duilib_utf8_to_wchar(name);
        if (!wide_name) return DUILIB_ERROR;
        
        impl->option_ui->SetName(wide_name);
        delete[] wide_name;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API char* duilib_option_get_text(duilib_option_t option) {
    if (!option) return nullptr;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return nullptr;
        
        CDuiString text = impl->option_ui->GetText();
        return duilib_wchar_to_utf8(text.GetData());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_option_set_text(duilib_option_t option, const char* text_content) {
    if (!option) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return DUILIB_ERROR;
        
        if (!text_content) {
            impl->option_ui->SetText(L"");
            return DUILIB_OK;
        }
        
        wchar_t* wide_text = duilib_utf8_to_wchar(text_content);
        if (!wide_text) return DUILIB_ERROR;
        
        impl->option_ui->SetText(wide_text);
        delete[] wide_text;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API bool duilib_option_is_visible(duilib_option_t option) {
    if (!option) return false;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return false;
        
        return impl->option_ui->IsVisible();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_option_set_visible(duilib_option_t option, bool visible) {
    if (!option) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return DUILIB_ERROR;
        
        impl->option_ui->SetVisible(visible);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API bool duilib_option_is_enabled(duilib_option_t option) {
    if (!option) return false;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return false;
        
        return impl->option_ui->IsEnabled();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_rect_t duilib_option_get_pos(duilib_option_t option) {
    duilib_rect_t result = {0, 0, 0, 0};
    if (!option) return result;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return result;
        
        const RECT& pos = impl->option_ui->GetPos();
        result.left = pos.left;
        result.top = pos.top;
        result.right = pos.right;
        result.bottom = pos.bottom;
        return result;
    } catch (...) {
        return result;
    }
}

DUILIB_C_API duilib_result_t duilib_option_set_pos(duilib_option_t option, duilib_rect_t pos, bool need_invalidate) {
    if (!option) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return DUILIB_ERROR;
        
        RECT rc = {pos.left, pos.top, pos.right, pos.bottom};
        impl->option_ui->SetPos(rc, need_invalidate);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API char* duilib_option_get_attribute(duilib_option_t option, const char* name) {
    if (!option || !name) return nullptr;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return nullptr;
        
        wchar_t* wide_name = duilib_utf8_to_wchar(name);
        if (!wide_name) return nullptr;
        
        CDuiString attr = impl->option_ui->GetAttribute(wide_name);
        delete[] wide_name;
        
        return duilib_wchar_to_utf8(attr.GetData());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_option_set_attribute(duilib_option_t option, const char* name, const char* value) {
    if (!option || !name) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_option_impl* impl = reinterpret_cast<duilib_option_impl*>(option);
        if (!impl->option_ui) return DUILIB_ERROR;
        
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
        
        impl->option_ui->SetAttribute(wide_name, wide_value);
        
        delete[] wide_name;
        if (wide_value) delete[] wide_value;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}