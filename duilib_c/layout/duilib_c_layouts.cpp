#include "duilib_c_layouts.h"
#include "../duilib_c_internal.h"

using namespace DuiLib;

//=============================================================================
// 布局控件包装结构定义
//=============================================================================

struct duilib_verticallayout {
    CVerticalLayoutUI* layout_ui;
};

struct duilib_horizontallayout {
    CHorizontalLayoutUI* layout_ui;
};

struct duilib_tablayout {
    CTabLayoutUI* layout_ui;
};

struct duilib_tilelayout {
    CTileLayoutUI* layout_ui;
};

struct duilib_childlayout {
    CChildLayoutUI* layout_ui;
};

//=============================================================================
// 布局模块全局状态
//=============================================================================

static bool g_layouts_initialized = false;

//=============================================================================
// 布局模块初始化和清理实现
//=============================================================================

DUILIB_C_API duilib_result_t duilib_layouts_initialize(void) {
    if (!g_initialized) return DUILIB_ERROR_NOT_INITIALIZED;
    
    try {
        if (g_layouts_initialized) return DUILIB_OK;
        
        // 注册所有布局类到DuiLib
        // 这里可以添加自定义布局的注册代码
        
        g_layouts_initialized = true;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_layouts_cleanup(void) {
    try {
        if (!g_layouts_initialized) return DUILIB_OK;
        
        // 清理布局模块资源
        // 这里可以添加资源清理代码
        
        g_layouts_initialized = false;
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

//=============================================================================
// 布局工厂方法实现
//=============================================================================

DUILIB_C_API duilib_control_t duilib_create_layout_by_class(const char* class_name) {
    if (!g_initialized || !g_layouts_initialized || !class_name) return nullptr;
    
    try {
        CControlUI* control_ui = nullptr;
        std::string class_str = class_name;
        
        if (class_str == "Container") {
            control_ui = new CContainerUI();
        } else if (class_str == "VerticalLayout") {
            control_ui = new CVerticalLayoutUI();
        } else if (class_str == "HorizontalLayout") {
            control_ui = new CHorizontalLayoutUI();
        } else if (class_str == "TabLayout") {
            control_ui = new CTabLayoutUI();
        } else if (class_str == "TileLayout") {
            control_ui = new CTileLayoutUI();
        } else if (class_str == "ChildLayout") {
            control_ui = new CChildLayoutUI();
        } else {
            // 未知布局类型
            return nullptr;
        }
        
        if (!control_ui) return nullptr;
        
        duilib_control_t control = new duilib_control();
        control->control = control_ui;
        return control;
    } catch (...) {
        return nullptr;
    }
}

//=============================================================================
// 布局类型检查实现
//=============================================================================

DUILIB_C_API duilib_layout_type_t duilib_get_layout_type(duilib_control_t control) {
    if (!control || !control->control) return DUILIB_LAYOUT_TYPE_UNKNOWN;
    
    try {
        CDuiString class_name = control->control->GetClass();
        std::string class_str = to_cstring(class_name);
        
        if (class_str == "Container") return DUILIB_LAYOUT_TYPE_CONTAINER;
        if (class_str == "VerticalLayout") return DUILIB_LAYOUT_TYPE_VERTICAL;
        if (class_str == "HorizontalLayout") return DUILIB_LAYOUT_TYPE_HORIZONTAL;
        if (class_str == "TabLayout") return DUILIB_LAYOUT_TYPE_TAB;
        if (class_str == "TileLayout") return DUILIB_LAYOUT_TYPE_TILE;
        if (class_str == "ChildLayout") return DUILIB_LAYOUT_TYPE_CHILD;
        
        return DUILIB_LAYOUT_TYPE_UNKNOWN;
    } catch (...) {
        return DUILIB_LAYOUT_TYPE_UNKNOWN;
    }
}

DUILIB_C_API bool duilib_is_layout_type(duilib_control_t control, duilib_layout_type_t type) {
    return duilib_get_layout_type(control) == type;
}

//=============================================================================
// 布局转换辅助函数实现
//=============================================================================

DUILIB_C_API duilib_verticallayout_t duilib_safe_cast_to_verticallayout(duilib_control_t control) {
    if (!control || !control->control) return nullptr;
    
    try {
        CVerticalLayoutUI* layout_ui = dynamic_cast<CVerticalLayoutUI*>(control->control);
        if (!layout_ui) return nullptr;
        
        duilib_verticallayout_t layout = new duilib_verticallayout();
        layout->layout_ui = layout_ui;
        return layout;
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_horizontallayout_t duilib_safe_cast_to_horizontallayout(duilib_control_t control) {
    if (!control || !control->control) return nullptr;
    
    try {
        CHorizontalLayoutUI* layout_ui = dynamic_cast<CHorizontalLayoutUI*>(control->control);
        if (!layout_ui) return nullptr;
        
        duilib_horizontallayout_t layout = new duilib_horizontallayout();
        layout->layout_ui = layout_ui;
        return layout;
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_tablayout_t duilib_safe_cast_to_tablayout(duilib_control_t control) {
    if (!control || !control->control) return nullptr;
    
    try {
        CTabLayoutUI* layout_ui = dynamic_cast<CTabLayoutUI*>(control->control);
        if (!layout_ui) return nullptr;
        
        duilib_tablayout_t layout = new duilib_tablayout();
        layout->layout_ui = layout_ui;
        return layout;
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_tilelayout_t duilib_safe_cast_to_tilelayout(duilib_control_t control) {
    if (!control || !control->control) return nullptr;
    
    try {
        CTileLayoutUI* layout_ui = dynamic_cast<CTileLayoutUI*>(control->control);
        if (!layout_ui) return nullptr;
        
        duilib_tilelayout_t layout = new duilib_tilelayout();
        layout->layout_ui = layout_ui;
        return layout;
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_childlayout_t duilib_safe_cast_to_childlayout(duilib_control_t control) {
    if (!control || !control->control) return nullptr;
    
    try {
        CChildLayoutUI* layout_ui = dynamic_cast<CChildLayoutUI*>(control->control);
        if (!layout_ui) return nullptr;
        
        duilib_childlayout_t layout = new duilib_childlayout();
        layout->layout_ui = layout_ui;
        return layout;
    } catch (...) {
        return nullptr;
    }
}

//=============================================================================
// 布局通用操作实现
//=============================================================================

DUILIB_C_API duilib_result_t duilib_layout_set_inset(duilib_control_t layout, duilib_rect_t inset) {
    if (!layout || !layout->control) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        CContainerUI* container = dynamic_cast<CContainerUI*>(layout->control);
        if (!container) return DUILIB_ERROR_INVALID_PARAMETER;
        
        RECT rc;
        rc.left = inset.left;
        rc.top = inset.top;
        rc.right = inset.right;
        rc.bottom = inset.bottom;
        container->SetInset(rc);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_rect_t duilib_layout_get_inset(duilib_control_t layout) {
    duilib_rect_t inset = {0, 0, 0, 0};
    
    if (!layout || !layout->control) return inset;
    
    try {
        CContainerUI* container = dynamic_cast<CContainerUI*>(layout->control);
        if (!container) return inset;
        
        RECT rc = container->GetInset();
        inset.left = rc.left;
        inset.top = rc.top;
        inset.right = rc.right;
        inset.bottom = rc.bottom;
        return inset;
    } catch (...) {
        return inset;
    }
}

DUILIB_C_API duilib_result_t duilib_layout_set_child_padding(duilib_control_t layout, int padding) {
    if (!layout || !layout->control) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        CContainerUI* container = dynamic_cast<CContainerUI*>(layout->control);
        if (!container) return DUILIB_ERROR_INVALID_PARAMETER;
        
        container->SetChildPadding(padding);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API int duilib_layout_get_child_padding(duilib_control_t layout) {
    if (!layout || !layout->control) return 0;
    
    try {
        CContainerUI* container = dynamic_cast<CContainerUI*>(layout->control);
        if (!container) return 0;
        
        return container->GetChildPadding();
    } catch (...) {
        return 0;
    }
}

//=============================================================================
// 布局通用子控件管理实现
//=============================================================================

DUILIB_C_API bool duilib_layout_add_control(duilib_control_t layout, duilib_control_t control) {
    if (!layout || !layout->control || !control || !control->control) return false;
    
    try {
        CContainerUI* container = dynamic_cast<CContainerUI*>(layout->control);
        if (!container) return false;
        
        return container->Add(control->control);
    } catch (...) {
        return false;
    }
}

DUILIB_C_API bool duilib_layout_add_control_at(duilib_control_t layout, duilib_control_t control, int index) {
    if (!layout || !layout->control || !control || !control->control) return false;
    
    try {
        CContainerUI* container = dynamic_cast<CContainerUI*>(layout->control);
        if (!container) return false;
        
        return container->AddAt(control->control, index);
    } catch (...) {
        return false;
    }
}

DUILIB_C_API bool duilib_layout_remove_control(duilib_control_t layout, duilib_control_t control, bool do_not_destroy) {
    if (!layout || !layout->control || !control || !control->control) return false;
    
    try {
        CContainerUI* container = dynamic_cast<CContainerUI*>(layout->control);
        if (!container) return false;
        
        return container->Remove(control->control, do_not_destroy);
    } catch (...) {
        return false;
    }
}

DUILIB_C_API bool duilib_layout_remove_control_at(duilib_control_t layout, int index, bool do_not_destroy) {
    if (!layout || !layout->control) return false;
    
    try {
        CContainerUI* container = dynamic_cast<CContainerUI*>(layout->control);
        if (!container) return false;
        
        return container->RemoveAt(index, do_not_destroy);
    } catch (...) {
        return false;
    }
}

DUILIB_C_API duilib_result_t duilib_layout_remove_all_controls(duilib_control_t layout) {
    if (!layout || !layout->control) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        CContainerUI* container = dynamic_cast<CContainerUI*>(layout->control);
        if (!container) return DUILIB_ERROR_INVALID_PARAMETER;
        
        container->RemoveAll();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API int duilib_layout_get_control_count(duilib_control_t layout) {
    if (!layout || !layout->control) return 0;
    
    try {
        CContainerUI* container = dynamic_cast<CContainerUI*>(layout->control);
        if (!container) return 0;
        
        return container->GetCount();
    } catch (...) {
        return 0;
    }
}

DUILIB_C_API duilib_control_t duilib_layout_get_control_at(duilib_control_t layout, int index) {
    if (!layout || !layout->control) return nullptr;
    
    try {
        CContainerUI* container = dynamic_cast<CContainerUI*>(layout->control);
        if (!container) return nullptr;
        
        CControlUI* control_ui = container->GetItemAt(index);
        if (!control_ui) return nullptr;
        
        duilib_control_t control = new duilib_control();
        control->control = control_ui;
        return control;
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API int duilib_layout_get_control_index(duilib_control_t layout, duilib_control_t control) {
    if (!layout || !layout->control || !control || !control->control) return -1;
    
    try {
        CContainerUI* container = dynamic_cast<CContainerUI*>(layout->control);
        if (!container) return -1;
        
        return container->GetItemIndex(control->control);
    } catch (...) {
        return -1;
    }
}

//=============================================================================
// 布局事件回调注册实现（基础框架）
//=============================================================================

DUILIB_C_API duilib_result_t duilib_layout_set_event_callback(duilib_control_t layout, duilib_layout_event_callback_t callback, void* user_data) {
    if (!layout || !layout->control || !callback) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        // 这里需要实现事件回调注册机制
        // 由于DuiLib的事件处理机制比较复杂，这里只提供接口框架
        // 实际实现需要扩展duilib_c_internal.h中的事件处理系统
        
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

//=============================================================================
// 布局辅助功能实现
//=============================================================================

DUILIB_C_API duilib_result_t duilib_layout_auto_size(duilib_control_t layout) {
    if (!layout || !layout->control) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        layout->control->NeedUpdate();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_layout_need_update(duilib_control_t layout) {
    if (!layout || !layout->control) return DUILIB_ERROR_INVALID_PARAMETER;
    
    try {
        layout->control->NeedUpdate();
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_size_t duilib_layout_get_suggested_size(duilib_control_t layout, duilib_size_t available) {
    duilib_size_t size = {0, 0};
    
    if (!layout || !layout->control) return size;
    
    try {
        SIZE sz_available;
        sz_available.cx = available.cx;
        sz_available.cy = available.cy;
        
        SIZE sz_result = layout->control->EstimateSize(sz_available);
        size.cx = sz_result.cx;
        size.cy = sz_result.cy;
        return size;
    } catch (...) {
        return size;
    }
}