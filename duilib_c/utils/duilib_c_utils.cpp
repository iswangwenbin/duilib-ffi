#include "duilib_c_utils.h"
#include "../../duilib/DuiLib/Utils/Utils.h"
#include <new>

using namespace DuiLib;

//=============================================================================
// Internal wrapper structures
//=============================================================================

struct duilib_stringorid {
    STRINGorID impl;
    duilib_stringorid(UINT id) : impl(id) {}
    duilib_stringorid(LPCTSTR str) : impl(str) {}
};

struct duilib_duistring {
    CDuiString impl;
};

struct duilib_duipoint {
    CDuiPoint impl;
    duilib_duipoint() : impl() {}
    duilib_duipoint(LONG x, LONG y) : impl(x, y) {}
    duilib_duipoint(const POINT& pt) : impl(pt) {}
};

struct duilib_duisize {
    CDuiSize impl;
    duilib_duisize() : impl() {}
    duilib_duisize(LONG cx, LONG cy) : impl(cx, cy) {}
    duilib_duisize(const SIZE& sz) : impl(sz) {}
};

struct duilib_duirect {
    CDuiRect impl;
    duilib_duirect() : impl() {}
    duilib_duirect(LONG left, LONG top, LONG right, LONG bottom) : impl(left, top, right, bottom) {}
    duilib_duirect(const RECT& rc) : impl(rc) {}
};

struct duilib_duiptrarray {
    CDuiPtrArray impl;
    duilib_duiptrarray(int prealloc_size = 0) : impl(prealloc_size) {}
};

struct duilib_duivalarray {
    CDuiValArray impl;
    duilib_duivalarray(int prealloc_size = 0) : impl(prealloc_size) {}
};

struct duilib_duistringptrmap {
    CDuiStringPtrMap impl;
    duilib_duistringptrmap(int prealloc_size = 83) : impl(prealloc_size) {}
};

struct duilib_waitcursor {
    CWaitCursor impl;
};

struct duilib_variant {
    CVariant impl;
    duilib_variant() : impl() {}
    duilib_variant(short value) : impl(value) {}
    duilib_variant(int value) : impl(value) {}
    duilib_variant(long value) : impl(value) {}
    duilib_variant(float value) : impl(value) {}
    duilib_variant(double value) : impl(value) {}
    duilib_variant(LPCTSTR value) : impl(value) {}
};

//=============================================================================
// STRINGorID implementation
//=============================================================================

DUILIB_C_API duilib_stringorid_t duilib_stringorid_create_id(unsigned int id) {
    try {
        return new(std::nothrow) duilib_stringorid(id);
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API duilib_stringorid_t duilib_stringorid_create_string(const char* str) {
    if (!str) return nullptr;
    try {
#ifdef _UNICODE
        int len = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
        if (len <= 0) return nullptr;
        
        wchar_t* wstr = new(std::nothrow) wchar_t[len];
        if (!wstr) return nullptr;
        
        MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, len);
        duilib_stringorid* result = new(std::nothrow) duilib_stringorid(wstr);
        delete[] wstr;
        return result;
#else
        return new(std::nothrow) duilib_stringorid(str);
#endif
    } catch (...) {
        return nullptr;
    }
}

DUILIB_C_API void duilib_stringorid_destroy(duilib_stringorid_t stringorid) {
    delete stringorid;
}

DUILIB_C_API bool duilib_stringorid_is_valid(duilib_stringorid_t stringorid) {
    return stringorid != nullptr;
}

DUILIB_C_API bool duilib_stringorid_is_id(duilib_stringorid_t stringorid) {
    return stringorid ? stringorid->impl.m_lpstr == nullptr : false;
}

DUILIB_C_API bool duilib_stringorid_is_string(duilib_stringorid_t stringorid) {
    return stringorid ? stringorid->impl.m_lpstr != nullptr : false;
}

DUILIB_C_API unsigned int duilib_stringorid_get_id(duilib_stringorid_t stringorid) {
    if (!stringorid || stringorid->impl.m_lpstr != nullptr) return 0;
    return PtrToUlong(stringorid->impl.m_lpstr);
}

DUILIB_C_API const char* duilib_stringorid_get_string(duilib_stringorid_t stringorid) {
    if (!stringorid || stringorid->impl.m_lpstr == nullptr) return nullptr;
    
    static thread_local char buffer[1024];
#ifdef _UNICODE
    WideCharToMultiByte(CP_UTF8, 0, stringorid->impl.m_lpstr, -1, buffer, sizeof(buffer), nullptr, nullptr);
    return buffer;
#else
    return stringorid->impl.m_lpstr;
#endif
}

//=============================================================================
// CDuiString implementation
//=============================================================================

DUILIB_C_API duilib_duistring_t duilib_duistring_create(void) {
    return new(std::nothrow) duilib_duistring();
}

DUILIB_C_API duilib_duistring_t duilib_duistring_create_string(const char* str) {
    if (!str) return nullptr;
    
    duilib_duistring* result = new(std::nothrow) duilib_duistring();
    if (!result) return nullptr;
    
#ifdef _UNICODE
    int len = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
    if (len <= 0) {
        delete result;
        return nullptr;
    }
    
    wchar_t* wstr = new(std::nothrow) wchar_t[len];
    if (!wstr) {
        delete result;
        return nullptr;
    }
    
    MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, len);
    result->impl = wstr;
    delete[] wstr;
#else
    result->impl = str;
#endif
    
    return result;
}

DUILIB_C_API duilib_duistring_t duilib_duistring_create_copy(duilib_duistring_t other) {
    if (!other) return nullptr;
    
    duilib_duistring* result = new(std::nothrow) duilib_duistring();
    if (!result) return nullptr;
    
    result->impl = other->impl;
    return result;
}

DUILIB_C_API void duilib_duistring_destroy(duilib_duistring_t duistring) {
    delete duistring;
}

DUILIB_C_API bool duilib_duistring_is_valid(duilib_duistring_t duistring) {
    return duistring != nullptr;
}

DUILIB_C_API const char* duilib_duistring_get_data(duilib_duistring_t duistring) {
    if (!duistring) return nullptr;
    
    static thread_local char buffer[4096];
#ifdef _UNICODE
    WideCharToMultiByte(CP_UTF8, 0, duistring->impl.GetData(), -1, buffer, sizeof(buffer), nullptr, nullptr);
    return buffer;
#else
    return duistring->impl.GetData();
#endif
}

DUILIB_C_API int duilib_duistring_get_length(duilib_duistring_t duistring) {
    return duistring ? duistring->impl.GetLength() : 0;
}

DUILIB_C_API bool duilib_duistring_is_empty(duilib_duistring_t duistring) {
    return duistring ? duistring->impl.IsEmpty() : true;
}

DUILIB_C_API void duilib_duistring_empty(duilib_duistring_t duistring) {
    if (duistring) {
        duistring->impl.Empty();
    }
}

DUILIB_C_API duilib_result_t duilib_duistring_assign(duilib_duistring_t duistring, const char* str) {
    if (!duistring || !str) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
#ifdef _UNICODE
        int len = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
        if (len <= 0) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
        
        wchar_t* wstr = new wchar_t[len];
        MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, len);
        duistring->impl = wstr;
        delete[] wstr;
#else
        duistring->impl = str;
#endif
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR_OUT_OF_MEMORY;
    }
}

DUILIB_C_API int duilib_duistring_compare(duilib_duistring_t duistring, const char* str) {
    if (!duistring || !str) return -1;
    
#ifdef _UNICODE
    int len = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
    if (len <= 0) return -1;
    
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, len);
    int result = duistring->impl.Compare(wstr);
    delete[] wstr;
    return result;
#else
    return duistring->impl.Compare(str);
#endif
}

DUILIB_C_API int duilib_duistring_compare_nocase(duilib_duistring_t duistring, const char* str) {
    if (!duistring || !str) return -1;
    
#ifdef _UNICODE
    int len = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
    if (len <= 0) return -1;
    
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, len);
    int result = duistring->impl.CompareNoCase(wstr);
    delete[] wstr;
    return result;
#else
    return duistring->impl.CompareNoCase(str);
#endif
}

DUILIB_C_API duilib_result_t duilib_duistring_append(duilib_duistring_t duistring, const char* str) {
    if (!duistring || !str) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    try {
#ifdef _UNICODE
        int len = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
        if (len <= 0) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
        
        wchar_t* wstr = new wchar_t[len];
        MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, len);
        duistring->impl += wstr;
        delete[] wstr;
#else
        duistring->impl += str;
#endif
        return DUILIB_RESULT_OK;
    } catch (...) {
        return DUILIB_RESULT_ERROR_OUT_OF_MEMORY;
    }
}

DUILIB_C_API void duilib_duistring_make_upper(duilib_duistring_t duistring) {
    if (duistring) {
        duistring->impl.MakeUpper();
    }
}

DUILIB_C_API void duilib_duistring_make_lower(duilib_duistring_t duistring) {
    if (duistring) {
        duistring->impl.MakeLower();
    }
}

DUILIB_C_API duilib_duistring_t duilib_duistring_left(duilib_duistring_t duistring, int count) {
    if (!duistring) return nullptr;
    
    duilib_duistring* result = new(std::nothrow) duilib_duistring();
    if (!result) return nullptr;
    
    result->impl = duistring->impl.Left(count);
    return result;
}

DUILIB_C_API duilib_duistring_t duilib_duistring_mid(duilib_duistring_t duistring, int pos, int count) {
    if (!duistring) return nullptr;
    
    duilib_duistring* result = new(std::nothrow) duilib_duistring();
    if (!result) return nullptr;
    
    if (count < 0) {
        result->impl = duistring->impl.Mid(pos);
    } else {
        result->impl = duistring->impl.Mid(pos, count);
    }
    return result;
}

DUILIB_C_API duilib_duistring_t duilib_duistring_right(duilib_duistring_t duistring, int count) {
    if (!duistring) return nullptr;
    
    duilib_duistring* result = new(std::nothrow) duilib_duistring();
    if (!result) return nullptr;
    
    result->impl = duistring->impl.Right(count);
    return result;
}

DUILIB_C_API int duilib_duistring_find(duilib_duistring_t duistring, const char* substr, int start_pos) {
    if (!duistring || !substr) return -1;
    
#ifdef _UNICODE
    int len = MultiByteToWideChar(CP_UTF8, 0, substr, -1, nullptr, 0);
    if (len <= 0) return -1;
    
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, substr, -1, wstr, len);
    int result = duistring->impl.Find(wstr, start_pos);
    delete[] wstr;
    return result;
#else
    return duistring->impl.Find(substr, start_pos);
#endif
}

DUILIB_C_API int duilib_duistring_replace(duilib_duistring_t duistring, const char* from, const char* to) {
    if (!duistring || !from || !to) return 0;
    
#ifdef _UNICODE
    int from_len = MultiByteToWideChar(CP_UTF8, 0, from, -1, nullptr, 0);
    int to_len = MultiByteToWideChar(CP_UTF8, 0, to, -1, nullptr, 0);
    if (from_len <= 0 || to_len <= 0) return 0;
    
    wchar_t* from_wstr = new wchar_t[from_len];
    wchar_t* to_wstr = new wchar_t[to_len];
    MultiByteToWideChar(CP_UTF8, 0, from, -1, from_wstr, from_len);
    MultiByteToWideChar(CP_UTF8, 0, to, -1, to_wstr, to_len);
    
    int result = duistring->impl.Replace(from_wstr, to_wstr);
    delete[] from_wstr;
    delete[] to_wstr;
    return result;
#else
    return duistring->impl.Replace(from, to);
#endif
}

DUILIB_C_API void duilib_duistring_trim_left(duilib_duistring_t duistring) {
    if (duistring) {
        duistring->impl.TrimLeft();
    }
}

DUILIB_C_API void duilib_duistring_trim_right(duilib_duistring_t duistring) {
    if (duistring) {
        duistring->impl.TrimRight();
    }
}

//=============================================================================
// CDuiPoint implementation  
//=============================================================================

DUILIB_C_API duilib_duipoint_t duilib_duipoint_create(void) {
    return new(std::nothrow) duilib_duipoint();
}

DUILIB_C_API duilib_duipoint_t duilib_duipoint_create_xy(long x, long y) {
    return new(std::nothrow) duilib_duipoint(x, y);
}

DUILIB_C_API void duilib_duipoint_destroy(duilib_duipoint_t duipoint) {
    delete duipoint;
}

DUILIB_C_API bool duilib_duipoint_is_valid(duilib_duipoint_t duipoint) {
    return duipoint != nullptr;
}

DUILIB_C_API long duilib_duipoint_get_x(duilib_duipoint_t duipoint) {
    return duipoint ? duipoint->impl.x : 0;
}

DUILIB_C_API long duilib_duipoint_get_y(duilib_duipoint_t duipoint) {
    return duipoint ? duipoint->impl.y : 0;
}

DUILIB_C_API void duilib_duipoint_set_x(duilib_duipoint_t duipoint, long x) {
    if (duipoint) {
        duipoint->impl.x = x;
    }
}

DUILIB_C_API void duilib_duipoint_set_y(duilib_duipoint_t duipoint, long y) {
    if (duipoint) {
        duipoint->impl.y = y;
    }
}

DUILIB_C_API void duilib_duipoint_offset(duilib_duipoint_t duipoint, long dx, long dy) {
    if (duipoint) {
        duipoint->impl.Offset(dx, dy);
    }
}

//=============================================================================
// CDuiSize implementation
//=============================================================================

DUILIB_C_API duilib_duisize_t duilib_duisize_create(void) {
    return new(std::nothrow) duilib_duisize();
}

DUILIB_C_API duilib_duisize_t duilib_duisize_create_wh(long width, long height) {
    return new(std::nothrow) duilib_duisize(width, height);
}

DUILIB_C_API void duilib_duisize_destroy(duilib_duisize_t duisize) {
    delete duisize;
}

DUILIB_C_API bool duilib_duisize_is_valid(duilib_duisize_t duisize) {
    return duisize != nullptr;
}

DUILIB_C_API long duilib_duisize_get_width(duilib_duisize_t duisize) {
    return duisize ? duisize->impl.cx : 0;
}

DUILIB_C_API long duilib_duisize_get_height(duilib_duisize_t duisize) {
    return duisize ? duisize->impl.cy : 0;
}

DUILIB_C_API void duilib_duisize_set_width(duilib_duisize_t duisize, long width) {
    if (duisize) {
        duisize->impl.cx = width;
    }
}

DUILIB_C_API void duilib_duisize_set_height(duilib_duisize_t duisize, long height) {
    if (duisize) {
        duisize->impl.cy = height;
    }
}

//=============================================================================
// CDuiRect implementation
//=============================================================================

DUILIB_C_API duilib_duirect_t duilib_duirect_create(void) {
    return new(std::nothrow) duilib_duirect();
}

DUILIB_C_API duilib_duirect_t duilib_duirect_create_ltrb(long left, long top, long right, long bottom) {
    return new(std::nothrow) duilib_duirect(left, top, right, bottom);
}

DUILIB_C_API void duilib_duirect_destroy(duilib_duirect_t duirect) {
    delete duirect;
}

DUILIB_C_API bool duilib_duirect_is_valid(duilib_duirect_t duirect) {
    return duirect != nullptr;
}

DUILIB_C_API long duilib_duirect_get_left(duilib_duirect_t duirect) {
    return duirect ? duirect->impl.left : 0;
}

DUILIB_C_API long duilib_duirect_get_top(duilib_duirect_t duirect) {
    return duirect ? duirect->impl.top : 0;
}

DUILIB_C_API long duilib_duirect_get_right(duilib_duirect_t duirect) {
    return duirect ? duirect->impl.right : 0;
}

DUILIB_C_API long duilib_duirect_get_bottom(duilib_duirect_t duirect) {
    return duirect ? duirect->impl.bottom : 0;
}

DUILIB_C_API void duilib_duirect_set_left(duilib_duirect_t duirect, long left) {
    if (duirect) {
        duirect->impl.left = left;
    }
}

DUILIB_C_API void duilib_duirect_set_top(duilib_duirect_t duirect, long top) {
    if (duirect) {
        duirect->impl.top = top;
    }
}

DUILIB_C_API void duilib_duirect_set_right(duilib_duirect_t duirect, long right) {
    if (duirect) {
        duirect->impl.right = right;
    }
}

DUILIB_C_API void duilib_duirect_set_bottom(duilib_duirect_t duirect, long bottom) {
    if (duirect) {
        duirect->impl.bottom = bottom;
    }
}

DUILIB_C_API long duilib_duirect_get_width(duilib_duirect_t duirect) {
    return duirect ? duirect->impl.GetWidth() : 0;
}

DUILIB_C_API long duilib_duirect_get_height(duilib_duirect_t duirect) {
    return duirect ? duirect->impl.GetHeight() : 0;
}

DUILIB_C_API bool duilib_duirect_is_empty(duilib_duirect_t duirect) {
    return duirect ? duirect->impl.IsRectEmpty() : true;
}

DUILIB_C_API bool duilib_duirect_is_null(duilib_duirect_t duirect) {
    return duirect ? duirect->impl.IsRectNull() : true;
}

DUILIB_C_API bool duilib_duirect_point_in_rect(duilib_duirect_t duirect, long x, long y) {
    if (!duirect) return false;
    POINT pt = {x, y};
    return duirect->impl.PtInRect(pt) != FALSE;
}

DUILIB_C_API void duilib_duirect_inflate(duilib_duirect_t duirect, long dx, long dy) {
    if (duirect) {
        duirect->impl.Inflate(dx, dy);
    }
}

DUILIB_C_API void duilib_duirect_deflate(duilib_duirect_t duirect, long dx, long dy) {
    if (duirect) {
        duirect->impl.Deflate(dx, dy);
    }
}

DUILIB_C_API void duilib_duirect_offset(duilib_duirect_t duirect, long dx, long dy) {
    if (duirect) {
        duirect->impl.Offset(dx, dy);
    }
}

DUILIB_C_API bool duilib_duirect_intersect_rect(duilib_duirect_t duirect, duilib_duirect_t other) {
    if (!duirect || !other) return false;
    return duirect->impl.IntersectRect(&duirect->impl, &other->impl) != FALSE;
}

DUILIB_C_API bool duilib_duirect_union_rect(duilib_duirect_t duirect, duilib_duirect_t other) {
    if (!duirect || !other) return false;
    return duirect->impl.UnionRect(&duirect->impl, &other->impl) != FALSE;
}

DUILIB_C_API bool duilib_duirect_subtract_rect(duilib_duirect_t duirect, duilib_duirect_t other) {
    if (!duirect || !other) return false;
    return duirect->impl.SubtractRect(&duirect->impl, &other->impl) != FALSE;
}

//=============================================================================
// CDuiPtrArray implementation
//=============================================================================

DUILIB_C_API duilib_duiptrarray_t duilib_duiptrarray_create(int prealloc_size) {
    return new(std::nothrow) duilib_duiptrarray(prealloc_size);
}

DUILIB_C_API void duilib_duiptrarray_destroy(duilib_duiptrarray_t ptrarray) {
    delete ptrarray;
}

DUILIB_C_API bool duilib_duiptrarray_is_valid(duilib_duiptrarray_t ptrarray) {
    return ptrarray != nullptr;
}

DUILIB_C_API bool duilib_duiptrarray_is_empty(duilib_duiptrarray_t ptrarray) {
    return ptrarray ? ptrarray->impl.IsEmpty() : true;
}

DUILIB_C_API bool duilib_duiptrarray_add(duilib_duiptrarray_t ptrarray, void* ptr) {
    return ptrarray ? ptrarray->impl.Add(ptr) : false;
}

DUILIB_C_API bool duilib_duiptrarray_insert_at(duilib_duiptrarray_t ptrarray, int index, void* ptr) {
    return ptrarray ? ptrarray->impl.InsertAt(index, ptr) : false;
}

DUILIB_C_API bool duilib_duiptrarray_remove(duilib_duiptrarray_t ptrarray, void* ptr) {
    return ptrarray ? ptrarray->impl.Remove(ptr) : false;
}

DUILIB_C_API bool duilib_duiptrarray_remove_at(duilib_duiptrarray_t ptrarray, int index) {
    return ptrarray ? ptrarray->impl.RemoveAt(index) : false;
}

DUILIB_C_API void duilib_duiptrarray_remove_all(duilib_duiptrarray_t ptrarray) {
    if (ptrarray) {
        ptrarray->impl.RemoveAll();
    }
}

DUILIB_C_API void* duilib_duiptrarray_get_at(duilib_duiptrarray_t ptrarray, int index) {
    return ptrarray ? ptrarray->impl.GetAt(index) : nullptr;
}

DUILIB_C_API void duilib_duiptrarray_set_at(duilib_duiptrarray_t ptrarray, int index, void* ptr) {
    if (ptrarray) {
        ptrarray->impl.SetAt(index, ptr);
    }
}

DUILIB_C_API int duilib_duiptrarray_get_size(duilib_duiptrarray_t ptrarray) {
    return ptrarray ? ptrarray->impl.GetSize() : 0;
}

DUILIB_C_API void** duilib_duiptrarray_get_data(duilib_duiptrarray_t ptrarray) {
    return ptrarray ? ptrarray->impl.GetData() : nullptr;
}

DUILIB_C_API int duilib_duiptrarray_find(duilib_duiptrarray_t ptrarray, void* ptr) {
    return ptrarray ? ptrarray->impl.Find(ptr) : -1;
}

//=============================================================================
// CDuiStringPtrMap implementation  
//=============================================================================

DUILIB_C_API duilib_duistringptrmap_t duilib_duistringptrmap_create(int prealloc_size) {
    return new(std::nothrow) duilib_duistringptrmap(prealloc_size);
}

DUILIB_C_API void duilib_duistringptrmap_destroy(duilib_duistringptrmap_t stringptrmap) {
    delete stringptrmap;
}

DUILIB_C_API bool duilib_duistringptrmap_is_valid(duilib_duistringptrmap_t stringptrmap) {
    return stringptrmap != nullptr;
}

DUILIB_C_API void duilib_duistringptrmap_resize(duilib_duistringptrmap_t stringptrmap, int size) {
    if (stringptrmap) {
        stringptrmap->impl.Resize(size);
    }
}

DUILIB_C_API void* duilib_duistringptrmap_find(duilib_duistringptrmap_t stringptrmap, const char* key, bool optimize) {
    if (!stringptrmap || !key) return nullptr;
    
#ifdef _UNICODE
    int len = MultiByteToWideChar(CP_UTF8, 0, key, -1, nullptr, 0);
    if (len <= 0) return nullptr;
    
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, key, -1, wstr, len);
    void* result = stringptrmap->impl.Find(wstr, optimize);
    delete[] wstr;
    return result;
#else
    return stringptrmap->impl.Find(key, optimize);
#endif
}

DUILIB_C_API bool duilib_duistringptrmap_insert(duilib_duistringptrmap_t stringptrmap, const char* key, void* ptr) {
    if (!stringptrmap || !key) return false;
    
#ifdef _UNICODE
    int len = MultiByteToWideChar(CP_UTF8, 0, key, -1, nullptr, 0);
    if (len <= 0) return false;
    
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, key, -1, wstr, len);
    bool result = stringptrmap->impl.Insert(wstr, ptr);
    delete[] wstr;
    return result;
#else
    return stringptrmap->impl.Insert(key, ptr);
#endif
}

DUILIB_C_API void* duilib_duistringptrmap_set(duilib_duistringptrmap_t stringptrmap, const char* key, void* ptr) {
    if (!stringptrmap || !key) return nullptr;
    
#ifdef _UNICODE
    int len = MultiByteToWideChar(CP_UTF8, 0, key, -1, nullptr, 0);
    if (len <= 0) return nullptr;
    
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, key, -1, wstr, len);
    void* result = stringptrmap->impl.Set(wstr, ptr);
    delete[] wstr;
    return result;
#else
    return stringptrmap->impl.Set(key, ptr);
#endif
}

DUILIB_C_API bool duilib_duistringptrmap_remove(duilib_duistringptrmap_t stringptrmap, const char* key) {
    if (!stringptrmap || !key) return false;
    
#ifdef _UNICODE
    int len = MultiByteToWideChar(CP_UTF8, 0, key, -1, nullptr, 0);
    if (len <= 0) return false;
    
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, key, -1, wstr, len);
    bool result = stringptrmap->impl.Remove(wstr);
    delete[] wstr;
    return result;
#else
    return stringptrmap->impl.Remove(key);
#endif
}

DUILIB_C_API void duilib_duistringptrmap_remove_all(duilib_duistringptrmap_t stringptrmap) {
    if (stringptrmap) {
        stringptrmap->impl.RemoveAll();
    }
}

DUILIB_C_API int duilib_duistringptrmap_get_size(duilib_duistringptrmap_t stringptrmap) {
    return stringptrmap ? stringptrmap->impl.GetSize() : 0;
}

DUILIB_C_API const char* duilib_duistringptrmap_get_at(duilib_duistringptrmap_t stringptrmap, int index) {
    if (!stringptrmap) return nullptr;
    
    LPCTSTR key = stringptrmap->impl.GetAt(index);
    if (!key) return nullptr;
    
    static thread_local char buffer[1024];
#ifdef _UNICODE
    WideCharToMultiByte(CP_UTF8, 0, key, -1, buffer, sizeof(buffer), nullptr, nullptr);
    return buffer;
#else
    return key;
#endif
}

DUILIB_C_API const char* duilib_duistringptrmap_operator_at(duilib_duistringptrmap_t stringptrmap, int index) {
    return duilib_duistringptrmap_get_at(stringptrmap, index);
}

//=============================================================================
// CWaitCursor implementation
//=============================================================================

DUILIB_C_API duilib_waitcursor_t duilib_waitcursor_create(void) {
    return new(std::nothrow) duilib_waitcursor();
}

DUILIB_C_API void duilib_waitcursor_destroy(duilib_waitcursor_t waitcursor) {
    delete waitcursor;
}

DUILIB_C_API bool duilib_waitcursor_is_valid(duilib_waitcursor_t waitcursor) {
    return waitcursor != nullptr;
}

//=============================================================================
// CVariant implementation
//=============================================================================

DUILIB_C_API duilib_variant_t duilib_variant_create(void) {
    return new(std::nothrow) duilib_variant();
}

DUILIB_C_API duilib_variant_t duilib_variant_create_short(short value) {
    return new(std::nothrow) duilib_variant(value);
}

DUILIB_C_API duilib_variant_t duilib_variant_create_int(int value) {
    return new(std::nothrow) duilib_variant(value);
}

DUILIB_C_API duilib_variant_t duilib_variant_create_long(long value) {
    return new(std::nothrow) duilib_variant(value);
}

DUILIB_C_API duilib_variant_t duilib_variant_create_float(float value) {
    return new(std::nothrow) duilib_variant(value);
}

DUILIB_C_API duilib_variant_t duilib_variant_create_double(double value) {
    return new(std::nothrow) duilib_variant(value);
}

DUILIB_C_API duilib_variant_t duilib_variant_create_string(const char* value) {
    if (!value) return nullptr;
    
#ifdef _UNICODE
    int len = MultiByteToWideChar(CP_UTF8, 0, value, -1, nullptr, 0);
    if (len <= 0) return nullptr;
    
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, value, -1, wstr, len);
    duilib_variant* result = new(std::nothrow) duilib_variant(wstr);
    delete[] wstr;
    return result;
#else
    return new(std::nothrow) duilib_variant(value);
#endif
}

DUILIB_C_API void duilib_variant_destroy(duilib_variant_t variant) {
    delete variant;
}

DUILIB_C_API bool duilib_variant_is_valid(duilib_variant_t variant) {
    return variant != nullptr;
}

DUILIB_C_API duilib_variant_type_t duilib_variant_get_type(duilib_variant_t variant) {
    if (!variant) return DUILIB_VARIANT_TYPE_EMPTY;
    
    switch (variant->impl.vt) {
        case VT_I2: return DUILIB_VARIANT_TYPE_SHORT;
        case VT_I4: return DUILIB_VARIANT_TYPE_LONG;
        case VT_R4: return DUILIB_VARIANT_TYPE_FLOAT;
        case VT_R8: return DUILIB_VARIANT_TYPE_DOUBLE;
        case VT_BSTR: return DUILIB_VARIANT_TYPE_STRING;
        default: return DUILIB_VARIANT_TYPE_EMPTY;
    }
}

DUILIB_C_API bool duilib_variant_is_empty(duilib_variant_t variant) {
    return variant ? (variant->impl.vt == VT_EMPTY) : true;
}

DUILIB_C_API short duilib_variant_get_short(duilib_variant_t variant) {
    if (!variant) return 0;
    return variant->impl;
}

DUILIB_C_API int duilib_variant_get_int(duilib_variant_t variant) {
    if (!variant) return 0;
    return variant->impl;
}

DUILIB_C_API long duilib_variant_get_long(duilib_variant_t variant) {
    if (!variant) return 0;
    return variant->impl;
}

DUILIB_C_API float duilib_variant_get_float(duilib_variant_t variant) {
    if (!variant) return 0.0f;
    return variant->impl;
}

DUILIB_C_API double duilib_variant_get_double(duilib_variant_t variant) {
    if (!variant) return 0.0;
    return variant->impl;
}

DUILIB_C_API const char* duilib_variant_get_string(duilib_variant_t variant) {
    if (!variant) return nullptr;
    
    CDuiString str = variant->impl;
    static thread_local char buffer[4096];
#ifdef _UNICODE
    WideCharToMultiByte(CP_UTF8, 0, str.GetData(), -1, buffer, sizeof(buffer), nullptr, nullptr);
    return buffer;
#else
    return str.GetData();
#endif
}

DUILIB_C_API duilib_result_t duilib_variant_set_short(duilib_variant_t variant, short value) {
    if (!variant) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    variant->impl = value;
    return DUILIB_RESULT_OK;
}

DUILIB_C_API duilib_result_t duilib_variant_set_int(duilib_variant_t variant, int value) {
    if (!variant) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    variant->impl = value;
    return DUILIB_RESULT_OK;
}

DUILIB_C_API duilib_result_t duilib_variant_set_long(duilib_variant_t variant, long value) {
    if (!variant) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    variant->impl = value;
    return DUILIB_RESULT_OK;
}

DUILIB_C_API duilib_result_t duilib_variant_set_float(duilib_variant_t variant, float value) {
    if (!variant) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    variant->impl = value;
    return DUILIB_RESULT_OK;
}

DUILIB_C_API duilib_result_t duilib_variant_set_double(duilib_variant_t variant, double value) {
    if (!variant) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    variant->impl = value;
    return DUILIB_RESULT_OK;
}

DUILIB_C_API duilib_result_t duilib_variant_set_string(duilib_variant_t variant, const char* value) {
    if (!variant || !value) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
#ifdef _UNICODE
    int len = MultiByteToWideChar(CP_UTF8, 0, value, -1, nullptr, 0);
    if (len <= 0) return DUILIB_RESULT_ERROR_INVALID_PARAMETER;
    
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_UTF8, 0, value, -1, wstr, len);
    variant->impl = wstr;
    delete[] wstr;
#else
    variant->impl = value;
#endif
    return DUILIB_RESULT_OK;
}

DUILIB_C_API void duilib_variant_clear(duilib_variant_t variant) {
    if (variant) {
        variant->impl.Clear();
    }
}

DUILIB_C_API bool duilib_variant_equals(duilib_variant_t variant, duilib_variant_t other) {
    if (!variant || !other) return false;
    return variant->impl == other->impl;
}