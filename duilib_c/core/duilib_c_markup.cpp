#include "../duilib_c_internal.h"
#include "duilib_c_markup.h"

// 标记解析器包装结构体
struct duilib_markup {
    CMarkup* markup;
};

//=============================================================================
// XML标记解析器API实现 - 对应 CMarkup
//=============================================================================

DUILIB_C_API duilib_markup_t duilib_markup_create(void) {
    try {
        duilib_markup_t markup = new duilib_markup;
        markup->markup = new CMarkup();
        return markup;
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API void duilib_markup_destroy(duilib_markup_t markup) {
    if (markup) {
        if (markup->markup) {
            delete markup->markup;
        }
        delete markup;
    }
}

DUILIB_C_API bool duilib_markup_load(duilib_markup_t markup, const char* xml) {
    if (!markup || !markup->markup || !xml) return false;

    try {
        return markup->markup->Load(from_cstring(xml));
    } catch (...) {
        return false;
    }
}

DUILIB_C_API bool duilib_markup_load_from_file(duilib_markup_t markup, const char* filename) {
    if (!markup || !markup->markup || !filename) return false;

    try {
        return markup->markup->LoadFromFile(from_cstring(filename));
    } catch (...) {
        return false;
    }
}

DUILIB_C_API bool duilib_markup_load_from_mem(duilib_markup_t markup, const void* data, int size) {
    if (!markup || !markup->markup || !data || size <= 0) return false;

    try {
        return markup->markup->LoadFromMem(static_cast<const BYTE*>(data), size);
    } catch (...) {
        return false;
    }
}

DUILIB_C_API bool duilib_markup_save(duilib_markup_t markup, const char* filename) {
    if (!markup || !markup->markup || !filename) return false;

    try {
        return markup->markup->Save(from_cstring(filename));
    } catch (...) {
        return false;
    }
}

DUILIB_C_API void* duilib_markup_get_root(duilib_markup_t markup) {
    if (!markup || !markup->markup) return nullptr;

    try {
        return markup->markup->GetRoot();
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API const char* duilib_markup_get_last_error(duilib_markup_t markup) {
    if (!markup || !markup->markup) return nullptr;

    try {
        return to_cstring(markup->markup->GetLastError());
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API void duilib_markup_get_last_error_location(duilib_markup_t markup, int* row, int* col) {
    if (!markup || !markup->markup || !row || !col) return;

    try {
        markup->markup->GetLastErrorLocation(row, col);
    } catch (...) {
        if (row) *row = 0;
        if (col) *col = 0;
    }
}

DUILIB_C_API duilib_result_t duilib_markup_set_preprocessor(duilib_markup_t markup, const char* preprocessor) {
    if (!markup || !markup->markup || !preprocessor) return DUILIB_ERROR_INVALID_PARAM;

    try {
        markup->markup->SetPreprocessor(from_cstring(preprocessor));
        return DUILIB_OK;
    } catch (...) {
        return DUILIB_ERROR_UNKNOWN;
    }
}