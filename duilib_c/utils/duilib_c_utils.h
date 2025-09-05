#ifndef __DUILIB_C_UTILS_H__
#define __DUILIB_C_UTILS_H__

#include "../core/duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// DuiLib工具类API - 对应 Utils.h
//=============================================================================

//=============================================================================
// STRINGorID - 字符串或ID包装器
//=============================================================================

// STRINGorID句柄
typedef struct duilib_stringorid* duilib_stringorid_t;

// 创建和销毁STRINGorID
DUILIB_C_API duilib_stringorid_t duilib_stringorid_create_string(const char* str);
DUILIB_C_API duilib_stringorid_t duilib_stringorid_create_id(unsigned int id);
DUILIB_C_API void duilib_stringorid_destroy(duilib_stringorid_t stringorid);

// 获取STRINGorID内容
DUILIB_C_API const char* duilib_stringorid_get_string(duilib_stringorid_t stringorid);

//=============================================================================
// CDuiPoint - 点结构
//=============================================================================

// CDuiPoint句柄
typedef struct duilib_duipoint* duilib_duipoint_t;

// 创建和销毁CDuiPoint
DUILIB_C_API duilib_duipoint_t duilib_duipoint_create(void);
DUILIB_C_API duilib_duipoint_t duilib_duipoint_create_xy(long x, long y);
DUILIB_C_API duilib_duipoint_t duilib_duipoint_create_from_point(duilib_point_t point);
DUILIB_C_API duilib_duipoint_t duilib_duipoint_create_from_lparam(long lparam);
DUILIB_C_API duilib_duipoint_t duilib_duipoint_create_from_string(const char* str);
DUILIB_C_API void duilib_duipoint_destroy(duilib_duipoint_t duipoint);

// CDuiPoint操作
DUILIB_C_API duilib_point_t duilib_duipoint_get_point(duilib_duipoint_t duipoint);
DUILIB_C_API duilib_result_t duilib_duipoint_set_point(duilib_duipoint_t duipoint, long x, long y);
DUILIB_C_API const char* duilib_duipoint_to_string(duilib_duipoint_t duipoint);

//=============================================================================
// CDuiSize - 尺寸结构
//=============================================================================

// CDuiSize句柄
typedef struct duilib_duisize* duilib_duisize_t;

// 创建和销毁CDuiSize
DUILIB_C_API duilib_duisize_t duilib_duisize_create(void);
DUILIB_C_API duilib_duisize_t duilib_duisize_create_wh(long cx, long cy);
DUILIB_C_API duilib_duisize_t duilib_duisize_create_from_size(duilib_size_t size);
DUILIB_C_API duilib_duisize_t duilib_duisize_create_from_rect(duilib_rect_t rect);
DUILIB_C_API duilib_duisize_t duilib_duisize_create_from_string(const char* str);
DUILIB_C_API void duilib_duisize_destroy(duilib_duisize_t duisize);

// CDuiSize操作
DUILIB_C_API duilib_size_t duilib_duisize_get_size(duilib_duisize_t duisize);
DUILIB_C_API duilib_result_t duilib_duisize_set_size(duilib_duisize_t duisize, long cx, long cy);
DUILIB_C_API const char* duilib_duisize_to_string(duilib_duisize_t duisize);

//=============================================================================
// CDuiRect - 矩形结构
//=============================================================================

// CDuiRect句柄
typedef struct duilib_duirect* duilib_duirect_t;

// 创建和销毁CDuiRect
DUILIB_C_API duilib_duirect_t duilib_duirect_create(void);
DUILIB_C_API duilib_duirect_t duilib_duirect_create_ltrb(long left, long top, long right, long bottom);
DUILIB_C_API duilib_duirect_t duilib_duirect_create_from_rect(duilib_rect_t rect);
DUILIB_C_API duilib_duirect_t duilib_duirect_create_from_string(const char* str);
DUILIB_C_API void duilib_duirect_destroy(duilib_duirect_t duirect);

// CDuiRect操作
DUILIB_C_API duilib_rect_t duilib_duirect_get_rect(duilib_duirect_t duirect);
DUILIB_C_API duilib_result_t duilib_duirect_set_rect(duilib_duirect_t duirect, long left, long top, long right, long bottom);
DUILIB_C_API const char* duilib_duirect_to_string(duilib_duirect_t duirect);

// CDuiRect几何操作
DUILIB_C_API int duilib_duirect_get_width(duilib_duirect_t duirect);
DUILIB_C_API int duilib_duirect_get_height(duilib_duirect_t duirect);
DUILIB_C_API duilib_result_t duilib_duirect_empty(duilib_duirect_t duirect);
DUILIB_C_API bool duilib_duirect_is_null(duilib_duirect_t duirect);
DUILIB_C_API duilib_result_t duilib_duirect_join(duilib_duirect_t duirect, duilib_rect_t rect);
DUILIB_C_API duilib_result_t duilib_duirect_reset_offset(duilib_duirect_t duirect);
DUILIB_C_API duilib_result_t duilib_duirect_normalize(duilib_duirect_t duirect);
DUILIB_C_API duilib_result_t duilib_duirect_offset(duilib_duirect_t duirect, int cx, int cy);
DUILIB_C_API duilib_result_t duilib_duirect_inflate(duilib_duirect_t duirect, int cx, int cy);
DUILIB_C_API duilib_result_t duilib_duirect_deflate(duilib_duirect_t duirect, int cx, int cy);
DUILIB_C_API duilib_result_t duilib_duirect_union(duilib_duirect_t duirect, duilib_duirect_t other);

//=============================================================================
// CDuiString - 字符串类
//=============================================================================

// CDuiString句柄
typedef struct duilib_duistring* duilib_duistring_t;

// 创建和销毁CDuiString
DUILIB_C_API duilib_duistring_t duilib_duistring_create(void);
DUILIB_C_API duilib_duistring_t duilib_duistring_create_char(char ch);
DUILIB_C_API duilib_duistring_t duilib_duistring_create_string(const char* str);
DUILIB_C_API duilib_duistring_t duilib_duistring_create_length(const char* str, int length);
DUILIB_C_API duilib_duistring_t duilib_duistring_create_copy(duilib_duistring_t src);
DUILIB_C_API void duilib_duistring_destroy(duilib_duistring_t duistring);

// CDuiString基础操作
DUILIB_C_API duilib_result_t duilib_duistring_empty(duilib_duistring_t duistring);
DUILIB_C_API int duilib_duistring_get_length(duilib_duistring_t duistring);
DUILIB_C_API bool duilib_duistring_is_empty(duilib_duistring_t duistring);
DUILIB_C_API char duilib_duistring_get_at(duilib_duistring_t duistring, int index);
DUILIB_C_API duilib_result_t duilib_duistring_set_at(duilib_duistring_t duistring, int index, char ch);
DUILIB_C_API const char* duilib_duistring_get_data(duilib_duistring_t duistring);

// CDuiString修改操作
DUILIB_C_API duilib_result_t duilib_duistring_append(duilib_duistring_t duistring, const char* str);
DUILIB_C_API duilib_result_t duilib_duistring_assign(duilib_duistring_t duistring, const char* str);
DUILIB_C_API duilib_result_t duilib_duistring_assign_length(duilib_duistring_t duistring, const char* str, int length);

// CDuiString比较操作
DUILIB_C_API int duilib_duistring_compare(duilib_duistring_t duistring, const char* str);
DUILIB_C_API int duilib_duistring_compare_nocase(duilib_duistring_t duistring, const char* str);

// CDuiString大小写转换
DUILIB_C_API duilib_result_t duilib_duistring_make_upper(duilib_duistring_t duistring);
DUILIB_C_API duilib_result_t duilib_duistring_make_lower(duilib_duistring_t duistring);

// CDuiString子字符串操作
DUILIB_C_API const char* duilib_duistring_left(duilib_duistring_t duistring, int length);
DUILIB_C_API const char* duilib_duistring_mid(duilib_duistring_t duistring, int pos, int length);
DUILIB_C_API const char* duilib_duistring_right(duilib_duistring_t duistring, int length);

// CDuiString查找和替换
DUILIB_C_API int duilib_duistring_find_char(duilib_duistring_t duistring, char ch, int pos);
DUILIB_C_API int duilib_duistring_find_string(duilib_duistring_t duistring, const char* str, int pos);
DUILIB_C_API int duilib_duistring_reverse_find(duilib_duistring_t duistring, char ch);
DUILIB_C_API int duilib_duistring_replace(duilib_duistring_t duistring, const char* from, const char* to);

// CDuiString格式化
DUILIB_C_API int duilib_duistring_format(duilib_duistring_t duistring, const char* format, ...);

//=============================================================================
// CDuiPtrArray - 指针数组
//=============================================================================

// CDuiPtrArray句柄
typedef struct duilib_duiptrarray* duilib_duiptrarray_t;

// 创建和销毁CDuiPtrArray
DUILIB_C_API duilib_duiptrarray_t duilib_duiptrarray_create(int prealloc_size);
DUILIB_C_API duilib_duiptrarray_t duilib_duiptrarray_create_copy(duilib_duiptrarray_t src);
DUILIB_C_API void duilib_duiptrarray_destroy(duilib_duiptrarray_t ptrarray);

// CDuiPtrArray基础操作
DUILIB_C_API duilib_result_t duilib_duiptrarray_empty(duilib_duiptrarray_t ptrarray);
DUILIB_C_API duilib_result_t duilib_duiptrarray_resize(duilib_duiptrarray_t ptrarray, int size);
DUILIB_C_API bool duilib_duiptrarray_is_empty(duilib_duiptrarray_t ptrarray);
DUILIB_C_API int duilib_duiptrarray_find(duilib_duiptrarray_t ptrarray, void* ptr);
DUILIB_C_API int duilib_duiptrarray_get_size(duilib_duiptrarray_t ptrarray);

// CDuiPtrArray元素操作
DUILIB_C_API bool duilib_duiptrarray_add(duilib_duiptrarray_t ptrarray, void* ptr);
DUILIB_C_API bool duilib_duiptrarray_set_at(duilib_duiptrarray_t ptrarray, int index, void* ptr);
DUILIB_C_API bool duilib_duiptrarray_insert_at(duilib_duiptrarray_t ptrarray, int index, void* ptr);
DUILIB_C_API bool duilib_duiptrarray_remove(duilib_duiptrarray_t ptrarray, int index, int count);
DUILIB_C_API void* duilib_duiptrarray_get_at(duilib_duiptrarray_t ptrarray, int index);
DUILIB_C_API void** duilib_duiptrarray_get_data(duilib_duiptrarray_t ptrarray);

//=============================================================================
// CDuiStringPtrMap - 字符串指针映射
//=============================================================================

// CDuiStringPtrMap句柄
typedef struct duilib_duistringptrmap* duilib_duistringptrmap_t;

// 创建和销毁CDuiStringPtrMap
DUILIB_C_API duilib_duistringptrmap_t duilib_duistringptrmap_create(int size);
DUILIB_C_API void duilib_duistringptrmap_destroy(duilib_duistringptrmap_t map);

// CDuiStringPtrMap操作
DUILIB_C_API duilib_result_t duilib_duistringptrmap_resize(duilib_duistringptrmap_t map, int size);
DUILIB_C_API void* duilib_duistringptrmap_find(duilib_duistringptrmap_t map, const char* key, bool optimize);
DUILIB_C_API bool duilib_duistringptrmap_insert(duilib_duistringptrmap_t map, const char* key, void* data);
DUILIB_C_API void* duilib_duistringptrmap_set(duilib_duistringptrmap_t map, const char* key, void* data);
DUILIB_C_API bool duilib_duistringptrmap_remove(duilib_duistringptrmap_t map, const char* key);
DUILIB_C_API duilib_result_t duilib_duistringptrmap_remove_all(duilib_duistringptrmap_t map);
DUILIB_C_API int duilib_duistringptrmap_get_size(duilib_duistringptrmap_t map);
DUILIB_C_API const char* duilib_duistringptrmap_get_at(duilib_duistringptrmap_t map, int index);

//=============================================================================
// CWaitCursor - 等待光标
//=============================================================================

// CWaitCursor句柄
typedef struct duilib_waitcursor* duilib_waitcursor_t;

// 创建和销毁CWaitCursor
DUILIB_C_API duilib_waitcursor_t duilib_waitcursor_create(void);
DUILIB_C_API void duilib_waitcursor_destroy(duilib_waitcursor_t waitcursor);

//=============================================================================
// CVariant - 变体类型（简化版本）
//=============================================================================

// 变体类型枚举
typedef enum {
    DUILIB_VARIANT_TYPE_EMPTY = 0,
    DUILIB_VARIANT_TYPE_INT,
    DUILIB_VARIANT_TYPE_FLOAT,
    DUILIB_VARIANT_TYPE_STRING,
    DUILIB_VARIANT_TYPE_DISPATCH
} duilib_variant_type_t;

// CVariant句柄
typedef struct duilib_variant* duilib_variant_t;

// 创建和销毁CVariant
DUILIB_C_API duilib_variant_t duilib_variant_create(void);
DUILIB_C_API duilib_variant_t duilib_variant_create_int(int value);
DUILIB_C_API duilib_variant_t duilib_variant_create_float(float value);
DUILIB_C_API duilib_variant_t duilib_variant_create_string(const char* value);
DUILIB_C_API void duilib_variant_destroy(duilib_variant_t variant);

// CVariant操作
DUILIB_C_API duilib_variant_type_t duilib_variant_get_type(duilib_variant_t variant);
DUILIB_C_API int duilib_variant_get_int(duilib_variant_t variant);
DUILIB_C_API float duilib_variant_get_float(duilib_variant_t variant);
DUILIB_C_API const char* duilib_variant_get_string(duilib_variant_t variant);
DUILIB_C_API duilib_result_t duilib_variant_set_int(duilib_variant_t variant, int value);
DUILIB_C_API duilib_result_t duilib_variant_set_float(duilib_variant_t variant, float value);
DUILIB_C_API duilib_result_t duilib_variant_set_string(duilib_variant_t variant, const char* value);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_UTILS_H__