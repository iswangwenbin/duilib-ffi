#include "duilib_c_wndshadow.h"
#include "../../duilib/DuiLib/Utils/WndShadow.h"
#include <new>
#include <map>

using namespace DuiLib;

//=============================================================================
// Internal wrapper structures
//=============================================================================

struct duilib_wndshadow {
    CWndShadow impl;
};

struct duilib_shadow_manager {
    std::map<HWND, duilib_wndshadow_t> shadow_map;
};

// Global shadow manager instance
static duilib_shadow_manager* g_global_shadow_manager = nullptr;

//=============================================================================
// Helper functions
//=============================================================================

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

static duilib_point_t ConvertPoint(LONG x, LONG y) {
    duilib_point_t result;
    result.x = x;
    result.y = y;
    return result;
}

static duilib_color_t ConvertColor(COLORREF color) {
    duilib_color_t result;
    result.r = GetRValue(color);
    result.g = GetGValue(color);
    result.b = GetBValue(color);
    result.a = 255; // Default alpha
    return result;
}

static COLORREF ConvertColor(const duilib_color_t& color) {
    return RGB(color.r, color.g, color.b);
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

//=============================================================================
// WindowShadow basic API implementation
//=============================================================================

DUILIB_C_API duilib_wndshadow_t duilib_wndshadow_create(void) {
    return new(std::nothrow) duilib_wndshadow();
}

DUILIB_C_API void duilib_wndshadow_destroy(duilib_wndshadow_t shadow) {
    delete shadow;
}

DUILIB_C_API bool duilib_wndshadow_is_valid(duilib_wndshadow_t shadow) {
    return shadow != nullptr;
}

//=============================================================================
// WindowShadow static initialization
//=============================================================================

DUILIB_C_API bool duilib_wndshadow_initialize(void* hinstance) {
    return CWndShadow::Initialize((HINSTANCE)hinstance) != FALSE;
}

//=============================================================================
// WindowShadow core methods
//=============================================================================

DUILIB_C_API void* duilib_wndshadow_get_hwnd(duilib_wndshadow_t shadow) {
    return shadow ? shadow->impl.GetHWnd() : nullptr;
}

DUILIB_C_API duilib_result_t duilib_wndshadow_create_shadow(duilib_wndshadow_t shadow, void* parent_hwnd) {
    if (!shadow || !parent_hwnd) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    bool result = shadow->impl.Create((HWND)parent_hwnd);
    return result ? DUILIB_RESULT_OK : DUILIB_RESULT_ERROR;
}

//=============================================================================
// WindowShadow image configuration
//=============================================================================

DUILIB_C_API bool duilib_wndshadow_set_image(duilib_wndshadow_t shadow, const char* image, duilib_rect_t corner, duilib_rect_t hole_offset) {
    if (!shadow || !image) return false;
    
    CDuiString image_str = ConvertUTF8ToString(image);
    RECT corner_rect = ConvertRect(corner);
    RECT hole_rect = ConvertRect(hole_offset);
    
    return shadow->impl.SetImage(image_str.GetData(), corner_rect, hole_rect);
}

//=============================================================================
// WindowShadow color configuration
//=============================================================================

DUILIB_C_API bool duilib_wndshadow_set_size(duilib_wndshadow_t shadow, int size) {
    if (!shadow) return false;
    shadow->impl.SetSize(size);
    return true;
}

DUILIB_C_API bool duilib_wndshadow_set_sharpness(duilib_wndshadow_t shadow, unsigned int sharpness) {
    if (!shadow) return false;
    shadow->impl.SetSharpness(sharpness);
    return true;
}

DUILIB_C_API bool duilib_wndshadow_set_darkness(duilib_wndshadow_t shadow, unsigned int darkness) {
    if (!shadow) return false;
    shadow->impl.SetDarkness(darkness);
    return true;
}

DUILIB_C_API bool duilib_wndshadow_set_position(duilib_wndshadow_t shadow, int x_offset, int y_offset) {
    if (!shadow) return false;
    shadow->impl.SetPosition(x_offset, y_offset);
    return true;
}

DUILIB_C_API bool duilib_wndshadow_set_color(duilib_wndshadow_t shadow, duilib_color_t color) {
    if (!shadow) return false;
    shadow->impl.SetColor(ConvertColor(color));
    return true;
}

//=============================================================================
// WindowShadow status management
//=============================================================================

DUILIB_C_API unsigned char duilib_wndshadow_get_status(duilib_wndshadow_t shadow) {
    if (!shadow) return 0;
    return shadow->impl.GetStatus();
}

DUILIB_C_API bool duilib_wndshadow_is_enabled(duilib_wndshadow_t shadow) {
    if (!shadow) return false;
    return (shadow->impl.GetStatus() & DUILIB_SHADOW_STATUS_ENABLED) != 0;
}

DUILIB_C_API bool duilib_wndshadow_is_visible(duilib_wndshadow_t shadow) {
    if (!shadow) return false;
    return (shadow->impl.GetStatus() & DUILIB_SHADOW_STATUS_VISIBLE) != 0;
}

DUILIB_C_API bool duilib_wndshadow_is_parent_visible(duilib_wndshadow_t shadow) {
    if (!shadow) return false;
    return (shadow->impl.GetStatus() & DUILIB_SHADOW_STATUS_PARENT_VISIBLE) != 0;
}

DUILIB_C_API duilib_result_t duilib_wndshadow_set_enabled(duilib_wndshadow_t shadow, bool enabled) {
    if (!shadow) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    if (enabled) {
        shadow->impl.RestoreParent();
    } else {
        // There's no direct disable method in CWndShadow, but we can hide it
        shadow->impl.Show(false);
    }
    
    return DUILIB_RESULT_OK;
}

//=============================================================================
// WindowShadow property getters
//=============================================================================

DUILIB_C_API int duilib_wndshadow_get_size(duilib_wndshadow_t shadow) {
    return shadow ? shadow->impl.GetSize() : 0;
}

DUILIB_C_API unsigned int duilib_wndshadow_get_sharpness(duilib_wndshadow_t shadow) {
    return shadow ? shadow->impl.GetSharpness() : 0;
}

DUILIB_C_API unsigned int duilib_wndshadow_get_darkness(duilib_wndshadow_t shadow) {
    return shadow ? shadow->impl.GetDarkness() : 0;
}

DUILIB_C_API duilib_point_t duilib_wndshadow_get_position(duilib_wndshadow_t shadow) {
    if (!shadow) return ConvertPoint(0, 0);
    
    CPoint pos = shadow->impl.GetPosition();
    return ConvertPoint(pos.x, pos.y);
}

DUILIB_C_API duilib_color_t duilib_wndshadow_get_color(duilib_wndshadow_t shadow) {
    if (!shadow) return ConvertColor(RGB(0, 0, 0));
    
    return ConvertColor(shadow->impl.GetColor());
}

//=============================================================================
// WindowShadow update and drawing
//=============================================================================

DUILIB_C_API duilib_result_t duilib_wndshadow_update(duilib_wndshadow_t shadow, void* parent_hwnd) {
    if (!shadow) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    if (parent_hwnd) {
        shadow->impl.Update((HWND)parent_hwnd);
    } else {
        // Use the existing parent if no new parent specified
        HWND hwnd = shadow->impl.GetHWnd();
        if (hwnd) {
            HWND parent = GetParent(hwnd);
            if (parent) {
                shadow->impl.Update(parent);
            }
        }
    }
    
    return DUILIB_RESULT_OK;
}

DUILIB_C_API duilib_result_t duilib_wndshadow_invalidate(duilib_wndshadow_t shadow) {
    if (!shadow) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    HWND hwnd = shadow->impl.GetHWnd();
    if (hwnd) {
        InvalidateRect(hwnd, nullptr, TRUE);
    }
    
    return DUILIB_RESULT_OK;
}

//=============================================================================
// WindowShadow helper functions
//=============================================================================

DUILIB_C_API duilib_result_t duilib_wndshadow_show(duilib_wndshadow_t shadow, bool show) {
    if (!shadow) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    shadow->impl.Show(show);
    return DUILIB_RESULT_OK;
}

DUILIB_C_API duilib_result_t duilib_wndshadow_move_window(duilib_wndshadow_t shadow, duilib_rect_t rect, bool repaint) {
    if (!shadow) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    RECT win_rect = ConvertRect(rect);
    HWND hwnd = shadow->impl.GetHWnd();
    if (hwnd) {
        MoveWindow(hwnd, win_rect.left, win_rect.top, 
                   win_rect.right - win_rect.left, 
                   win_rect.bottom - win_rect.top, 
                   repaint ? TRUE : FALSE);
    }
    
    return DUILIB_RESULT_OK;
}

DUILIB_C_API duilib_result_t duilib_wndshadow_set_window_pos(duilib_wndshadow_t shadow, void* hwnd_insert_after, duilib_rect_t rect, unsigned int flags) {
    if (!shadow) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    HWND hwnd = shadow->impl.GetHWnd();
    if (hwnd) {
        RECT win_rect = ConvertRect(rect);
        SetWindowPos(hwnd, (HWND)hwnd_insert_after, 
                     win_rect.left, win_rect.top,
                     win_rect.right - win_rect.left,
                     win_rect.bottom - win_rect.top,
                     flags);
    }
    
    return DUILIB_RESULT_OK;
}

//=============================================================================
// Preset shadow configurations
//=============================================================================

DUILIB_C_API duilib_result_t duilib_wndshadow_apply_config(duilib_wndshadow_t shadow, const duilib_shadow_config_t* config) {
    if (!shadow || !config) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        // Apply color-based configuration
        if (config->size > 0) {
            shadow->impl.SetSize(config->size);
        }
        
        shadow->impl.SetSharpness(config->sharpness);
        shadow->impl.SetDarkness(config->darkness);
        shadow->impl.SetPosition(config->x_offset, config->y_offset);
        shadow->impl.SetColor(ConvertColor(config->color));
        
        // Apply image-based configuration if image is provided
        if (config->image && strlen(config->image) > 0) {
            CDuiString image_str = ConvertUTF8ToString(config->image);
            RECT corner_rect = ConvertRect(config->corner);
            RECT hole_rect = ConvertRect(config->hole_offset);
            
            shadow->impl.SetImage(image_str.GetData(), corner_rect, hole_rect);
        }
        
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_result_t duilib_wndshadow_get_config(duilib_wndshadow_t shadow, duilib_shadow_config_t* config) {
    if (!shadow || !config) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        memset(config, 0, sizeof(duilib_shadow_config_t));
        
        config->size = shadow->impl.GetSize();
        config->sharpness = shadow->impl.GetSharpness();
        config->darkness = shadow->impl.GetDarkness();
        
        CPoint pos = shadow->impl.GetPosition();
        config->x_offset = pos.x;
        config->y_offset = pos.y;
        
        config->color = ConvertColor(shadow->impl.GetColor());
        
        // Note: Image and rect information cannot be retrieved from CWndShadow
        config->image = nullptr;
        memset(&config->corner, 0, sizeof(duilib_rect_t));
        memset(&config->hole_offset, 0, sizeof(duilib_rect_t));
        
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

//=============================================================================
// Common shadow presets
//=============================================================================

DUILIB_C_API duilib_shadow_config_t duilib_shadow_config_default(void) {
    duilib_shadow_config_t config;
    memset(&config, 0, sizeof(config));
    
    config.size = 5;
    config.sharpness = 20;
    config.darkness = 150;
    config.x_offset = 0;
    config.y_offset = 0;
    config.color.r = 0;
    config.color.g = 0;
    config.color.b = 0;
    config.color.a = 255;
    config.image = nullptr;
    
    return config;
}

DUILIB_C_API duilib_shadow_config_t duilib_shadow_config_simple(int size, duilib_color_t color) {
    duilib_shadow_config_t config;
    memset(&config, 0, sizeof(config));
    
    config.size = size;
    config.sharpness = 20;
    config.darkness = 150;
    config.x_offset = 0;
    config.y_offset = 0;
    config.color = color;
    config.image = nullptr;
    
    return config;
}

DUILIB_C_API duilib_shadow_config_t duilib_shadow_config_soft(int size, unsigned int darkness) {
    duilib_shadow_config_t config;
    memset(&config, 0, sizeof(config));
    
    config.size = size;
    config.sharpness = 50; // More blur for soft shadow
    config.darkness = darkness;
    config.x_offset = 0;
    config.y_offset = 0;
    config.color.r = 0;
    config.color.g = 0;
    config.color.b = 0;
    config.color.a = 255;
    config.image = nullptr;
    
    return config;
}

DUILIB_C_API duilib_shadow_config_t duilib_shadow_config_hard(int size, duilib_color_t color, int x_offset, int y_offset) {
    duilib_shadow_config_t config;
    memset(&config, 0, sizeof(config));
    
    config.size = size;
    config.sharpness = 5; // Less blur for hard shadow
    config.darkness = 200;
    config.x_offset = x_offset;
    config.y_offset = y_offset;
    config.color = color;
    config.image = nullptr;
    
    return config;
}

DUILIB_C_API duilib_shadow_config_t duilib_shadow_config_image(const char* image, duilib_rect_t corner, duilib_rect_t hole_offset) {
    duilib_shadow_config_t config;
    memset(&config, 0, sizeof(config));
    
    config.size = 0; // Size is determined by image
    config.sharpness = 0;
    config.darkness = 0;
    config.x_offset = 0;
    config.y_offset = 0;
    config.color.r = 0;
    config.color.g = 0;
    config.color.b = 0;
    config.color.a = 255;
    config.image = image;
    config.corner = corner;
    config.hole_offset = hole_offset;
    
    return config;
}

//=============================================================================
// WindowShadow manager implementation
//=============================================================================

DUILIB_C_API duilib_shadow_manager_t duilib_shadow_manager_create(void) {
    return new(std::nothrow) duilib_shadow_manager();
}

DUILIB_C_API void duilib_shadow_manager_destroy(duilib_shadow_manager_t manager) {
    if (manager == g_global_shadow_manager) {
        g_global_shadow_manager = nullptr;
    }
    
    if (manager) {
        // Clean up all shadows
        for (auto& pair : manager->shadow_map) {
            duilib_wndshadow_destroy(pair.second);
        }
        manager->shadow_map.clear();
        delete manager;
    }
}

DUILIB_C_API duilib_wndshadow_t duilib_shadow_manager_add_shadow(duilib_shadow_manager_t manager, void* hwnd, const duilib_shadow_config_t* config) {
    if (!manager || !hwnd) return nullptr;
    
    // Check if shadow already exists for this window
    HWND window = (HWND)hwnd;
    auto it = manager->shadow_map.find(window);
    if (it != manager->shadow_map.end()) {
        return it->second; // Return existing shadow
    }
    
    // Create new shadow
    duilib_wndshadow_t shadow = duilib_wndshadow_create();
    if (!shadow) return nullptr;
    
    // Create shadow window
    if (duilib_wndshadow_create_shadow(shadow, hwnd) != DUILIB_RESULT_OK) {
        duilib_wndshadow_destroy(shadow);
        return nullptr;
    }
    
    // Apply configuration if provided
    if (config) {
        if (duilib_wndshadow_apply_config(shadow, config) != DUILIB_RESULT_OK) {
            duilib_wndshadow_destroy(shadow);
            return nullptr;
        }
    }
    
    // Store in map
    manager->shadow_map[window] = shadow;
    return shadow;
}

DUILIB_C_API duilib_result_t duilib_shadow_manager_remove_shadow(duilib_shadow_manager_t manager, void* hwnd) {
    if (!manager || !hwnd) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    HWND window = (HWND)hwnd;
    auto it = manager->shadow_map.find(window);
    if (it != manager->shadow_map.end()) {
        duilib_wndshadow_destroy(it->second);
        manager->shadow_map.erase(it);
        return DUILIB_RESULT_OK;
    }
    
    return DUILIB_RESULT_ERROR_NOT_FOUND;
}

DUILIB_C_API duilib_wndshadow_t duilib_shadow_manager_get_shadow(duilib_shadow_manager_t manager, void* hwnd) {
    if (!manager || !hwnd) return nullptr;
    
    HWND window = (HWND)hwnd;
    auto it = manager->shadow_map.find(window);
    return it != manager->shadow_map.end() ? it->second : nullptr;
}

DUILIB_C_API duilib_result_t duilib_shadow_manager_update_all(duilib_shadow_manager_t manager) {
    if (!manager) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        for (auto& pair : manager->shadow_map) {
            duilib_wndshadow_update(pair.second, pair.first);
        }
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_result_t duilib_shadow_manager_show_all(duilib_shadow_manager_t manager, bool show) {
    if (!manager) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
        for (auto& pair : manager->shadow_map) {
            duilib_wndshadow_show(pair.second, show);
        }
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR;
    }
}

DUILIB_C_API duilib_shadow_manager_t duilib_get_global_shadow_manager(void) {
    if (!g_global_shadow_manager) {
        g_global_shadow_manager = new(std::nothrow) duilib_shadow_manager();
    }
    return g_global_shadow_manager;
}