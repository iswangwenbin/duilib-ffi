#include "../duilib_c_internal.h"
#include "duilib_c_render.h"

//=============================================================================
// 渲染引擎API实现 - 对应 CRenderEngine
//=============================================================================

DUILIB_C_API duilib_result_t duilib_render_draw_color(void* hdc, duilib_rect_t rect, duilib_color_t color) {
    if (!hdc) return DUILIB_ERROR_INVALID_PARAM;

    try {
        RECT rc = {rect.left, rect.top, rect.right, rect.bottom};
        CRenderEngine::DrawColor(static_cast<HDC>(hdc), rc, color);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_render_draw_gradient(void* hdc, duilib_rect_t rect, duilib_color_t color1, duilib_color_t color2, bool vertical, int steps) {
    if (!hdc) return DUILIB_ERROR_INVALID_PARAM;

    try {
        RECT rc = {rect.left, rect.top, rect.right, rect.bottom};
        CRenderEngine::DrawGradient(static_cast<HDC>(hdc), rc, color1, color2, vertical, steps);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_render_draw_line(void* hdc, duilib_rect_t rect, int size, duilib_color_t color, int style) {
    if (!hdc) return DUILIB_ERROR_INVALID_PARAM;

    try {
        RECT rc = {rect.left, rect.top, rect.right, rect.bottom};
        CRenderEngine::DrawLine(static_cast<HDC>(hdc), rc, size, color, style);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_render_draw_rect(void* hdc, duilib_rect_t rect, int size, duilib_color_t color) {
    if (!hdc) return DUILIB_ERROR_INVALID_PARAM;

    try {
        RECT rc = {rect.left, rect.top, rect.right, rect.bottom};
        CRenderEngine::DrawRect(static_cast<HDC>(hdc), rc, size, color);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_render_draw_round_rect(void* hdc, duilib_rect_t rect, int width, int height, int size, duilib_color_t color) {
    if (!hdc) return DUILIB_ERROR_INVALID_PARAM;

    try {
        RECT rc = {rect.left, rect.top, rect.right, rect.bottom};
        CRenderEngine::DrawRoundRect(static_cast<HDC>(hdc), rc, width, height, size, color);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_render_draw_text(void* hdc, duilib_manager_t manager, duilib_rect_t rect, const char* text, duilib_color_t color, int font, uint32_t style) {
    if (!hdc || !text) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CPaintManagerUI* paint_manager = nullptr;
        if (manager && g_managers.find(manager) != g_managers.end()) {
            paint_manager = g_managers[manager];
        }

        RECT rc = {rect.left, rect.top, rect.right, rect.bottom};
        CRenderEngine::DrawText(static_cast<HDC>(hdc), paint_manager, rc, from_cstring(text), color, font, style);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_render_draw_html_text(void* hdc, duilib_manager_t manager, duilib_rect_t rect, const char* html_text, duilib_color_t color, const char** links, const char** link_fonts, int* link_font_colors, duilib_rect_t* link_rects, int link_count, uint32_t style) {
    if (!hdc || !html_text) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CPaintManagerUI* paint_manager = nullptr;
        if (manager && g_managers.find(manager) != g_managers.end()) {
            paint_manager = g_managers[manager];
        }

        RECT rc = {rect.left, rect.top, rect.right, rect.bottom};
        
        // 转换链接数据结构 - 这里需要根据实际的CRenderEngine::DrawHtmlText接口调整
        // 由于参数较复杂，这里给出基本框架，具体实现需要参考DuiLib源码
        CRenderEngine::DrawText(static_cast<HDC>(hdc), paint_manager, rc, from_cstring(html_text), color, 0, style);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_render_draw_image(void* hdc, void* bitmap, duilib_rect_t dest, duilib_rect_t src, duilib_rect_t corner, duilib_rect_t mask, uint8_t alpha, bool hole, bool xtiled, bool ytiled) {
    if (!hdc) return DUILIB_ERROR_INVALID_PARAM;

    try {
        RECT rcDest = {dest.left, dest.top, dest.right, dest.bottom};
        RECT rcSrc = {src.left, src.top, src.right, src.bottom};
        RECT rcCorner = {corner.left, corner.top, corner.right, corner.bottom};
        RECT rcMask = {mask.left, mask.top, mask.right, mask.bottom};
        
        CRenderEngine::DrawImage(static_cast<HDC>(hdc), static_cast<HBITMAP>(bitmap), rcDest, rcSrc, rcCorner, rcMask, alpha, hole, xtiled, ytiled);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API duilib_result_t duilib_render_draw_image_string(void* hdc, duilib_manager_t manager, duilib_rect_t rect, duilib_rect_t paint_rect, const char* image_name, const char* restype, duilib_rect_t mask) {
    if (!hdc || !image_name) return DUILIB_ERROR_INVALID_PARAM;

    try {
        CPaintManagerUI* paint_manager = nullptr;
        if (manager && g_managers.find(manager) != g_managers.end()) {
            paint_manager = g_managers[manager];
        }

        RECT rc = {rect.left, rect.top, rect.right, rect.bottom};
        RECT rcPaint = {paint_rect.left, paint_rect.top, paint_rect.right, paint_rect.bottom};
        RECT rcMask = {mask.left, mask.top, mask.right, mask.bottom};

        CRenderEngine::DrawImageString(static_cast<HDC>(hdc), paint_manager, rc, rcPaint, 
                                      from_cstring(image_name), 
                                      restype ? from_cstring(restype) : CDuiString(),
                                      rcMask);
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}

DUILIB_C_API void* duilib_render_load_image(const char* bitmap, const char* type, duilib_color_t mask) {
    if (!bitmap) return nullptr;

    try {
        return CRenderEngine::LoadImage(from_cstring(bitmap), 
                                       type ? from_cstring(type) : CDuiString(), 
                                       mask);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API void duilib_render_free_image(void* bitmap) {
    if (bitmap) {
        try {
            CRenderEngine::FreeImage(static_cast<HBITMAP>(bitmap));
        } catch (...) {
            // 忽略异常
        }
    }
}

DUILIB_C_API uint32_t duilib_render_adjust_color(uint32_t color, short h, short s, short l) {
    try {
        return CRenderEngine::AdjustColor(color, h, s, l);
    } catch (...) {
        return color;
    }
}

DUILIB_C_API void* duilib_render_create_round_rect_rgn(int left, int top, int right, int bottom, int width, int height) {
    try {
        return CRenderEngine::CreateRoundRectRgn(left, top, right, bottom, width, height);
    } catch (...) {
        return nullptr;
    }
}