#ifndef __DUILIB_C_RENDER_H__
#define __DUILIB_C_RENDER_H__

#include "duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 渲染引擎API - 对应 CRenderEngine
//=============================================================================

// 渲染引擎静态方法 - 基础绘制
DUILIB_C_API duilib_result_t duilib_render_draw_color(void* hdc, duilib_rect_t rect, duilib_color_t color);
DUILIB_C_API duilib_result_t duilib_render_draw_gradient(void* hdc, duilib_rect_t rect, duilib_color_t color1, duilib_color_t color2, bool vertical, int steps);
DUILIB_C_API duilib_result_t duilib_render_draw_line(void* hdc, duilib_rect_t rect, int size, duilib_color_t color, int style);
DUILIB_C_API duilib_result_t duilib_render_draw_rect(void* hdc, duilib_rect_t rect, int size, duilib_color_t color);
DUILIB_C_API duilib_result_t duilib_render_draw_round_rect(void* hdc, duilib_rect_t rect, int width, int height, int size, duilib_color_t color);

// 渲染引擎静态方法 - 文本绘制
DUILIB_C_API duilib_result_t duilib_render_draw_text(void* hdc, duilib_manager_t manager, duilib_rect_t rect, const char* text, duilib_color_t color, int font, uint32_t style);
DUILIB_C_API duilib_result_t duilib_render_draw_html_text(void* hdc, duilib_manager_t manager, duilib_rect_t rect, const char* html_text, duilib_color_t color, const char** links, const char** link_fonts, int* link_font_colors, duilib_rect_t* link_rects, int link_count, uint32_t style);

// 渲染引擎静态方法 - 图像绘制
DUILIB_C_API duilib_result_t duilib_render_draw_image(void* hdc, void* bitmap, duilib_rect_t dest, duilib_rect_t src, duilib_rect_t corner, duilib_rect_t mask, uint8_t alpha, bool hole, bool xtiled, bool ytiled);
DUILIB_C_API duilib_result_t duilib_render_draw_image_string(void* hdc, duilib_manager_t manager, duilib_rect_t rect, duilib_rect_t paint_rect, const char* image_name, const char* restype, duilib_rect_t mask);

// 渲染引擎静态方法 - 图像缓存
DUILIB_C_API void* duilib_render_load_image(const char* bitmap, const char* type, duilib_color_t mask);
DUILIB_C_API void duilib_render_free_image(void* bitmap);

// 渲染引擎静态方法 - 工具函数
DUILIB_C_API uint32_t duilib_render_adjust_color(uint32_t color, short h, short s, short l);
DUILIB_C_API void* duilib_render_create_round_rect_rgn(int left, int top, int right, int bottom, int width, int height);

//=============================================================================
// 渲染裁剪API - 对应 CRenderClip
//=============================================================================

// 渲染裁剪结构体 - 对应 CRenderClip
typedef struct duilib_render_clip* duilib_render_clip_t;

// 裁剪结构信息
typedef struct {
    duilib_rect_t item;      // 项目矩形
    void* hdc;              // 设备上下文
    void* rgn;              // 区域句柄
    void* old_rgn;          // 旧区域句柄  
} duilib_clip_info_t;

// 创建和销毁渲染裁剪
DUILIB_C_API duilib_render_clip_t duilib_render_clip_create(void);
DUILIB_C_API void duilib_render_clip_destroy(duilib_render_clip_t clip);

// 生成裁剪区域
DUILIB_C_API duilib_result_t duilib_render_clip_generate_clip(void* hdc, duilib_rect_t rc, duilib_render_clip_t clip);
DUILIB_C_API duilib_result_t duilib_render_clip_generate_round_clip(void* hdc, duilib_rect_t rc, duilib_rect_t item, int width, int height, duilib_render_clip_t clip);

// 使用旧裁剪区域
DUILIB_C_API duilib_result_t duilib_render_clip_use_old_clip_begin(void* hdc, duilib_render_clip_t clip);
DUILIB_C_API duilib_result_t duilib_render_clip_use_old_clip_end(void* hdc, duilib_render_clip_t clip);

// 获取裁剪信息
DUILIB_C_API const duilib_clip_info_t* duilib_render_clip_get_info(duilib_render_clip_t clip);

//=============================================================================
// CRenderEngine 缺失方法补充
//=============================================================================

// 高级位图操作
DUILIB_C_API void* duilib_render_create_argb32_bitmap(void* hdc, int cx, int cy, void** bits);
DUILIB_C_API duilib_result_t duilib_render_adjust_image(bool use_hsl, const duilib_image_info_t* image, short h, short s, short l);

// 位图生成
DUILIB_C_API void* duilib_render_generate_bitmap(duilib_manager_t manager, duilib_rect_t rc, duilib_control_t stop_control, uint32_t filter_color);
DUILIB_C_API void* duilib_render_generate_control_bitmap(duilib_manager_t manager, duilib_control_t control, duilib_rect_t rc, uint32_t filter_color);

// 文本尺寸计算
DUILIB_C_API duilib_size_t duilib_render_get_text_size(void* hdc, duilib_manager_t manager, const char* text, int font, uint32_t style);

// 高级绘制方法
DUILIB_C_API bool duilib_render_draw_image_with_manager(void* hdc, duilib_manager_t manager, duilib_rect_t item, duilib_rect_t paint, const char* image_name, const char* res_type, duilib_rect_t mask);

//=============================================================================
// CRenderEngine 剩余缺失方法补充 - 完整1:1对应
//=============================================================================

// 完整的DrawImage方法 - 对应原始重载版本
DUILIB_C_API duilib_result_t duilib_render_draw_image_full(void* hdc, void* bitmap, duilib_rect_t dest_rect, duilib_rect_t paint_rect, duilib_rect_t bmp_part_rect, duilib_rect_t scale9_rect, bool alpha_channel, uint8_t fade, bool hole, bool xtiled, bool ytiled);

// 绘制信息结构体版本的绘制
DUILIB_C_API bool duilib_render_draw_image_with_draw_info(void* hdc, duilib_manager_t manager, const duilib_draw_info_t* draw_info);

// 图像加载重载版本 - STRINGorID支持
DUILIB_C_API const duilib_image_info_t* duilib_render_load_image_string_or_id(void* string_or_id, const char* type, uint32_t mask);
DUILIB_C_API duilib_result_t duilib_render_free_image_with_delete(const duilib_image_info_t* image, bool delete_image);

// 圆角矩形区域创建
DUILIB_C_API void* duilib_render_create_round_rect_region(duilib_rect_t rect, int width, int height);

//=============================================================================
// CRenderClip 剩余缺失方法补充 - 完整1:1对应
//=============================================================================

// CRenderClip构造函数和析构函数对应的初始化清理方法
DUILIB_C_API duilib_result_t duilib_render_clip_init(duilib_render_clip_t clip, duilib_rect_t item, void* hdc, void* rgn, void* old_rgn);
DUILIB_C_API duilib_result_t duilib_render_clip_cleanup(duilib_render_clip_t clip);

// 静态方法的实例版本
DUILIB_C_API duilib_result_t duilib_render_clip_generate_clip_rect(duilib_render_clip_t clip, void* hdc, duilib_rect_t rect);
DUILIB_C_API duilib_result_t duilib_render_clip_generate_round_clip_rect(duilib_render_clip_t clip, void* hdc, duilib_rect_t rect, duilib_rect_t item, int width, int height);

// 裁剪区域状态查询
DUILIB_C_API bool duilib_render_clip_has_clip(duilib_render_clip_t clip);
DUILIB_C_API bool duilib_render_clip_has_old_clip(duilib_render_clip_t clip);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_RENDER_H__