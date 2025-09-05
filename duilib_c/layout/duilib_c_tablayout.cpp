#include "duilib_c_tablayout.h"
#include "../../duilib/DuiLib/Layout/UITabLayout.h"
#include <new>

using namespace DuiLib;

//=============================================================================
// Internal wrapper structure
//=============================================================================

struct duilib_tablayout {
    CTabLayoutUI* layout_ui;
    
    duilib_tablayout() {
        layout_ui = new(std::nothrow) CTabLayoutUI();
    }
    
    ~duilib_tablayout() {
        // Note: Do not delete layout_ui here as it's managed by DuiLib
        // The DuiLib manager will handle the cleanup
    }
};

//=============================================================================
// Helper functions
//=============================================================================

static bool is_valid_tab_layout(duilib_tablayout_t layout) {
    return layout && layout->layout_ui;
}

static void ConvertStringToUTF8(LPCTSTR src, char* dst, size_t dst_size) {
    if (!src || !dst || dst_size == 0) return;
    
#ifdef _UNICODE
    WideCharToMultiByte(CP_UTF8, 0, src, -1, dst, (int)dst_size, nullptr, nullptr);
#else
    strncpy_s(dst, dst_size, src, _TRUNCATE);
#endif
}

static CDuiString ConvertUTF8ToString(const char* utf8_str) {
    if (!utf8_str) return CDuiString();
    
#ifdef _UNICODE
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8_str, -1, nullptr, 0);
    if (len <= 0) return CDuiString();
    
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, utf8_str, -1, wstr, len);
    CDuiString result(wstr);
    delete[] wstr;
    return result;
#else
    return CDuiString(utf8_str);
#endif
}

static RECT ConvertRect(const duilib_rect_t& rect) {
    RECT result;
    result.left = rect.left;
    result.top = rect.top;
    result.right = rect.right;
    result.bottom = rect.bottom;
    return result;
}

static duilib_rect_t ConvertRect(const RECT& rect) {
    duilib_rect_t result;
    result.left = rect.left;
    result.top = rect.top;
    result.right = rect.right;
    result.bottom = rect.bottom;
    return result;
}

//=============================================================================
// CTabLayoutUI C API implementation
//=============================================================================

DUILIB_C_API duilib_tablayout_t duilib_tablayout_create(void) {
    return new(std::nothrow) duilib_tablayout();
}

DUILIB_C_API void duilib_tablayout_destroy(duilib_tablayout_t layout) {
    delete layout;
}

DUILIB_C_API bool duilib_tablayout_is_valid(duilib_tablayout_t layout) {
    return is_valid_tab_layout(layout);
}

//=============================================================================
// Type conversion methods
//=============================================================================

DUILIB_C_API duilib_container_t duilib_tablayout_to_container(duilib_tablayout_t layout) {
    if (!is_valid_tab_layout(layout)) return nullptr;
    return (duilib_container_t)layout->layout_ui;
}

DUILIB_C_API duilib_control_t duilib_tablayout_to_control(duilib_tablayout_t layout) {
    if (!is_valid_tab_layout(layout)) return nullptr;
    return (duilib_control_t)layout->layout_ui;
}

DUILIB_C_API duilib_tablayout_t duilib_tablayout_from_container(duilib_container_t container) {
    if (!container) return nullptr;
    
    CContainerUI* container_ui = (CContainerUI*)container;
    CTabLayoutUI* tablayout = dynamic_cast<CTabLayoutUI*>(container_ui);
    if (!tablayout) return nullptr;
    
    duilib_tablayout_t result = new(std::nothrow) duilib_tablayout();
    if (result) {
        delete result->layout_ui; // Delete the new one
        result->layout_ui = tablayout; // Use the existing one
    }
    return result;
}

//=============================================================================
// Class information methods
//=============================================================================

DUILIB_C_API const char* duilib_tablayout_get_class(duilib_tablayout_t layout) {
    if (!is_valid_tab_layout(layout)) return nullptr;
    
    static thread_local char class_name[256];
    LPCTSTR class_str = layout->layout_ui->GetClass();
    ConvertStringToUTF8(class_str, class_name, sizeof(class_name));
    return class_name;
}

//=============================================================================
// Child control management methods (overridden from CContainerUI)
//=============================================================================

DUILIB_C_API duilib_result_t duilib_tablayout_add_control(duilib_tablayout_t layout, duilib_control_t control) {
    if (!is_valid_tab_layout(layout) || !control) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        bool success = layout->layout_ui->Add((CControlUI*)control);
        return success ? DUILIB_RESULT_OK : DUILIB_RESULT_ERROR;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_result_t duilib_tablayout_add_control_at(duilib_tablayout_t layout, duilib_control_t control, int index) {
    if (!is_valid_tab_layout(layout) || !control) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        bool success = layout->layout_ui->AddAt((CControlUI*)control, index);
        return success ? DUILIB_RESULT_OK : DUILIB_RESULT_ERROR;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_result_t duilib_tablayout_remove_control(duilib_tablayout_t layout, duilib_control_t control, bool do_not_destroy) {
    if (!is_valid_tab_layout(layout) || !control) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        bool success = layout->layout_ui->Remove((CControlUI*)control, do_not_destroy);
        return success ? DUILIB_RESULT_OK : DUILIB_RESULT_ERROR;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API void duilib_tablayout_remove_all(duilib_tablayout_t layout) {
    if (!is_valid_tab_layout(layout)) return;
    
    try {
        layout->layout_ui->RemoveAll();
    } catch (...) {
        // Ignore exceptions
    }
}

//=============================================================================
// Tab selection methods (specific to CTabLayoutUI)
//=============================================================================

DUILIB_C_API int duilib_tablayout_get_cur_sel(duilib_tablayout_t layout) {
    if (!is_valid_tab_layout(layout)) return -1;
    
    try {
        return layout->layout_ui->GetCurSel();
    } catch (...) {
        return -1;
    }
}

DUILIB_C_API duilib_result_t duilib_tablayout_select_item_by_index(duilib_tablayout_t layout, int index, bool trigger_event) {
    if (!is_valid_tab_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        bool success = layout->layout_ui->SelectItem(index, trigger_event);
        return success ? DUILIB_RESULT_OK : DUILIB_RESULT_ERROR;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_result_t duilib_tablayout_select_item_by_control(duilib_tablayout_t layout, duilib_control_t control, bool trigger_event) {
    if (!is_valid_tab_layout(layout) || !control) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        bool success = layout->layout_ui->SelectItem((CControlUI*)control, trigger_event);
        return success ? DUILIB_RESULT_OK : DUILIB_RESULT_ERROR;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

//=============================================================================
// Layout methods
//=============================================================================

DUILIB_C_API duilib_result_t duilib_tablayout_set_pos(duilib_tablayout_t layout, duilib_rect_t rect, bool need_invalidate) {
    if (!is_valid_tab_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        RECT win_rect = ConvertRect(rect);
        layout->layout_ui->SetPos(win_rect, need_invalidate);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

//=============================================================================
// Attribute methods
//=============================================================================

DUILIB_C_API duilib_result_t duilib_tablayout_set_attribute(duilib_tablayout_t layout, const char* name, const char* value) {
    if (!is_valid_tab_layout(layout) || !name || !value) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        CDuiString attr_name = ConvertUTF8ToString(name);
        CDuiString attr_value = ConvertUTF8ToString(value);
        
        layout->layout_ui->SetAttribute(attr_name.GetData(), attr_value.GetData());
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

//=============================================================================
// Container information methods
//=============================================================================

DUILIB_C_API duilib_control_t duilib_tablayout_get_item_at(duilib_tablayout_t layout, int index) {
    if (!is_valid_tab_layout(layout)) return nullptr;
    
    try {
        return (duilib_control_t)layout->layout_ui->GetItemAt(index);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API int duilib_tablayout_get_item_index(duilib_tablayout_t layout, duilib_control_t control) {
    if (!is_valid_tab_layout(layout) || !control) return -1;
    
    try {
        return layout->layout_ui->GetItemIndex((CControlUI*)control);
    } catch (...) {
        return -1;
    }
}

DUILIB_C_API int duilib_tablayout_get_count(duilib_tablayout_t layout) {
    if (!is_valid_tab_layout(layout)) return 0;
    
    try {
        return layout->layout_ui->GetCount();
    } catch (...) {
        return 0;
    }
}

//=============================================================================
// Container properties methods (inherited from CContainerUI)
//=============================================================================

DUILIB_C_API duilib_rect_t duilib_tablayout_get_inset(duilib_tablayout_t layout) {
    if (!is_valid_tab_layout(layout)) {
        duilib_rect_t empty = {0};
        return empty;
    }
    
    try {
        RECT rect = layout->layout_ui->GetInset();
        return ConvertRect(rect);
    } catch (...) {
        duilib_rect_t empty = {0};
        return empty;
    }
}

DUILIB_C_API duilib_result_t duilib_tablayout_set_inset(duilib_tablayout_t layout, duilib_rect_t inset) {
    if (!is_valid_tab_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        RECT rect = ConvertRect(inset);
        layout->layout_ui->SetInset(rect);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API int duilib_tablayout_get_child_padding(duilib_tablayout_t layout) {
    if (!is_valid_tab_layout(layout)) return 0;
    return layout->layout_ui->GetChildPadding();
}

DUILIB_C_API duilib_result_t duilib_tablayout_set_child_padding(duilib_tablayout_t layout, int padding) {
    if (!is_valid_tab_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    layout->layout_ui->SetChildPadding(padding);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API unsigned int duilib_tablayout_get_child_align(duilib_tablayout_t layout) {
    if (!is_valid_tab_layout(layout)) return 0;
    return layout->layout_ui->GetChildAlign();
}

DUILIB_C_API duilib_result_t duilib_tablayout_set_child_align(duilib_tablayout_t layout, unsigned int align) {
    if (!is_valid_tab_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    layout->layout_ui->SetChildAlign(align);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API unsigned int duilib_tablayout_get_child_valign(duilib_tablayout_t layout) {
    if (!is_valid_tab_layout(layout)) return 0;
    return layout->layout_ui->GetChildVAlign();
}

DUILIB_C_API duilib_result_t duilib_tablayout_set_child_valign(duilib_tablayout_t layout, unsigned int valign) {
    if (!is_valid_tab_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    layout->layout_ui->SetChildVAlign(valign);
    return DUILIB_RESULT_OK;
}

//=============================================================================
// Mouse and keyboard methods
//=============================================================================

DUILIB_C_API bool duilib_tablayout_is_mouse_enabled(duilib_tablayout_t layout) {
    if (!is_valid_tab_layout(layout)) return false;
    return layout->layout_ui->IsMouseEnabled();
}

DUILIB_C_API duilib_result_t duilib_tablayout_set_mouse_enabled(duilib_tablayout_t layout, bool enable) {
    if (!is_valid_tab_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    layout->layout_ui->SetMouseEnabled(enable);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API bool duilib_tablayout_is_mouse_child_enabled(duilib_tablayout_t layout) {
    if (!is_valid_tab_layout(layout)) return false;
    return layout->layout_ui->IsMouseChildEnabled();
}

DUILIB_C_API duilib_result_t duilib_tablayout_set_mouse_child_enabled(duilib_tablayout_t layout, bool enable) {
    if (!is_valid_tab_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    layout->layout_ui->SetMouseChildEnabled(enable);
    return DUILIB_RESULT_OK;
}

//=============================================================================
// Scrollbar methods
//=============================================================================

DUILIB_C_API duilib_result_t duilib_tablayout_enable_scrollbar(duilib_tablayout_t layout, bool enable_vertical, bool enable_horizontal) {
    if (!is_valid_tab_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        layout->layout_ui->EnableScrollBar(enable_vertical, enable_horizontal);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_control_t duilib_tablayout_get_vertical_scrollbar(duilib_tablayout_t layout) {
    if (!is_valid_tab_layout(layout)) return nullptr;
    
    try {
        return (duilib_control_t)layout->layout_ui->GetVerticalScrollBar();
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_control_t duilib_tablayout_get_horizontal_scrollbar(duilib_tablayout_t layout) {
    if (!is_valid_tab_layout(layout)) return nullptr;
    
    try {
        return (duilib_control_t)layout->layout_ui->GetHorizontalScrollBar();
    } catch (...) {
        return nullptr;
    }
}

//=============================================================================
// Scroll position methods
//=============================================================================

DUILIB_C_API duilib_size_t duilib_tablayout_get_scroll_pos(duilib_tablayout_t layout) {
    if (!is_valid_tab_layout(layout)) {
        duilib_size_t empty = {0, 0};
        return empty;
    }
    
    try {
        SIZE pos = layout->layout_ui->GetScrollPos();
        duilib_size_t result = {pos.cx, pos.cy};
        return result;
    } catch (...) {
        duilib_size_t empty = {0, 0};
        return empty;
    }
}

DUILIB_C_API duilib_result_t duilib_tablayout_set_scroll_pos(duilib_tablayout_t layout, duilib_size_t pos) {
    if (!is_valid_tab_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        SIZE scroll_pos = {pos.width, pos.height};
        layout->layout_ui->SetScrollPos(scroll_pos);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_size_t duilib_tablayout_get_scroll_range(duilib_tablayout_t layout) {
    if (!is_valid_tab_layout(layout)) {
        duilib_size_t empty = {0, 0};
        return empty;
    }
    
    try {
        SIZE range = layout->layout_ui->GetScrollRange();
        duilib_size_t result = {range.cx, range.cy};
        return result;
    } catch (...) {
        duilib_size_t empty = {0, 0};
        return empty;
    }
}

//=============================================================================
// Visibility and state methods (inherited from CControlUI)
//=============================================================================

DUILIB_C_API bool duilib_tablayout_is_visible(duilib_tablayout_t layout) {
    if (!is_valid_tab_layout(layout)) return false;
    return layout->layout_ui->IsVisible();
}

DUILIB_C_API duilib_result_t duilib_tablayout_set_visible(duilib_tablayout_t layout, bool visible) {
    if (!is_valid_tab_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    layout->layout_ui->SetVisible(visible);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API bool duilib_tablayout_is_enabled(duilib_tablayout_t layout) {
    if (!is_valid_tab_layout(layout)) return false;
    return layout->layout_ui->IsEnabled();
}

DUILIB_C_API duilib_result_t duilib_tablayout_set_enabled(duilib_tablayout_t layout, bool enabled) {
    if (!is_valid_tab_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    layout->layout_ui->SetEnabled(enabled);
    return DUILIB_RESULT_OK;
}

//=============================================================================
// Control search methods
//=============================================================================

DUILIB_C_API duilib_control_t duilib_tablayout_find_control(duilib_tablayout_t layout, const char* name) {
    if (!is_valid_tab_layout(layout) || !name) return nullptr;
    
    try {
        CDuiString control_name = ConvertUTF8ToString(name);
        return (duilib_control_t)layout->layout_ui->FindControl(control_name.GetData());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API int duilib_tablayout_find_selectable(duilib_tablayout_t layout, int index, bool forward) {
    if (!is_valid_tab_layout(layout)) return -1;
    
    try {
        return layout->layout_ui->FindSelectable(index, forward);
    } catch (...) {
        return -1;
    }
}