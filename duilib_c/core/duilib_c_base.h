#ifndef __DUILIB_C_BASE_H__
#define __DUILIB_C_BASE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <windows.h>
#include <stdint.h>
#include <stdbool.h>

// API导出宏
#ifdef DUILIB_C_EXPORTS
    #define DUILIB_C_API __declspec(dllexport)
#else
    #define DUILIB_C_API __declspec(dllimport)
#endif

// 错误码定义
typedef enum {
    DUILIB_OK = 0,
    DUILIB_ERROR_INVALID_PARAM = -1,
    DUILIB_ERROR_NOT_INITIALIZED = -2,
    DUILIB_ERROR_NOT_FOUND = -3,
    DUILIB_ERROR_MEMORY = -4,
    DUILIB_ERROR_UNKNOWN = -999
} duilib_result_t;

// 前置声明 - 不透明指针
typedef struct duilib_manager* duilib_manager_t;
typedef struct duilib_control* duilib_control_t;
typedef struct duilib_window* duilib_window_t;
typedef struct duilib_notify_pump* duilib_notify_pump_t;

// 事件类型
typedef enum {
    DUILIB_EVENT_CLICK = 1,
    DUILIB_EVENT_BUTTON_DOWN,
    DUILIB_EVENT_BUTTON_UP,
    DUILIB_EVENT_MOUSE_ENTER,
    DUILIB_EVENT_MOUSE_LEAVE,
    DUILIB_EVENT_KEY_DOWN,
    DUILIB_EVENT_KEY_UP,
    DUILIB_EVENT_TEXT_CHANGED,
    DUILIB_EVENT_VALUE_CHANGED,
    DUILIB_EVENT_WINDOW_CLOSE
} duilib_event_type_t;

// 事件结构体
typedef struct {
    duilib_event_type_t type;
    duilib_control_t sender;
    void* user_data;
    union {
        struct {
            int x, y;
            int button;
        } mouse;
        struct {
            int key_code;
            int modifiers;
        } key;
        struct {
            const char* text;
        } text;
    } data;
} duilib_event_t;

// 事件回调函数类型
typedef void (*duilib_event_callback_t)(const duilib_event_t* event);

// 消息映射结构体 - 对应 DUI_MSGMAP_ENTRY
typedef struct {
    const char* msg_type;        // 消息类型
    const char* ctrl_name;       // 控件名称
    uint32_t sig;                // 签名类型
    duilib_event_callback_t pfn; // 处理函数
} duilib_msgmap_entry_t;

// 消息映射表 - 对应 DUI_MSGMAP  
typedef struct {
    const void* base_map;                    // 基础映射表
    const duilib_msgmap_entry_t* entries;    // 条目数组
} duilib_msgmap_t;

// 消息签名类型 - 对应 DuiSig
typedef enum {
    DUILIB_SIG_END = 0,   // 标记消息映射结束
    DUILIB_SIG_LWL,       // LRESULT (WPARAM, LPARAM)  
    DUILIB_SIG_VN         // void (TNotifyUI)
} duilib_sig_t;

// 矩形结构
typedef struct {
    int left, top, right, bottom;
} duilib_rect_t;

// 尺寸结构
typedef struct {
    int width, height;
} duilib_size_t;

// 点结构
typedef struct {
    int x, y;
} duilib_point_t;

// 浮动百分比结构
typedef struct {
    double left, top, right, bottom;
} duilib_float_percent_t;

// 颜色定义
typedef uint32_t duilib_color_t;

//=============================================================================
// UIDefine.h 常量定义补充
//=============================================================================

// 窗口样式常量
#define DUILIB_WNDSTYLE_CONTAINER  (0)
#define DUILIB_WNDSTYLE_FRAME      (0x16CF0000L) // WS_VISIBLE | WS_OVERLAPPEDWINDOW
#define DUILIB_WNDSTYLE_CHILD      (0x56000000L) // WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN  
#define DUILIB_WNDSTYLE_DIALOG     (0x96C80000L) // WS_VISIBLE | WS_POPUPWINDOW | WS_CAPTION | WS_DLGFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN

#define DUILIB_WNDSTYLE_EX_FRAME   (0x00000100L) // WS_EX_WINDOWEDGE
#define DUILIB_WNDSTYLE_EX_DIALOG  (0x00000088L) // WS_EX_TOOLWINDOW | WS_EX_DLGMODALFRAME

#define DUILIB_CLASSSTYLE_CONTAINER  (0)
#define DUILIB_CLASSSTYLE_FRAME      (0x00000003L) // CS_VREDRAW | CS_HREDRAW
#define DUILIB_CLASSSTYLE_CHILD      (0x00000203L) // CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS
#define DUILIB_CLASSSTYLE_DIALOG     (0x00000203L) // CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS

// DUI消息类型常量
#define DUILIB_MSGTYPE_MENU                   "menu"
#define DUILIB_MSGTYPE_LINK                   "link"
#define DUILIB_MSGTYPE_TIMER                  "timer"
#define DUILIB_MSGTYPE_CLICK                  "click"
#define DUILIB_MSGTYPE_RETURN                 "return"
#define DUILIB_MSGTYPE_SCROLL                 "scroll"
#define DUILIB_MSGTYPE_DROPDOWN               "dropdown"
#define DUILIB_MSGTYPE_SETFOCUS               "setfocus"
#define DUILIB_MSGTYPE_KILLFOCUS              "killfocus"
#define DUILIB_MSGTYPE_ITEMCLICK              "itemclick"
#define DUILIB_MSGTYPE_TABSELECT              "tabselect"
#define DUILIB_MSGTYPE_ITEMSELECT             "itemselect"
#define DUILIB_MSGTYPE_ITEMEXPAND             "itemexpand"
#define DUILIB_MSGTYPE_WINDOWINIT             "windowinit"
#define DUILIB_MSGTYPE_BUTTONDOWN             "buttondown"
#define DUILIB_MSGTYPE_MOUSEENTER             "mouseenter"
#define DUILIB_MSGTYPE_MOUSELEAVE             "mouseleave"
#define DUILIB_MSGTYPE_TEXTCHANGED            "textchanged"
#define DUILIB_MSGTYPE_HEADERCLICK            "headerclick"
#define DUILIB_MSGTYPE_ITEMDBCLICK            "itemdbclick"
#define DUILIB_MSGTYPE_SHOWACTIVEX            "showactivex"
#define DUILIB_MSGTYPE_ITEMCOLLAPSE           "itemcollapse"
#define DUILIB_MSGTYPE_ITEMACTIVATE           "itemactivate"
#define DUILIB_MSGTYPE_VALUECHANGED           "valuechanged"
#define DUILIB_MSGTYPE_SELECTCHANGED          "selectchanged"

// 控件名称常量
#define DUILIB_CTR_EDIT                       "Edit"
#define DUILIB_CTR_LIST                       "List"
#define DUILIB_CTR_TEXT                       "Text"
#define DUILIB_CTR_TREE                       "Tree"
#define DUILIB_CTR_HBOX                       "HBox"
#define DUILIB_CTR_VBOX                       "VBox"
#define DUILIB_CTR_ILIST                      "IList"
#define DUILIB_CTR_COMBO                      "Combo"
#define DUILIB_CTR_LABEL                      "Label"
#define DUILIB_CTR_FLASH                      "Flash"
#define DUILIB_CTR_BUTTON                     "Button"
#define DUILIB_CTR_OPTION                     "Option"
#define DUILIB_CTR_SLIDER                     "Slider"
#define DUILIB_CTR_CONTROL                    "Control"
#define DUILIB_CTR_ACTIVEX                    "ActiveX"
#define DUILIB_CTR_GIFANIM                    "GifAnim"
#define DUILIB_CTR_PROGRESS                   "Progress"
#define DUILIB_CTR_RICHEDIT                   "RichEdit"
#define DUILIB_CTR_CHECKBOX                   "CheckBox"
#define DUILIB_CTR_COMBOBOX                   "ComboBox"
#define DUILIB_CTR_DATETIME                   "DateTime"
#define DUILIB_CTR_TREEVIEW                   "TreeView"
#define DUILIB_CTR_TREENODE                   "TreeNode"
#define DUILIB_CTR_ILISTITEM                  "IListItem"
#define DUILIB_CTR_CONTAINER                  "Container"
#define DUILIB_CTR_TABLAYOUT                  "TabLayout"
#define DUILIB_CTR_SCROLLBAR                  "ScrollBar"
#define DUILIB_CTR_ICONTAINER                 "IContainer"
#define DUILIB_CTR_ILISTOWNER                 "IListOwner"
#define DUILIB_CTR_LISTHEADER                 "ListHeader"
#define DUILIB_CTR_TILELAYOUT                 "TileLayout"
#define DUILIB_CTR_WEBBROWSER                 "WebBrowser"
#define DUILIB_CTR_CHILDLAYOUT                "ChildLayout"
#define DUILIB_CTR_LISTELEMENT                "ListElement"
#define DUILIB_CTR_VIRTUALLIST                "VirtualList"
#define DUILIB_CTR_VERTICALLAYOUT             "VerticalLayout"
#define DUILIB_CTR_LISTHEADERITEM             "ListHeaderItem"
#define DUILIB_CTR_LISTHBOXELEMENT            "ListHBoxElement"
#define DUILIB_CTR_LISTTEXTELEMENT            "ListTextElement"
#define DUILIB_CTR_HORIZONTALLAYOUT           "HorizontalLayout"
#define DUILIB_CTR_LISTLABELELEMENT           "ListLabelElement"
#define DUILIB_CTR_LISTCONTAINERELEMENT       "ListContainerElement"

// 控件查找标志
#define DUILIB_FIND_ALL           0x00000000
#define DUILIB_FIND_VISIBLE       0x00000001
#define DUILIB_FIND_ENABLED       0x00000002
#define DUILIB_FIND_HITTEST       0x00000004
#define DUILIB_FIND_UPDATETEST    0x00000008
#define DUILIB_FIND_TOP_FIRST     0x00000010
#define DUILIB_FIND_ME_FIRST      0x80000000

// 控件标志
#define DUILIB_FLAG_TABSTOP       0x00000001
#define DUILIB_FLAG_SETCURSOR     0x00000002
#define DUILIB_FLAG_WANTRETURN    0x00000004

// 布局拉伸标志
#define DUILIB_STRETCH_NEWGROUP   0x00000001
#define DUILIB_STRETCH_NEWLINE    0x00000002
#define DUILIB_STRETCH_MOVE_X     0x00000004
#define DUILIB_STRETCH_MOVE_Y     0x00000008
#define DUILIB_STRETCH_SIZE_X     0x00000010
#define DUILIB_STRETCH_SIZE_Y     0x00000020

// 控件状态标志
#define DUILIB_STATE_FOCUSED      0x00000001
#define DUILIB_STATE_SELECTED     0x00000002
#define DUILIB_STATE_DISABLED     0x00000004
#define DUILIB_STATE_HOT          0x00000008
#define DUILIB_STATE_PUSHED       0x00000010
#define DUILIB_STATE_READONLY     0x00000020
#define DUILIB_STATE_CAPTURED     0x00000040

// 辅助宏定义
#define DUILIB_COLOR_RGB(r, g, b) (((uint32_t)(r) << 16) | ((uint32_t)(g) << 8) | (uint32_t)(b))
#define DUILIB_COLOR_ARGB(a, r, g, b) (((uint32_t)(a) << 24) | ((uint32_t)(r) << 16) | ((uint32_t)(g) << 8) | (uint32_t)(b))

#define DUILIB_RECT(l, t, r, b) {l, t, r, b}
#define DUILIB_SIZE(w, h) {w, h}

//=============================================================================
// 核心初始化API
//=============================================================================

// 初始化duilib库
DUILIB_C_API duilib_result_t duilib_init(void);

// 清理duilib库
DUILIB_C_API void duilib_cleanup(void);

//=============================================================================
// 消息循环API
//=============================================================================

// 运行消息循环
DUILIB_C_API int duilib_message_loop(void);

// 处理单个消息
DUILIB_C_API bool duilib_translate_message(MSG* msg);

// 退出消息循环
DUILIB_C_API void duilib_quit_message_loop(int exit_code);

//=============================================================================
// 内存管理API
//=============================================================================

// 释放控件包装器（重要：避免内存泄漏）
DUILIB_C_API void duilib_control_destroy(duilib_control_t control);

//=============================================================================
// 工具函数API
//=============================================================================

// 设置资源路径
DUILIB_C_API duilib_result_t duilib_set_resource_path(const char* path);

// 设置资源ZIP文件
DUILIB_C_API duilib_result_t duilib_set_resource_zip(const char* zip_file);

// 全局静态方法
DUILIB_C_API void* duilib_get_instance(void);
DUILIB_C_API const char* duilib_get_instance_path(void);
DUILIB_C_API const char* duilib_get_current_path(void);
DUILIB_C_API void* duilib_get_resource_dll(void);
DUILIB_C_API const char* duilib_get_resource_zip(void);
DUILIB_C_API bool duilib_is_cached_resource_zip(void);
DUILIB_C_API void* duilib_get_resource_zip_handle(void);
DUILIB_C_API duilib_result_t duilib_set_instance(void* hinst);
DUILIB_C_API duilib_result_t duilib_set_current_path(const char* path);
DUILIB_C_API duilib_result_t duilib_set_resource_dll(void* hinst);
DUILIB_C_API duilib_result_t duilib_get_hsl(short* h, short* s, short* l);
DUILIB_C_API duilib_result_t duilib_set_hsl(bool use_hsl, short h, short s, short l);
DUILIB_C_API duilib_result_t duilib_reload_skin(void);
DUILIB_C_API duilib_manager_t duilib_get_paint_manager(const char* name);
DUILIB_C_API duilib_result_t duilib_load_plugin(const char* module_name);

//=============================================================================
// 消息泵 API - 对应 CNotifyPump
//=============================================================================

// 创建和销毁消息泵
DUILIB_C_API duilib_notify_pump_t duilib_notify_pump_create(void);
DUILIB_C_API void duilib_notify_pump_destroy(duilib_notify_pump_t pump);

// 虚拟窗口管理
DUILIB_C_API bool duilib_notify_pump_add_virtual_wnd(duilib_notify_pump_t pump, const char* name, duilib_notify_pump_t object);
DUILIB_C_API bool duilib_notify_pump_remove_virtual_wnd(duilib_notify_pump_t pump, const char* name);

// 消息处理
DUILIB_C_API duilib_result_t duilib_notify_pump_notify(duilib_notify_pump_t pump, const duilib_event_t* msg);
DUILIB_C_API bool duilib_notify_pump_loop_dispatch(duilib_notify_pump_t pump, const duilib_event_t* msg);

// 消息映射管理
DUILIB_C_API duilib_result_t duilib_notify_pump_set_message_map(duilib_notify_pump_t pump, const duilib_msgmap_t* message_map);
DUILIB_C_API const duilib_msgmap_t* duilib_notify_pump_get_message_map(duilib_notify_pump_t pump);

// 多语言支持
DUILIB_C_API duilib_result_t duilib_add_multi_language_string(int id, const char* text);
DUILIB_C_API const char* duilib_get_multi_language_string(int id);
DUILIB_C_API duilib_result_t duilib_remove_multi_language_string(int id);
DUILIB_C_API duilib_result_t duilib_remove_all_multi_language_strings(void);

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_BASE_H__