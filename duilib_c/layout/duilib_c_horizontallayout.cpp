#include "duilib_c_horizontallayout.h"
#include "../../duilib/DuiLib/Layout/UIHorizontalLayout.h"
#include <new>

using namespace DuiLib;

//=============================================================================
// Internal wrapper structure
//=============================================================================

struct duilib_horizontallayout {
    CHorizontalLayoutUI* layout_ui;
    
    duilib_horizontallayout() {
        layout_ui = new(std::nothrow) CHorizontalLayoutUI();
    }
    
    ~duilib_horizontallayout() {
        // Note: Do not delete layout_ui here as it's managed by DuiLib
        // The DuiLib manager will handle the cleanup
    }
};

//=============================================================================
// Helper functions
//=============================================================================

static bool is_valid_horizontal_layout(duilib_horizontallayout_t layout) {
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
// CHorizontalLayoutUI C API implementation
//=============================================================================

DUILIB_C_API duilib_horizontallayout_t duilib_horizontallayout_create(void) {
    return new(std::nothrow) duilib_horizontallayout();
}

DUILIB_C_API void duilib_horizontallayout_destroy(duilib_horizontallayout_t layout) {
    delete layout;
}

DUILIB_C_API bool duilib_horizontallayout_is_valid(duilib_horizontallayout_t layout) {
    return is_valid_horizontal_layout(layout);
}

//=============================================================================
// Type conversion methods
//=============================================================================

DUILIB_C_API duilib_container_t duilib_horizontallayout_to_container(duilib_horizontallayout_t layout) {
    if (!is_valid_horizontal_layout(layout)) return nullptr;
    return (duilib_container_t)layout->layout_ui;
}

DUILIB_C_API duilib_control_t duilib_horizontallayout_to_control(duilib_horizontallayout_t layout) {
    if (!is_valid_horizontal_layout(layout)) return nullptr;
    return (duilib_control_t)layout->layout_ui;
}

DUILIB_C_API duilib_horizontallayout_t duilib_horizontallayout_from_container(duilib_container_t container) {
    if (!container) return nullptr;
    
    CContainerUI* container_ui = (CContainerUI*)container;
    CHorizontalLayoutUI* hlayout = dynamic_cast<CHorizontalLayoutUI*>(container_ui);
    if (!hlayout) return nullptr;
    
    duilib_horizontallayout_t result = new(std::nothrow) duilib_horizontallayout();
    if (result) {
        delete result->layout_ui; // Delete the new one
        result->layout_ui = hlayout; // Use the existing one
    }
    return result;
}

//=============================================================================
// Class information methods
//=============================================================================

DUILIB_C_API const char* duilib_horizontallayout_get_class(duilib_horizontallayout_t layout) {
    if (!is_valid_horizontal_layout(layout)) return nullptr;
    
    static thread_local char class_name[256];
    LPCTSTR class_str = layout->layout_ui->GetClass();
    ConvertStringToUTF8(class_str, class_name, sizeof(class_name));
    return class_name;
}

DUILIB_C_API unsigned int duilib_horizontallayout_get_control_flags(duilib_horizontallayout_t layout) {
    if (!is_valid_horizontal_layout(layout)) return 0;
    return layout->layout_ui->GetControlFlags();
}

//=============================================================================
// Separator related methods (specific to HorizontalLayoutUI)
//=============================================================================

DUILIB_C_API duilib_result_t duilib_horizontallayout_set_sep_width(duilib_horizontallayout_t layout, int width) {
    if (!is_valid_horizontal_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        layout->layout_ui->SetSepWidth(width);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API int duilib_horizontallayout_get_sep_width(duilib_horizontallayout_t layout) {
    if (!is_valid_horizontal_layout(layout)) return 0;
    return layout->layout_ui->GetSepWidth();
}

DUILIB_C_API duilib_result_t duilib_horizontallayout_set_sep_imm_mode(duilib_horizontallayout_t layout, bool immediately) {
    if (!is_valid_horizontal_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        layout->layout_ui->SetSepImmMode(immediately);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API bool duilib_horizontallayout_is_sep_imm_mode(duilib_horizontallayout_t layout) {
    if (!is_valid_horizontal_layout(layout)) return false;
    return layout->layout_ui->IsSepImmMode();
}

//=============================================================================
// Layout and paint methods
//=============================================================================

DUILIB_C_API duilib_result_t duilib_horizontallayout_set_pos(duilib_horizontallayout_t layout, duilib_rect_t rect, bool need_invalidate) {
    if (!is_valid_horizontal_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        RECT win_rect = ConvertRect(rect);
        layout->layout_ui->SetPos(win_rect, need_invalidate);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_result_t duilib_horizontallayout_do_post_paint(duilib_horizontallayout_t layout, void* hdc, duilib_rect_t paint_rect) {
    if (!is_valid_horizontal_layout(layout) || !hdc) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        RECT rect = ConvertRect(paint_rect);
        layout->layout_ui->DoPostPaint((HDC)hdc, rect);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_rect_t duilib_horizontallayout_get_thumb_rect(duilib_horizontallayout_t layout, bool use_new) {
    if (!is_valid_horizontal_layout(layout)) {
        duilib_rect_t empty = {0};
        return empty;
    }
    
    try {
        RECT rect = layout->layout_ui->GetThumbRect(use_new);
        return ConvertRect(rect);
    } catch (...) {
        duilib_rect_t empty = {0};
        return empty;
    }
}

//=============================================================================
// Event handling methods  
//=============================================================================

DUILIB_C_API duilib_result_t duilib_horizontallayout_do_event(duilib_horizontallayout_t layout, duilib_ui_event_t* event) {
    if (!is_valid_horizontal_layout(layout) || !event) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        // Convert C event structure to DuiLib TEventUI
        TEventUI ui_event = {0};
        
        // Convert event type
        if (event->type == DUILIB_UI_EVENT_BUTTONDOWN) {
            ui_event.Type = UIEVENT_BUTTONDOWN;
        } else if (event->type == DUILIB_UI_EVENT_BUTTONUP) {
            ui_event.Type = UIEVENT_BUTTONUP;
        } else if (event->type == DUILIB_UI_EVENT_MOUSEMOVE) {
            ui_event.Type = UIEVENT_MOUSEMOVE;
        } else if (event->type == DUILIB_UI_EVENT_MOUSELEAVE) {
            ui_event.Type = UIEVENT_MOUSELEAVE;
        } else {
            ui_event.Type = UIEVENT_LAST; // Unknown event type
        }
        
        // Set event data
        ui_event.pSender = (CControlUI*)event->sender;
        ui_event.wParam = event->wparam;
        ui_event.lParam = event->lparam;
        ui_event.ptMouse.x = event->point.x;
        ui_event.ptMouse.y = event->point.y;
        ui_event.wKeyState = event->key_state;
        ui_event.dwTimestamp = event->timestamp;
        
        layout->layout_ui->DoEvent(ui_event);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

//=============================================================================
// Attribute methods
//=============================================================================

DUILIB_C_API duilib_result_t duilib_horizontallayout_set_attribute(duilib_horizontallayout_t layout, const char* name, const char* value) {
    if (!is_valid_horizontal_layout(layout) || !name || !value) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
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

DUILIB_C_API duilib_result_t duilib_horizontallayout_add_control(duilib_horizontallayout_t layout, duilib_control_t control) {
    if (!is_valid_horizontal_layout(layout) || !control) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        bool success = layout->layout_ui->Add((CControlUI*)control);
        return success ? DUILIB_RESULT_OK : DUILIB_RESULT_ERROR;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_result_t duilib_horizontallayout_add_control_at(duilib_horizontallayout_t layout, duilib_control_t control, int index) {
    if (!is_valid_horizontal_layout(layout) || !control) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        bool success = layout->layout_ui->AddAt((CControlUI*)control, index);
        return success ? DUILIB_RESULT_OK : DUILIB_RESULT_ERROR;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_result_t duilib_horizontallayout_remove_control(duilib_horizontallayout_t layout, duilib_control_t control, bool do_not_destroy) {
    if (!is_valid_horizontal_layout(layout) || !control) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        bool success = layout->layout_ui->Remove((CControlUI*)control, do_not_destroy);
        return success ? DUILIB_RESULT_OK : DUILIB_RESULT_ERROR;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_result_t duilib_horizontallayout_remove_control_at(duilib_horizontallayout_t layout, int index, bool do_not_destroy) {
    if (!is_valid_horizontal_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        bool success = layout->layout_ui->RemoveAt(index, do_not_destroy);
        return success ? DUILIB_RESULT_OK : DUILIB_RESULT_ERROR;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API void duilib_horizontallayout_remove_all(duilib_horizontallayout_t layout) {
    if (!is_valid_horizontal_layout(layout)) return;
    
    try {
        layout->layout_ui->RemoveAll();
    } catch (...) {
        // Ignore exceptions
    }
}

DUILIB_C_API duilib_control_t duilib_horizontallayout_get_item_at(duilib_horizontallayout_t layout, int index) {
    if (!is_valid_horizontal_layout(layout)) return nullptr;
    
    try {
        return (duilib_control_t)layout->layout_ui->GetItemAt(index);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API int duilib_horizontallayout_get_item_index(duilib_horizontallayout_t layout, duilib_control_t control) {
    if (!is_valid_horizontal_layout(layout) || !control) return -1;
    
    try {
        return layout->layout_ui->GetItemIndex((CControlUI*)control);
    } catch (...) {
        return -1;
    }
}

DUILIB_C_API int duilib_horizontallayout_get_count(duilib_horizontallayout_t layout) {
    if (!is_valid_horizontal_layout(layout)) return 0;
    
    try {
        return layout->layout_ui->GetCount();
    } catch (...) {
        return 0;
    }
}

//=============================================================================
// Container properties methods
//=============================================================================

DUILIB_C_API duilib_rect_t duilib_horizontallayout_get_inset(duilib_horizontallayout_t layout) {
    if (!is_valid_horizontal_layout(layout)) {
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

DUILIB_C_API duilib_result_t duilib_horizontallayout_set_inset(duilib_horizontallayout_t layout, duilib_rect_t inset) {
    if (!is_valid_horizontal_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        RECT rect = ConvertRect(inset);
        layout->layout_ui->SetInset(rect);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API int duilib_horizontallayout_get_child_padding(duilib_horizontallayout_t layout) {
    if (!is_valid_horizontal_layout(layout)) return 0;
    return layout->layout_ui->GetChildPadding();
}

DUILIB_C_API duilib_result_t duilib_horizontallayout_set_child_padding(duilib_horizontallayout_t layout, int padding) {
    if (!is_valid_horizontal_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    layout->layout_ui->SetChildPadding(padding);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API unsigned int duilib_horizontallayout_get_child_align(duilib_horizontallayout_t layout) {
    if (!is_valid_horizontal_layout(layout)) return 0;
    return layout->layout_ui->GetChildAlign();
}

DUILIB_C_API duilib_result_t duilib_horizontallayout_set_child_align(duilib_horizontallayout_t layout, unsigned int align) {
    if (!is_valid_horizontal_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    layout->layout_ui->SetChildAlign(align);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API unsigned int duilib_horizontallayout_get_child_valign(duilib_horizontallayout_t layout) {
    if (!is_valid_horizontal_layout(layout)) return 0;
    return layout->layout_ui->GetChildVAlign();
}

DUILIB_C_API duilib_result_t duilib_horizontallayout_set_child_valign(duilib_horizontallayout_t layout, unsigned int valign) {
    if (!is_valid_horizontal_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    layout->layout_ui->SetChildVAlign(valign);
    return DUILIB_RESULT_OK;
}

//=============================================================================
// Scrollbar methods
//=============================================================================

DUILIB_C_API duilib_result_t duilib_horizontallayout_enable_scrollbar(duilib_horizontallayout_t layout, bool enable_vertical, bool enable_horizontal) {
    if (!is_valid_horizontal_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        layout->layout_ui->EnableScrollBar(enable_vertical, enable_horizontal);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_control_t duilib_horizontallayout_get_vertical_scrollbar(duilib_horizontallayout_t layout) {
    if (!is_valid_horizontal_layout(layout)) return nullptr;
    
    try {
        return (duilib_control_t)layout->layout_ui->GetVerticalScrollBar();
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_control_t duilib_horizontallayout_get_horizontal_scrollbar(duilib_horizontallayout_t layout) {
    if (!is_valid_horizontal_layout(layout)) return nullptr;
    
    try {
        return (duilib_control_t)layout->layout_ui->GetHorizontalScrollBar();
    } catch (...) {
        return nullptr;
    }
}

//=============================================================================
// Scroll position methods
//=============================================================================

DUILIB_C_API duilib_size_t duilib_horizontallayout_get_scroll_pos(duilib_horizontallayout_t layout) {
    if (!is_valid_horizontal_layout(layout)) {
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

DUILIB_C_API duilib_result_t duilib_horizontallayout_set_scroll_pos(duilib_horizontallayout_t layout, duilib_size_t pos) {
    if (!is_valid_horizontal_layout(layout)) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        SIZE scroll_pos = {pos.width, pos.height};
        layout->layout_ui->SetScrollPos(scroll_pos);
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_size_t duilib_horizontallayout_get_scroll_range(duilib_horizontallayout_t layout) {
    if (!is_valid_horizontal_layout(layout)) {
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
// Scroll operation methods
//=============================================================================

DUILIB_C_API void duilib_horizontallayout_line_up(duilib_horizontallayout_t layout) {
    if (is_valid_horizontal_layout(layout)) {
        try {
            layout->layout_ui->LineUp();
        } catch (...) {}
    }
}

DUILIB_C_API void duilib_horizontallayout_line_down(duilib_horizontallayout_t layout) {
    if (is_valid_horizontal_layout(layout)) {
        try {
            layout->layout_ui->LineDown();
        } catch (...) {}
    }
}

DUILIB_C_API void duilib_horizontallayout_line_left(duilib_horizontallayout_t layout) {
    if (is_valid_horizontal_layout(layout)) {
        try {
            layout->layout_ui->LineLeft();
        } catch (...) {}
    }
}

DUILIB_C_API void duilib_horizontallayout_line_right(duilib_horizontallayout_t layout) {
    if (is_valid_horizontal_layout(layout)) {
        try {
            layout->layout_ui->LineRight();
        } catch (...) {}
    }
}

DUILIB_C_API void duilib_horizontallayout_page_up(duilib_horizontallayout_t layout) {
    if (is_valid_horizontal_layout(layout)) {
        try {
            layout->layout_ui->PageUp();
        } catch (...) {}
    }
}

DUILIB_C_API void duilib_horizontallayout_page_down(duilib_horizontallayout_t layout) {
    if (is_valid_horizontal_layout(layout)) {
        try {
            layout->layout_ui->PageDown();
        } catch (...) {}
    }
}

DUILIB_C_API void duilib_horizontallayout_page_left(duilib_horizontallayout_t layout) {
    if (is_valid_horizontal_layout(layout)) {
        try {
            layout->layout_ui->PageLeft();
        } catch (...) {}
    }
}

DUILIB_C_API void duilib_horizontallayout_page_right(duilib_horizontallayout_t layout) {
    if (is_valid_horizontal_layout(layout)) {
        try {
            layout->layout_ui->PageRight();
        } catch (...) {}
    }
}

DUILIB_C_API void duilib_horizontallayout_home_up(duilib_horizontallayout_t layout) {
    if (is_valid_horizontal_layout(layout)) {
        try {
            layout->layout_ui->HomeUp();
        } catch (...) {}
    }
}

DUILIB_C_API void duilib_horizontallayout_end_down(duilib_horizontallayout_t layout) {
    if (is_valid_horizontal_layout(layout)) {
        try {
            layout->layout_ui->EndDown();
        } catch (...) {}
    }
}

DUILIB_C_API void duilib_horizontallayout_home_left(duilib_horizontallayout_t layout) {
    if (is_valid_horizontal_layout(layout)) {
        try {
            layout->layout_ui->HomeLeft();
        } catch (...) {}
    }
}

DUILIB_C_API void duilib_horizontallayout_end_right(duilib_horizontallayout_t layout) {
    if (is_valid_horizontal_layout(layout)) {
        try {
            layout->layout_ui->EndRight();
        } catch (...) {}
    }
}