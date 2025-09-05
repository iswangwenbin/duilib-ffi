#include "../duilib_c_internal.h"
#include "duilib_c_container.h"

//=============================================================================
// 容器控件操作
//=============================================================================

DUILIB_C_API duilib_result_t duilib_container_add(duilib_control_t container, duilib_control_t control) {
    if (!container || !control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        bool result = ctr->Add(control->control);
        return result ? DUILIB_OK : DUILIB_ERROR_UNKNOWN;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_container_add_at(duilib_control_t container, duilib_control_t control, int index) {
    if (!container || !control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        bool result = ctr->AddAt(control->control, index);
        return result ? DUILIB_OK : DUILIB_ERROR_UNKNOWN;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_container_remove(duilib_control_t container, duilib_control_t control) {
    if (!container || !control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        bool result = ctr->Remove(control->control);
        return result ? DUILIB_OK : DUILIB_ERROR_UNKNOWN;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_container_remove_at(duilib_control_t container, int index) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        bool result = ctr->RemoveAt(index);
        return result ? DUILIB_OK : DUILIB_ERROR_UNKNOWN;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_container_remove_all(duilib_control_t container) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->RemoveAll();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API int duilib_container_get_count(duilib_control_t container) {
    if (!container) return 0;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return 0;
        
        return ctr->GetCount();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_control_t duilib_container_get_item_at(duilib_control_t container, int index) {
    if (!container) return nullptr;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return nullptr;
        
        CControlUI* control = ctr->GetItemAt(index);
        if (!control) return nullptr;
        
        return new duilib_control{control};
    } catch (...) {
        return nullptr;
    }
}

//=============================================================================
// 容器特殊方法
//=============================================================================

DUILIB_C_API duilib_rect_t duilib_container_get_inset(duilib_control_t container) {
    duilib_rect_t result = {0, 0, 0, 0};
    if (!container) return result;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return result;
        
        RECT rc = ctr->GetInset();
        result.left = rc.left;
        result.top = rc.top;
        result.right = rc.right;
        result.bottom = rc.bottom;
        return result;
    } catch (...) {
        return result;
    }
}

DUILIB_C_API duilib_result_t duilib_container_set_inset(duilib_control_t container, duilib_rect_t inset) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        RECT rc = {inset.left, inset.top, inset.right, inset.bottom};
        ctr->SetInset(rc);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API int duilib_container_get_child_padding(duilib_control_t container) {
    if (!container) return 0;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return 0;
        
        return ctr->GetChildPadding();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_container_set_child_padding(duilib_control_t container, int padding) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->SetChildPadding(padding);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API uint32_t duilib_container_get_child_align(duilib_control_t container) {
    if (!container) return 0;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return 0;
        
        return ctr->GetChildAlign();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_container_set_child_align(duilib_control_t container, uint32_t align) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->SetChildAlign(align);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API uint32_t duilib_container_get_child_valign(duilib_control_t container) {
    if (!container) return 0;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return 0;
        
        return ctr->GetChildVAlign();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_container_set_child_valign(duilib_control_t container, uint32_t valign) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->SetChildVAlign(valign);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API bool duilib_container_is_auto_destroy(duilib_control_t container) {
    if (!container) return false;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return false;
        
        return ctr->IsAutoDestroy();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_container_set_auto_destroy(duilib_control_t container, bool auto_destroy) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->SetAutoDestroy(auto_destroy);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API bool duilib_container_is_mouse_child_enabled(duilib_control_t container) {
    if (!container) return false;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return false;
        
        return ctr->IsMouseChildEnabled();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_container_set_mouse_child_enabled(duilib_control_t container, bool enabled) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->SetMouseChildEnabled(enabled);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

//=============================================================================
// 子控件操作辅助方法
//=============================================================================

DUILIB_C_API duilib_result_t duilib_container_set_sub_control_text(duilib_control_t container, const char* sub_name, const char* text) {
    if (!container || !sub_name || !text) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->SetSubControlText(from_cstring(sub_name), from_cstring(text));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API const char* duilib_container_get_sub_control_text(duilib_control_t container, const char* sub_name) {
    if (!container || !sub_name) return nullptr;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return nullptr;
        
        return to_cstring(ctr->GetSubControlText(from_cstring(sub_name)));
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_control_t duilib_container_find_sub_control(duilib_control_t container, const char* sub_name) {
    if (!container || !sub_name) return nullptr;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return nullptr;
        
        CControlUI* control = ctr->FindSubControl(from_cstring(sub_name));
        if (!control) return nullptr;
        
        return new duilib_control{control};
    } catch (...) {
        return nullptr;
    }
}

//=============================================================================
// 滚动条相关 - 基本实现，需要真实的CContainerUI滚动方法
//=============================================================================

DUILIB_C_API duilib_size_t duilib_container_get_scroll_pos(duilib_control_t container) {
    duilib_size_t result = {0, 0};
    if (!container) return result;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return result;
        
        SIZE sz = ctr->GetScrollPos();
        result.width = sz.cx;
        result.height = sz.cy;
        return result;
    } catch (...) {
        return result;
    }
}

DUILIB_C_API duilib_size_t duilib_container_get_scroll_range(duilib_control_t container) {
    duilib_size_t result = {0, 0};
    if (!container) return result;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return result;
        
        SIZE sz = ctr->GetScrollRange();
        result.width = sz.cx;
        result.height = sz.cy;
        return result;
    } catch (...) {
        return result;
    }
}

DUILIB_C_API duilib_result_t duilib_container_set_scroll_pos(duilib_control_t container, duilib_size_t pos) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        SIZE sz = {pos.width, pos.height};
        ctr->SetScrollPos(sz);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_container_enable_scroll_bar(duilib_control_t container, bool vertical, bool horizontal) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->EnableScrollBar(horizontal, vertical);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

//=============================================================================
// 滚动操作
//=============================================================================

DUILIB_C_API duilib_result_t duilib_container_line_up(duilib_control_t container) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->LineUp();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_container_line_down(duilib_control_t container) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->LineDown();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_container_page_up(duilib_control_t container) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->PageUp();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_container_page_down(duilib_control_t container) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->PageDown();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_container_home_up(duilib_control_t container) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->HomeUp();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_container_end_down(duilib_control_t container) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->EndDown();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_container_line_left(duilib_control_t container) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->LineLeft();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_container_line_right(duilib_control_t container) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->LineRight();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_container_page_left(duilib_control_t container) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->PageLeft();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_container_page_right(duilib_control_t container) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->PageRight();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_container_home_left(duilib_control_t container) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->HomeLeft();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_container_end_right(duilib_control_t container) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->EndRight();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

//=============================================================================
// CContainerUI 缺失方法补充
//=============================================================================

DUILIB_C_API int duilib_container_get_item_index(duilib_control_t container, duilib_control_t control) {
    if (!container || !control) return -1;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return -1;
        
        return ctr->GetItemIndex(control->control);
    } catch (...) {
        return -1;
    }
}

DUILIB_C_API duilib_result_t duilib_container_set_item_index(duilib_control_t container, duilib_control_t control, int new_index) {
    if (!container || !control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        bool result = ctr->SetItemIndex(control->control, new_index);
        return result ? DUILIB_OK : DUILIB_ERROR_UNKNOWN;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_container_set_multi_item_index(duilib_control_t container, duilib_control_t start_control, int count, int new_start_index) {
    if (!container || !start_control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        bool result = ctr->SetMultiItemIndex(start_control->control, count, new_start_index);
        return result ? DUILIB_OK : DUILIB_ERROR_UNKNOWN;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API bool duilib_container_is_delayed_destroy(duilib_control_t container) {
    if (!container) return false;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return false;
        
        return ctr->IsDelayedDestroy();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_container_set_delayed_destroy(duilib_control_t container, bool delayed) {
    if (!container) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->SetDelayedDestroy(delayed);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API int duilib_container_find_selectable(duilib_control_t container, int index, bool forward) {
    if (!container) return -1;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return -1;
        
        return ctr->FindSelectable(index, forward);
    } catch (...) {
        return -1;
    }
}

DUILIB_C_API duilib_result_t duilib_container_set_sub_control_fixed_height(duilib_control_t container, const char* sub_name, int height) {
    if (!container || !sub_name) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->SetSubControlFixedHeight(from_cstring(sub_name), height);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API int duilib_container_get_sub_control_fixed_height(duilib_control_t container, const char* sub_name) {
    if (!container || !sub_name) return 0;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return 0;
        
        return ctr->GetSubControlFixedHeight(from_cstring(sub_name));
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_container_set_sub_control_fixed_width(duilib_control_t container, const char* sub_name, int width) {
    if (!container || !sub_name) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->SetSubControlFixedWidth(from_cstring(sub_name), width);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API int duilib_container_get_sub_control_fixed_width(duilib_control_t container, const char* sub_name) {
    if (!container || !sub_name) return 0;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return 0;
        
        return ctr->GetSubControlFixedWidth(from_cstring(sub_name));
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_container_set_sub_control_user_data(duilib_control_t container, const char* sub_name, const char* user_data) {
    if (!container || !sub_name || !user_data) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return DUILIB_ERROR_INVALID_PARAM;
        
        ctr->SetSubControlUserData(from_cstring(sub_name), from_cstring(user_data));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API const char* duilib_container_get_sub_control_user_data(duilib_control_t container, const char* sub_name) {
    if (!container || !sub_name) return nullptr;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return nullptr;
        
        return to_cstring(ctr->GetSubControlUserData(from_cstring(sub_name)));
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_control_t duilib_container_get_vertical_scroll_bar(duilib_control_t container) {
    if (!container) return nullptr;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return nullptr;
        
        CScrollBarUI* scrollbar = ctr->GetVerticalScrollBar();
        if (!scrollbar) return nullptr;
        
        return new duilib_control{scrollbar};
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_control_t duilib_container_get_horizontal_scroll_bar(duilib_control_t container) {
    if (!container) return nullptr;

    try {
        CContainerUI* ctr = safe_control_cast<CContainerUI>(container);
        if (!ctr) return nullptr;
        
        CScrollBarUI* scrollbar = ctr->GetHorizontalScrollBar();
        if (!scrollbar) return nullptr;
        
        return new duilib_control{scrollbar};
    } catch (...) {
        return nullptr;
    }
}