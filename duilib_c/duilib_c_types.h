#ifndef DUILIB_C_TYPES_H
#define DUILIB_C_TYPES_H

// This header provides forward declarations and common types for DuiLib C API
// 这个头文件为 DuiLib C API 提供前置声明和通用类型

#include "core/duilib_c_base.h"

// Additional control types for specific controls (matching actual implementations)
typedef struct duilib_label* duilib_label_t;
typedef struct duilib_button* duilib_button_t;
typedef struct duilib_text_impl* duilib_text_t;
typedef struct duilib_progress_impl* duilib_progress_t;
typedef struct duilib_option_impl* duilib_option_t;

// Container types (matching actual implementations)
typedef struct duilib_container_impl* duilib_container_t;
typedef struct duilib_verticallayout* duilib_verticallayout_t;
typedef struct duilib_horizontallayout* duilib_horizontallayout_t;
typedef struct duilib_tablayout* duilib_tablayout_t;
typedef struct duilib_tilelayout* duilib_tilelayout_t;
typedef struct duilib_childlayout* duilib_childlayout_t;

// Core types (forward declarations to avoid circular dependencies)
typedef struct duilib_markup* duilib_markup_t;
typedef struct duilib_markup_node* duilib_markup_node_t;
typedef struct duilib_dlgbuilder_impl* duilib_dlgbuilder_t;

#endif // DUILIB_C_TYPES_H