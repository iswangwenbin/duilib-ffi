#include "duilib_c_tilelayout.h"
#include "../../duilib/DuiLib/Layout/UITileLayout.h"
#include <new>

using namespace DuiLib;

//=============================================================================
// Internal wrapper structure
//=============================================================================

struct duilib_tilelayout {
    CTileLayoutUI* layout_ui;
    
    duilib_tilelayout() {
        layout_ui = new(std::nothrow) CTileLayoutUI();
    }
    
    ~duilib_tilelayout() {
        // Note: Do not delete layout_ui here as it's managed by DuiLib
        // The DuiLib manager will handle the cleanup
    }
};

//=============================================================================
// Helper functions
//=============================================================================

static bool is_valid_tile_layout(duilib_tilelayout_t layout) {
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

static SIZE ConvertSize(const duilib_size_t& size) {
    SIZE result;
    result.cx = size.width;
    result.cy = size.height;
    return result;
}

static duilib_size_t ConvertSize(const SIZE& size) {
    duilib_size_t result;
    result.width = size.cx;
    result.height = size.cy;
    return result;
}

//=============================================================================
// CTileLayoutUI C API implementation
//=============================================================================

DUILIB_C_API duilib_tilelayout_t duilib_tilelayout_create(void) {
    return new(std::nothrow) duilib_tilelayout();
}

DUILIB_C_API void duilib_tilelayout_destroy(duilib_tilelayout_t layout) {
    delete layout;
}

DUILIB_C_API bool duilib_tilelayout_is_valid(duilib_tilelayout_t layout) {
    return is_valid_tile_layout(layout);
}

//=============================================================================
// Type conversion methods
//=============================================================================

DUILIB_C_API duilib_container_t duilib_tilelayout_to_container(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) return nullptr;
    return (duilib_container_t)layout->layout_ui;
}

DUILIB_C_API duilib_control_t duilib_tilelayout_to_control(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) return nullptr;
    return (duilib_control_t)layout->layout_ui;
}

DUILIB_C_API duilib_tilelayout_t duilib_tilelayout_from_container(duilib_container_t container) {
    if (!container) return nullptr;
    
    CContainerUI* container_ui = (CContainerUI*)container;
    CTileLayoutUI* tilelayout = dynamic_cast<CTileLayoutUI*>(container_ui);
    if (!tilelayout) return nullptr;
    
    duilib_tilelayout_t result = new(std::nothrow) duilib_tilelayout();
    if (result) {
        delete result->layout_ui; // Delete the new one
        result->layout_ui = tilelayout; // Use the existing one
    }
    return result;
}

//=============================================================================
// Class information methods
//=============================================================================

DUILIB_C_API const char* duilib_tilelayout_get_class(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) return nullptr;
    
    static thread_local char class_name[256];
    LPCTSTR class_str = layout->layout_ui->GetClass();
    ConvertStringToUTF8(class_str, class_name, sizeof(class_name));
    return class_name;
}

//=============================================================================
// Layout methods
//=============================================================================

DUILIB_C_API duilib_result_t duilib_tilelayout_set_pos(duilib_tilelayout_t layout, duilib_rect_t rect, bool need_invalidate) {
    if (!is_valid_tile_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        RECT win_rect = ConvertRect(rect);
        layout->layout_ui->SetPos(win_rect, need_invalidate);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

//=============================================================================
// Fixed columns management methods (specific to CTileLayoutUI)
//=============================================================================

DUILIB_C_API int duilib_tilelayout_get_fixed_columns(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) return 0;
    
    try {
        return layout->layout_ui->GetFixedColumns();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_tilelayout_set_fixed_columns(duilib_tilelayout_t layout, int columns) {
    if (!is_valid_tile_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        layout->layout_ui->SetFixedColumns(columns);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

//=============================================================================
// Child vertical padding methods (specific to CTileLayoutUI)
//=============================================================================

DUILIB_C_API int duilib_tilelayout_get_child_vpadding(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) return 0;
    
    try {
        return layout->layout_ui->GetChildVPadding();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_tilelayout_set_child_vpadding(duilib_tilelayout_t layout, int padding) {
    if (!is_valid_tile_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        layout->layout_ui->SetChildVPadding(padding);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

//=============================================================================
// Item size management methods (specific to CTileLayoutUI)
//=============================================================================

DUILIB_C_API duilib_size_t duilib_tilelayout_get_item_size(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) {
        duilib_size_t empty = {0, 0};
        return empty;
    }
    
    try {
        SIZE size = layout->layout_ui->GetItemSize();
        return ConvertSize(size);
    } catch (...) {
        duilib_size_t empty = {0, 0};
        return empty;
    }
}

DUILIB_C_API duilib_result_t duilib_tilelayout_set_item_size(duilib_tilelayout_t layout, duilib_size_t size) {
    if (!is_valid_tile_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        SIZE item_size = ConvertSize(size);
        layout->layout_ui->SetItemSize(item_size);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

//=============================================================================
// Grid information query methods (specific to CTileLayoutUI)
//=============================================================================

DUILIB_C_API int duilib_tilelayout_get_columns(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) return 0;
    
    try {
        return layout->layout_ui->GetColumns();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API int duilib_tilelayout_get_rows(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) return 0;
    
    try {
        return layout->layout_ui->GetRows();
    } catch (...) {
        return 0;
    }
}

//=============================================================================
// Attribute methods
//=============================================================================

DUILIB_C_API duilib_result_t duilib_tilelayout_set_attribute(duilib_tilelayout_t layout, const char* name, const char* value) {
    if (!is_valid_tile_layout(layout) || !name || !value) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
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
// Container methods (inherited from CContainerUI)
//=============================================================================

DUILIB_C_API duilib_result_t duilib_tilelayout_add_control(duilib_tilelayout_t layout, duilib_control_t control) {
    if (!is_valid_tile_layout(layout) || !control) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        bool success = layout->layout_ui->Add((CControlUI*)control);
        return success ? DUILIB_RESULT_OK : DUILIB_RESULT_ERROR;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_result_t duilib_tilelayout_add_control_at(duilib_tilelayout_t layout, duilib_control_t control, int index) {
    if (!is_valid_tile_layout(layout) || !control) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        bool success = layout->layout_ui->AddAt((CControlUI*)control, index);
        return success ? DUILIB_RESULT_OK : DUILIB_RESULT_ERROR;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_result_t duilib_tilelayout_remove_control(duilib_tilelayout_t layout, duilib_control_t control, bool do_not_destroy) {
    if (!is_valid_tile_layout(layout) || !control) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        bool success = layout->layout_ui->Remove((CControlUI*)control, do_not_destroy);
        return success ? DUILIB_RESULT_OK : DUILIB_RESULT_ERROR;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_result_t duilib_tilelayout_remove_control_at(duilib_tilelayout_t layout, int index, bool do_not_destroy) {
    if (!is_valid_tile_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        bool success = layout->layout_ui->RemoveAt(index, do_not_destroy);
        return success ? DUILIB_RESULT_OK : DUILIB_RESULT_ERROR;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API void duilib_tilelayout_remove_all(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) return;
    
    try {
        layout->layout_ui->RemoveAll();
    } catch (...) {
        // Ignore exceptions
    }
}

DUILIB_C_API duilib_control_t duilib_tilelayout_get_item_at(duilib_tilelayout_t layout, int index) {
    if (!is_valid_tile_layout(layout)) return nullptr;
    
    try {
        return (duilib_control_t)layout->layout_ui->GetItemAt(index);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API int duilib_tilelayout_get_item_index(duilib_tilelayout_t layout, duilib_control_t control) {
    if (!is_valid_tile_layout(layout) || !control) return -1;
    
    try {
        return layout->layout_ui->GetItemIndex((CControlUI*)control);
    } catch (...) {
        return -1;
    }
}

DUILIB_C_API int duilib_tilelayout_get_count(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) return 0;
    
    try {
        return layout->layout_ui->GetCount();
    } catch (...) {
        return 0;
    }
}

//=============================================================================
// Container properties methods
//=============================================================================

DUILIB_C_API duilib_rect_t duilib_tilelayout_get_inset(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) {
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

DUILIB_C_API duilib_result_t duilib_tilelayout_set_inset(duilib_tilelayout_t layout, duilib_rect_t inset) {
    if (!is_valid_tile_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        RECT rect = ConvertRect(inset);
        layout->layout_ui->SetInset(rect);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API int duilib_tilelayout_get_child_padding(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) return 0;
    return layout->layout_ui->GetChildPadding();
}

DUILIB_C_API duilib_result_t duilib_tilelayout_set_child_padding(duilib_tilelayout_t layout, int padding) {
    if (!is_valid_tile_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    layout->layout_ui->SetChildPadding(padding);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API unsigned int duilib_tilelayout_get_child_align(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) return 0;
    return layout->layout_ui->GetChildAlign();
}

DUILIB_C_API duilib_result_t duilib_tilelayout_set_child_align(duilib_tilelayout_t layout, unsigned int align) {
    if (!is_valid_tile_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    layout->layout_ui->SetChildAlign(align);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API unsigned int duilib_tilelayout_get_child_valign(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) return 0;
    return layout->layout_ui->GetChildVAlign();
}

DUILIB_C_API duilib_result_t duilib_tilelayout_set_child_valign(duilib_tilelayout_t layout, unsigned int valign) {
    if (!is_valid_tile_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    layout->layout_ui->SetChildVAlign(valign);
    return DUILIB_RESULT_OK;
}

//=============================================================================
// Scrollbar methods
//=============================================================================

DUILIB_C_API duilib_result_t duilib_tilelayout_enable_scrollbar(duilib_tilelayout_t layout, bool enable_vertical, bool enable_horizontal) {
    if (!is_valid_tile_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        layout->layout_ui->EnableScrollBar(enable_vertical, enable_horizontal);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_control_t duilib_tilelayout_get_vertical_scrollbar(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) return nullptr;
    
    try {
        return (duilib_control_t)layout->layout_ui->GetVerticalScrollBar();
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_control_t duilib_tilelayout_get_horizontal_scrollbar(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) return nullptr;
    
    try {
        return (duilib_control_t)layout->layout_ui->GetHorizontalScrollBar();
    } catch (...) {
        return nullptr;
    }
}

//=============================================================================
// Scroll position methods
//=============================================================================

DUILIB_C_API duilib_size_t duilib_tilelayout_get_scroll_pos(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) {
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

DUILIB_C_API duilib_result_t duilib_tilelayout_set_scroll_pos(duilib_tilelayout_t layout, duilib_size_t pos) {
    if (!is_valid_tile_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        SIZE scroll_pos = {pos.width, pos.height};
        layout->layout_ui->SetScrollPos(scroll_pos);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_size_t duilib_tilelayout_get_scroll_range(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) {
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
// Visibility and state methods
//=============================================================================

DUILIB_C_API bool duilib_tilelayout_is_visible(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) return false;
    return layout->layout_ui->IsVisible();
}

DUILIB_C_API duilib_result_t duilib_tilelayout_set_visible(duilib_tilelayout_t layout, bool visible) {
    if (!is_valid_tile_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    layout->layout_ui->SetVisible(visible);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API bool duilib_tilelayout_is_enabled(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) return false;
    return layout->layout_ui->IsEnabled();
}

DUILIB_C_API duilib_result_t duilib_tilelayout_set_enabled(duilib_tilelayout_t layout, bool enabled) {
    if (!is_valid_tile_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    layout->layout_ui->SetEnabled(enabled);
    return DUILIB_RESULT_OK;
}

//=============================================================================
// Mouse and keyboard methods
//=============================================================================

DUILIB_C_API bool duilib_tilelayout_is_mouse_enabled(duilib_tilelayout_t layout) {
    if (!is_valid_tile_layout(layout)) return false;
    return layout->layout_ui->IsMouseEnabled();
}

DUILIB_C_API duilib_result_t duilib_tilelayout_set_mouse_enabled(duilib_tilelayout_t layout, bool enable) {
    if (!is_valid_tile_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    layout->layout_ui->SetMouseEnabled(enable);
    return DUILIB_RESULT_OK;
}

//=============================================================================
// Control search methods
//=============================================================================

DUILIB_C_API duilib_control_t duilib_tilelayout_find_control(duilib_tilelayout_t layout, const char* name) {
    if (!is_valid_tile_layout(layout) || !name) return nullptr;
    
    try {
        CDuiString control_name = ConvertUTF8ToString(name);
        return (duilib_control_t)layout->layout_ui->FindControl(control_name.GetData());
    } catch (...) {
        return nullptr;
    }
}