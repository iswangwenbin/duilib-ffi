#ifndef DUILIB_C_TEXT_H
#define DUILIB_C_TEXT_H

#include "../duilib_c_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// Text control handle
typedef struct duilib_text_impl* duilib_text_t;

// Create and destroy functions
DUILIB_C_API duilib_text_t duilib_text_create();
DUILIB_C_API duilib_result_t duilib_text_destroy(duilib_text_t text);

// Type conversion functions
DUILIB_C_API duilib_control_t duilib_text_to_control(duilib_text_t text);
DUILIB_C_API duilib_label_t duilib_text_to_label(duilib_text_t text);
DUILIB_C_API duilib_text_t duilib_text_from_control(duilib_control_t control);

// CTextUI specific methods
DUILIB_C_API const char* duilib_text_get_class(duilib_text_t text);
DUILIB_C_API unsigned int duilib_text_get_control_flags(duilib_text_t text);
DUILIB_C_API void* duilib_text_get_interface(duilib_text_t text, const char* name);

// Link management functions
DUILIB_C_API char* duilib_text_get_link_content(duilib_text_t text, int index);

// Event handling
DUILIB_C_API duilib_result_t duilib_text_do_event(duilib_text_t text, duilib_event_t event);

// Painting
DUILIB_C_API duilib_result_t duilib_text_paint_text(duilib_text_t text, void* hdc);

// Inherited CLabelUI methods
DUILIB_C_API duilib_result_t duilib_text_set_text_style(duilib_text_t text, unsigned int style);
DUILIB_C_API unsigned int duilib_text_get_text_style(duilib_text_t text);
DUILIB_C_API bool duilib_text_is_multi_line(duilib_text_t text);
DUILIB_C_API duilib_result_t duilib_text_set_multi_line(duilib_text_t text, bool multi_line);
DUILIB_C_API duilib_result_t duilib_text_set_text_color(duilib_text_t text, unsigned long color);
DUILIB_C_API unsigned long duilib_text_get_text_color(duilib_text_t text);
DUILIB_C_API duilib_result_t duilib_text_set_disabled_text_color(duilib_text_t text, unsigned long color);
DUILIB_C_API unsigned long duilib_text_get_disabled_text_color(duilib_text_t text);
DUILIB_C_API duilib_result_t duilib_text_set_font(duilib_text_t text, int index);
DUILIB_C_API int duilib_text_get_font(duilib_text_t text);
DUILIB_C_API duilib_rect_t duilib_text_get_text_padding(duilib_text_t text);
DUILIB_C_API duilib_result_t duilib_text_set_text_padding(duilib_text_t text, duilib_rect_t padding);
DUILIB_C_API bool duilib_text_is_show_html(duilib_text_t text);
DUILIB_C_API duilib_result_t duilib_text_set_show_html(duilib_text_t text, bool show_html);

// Inherited CControlUI methods
DUILIB_C_API char* duilib_text_get_name(duilib_text_t text);
DUILIB_C_API duilib_result_t duilib_text_set_name(duilib_text_t text, const char* name);
DUILIB_C_API char* duilib_text_get_text(duilib_text_t text);
DUILIB_C_API duilib_result_t duilib_text_set_text(duilib_text_t text, const char* text_content);
DUILIB_C_API bool duilib_text_is_visible(duilib_text_t text);
DUILIB_C_API duilib_result_t duilib_text_set_visible(duilib_text_t text, bool visible);
DUILIB_C_API bool duilib_text_is_enabled(duilib_text_t text);
DUILIB_C_API duilib_result_t duilib_text_set_enabled(duilib_text_t text, bool enabled);
DUILIB_C_API duilib_rect_t duilib_text_get_pos(duilib_text_t text);
DUILIB_C_API duilib_result_t duilib_text_set_pos(duilib_text_t text, duilib_rect_t pos, bool need_invalidate);
DUILIB_C_API duilib_size_t duilib_text_estimate_size(duilib_text_t text, duilib_size_t available);
DUILIB_C_API char* duilib_text_get_attribute(duilib_text_t text, const char* name);
DUILIB_C_API duilib_result_t duilib_text_set_attribute(duilib_text_t text, const char* name, const char* value);

#ifdef __cplusplus
}
#endif

#endif // DUILIB_C_TEXT_H