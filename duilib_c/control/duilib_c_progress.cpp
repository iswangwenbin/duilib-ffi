#include "duilib_c_progress.h"
#include "../duilib_c_internal.h"
#include "../../duilib/DuiLib/Control/UIProgress.h"
#include <cstring>

using namespace DuiLib;

// Progress control wrapper structure
struct duilib_progress_impl {
    CProgressUI* progress_ui;
    
    explicit duilib_progress_impl(CProgressUI* ui = nullptr) : progress_ui(ui) {}
};

// Create and destroy functions
DUILIB_C_API duilib_progress_t duilib_progress_create() {
    try {
        CProgressUI* progress_ui = new CProgressUI();
        if (!progress_ui) return nullptr;
        
        duilib_progress_impl* impl = new duilib_progress_impl(progress_ui);
        return reinterpret_cast<duilib_progress_t>(impl);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_progress_destroy(duilib_progress_t progress) {
    if (!progress) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (impl->progress_ui) {
            delete impl->progress_ui;
        }
        delete impl;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

// Type conversion functions
DUILIB_C_API duilib_control_t duilib_progress_to_control(duilib_progress_t progress) {
    if (!progress) return nullptr;
    
    duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
    return reinterpret_cast<duilib_control_t>(impl->progress_ui);
}

DUILIB_C_API duilib_label_t duilib_progress_to_label(duilib_progress_t progress) {
    if (!progress) return nullptr;
    
    duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
    return reinterpret_cast<duilib_label_t>(impl->progress_ui);
}

DUILIB_C_API duilib_progress_t duilib_progress_from_control(duilib_control_t control) {
    if (!control) return nullptr;
    
    CControlUI* ctrl = reinterpret_cast<CControlUI*>(control);
    CProgressUI* progress_ui = dynamic_cast<CProgressUI*>(ctrl);
    if (!progress_ui) return nullptr;
    
    try {
        duilib_progress_impl* impl = new duilib_progress_impl(progress_ui);
        return reinterpret_cast<duilib_progress_t>(impl);
    } catch (...) {
        return nullptr;
    }
}

// CProgressUI specific methods
DUILIB_C_API const char* duilib_progress_get_class(duilib_progress_t progress) {
    if (!progress) return nullptr;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return nullptr;
        
        LPCTSTR class_name = impl->progress_ui->GetClass();
        return duilib_wchar_to_utf8(class_name);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API void* duilib_progress_get_interface(duilib_progress_t progress, const char* name) {
    if (!progress || !name) return nullptr;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return nullptr;
        
        wchar_t* wide_name = duilib_utf8_to_wchar(name);
        if (!wide_name) return nullptr;
        
        void* result = impl->progress_ui->GetInterface(wide_name);
        delete[] wide_name;
        return result;
    } catch (...) {
        return nullptr;
    }
}

// Orientation methods
DUILIB_C_API bool duilib_progress_is_horizontal(duilib_progress_t progress) {
    if (!progress) return true;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return true;
        
        return impl->progress_ui->IsHorizontal();
    } catch (...) {
        return true;
    }
}

DUILIB_C_API duilib_result_t duilib_progress_set_horizontal(duilib_progress_t progress, bool horizontal) {
    if (!progress) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return DUILIB_ERROR;
        
        impl->progress_ui->SetHorizontal(horizontal);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

// Value range methods
DUILIB_C_API int duilib_progress_get_min_value(duilib_progress_t progress) {
    if (!progress) return 0;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return 0;
        
        return impl->progress_ui->GetMinValue();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_progress_set_min_value(duilib_progress_t progress, int min_value) {
    if (!progress) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return DUILIB_ERROR;
        
        impl->progress_ui->SetMinValue(min_value);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API int duilib_progress_get_max_value(duilib_progress_t progress) {
    if (!progress) return 100;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return 100;
        
        return impl->progress_ui->GetMaxValue();
    } catch (...) {
        return 100;
    }
}

DUILIB_C_API duilib_result_t duilib_progress_set_max_value(duilib_progress_t progress, int max_value) {
    if (!progress) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return DUILIB_ERROR;
        
        impl->progress_ui->SetMaxValue(max_value);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

// Current value methods
DUILIB_C_API int duilib_progress_get_value(duilib_progress_t progress) {
    if (!progress) return 0;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return 0;
        
        return impl->progress_ui->GetValue();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_progress_set_value(duilib_progress_t progress, int value) {
    if (!progress) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return DUILIB_ERROR;
        
        impl->progress_ui->SetValue(value);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

// Foreground image methods
DUILIB_C_API char* duilib_progress_get_fore_image(duilib_progress_t progress) {
    if (!progress) return nullptr;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return nullptr;
        
        LPCTSTR fore_image = impl->progress_ui->GetForeImage();
        return duilib_wchar_to_utf8(fore_image);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_progress_set_fore_image(duilib_progress_t progress, const char* image) {
    if (!progress) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return DUILIB_ERROR;
        
        if (!image) {
            impl->progress_ui->SetForeImage(L"");
            return DUILIB_OK;
        }
        
        wchar_t* wide_image = duilib_utf8_to_wchar(image);
        if (!wide_image) return DUILIB_ERROR;
        
        impl->progress_ui->SetForeImage(wide_image);
        delete[] wide_image;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

// Painting methods
DUILIB_C_API duilib_result_t duilib_progress_paint_status_image(duilib_progress_t progress, void* hdc) {
    if (!progress || !hdc) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return DUILIB_ERROR;
        
        impl->progress_ui->PaintStatusImage(reinterpret_cast<HDC>(hdc));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

// Inherited CControlUI methods
DUILIB_C_API char* duilib_progress_get_name(duilib_progress_t progress) {
    if (!progress) return nullptr;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return nullptr;
        
        CDuiString name = impl->progress_ui->GetName();
        return duilib_wchar_to_utf8(name.GetData());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_progress_set_name(duilib_progress_t progress, const char* name) {
    if (!progress || !name) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return DUILIB_ERROR;
        
        wchar_t* wide_name = duilib_utf8_to_wchar(name);
        if (!wide_name) return DUILIB_ERROR;
        
        impl->progress_ui->SetName(wide_name);
        delete[] wide_name;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API char* duilib_progress_get_text(duilib_progress_t progress) {
    if (!progress) return nullptr;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return nullptr;
        
        CDuiString text = impl->progress_ui->GetText();
        return duilib_wchar_to_utf8(text.GetData());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_progress_set_text(duilib_progress_t progress, const char* text_content) {
    if (!progress) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return DUILIB_ERROR;
        
        if (!text_content) {
            impl->progress_ui->SetText(L"");
            return DUILIB_OK;
        }
        
        wchar_t* wide_text = duilib_utf8_to_wchar(text_content);
        if (!wide_text) return DUILIB_ERROR;
        
        impl->progress_ui->SetText(wide_text);
        delete[] wide_text;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API bool duilib_progress_is_visible(duilib_progress_t progress) {
    if (!progress) return false;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return false;
        
        return impl->progress_ui->IsVisible();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_progress_set_visible(duilib_progress_t progress, bool visible) {
    if (!progress) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return DUILIB_ERROR;
        
        impl->progress_ui->SetVisible(visible);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API bool duilib_progress_is_enabled(duilib_progress_t progress) {
    if (!progress) return false;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return false;
        
        return impl->progress_ui->IsEnabled();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_progress_set_enabled(duilib_progress_t progress, bool enabled) {
    if (!progress) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return DUILIB_ERROR;
        
        impl->progress_ui->SetEnabled(enabled);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API duilib_rect_t duilib_progress_get_pos(duilib_progress_t progress) {
    duilib_rect_t result = {0, 0, 0, 0};
    if (!progress) return result;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return result;
        
        const RECT& pos = impl->progress_ui->GetPos();
        result.left = pos.left;
        result.top = pos.top;
        result.right = pos.right;
        result.bottom = pos.bottom;
        return result;
    } catch (...) {
        return result;
    }
}

DUILIB_C_API duilib_result_t duilib_progress_set_pos(duilib_progress_t progress, duilib_rect_t pos, bool need_invalidate) {
    if (!progress) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return DUILIB_ERROR;
        
        RECT rc = {pos.left, pos.top, pos.right, pos.bottom};
        impl->progress_ui->SetPos(rc, need_invalidate);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}

DUILIB_C_API char* duilib_progress_get_attribute(duilib_progress_t progress, const char* name) {
    if (!progress || !name) return nullptr;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return nullptr;
        
        wchar_t* wide_name = duilib_utf8_to_wchar(name);
        if (!wide_name) return nullptr;
        
        CDuiString attr = impl->progress_ui->GetAttribute(wide_name);
        delete[] wide_name;
        
        return duilib_wchar_to_utf8(attr.GetData());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_progress_set_attribute(duilib_progress_t progress, const char* name, const char* value) {
    if (!progress || !name) return DUILIB_INVALID_PARAM;
    
    try {
        duilib_progress_impl* impl = reinterpret_cast<duilib_progress_impl*>(progress);
        if (!impl->progress_ui) return DUILIB_ERROR;
        
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
        
        impl->progress_ui->SetAttribute(wide_name, wide_value);
        
        delete[] wide_name;
        if (wide_value) delete[] wide_value;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR;
    }
}