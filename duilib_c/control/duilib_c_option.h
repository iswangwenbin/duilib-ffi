#ifndef DUILIB_C_OPTION_H
#define DUILIB_C_OPTION_H

#include "../duilib_c_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// Option control handle
typedef struct duilib_option_impl* duilib_option_t;

// Create and destroy functions
DUILIB_C_API duilib_option_t duilib_option_create();
DUILIB_C_API duilib_result_t duilib_option_destroy(duilib_option_t option);

// Type conversion functions
DUILIB_C_API duilib_control_t duilib_option_to_control(duilib_option_t option);
DUILIB_C_API duilib_button_t duilib_option_to_button(duilib_option_t option);
DUILIB_C_API duilib_option_t duilib_option_from_control(duilib_control_t control);

// COptionUI specific methods
DUILIB_C_API const char* duilib_option_get_class(duilib_option_t option);
DUILIB_C_API void* duilib_option_get_interface(duilib_option_t option, const char* name);

// Manager and lifecycle
DUILIB_C_API duilib_result_t duilib_option_set_manager(duilib_option_t option, void* manager, duilib_control_t parent, bool init);

// Activation and state
DUILIB_C_API bool duilib_option_activate(duilib_option_t option);
DUILIB_C_API duilib_result_t duilib_option_set_enabled(duilib_option_t option, bool enabled);

// Selected state images
DUILIB_C_API char* duilib_option_get_selected_image(duilib_option_t option);
DUILIB_C_API duilib_result_t duilib_option_set_selected_image(duilib_option_t option, const char* image);
DUILIB_C_API char* duilib_option_get_selected_hot_image(duilib_option_t option);
DUILIB_C_API duilib_result_t duilib_option_set_selected_hot_image(duilib_option_t option, const char* image);

// Selected state colors
DUILIB_C_API duilib_result_t duilib_option_set_selected_text_color(duilib_option_t option, unsigned long color);
DUILIB_C_API unsigned long duilib_option_get_selected_text_color(duilib_option_t option);
DUILIB_C_API duilib_result_t duilib_option_set_selected_bk_color(duilib_option_t option, unsigned long color);
DUILIB_C_API unsigned long duilib_option_get_selected_bk_color(duilib_option_t option);

// Foreground image
DUILIB_C_API char* duilib_option_get_fore_image(duilib_option_t option);
DUILIB_C_API duilib_result_t duilib_option_set_fore_image(duilib_option_t option, const char* image);

// Group management
DUILIB_C_API char* duilib_option_get_group(duilib_option_t option);
DUILIB_C_API duilib_result_t duilib_option_set_group(duilib_option_t option, const char* group_name);

// Selection state
DUILIB_C_API bool duilib_option_is_selected(duilib_option_t option);
DUILIB_C_API duilib_result_t duilib_option_set_selected(duilib_option_t option, bool selected, bool trigger_event);

// Layout and rendering
DUILIB_C_API duilib_size_t duilib_option_estimate_size(duilib_option_t option, duilib_size_t available);
DUILIB_C_API duilib_result_t duilib_option_paint_status_image(duilib_option_t option, void* hdc);
DUILIB_C_API duilib_result_t duilib_option_paint_text(duilib_option_t option, void* hdc);

// Inherited CControlUI methods
DUILIB_C_API char* duilib_option_get_name(duilib_option_t option);
DUILIB_C_API duilib_result_t duilib_option_set_name(duilib_option_t option, const char* name);
DUILIB_C_API char* duilib_option_get_text(duilib_option_t option);
DUILIB_C_API duilib_result_t duilib_option_set_text(duilib_option_t option, const char* text_content);
DUILIB_C_API bool duilib_option_is_visible(duilib_option_t option);
DUILIB_C_API duilib_result_t duilib_option_set_visible(duilib_option_t option, bool visible);
DUILIB_C_API bool duilib_option_is_enabled(duilib_option_t option);
DUILIB_C_API duilib_rect_t duilib_option_get_pos(duilib_option_t option);
DUILIB_C_API duilib_result_t duilib_option_set_pos(duilib_option_t option, duilib_rect_t pos, bool need_invalidate);
DUILIB_C_API char* duilib_option_get_attribute(duilib_option_t option, const char* name);
DUILIB_C_API duilib_result_t duilib_option_set_attribute(duilib_option_t option, const char* name, const char* value);

#ifdef __cplusplus
}
#endif

#endif // DUILIB_C_OPTION_H