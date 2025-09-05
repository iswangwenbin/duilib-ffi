#ifndef DUILIB_C_PROGRESS_H
#define DUILIB_C_PROGRESS_H

#include "../duilib_c_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// Progress control handle
typedef struct duilib_progress_impl* duilib_progress_t;

// Create and destroy functions
DUILIB_C_API duilib_progress_t duilib_progress_create();
DUILIB_C_API duilib_result_t duilib_progress_destroy(duilib_progress_t progress);

// Type conversion functions
DUILIB_C_API duilib_control_t duilib_progress_to_control(duilib_progress_t progress);
DUILIB_C_API duilib_label_t duilib_progress_to_label(duilib_progress_t progress);
DUILIB_C_API duilib_progress_t duilib_progress_from_control(duilib_control_t control);

// CProgressUI specific methods
DUILIB_C_API const char* duilib_progress_get_class(duilib_progress_t progress);
DUILIB_C_API void* duilib_progress_get_interface(duilib_progress_t progress, const char* name);

// Orientation
DUILIB_C_API bool duilib_progress_is_horizontal(duilib_progress_t progress);
DUILIB_C_API duilib_result_t duilib_progress_set_horizontal(duilib_progress_t progress, bool horizontal);

// Value range
DUILIB_C_API int duilib_progress_get_min_value(duilib_progress_t progress);
DUILIB_C_API duilib_result_t duilib_progress_set_min_value(duilib_progress_t progress, int min_value);
DUILIB_C_API int duilib_progress_get_max_value(duilib_progress_t progress);
DUILIB_C_API duilib_result_t duilib_progress_set_max_value(duilib_progress_t progress, int max_value);

// Current value
DUILIB_C_API int duilib_progress_get_value(duilib_progress_t progress);
DUILIB_C_API duilib_result_t duilib_progress_set_value(duilib_progress_t progress, int value);

// Foreground image
DUILIB_C_API char* duilib_progress_get_fore_image(duilib_progress_t progress);
DUILIB_C_API duilib_result_t duilib_progress_set_fore_image(duilib_progress_t progress, const char* image);

// Painting
DUILIB_C_API duilib_result_t duilib_progress_paint_status_image(duilib_progress_t progress, void* hdc);

// Inherited CControlUI methods
DUILIB_C_API char* duilib_progress_get_name(duilib_progress_t progress);
DUILIB_C_API duilib_result_t duilib_progress_set_name(duilib_progress_t progress, const char* name);
DUILIB_C_API char* duilib_progress_get_text(duilib_progress_t progress);
DUILIB_C_API duilib_result_t duilib_progress_set_text(duilib_progress_t progress, const char* text_content);
DUILIB_C_API bool duilib_progress_is_visible(duilib_progress_t progress);
DUILIB_C_API duilib_result_t duilib_progress_set_visible(duilib_progress_t progress, bool visible);
DUILIB_C_API bool duilib_progress_is_enabled(duilib_progress_t progress);
DUILIB_C_API duilib_result_t duilib_progress_set_enabled(duilib_progress_t progress, bool enabled);
DUILIB_C_API duilib_rect_t duilib_progress_get_pos(duilib_progress_t progress);
DUILIB_C_API duilib_result_t duilib_progress_set_pos(duilib_progress_t progress, duilib_rect_t pos, bool need_invalidate);
DUILIB_C_API char* duilib_progress_get_attribute(duilib_progress_t progress, const char* name);
DUILIB_C_API duilib_result_t duilib_progress_set_attribute(duilib_progress_t progress, const char* name, const char* value);

#ifdef __cplusplus
}
#endif

#endif // DUILIB_C_PROGRESS_H