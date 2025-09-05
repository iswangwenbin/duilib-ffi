#ifndef __DUILIB_C_MARKUP_H__
#define __DUILIB_C_MARKUP_H__

#include "duilib_c_base.h"

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// XML标记解析器API - 对应 CMarkup
//=============================================================================

// 标记解析器句柄
typedef struct duilib_markup* duilib_markup_t;
typedef struct duilib_markup_node* duilib_markup_node_t;

// XML 编码类型 - 对应原始定义
typedef enum {
    DUILIB_XML_ENCODING_UTF8 = 0,
    DUILIB_XML_ENCODING_UNICODE = 1,
    DUILIB_XML_ENCODING_ANSI = 2
} duilib_xml_encoding_t;

// 创建和销毁标记解析器
DUILIB_C_API duilib_markup_t duilib_markup_create(void);
DUILIB_C_API void duilib_markup_destroy(duilib_markup_t markup);

// 加载XML
DUILIB_C_API bool duilib_markup_load(duilib_markup_t markup, const char* xml);
DUILIB_C_API bool duilib_markup_load_from_file(duilib_markup_t markup, const char* filename, duilib_xml_encoding_t encoding);
DUILIB_C_API bool duilib_markup_load_from_mem(duilib_markup_t markup, const void* data, uint32_t size, duilib_xml_encoding_t encoding);

// CMarkup 缺失方法补充
DUILIB_C_API duilib_result_t duilib_markup_release(duilib_markup_t markup);
DUILIB_C_API bool duilib_markup_is_valid(duilib_markup_t markup);
DUILIB_C_API duilib_result_t duilib_markup_set_preserve_whitespace(duilib_markup_t markup, bool preserve);

// 获取根元素
DUILIB_C_API duilib_markup_node_t duilib_markup_get_root(duilib_markup_t markup);

// 错误处理
DUILIB_C_API duilib_result_t duilib_markup_get_last_error_message(duilib_markup_t markup, char* message, size_t max_chars);
DUILIB_C_API duilib_result_t duilib_markup_get_last_error_location(duilib_markup_t markup, char* source, size_t max_chars);

//=============================================================================
// CMarkupNode API - 对应 CMarkupNode 类
//=============================================================================

// 节点基本操作
DUILIB_C_API bool duilib_markup_node_is_valid(duilib_markup_node_t node);

// 节点导航
DUILIB_C_API duilib_markup_node_t duilib_markup_node_get_parent(duilib_markup_node_t node);
DUILIB_C_API duilib_markup_node_t duilib_markup_node_get_sibling(duilib_markup_node_t node);
DUILIB_C_API duilib_markup_node_t duilib_markup_node_get_child(duilib_markup_node_t node);
DUILIB_C_API duilib_markup_node_t duilib_markup_node_get_child_by_name(duilib_markup_node_t node, const char* name);

// 节点状态查询
DUILIB_C_API bool duilib_markup_node_has_siblings(duilib_markup_node_t node);
DUILIB_C_API bool duilib_markup_node_has_children(duilib_markup_node_t node);

// 节点内容
DUILIB_C_API const char* duilib_markup_node_get_name(duilib_markup_node_t node);
DUILIB_C_API const char* duilib_markup_node_get_value(duilib_markup_node_t node);

// 属性管理
DUILIB_C_API bool duilib_markup_node_has_attributes(duilib_markup_node_t node);
DUILIB_C_API bool duilib_markup_node_has_attribute(duilib_markup_node_t node, const char* name);
DUILIB_C_API int duilib_markup_node_get_attribute_count(duilib_markup_node_t node);

// 属性获取
DUILIB_C_API const char* duilib_markup_node_get_attribute_name(duilib_markup_node_t node, int index);
DUILIB_C_API const char* duilib_markup_node_get_attribute_value_by_index(duilib_markup_node_t node, int index);
DUILIB_C_API const char* duilib_markup_node_get_attribute_value(duilib_markup_node_t node, const char* name);

// 属性获取 - 缓冲区版本（安全版本）
DUILIB_C_API bool duilib_markup_node_get_attribute_value_by_index_safe(duilib_markup_node_t node, int index, char* value, size_t max_chars);
DUILIB_C_API bool duilib_markup_node_get_attribute_value_safe(duilib_markup_node_t node, const char* name, char* value, size_t max_chars);

// 节点销毁（如果需要的话）
DUILIB_C_API void duilib_markup_node_destroy(duilib_markup_node_t node);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_MARKUP_H__