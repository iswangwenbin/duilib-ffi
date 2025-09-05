#include "../duilib_c_internal.h"
#include "duilib_c_control.h"

//=============================================================================
// 控件查找API实现
//=============================================================================

DUILIB_C_API duilib_control_t duilib_find_control(duilib_manager_t manager, const char* name) {
    if (!manager || !manager->paint_manager || !name) return nullptr;

    try {
        CControlUI* control = manager->paint_manager->FindControl(from_cstring(name));
        if (control) {
            duilib_control_t wrapper = new duilib_control;
            wrapper->control = control;
            return wrapper;
        }
        return nullptr;
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_control_t duilib_find_control_by_class(duilib_manager_t manager, const char* class_name) {
    if (!manager || !manager->paint_manager || !class_name) return nullptr;

    try {
        CControlUI* control = manager->paint_manager->FindControl(from_cstring(class_name));
        if (control) {
            duilib_control_t wrapper = new duilib_control;
            wrapper->control = control;
            return wrapper;
        }
        return nullptr;
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_control_t duilib_find_control_at_point(duilib_manager_t manager, int x, int y) {
    if (!manager || !manager->paint_manager) return nullptr;

    try {
        POINT pt = {x, y};
        CControlUI* control = manager->paint_manager->FindControlAtPoint(pt);
        if (control) {
            duilib_control_t wrapper = new duilib_control;
            wrapper->control = control;
            return wrapper;
        }
        return nullptr;
    } catch (...) {
        return nullptr;
    }
}

//=============================================================================
// 控件属性API实现
//=============================================================================

DUILIB_C_API const char* duilib_control_get_name(duilib_control_t control) {
    if (!control || !control->control) return nullptr;

    try {
        return to_cstring(control->control->GetName());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_name(duilib_control_t control, const char* name) {
    if (!control || !control->control || !name) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetName(from_cstring(name));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API const char* duilib_control_get_text(duilib_control_t control) {
    if (!control || !control->control) return nullptr;

    try {
        return to_cstring(control->control->GetText());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_text(duilib_control_t control, const char* text) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetText(from_cstring(text ? text : ""));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_rect_t duilib_control_get_pos(duilib_control_t control) {
    duilib_rect_t rect = {0, 0, 0, 0};
    if (!control || !control->control) return rect;

    try {
        RECT rc = control->control->GetPos();
        rect.left = rc.left;
        rect.top = rc.top;
        rect.right = rc.right;
        rect.bottom = rc.bottom;
    } catch (...) {
    }
    return rect;
}

DUILIB_C_API duilib_result_t duilib_control_set_pos(duilib_control_t control, duilib_rect_t rect) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        RECT rc = {rect.left, rect.top, rect.right, rect.bottom};
        control->control->SetPos(rc);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API bool duilib_control_is_visible(duilib_control_t control) {
    if (!control || !control->control) return false;

    try {
        return control->control->IsVisible();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_visible(duilib_control_t control, bool visible) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetVisible(visible);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API bool duilib_control_is_enabled(duilib_control_t control) {
    if (!control || !control->control) return false;

    try {
        return control->control->IsEnabled();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_enabled(duilib_control_t control, bool enabled) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetEnabled(enabled);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API int duilib_control_get_width(duilib_control_t control) {
    if (!control || !control->control) return 0;

    try {
        RECT rc = control->control->GetPos();
        return rc.right - rc.left;
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API int duilib_control_get_height(duilib_control_t control) {
    if (!control || !control->control) return 0;

    try {
        RECT rc = control->control->GetPos();
        return rc.bottom - rc.top;
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API int duilib_control_get_x(duilib_control_t control) {
    if (!control || !control->control) return 0;

    try {
        RECT rc = control->control->GetPos();
        return rc.left;
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API int duilib_control_get_y(duilib_control_t control) {
    if (!control || !control->control) return 0;

    try {
        RECT rc = control->control->GetPos();
        return rc.top;
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_rect_t duilib_control_get_padding(duilib_control_t control) {
    duilib_rect_t rect = {0, 0, 0, 0};
    if (!control || !control->control) return rect;

    try {
        RECT rc = control->control->GetPadding();
        rect.left = rc.left;
        rect.top = rc.top;
        rect.right = rc.right;
        rect.bottom = rc.bottom;
    } catch (...) {
    }
    return rect;
}

DUILIB_C_API duilib_result_t duilib_control_set_padding(duilib_control_t control, duilib_rect_t padding) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        RECT rc = {padding.left, padding.top, padding.right, padding.bottom};
        control->control->SetPadding(rc);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API const char* duilib_control_get_tooltip(duilib_control_t control) {
    if (!control || !control->control) return nullptr;

    try {
        return to_cstring(control->control->GetToolTip());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_tooltip(duilib_control_t control, const char* tooltip) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetToolTip(from_cstring(tooltip ? tooltip : ""));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API const char* duilib_control_get_user_data(duilib_control_t control) {
    if (!control || !control->control) return nullptr;

    try {
        return to_cstring(control->control->GetUserData());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_user_data(duilib_control_t control, const char* user_data) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetUserData(from_cstring(user_data ? user_data : ""));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API uintptr_t duilib_control_get_tag(duilib_control_t control) {
    if (!control || !control->control) return 0;

    try {
        return control->control->GetTag();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_tag(duilib_control_t control, uintptr_t tag) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetTag(tag);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

//=============================================================================
// 控件样式API实现
//=============================================================================

DUILIB_C_API duilib_result_t duilib_control_set_bk_color(duilib_control_t control, duilib_color_t color) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetBkColor(color);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_bk_image(duilib_control_t control, const char* image_path) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetBkImage(from_cstring(image_path ? image_path : ""));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_border_color(duilib_control_t control, duilib_color_t color) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetBorderColor(color);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_border_size(duilib_control_t control, int size) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetBorderSize(size);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_border_size_rect(duilib_control_t control, duilib_rect_t rect) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        RECT rc = {rect.left, rect.top, rect.right, rect.bottom};
        control->control->SetBorderSize(rc);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_rect_t duilib_control_get_border_size(duilib_control_t control) {
    duilib_rect_t rect = {0, 0, 0, 0};
    if (!control || !control->control) return rect;

    try {
        RECT rc = control->control->GetBorderSize();
        rect.left = rc.left;
        rect.top = rc.top;
        rect.right = rc.right;
        rect.bottom = rc.bottom;
    } catch (...) {
    }
    return rect;
}

//=============================================================================
// 通用属性API实现
//=============================================================================

DUILIB_C_API duilib_result_t duilib_control_set_attribute(duilib_control_t control, const char* name, const char* value) {
    if (!control || !control->control || !name) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetAttribute(from_cstring(name), from_cstring(value ? value : ""));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API const char* duilib_control_get_attribute(duilib_control_t control, const char* name) {
    if (!control || !control->control || !name) return nullptr;

    try {
        return to_cstring(control->control->GetAttribute(from_cstring(name)));
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API const char* duilib_control_get_class(duilib_control_t control) {
    if (!control || !control->control) return nullptr;

    try {
        return to_cstring(control->control->GetClass());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API bool duilib_control_is_focused(duilib_control_t control) {
    if (!control || !control->control) return false;

    try {
        return control->control->IsFocused();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_focus(duilib_control_t control) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetFocus();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API bool duilib_control_is_float(duilib_control_t control) {
    if (!control || !control->control) return false;

    try {
        return control->control->IsFloat();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_float(duilib_control_t control, bool is_float) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetFloat(is_float);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_control_t duilib_control_get_parent(duilib_control_t control) {
    if (!control || !control->control) return nullptr;

    try {
        CControlUI* parent = control->control->GetParent();
        if (parent) {
            duilib_control_t wrapper = new duilib_control;
            wrapper->control = parent;
            return wrapper;
        }
        return nullptr;
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API int duilib_control_get_fixed_width(duilib_control_t control) {
    if (!control || !control->control) return 0;

    try {
        return control->control->GetFixedWidth();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API int duilib_control_get_fixed_height(duilib_control_t control) {
    if (!control || !control->control) return 0;

    try {
        return control->control->GetFixedHeight();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API int duilib_control_get_min_width(duilib_control_t control) {
    if (!control || !control->control) return 0;

    try {
        return control->control->GetMinWidth();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API int duilib_control_get_min_height(duilib_control_t control) {
    if (!control || !control->control) return 0;

    try {
        return control->control->GetMinHeight();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API int duilib_control_get_max_width(duilib_control_t control) {
    if (!control || !control->control) return 0;

    try {
        return control->control->GetMaxWidth();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API int duilib_control_get_max_height(duilib_control_t control) {
    if (!control || !control->control) return 0;

    try {
        return control->control->GetMaxHeight();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_color_t duilib_control_get_bk_color(duilib_control_t control) {
    if (!control || !control->control) return 0;

    try {
        return control->control->GetBkColor();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_color_t duilib_control_get_bk_color2(duilib_control_t control) {
    if (!control || !control->control) return 0;

    try {
        return control->control->GetBkColor2();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_color_t duilib_control_get_bk_color3(duilib_control_t control) {
    if (!control || !control->control) return 0;

    try {
        return control->control->GetBkColor3();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_bk_color2(duilib_control_t control, duilib_color_t color) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetBkColor2(color);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_bk_color3(duilib_control_t control, duilib_color_t color) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetBkColor3(color);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API const char* duilib_control_get_bk_image(duilib_control_t control) {
    if (!control || !control->control) return nullptr;

    try {
        return to_cstring(control->control->GetBkImage());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_color_t duilib_control_get_border_color(duilib_control_t control) {
    if (!control || !control->control) return 0;

    try {
        return control->control->GetBorderColor();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_color_t duilib_control_get_focus_border_color(duilib_control_t control) {
    if (!control || !control->control) return 0;

    try {
        return control->control->GetFocusBorderColor();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_focus_border_color(duilib_control_t control, duilib_color_t color) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetFocusBorderColor(color);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API bool duilib_control_is_mouse_enabled(duilib_control_t control) {
    if (!control || !control->control) return false;

    try {
        return control->control->IsMouseEnabled();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_mouse_enabled(duilib_control_t control, bool enabled) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetMouseEnabled(enabled);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API bool duilib_control_is_keyboard_enabled(duilib_control_t control) {
    if (!control || !control->control) return false;

    try {
        return control->control->IsKeyboardEnabled();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_keyboard_enabled(duilib_control_t control, bool enabled) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetKeyboardEnabled(enabled);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API char duilib_control_get_shortcut(duilib_control_t control) {
    if (!control || !control->control) return 0;

    try {
        return control->control->GetShortcut();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_shortcut(duilib_control_t control, char shortcut) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetShortcut(shortcut);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API bool duilib_control_is_context_menu_used(duilib_control_t control) {
    if (!control || !control->control) return false;

    try {
        return control->control->IsContextMenuUsed();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_context_menu_used(duilib_control_t control, bool used) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetContextMenuUsed(used);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_invalidate(duilib_control_t control) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->Invalidate();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API bool duilib_control_is_update_needed(duilib_control_t control) {
    if (!control || !control->control) return false;

    try {
        return control->control->IsUpdateNeeded();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_control_need_update(duilib_control_t control) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->NeedUpdate();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API int duilib_control_get_tooltip_width(duilib_control_t control) {
    if (!control || !control->control) return 0;

    try {
        return control->control->GetToolTipWidth();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_tooltip_width(duilib_control_t control, int width) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetToolTipWidth(width);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_size_t duilib_control_get_fixed_xy(duilib_control_t control) {
    duilib_size_t size = {0, 0};
    if (!control || !control->control) return size;

    try {
        SIZE sz = control->control->GetFixedXY();
        size.cx = sz.cx;
        size.cy = sz.cy;
    } catch (...) {
    }
    return size;
}

DUILIB_C_API duilib_result_t duilib_control_set_fixed_xy(duilib_control_t control, duilib_size_t xy) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        SIZE sz = {xy.cx, xy.cy};
        control->control->SetFixedXY(sz);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_rect_t duilib_control_get_relative_pos(duilib_control_t control) {
    duilib_rect_t rect = {0, 0, 0, 0};
    if (!control || !control->control) return rect;

    try {
        RECT rc = control->control->GetRelativePos();
        rect.left = rc.left;
        rect.top = rc.top;
        rect.right = rc.right;
        rect.bottom = rc.bottom;
    } catch (...) {
    }
    return rect;
}

DUILIB_C_API duilib_rect_t duilib_control_get_client_pos(duilib_control_t control) {
    duilib_rect_t rect = {0, 0, 0, 0};
    if (!control || !control->control) return rect;

    try {
        RECT rc = control->control->GetClientPos();
        rect.left = rc.left;
        rect.top = rc.top;
        rect.right = rc.right;
        rect.bottom = rc.bottom;
    } catch (...) {
    }
    return rect;
}

DUILIB_C_API duilib_result_t duilib_control_move(duilib_control_t control, duilib_size_t offset) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        SIZE sz = {offset.cx, offset.cy};
        control->control->Move(sz);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_control_t duilib_control_get_cover(duilib_control_t control) {
    if (!control || !control->control) return nullptr;

    try {
        CControlUI* cover = control->control->GetCover();
        if (cover) {
            duilib_control_t wrapper = new duilib_control;
            wrapper->control = cover;
            return wrapper;
        }
        return nullptr;
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_cover(duilib_control_t control, duilib_control_t cover) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetCover(cover ? cover->control : nullptr);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API void* duilib_control_get_native_window(duilib_control_t control) {
    if (!control || !control->control) return nullptr;

    try {
        return control->control->GetNativeWindow();
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_size_t duilib_control_get_border_round(duilib_control_t control) {
    duilib_size_t size = {0, 0};
    if (!control || !control->control) return size;

    try {
        SIZE sz = control->control->GetBorderRound();
        size.cx = sz.cx;
        size.cy = sz.cy;
    } catch (...) {
    }
    return size;
}

DUILIB_C_API duilib_result_t duilib_control_set_border_round(duilib_control_t control, duilib_size_t round) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        SIZE sz = {round.cx, round.cy};
        control->control->SetBorderRound(sz);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API int duilib_control_get_border_style(duilib_control_t control) {
    if (!control || !control->control) return 0;

    try {
        return control->control->GetBorderStyle();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_border_style(duilib_control_t control, int style) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetBorderStyle(style);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_size_t duilib_control_estimate_size(duilib_control_t control, duilib_size_t available) {
    duilib_size_t size = {0, 0};
    if (!control || !control->control) return size;

    try {
        SIZE avail = {available.cx, available.cy};
        SIZE sz = control->control->EstimateSize(avail);
        size.cx = sz.cx;
        size.cy = sz.cy;
    } catch (...) {
    }
    return size;
}

// Additional missing implementations...

DUILIB_C_API duilib_result_t duilib_control_add_custom_attribute(duilib_control_t control, const char* name, const char* value) {
    if (!control || !control->control || !name) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->AddCustomAttribute(from_cstring(name), from_cstring(value ? value : ""));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API const char* duilib_control_get_custom_attribute(duilib_control_t control, const char* name) {
    if (!control || !control->control || !name) return nullptr;

    try {
        return to_cstring(control->control->GetCustomAttribute(from_cstring(name)));
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_control_remove_custom_attribute(duilib_control_t control, const char* name) {
    if (!control || !control->control || !name) return DUILIB_ERROR_INVALID_PARAM;

    try {
        bool result = control->control->RemoveCustomAttribute(from_cstring(name));
        return result ? DUILIB_OK : DUILIB_ERROR_UNKNOWN;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_remove_all_custom_attributes(duilib_control_t control) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->RemoveAllCustomAttribute();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API bool duilib_control_is_color_hsl(duilib_control_t control) {
    if (!control || !control->control) return false;

    try {
        return control->control->IsColorHSL();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_color_hsl(duilib_control_t control, bool hsl) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetColorHSL(hsl);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API const char* duilib_control_get_virtual_wnd(duilib_control_t control) {
    if (!control || !control->control) return nullptr;

    try {
        return to_cstring(control->control->GetVirtualWnd());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_virtual_wnd(duilib_control_t control, const char* virtual_wnd) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetVirtualWnd(from_cstring(virtual_wnd ? virtual_wnd : ""));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API bool duilib_control_activate(duilib_control_t control) {
    if (!control || !control->control) return false;

    try {
        return control->control->Activate();
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_control_init(duilib_control_t control) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->Init();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_do_init(duilib_control_t control) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->DoInit();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API const char* duilib_control_get_attribute_list(duilib_control_t control, bool ignore_default) {
    if (!control || !control->control) return nullptr;

    try {
        return to_cstring(control->control->GetAttributeList(ignore_default));
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_attribute_list(duilib_control_t control, const char* attr_list) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetAttributeList(from_cstring(attr_list ? attr_list : ""));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

// Additional CControlUI methods implementation...

DUILIB_C_API duilib_manager_t duilib_control_get_manager(duilib_control_t control) {
    if (!control || !control->control) return nullptr;

    try {
        CPaintManagerUI* pm = control->control->GetManager();
        if (pm) {
            // Find existing wrapper
            for (auto& pair : g_managers) {
                if (pair.second == pm) {
                    return pair.first;
                }
            }
        }
        return nullptr;
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_manager(duilib_control_t control, duilib_manager_t manager, duilib_control_t parent, bool init) {
    if (!control || !control->control || !manager || !manager->paint_manager) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetManager(manager->paint_manager, parent ? parent->control : nullptr, init);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_intern_visible(duilib_control_t control, bool visible) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetInternVisible(visible);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_need_parent_update(duilib_control_t control) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->NeedParentUpdate();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API uint32_t duilib_control_get_adjust_color(duilib_control_t control, uint32_t color) {
    if (!control || !control->control) return color;

    try {
        return control->control->GetAdjustColor(color);
    } catch (...) {
        return color;
    }
}

DUILIB_C_API duilib_float_percent_t duilib_control_get_float_percent(duilib_control_t control) {
    duilib_float_percent_t percent = {0};
    if (!control || !control->control) return percent;

    try {
        TPercentInfo info = control->control->GetFloatPercent();
        percent.left = info.left;
        percent.top = info.top;
        percent.right = info.right;
        percent.bottom = info.bottom;
    } catch (...) {
    }
    return percent;
}

DUILIB_C_API duilib_result_t duilib_control_set_float_percent(duilib_control_t control, duilib_float_percent_t percent) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        TPercentInfo info;
        info.left = percent.left;
        info.top = percent.top;
        info.right = percent.right;
        info.bottom = percent.bottom;
        control->control->SetFloatPercent(info);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

// Paint methods (these might need adjustment based on actual duilib implementation)

DUILIB_C_API duilib_result_t duilib_control_paint(duilib_control_t control, void* hdc, duilib_rect_t paint_rect, duilib_control_t stop_control) {
    if (!control || !control->control || !hdc) return DUILIB_ERROR_INVALID_PARAM;

    try {
        RECT rc = {paint_rect.left, paint_rect.top, paint_rect.right, paint_rect.bottom};
        control->control->Paint((HDC)hdc, rc, stop_control ? stop_control->control : nullptr);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_do_paint(duilib_control_t control, void* hdc, duilib_rect_t paint_rect, duilib_control_t stop_control) {
    if (!control || !control->control || !hdc) return DUILIB_ERROR_INVALID_PARAM;

    try {
        RECT rc = {paint_rect.left, paint_rect.top, paint_rect.right, paint_rect.bottom};
        control->control->DoPaint((HDC)hdc, rc, stop_control ? stop_control->control : nullptr);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_paint_bk_color(duilib_control_t control, void* hdc) {
    if (!control || !control->control || !hdc) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->PaintBkColor((HDC)hdc);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_paint_bk_image(duilib_control_t control, void* hdc) {
    if (!control || !control->control || !hdc) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->PaintBkImage((HDC)hdc);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_paint_status_image(duilib_control_t control, void* hdc) {
    if (!control || !control->control || !hdc) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->PaintStatusImage((HDC)hdc);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_paint_text(duilib_control_t control, void* hdc) {
    if (!control || !control->control || !hdc) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->PaintText((HDC)hdc);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_paint_border(duilib_control_t control, void* hdc) {
    if (!control || !control->control || !hdc) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->PaintBorder((HDC)hdc);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_do_post_paint(duilib_control_t control, void* hdc, duilib_rect_t paint_rect) {
    if (!control || !control->control || !hdc) return DUILIB_ERROR_INVALID_PARAM;

    try {
        RECT rc = {paint_rect.left, paint_rect.top, paint_rect.right, paint_rect.bottom};
        control->control->DoPostPaint((HDC)hdc, rc);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_draw_image(duilib_control_t control, void* hdc, const char* image_name) {
    if (!control || !control->control || !hdc || !image_name) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->DrawImage((HDC)hdc, from_cstring(image_name));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

// Layout attribute setters

DUILIB_C_API duilib_result_t duilib_control_set_fixed_width(duilib_control_t control, int width) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetFixedWidth(width);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_fixed_height(duilib_control_t control, int height) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetFixedHeight(height);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_min_width(duilib_control_t control, int min_width) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetMinWidth(min_width);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_min_height(duilib_control_t control, int min_height) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetMinHeight(min_height);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_max_width(duilib_control_t control, int max_width) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetMaxWidth(max_width);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_control_set_max_height(duilib_control_t control, int max_height) {
    if (!control || !control->control) return DUILIB_ERROR_INVALID_PARAM;

    try {
        control->control->SetMaxHeight(max_height);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}