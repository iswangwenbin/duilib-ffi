//==============================================================================
// NSIS插件 - DuiLib_C 安装界面插件
// 为NSIS安装程序提供自定义DuiLib界面支持
//==============================================================================

#include "../duilib_c/duilib_c.h"
#include "../duilib_c/nsis/api.h"
#include "../duilib_c/nsis/pluginapi.h"
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

//==============================================================================
// 插件全局变量
//==============================================================================

static HINSTANCE g_hInstance = NULL;
static installer_window_t* g_pInstaller = NULL;
static HWND g_hwndParent = NULL;

// NSIS插件必需的导出变量
HWND g_hwndParent;
int g_stringsize = 1024;
TCHAR *g_variables;

//==============================================================================
// 安装程序窗口结构 (从之前的代码复用)
//==============================================================================

typedef struct {
    duilib_winimplbase_t window;
    duilib_manager_t paint_manager;
    
    // 控件句柄
    duilib_button_t btn_close;
    duilib_button_t btn_minimize;
    duilib_button_t btn_install;
    duilib_button_t btn_custom_install;
    duilib_button_t btn_choose_path;
    
    duilib_label_t lbl_title;
    duilib_label_t lbl_status;
    duilib_progress_t progress_install;
    duilib_edit_t edit_install_path;
    duilib_control_t custom_area;
    
    // NSIS回调相关
    char install_path[MAX_PATH];
    int install_progress;
    BOOL install_cancelled;
    BOOL custom_area_visible;
    
} installer_window_t;

//==============================================================================
// NSIS回调函数
//==============================================================================

// 从NSIS获取安装路径
void nsis_get_install_dir(char* path, int max_len) {
    // 通过NSIS API获取$INSTDIR变量
    getuservar(INST_0, path, max_len);  // $0 = $INSTDIR
}

// 向NSIS设置安装路径
void nsis_set_install_dir(const char* path) {
    // 通过NSIS API设置$INSTDIR变量
    setuservar(INST_0, path);  // $0 = new install path
}

// 向NSIS报告安装进度
void nsis_report_progress(int progress) {
    char progress_str[32];
    sprintf(progress_str, "%d", progress);
    setuservar(INST_1, progress_str);  // $1 = progress percentage
}

// 向NSIS报告安装状态
void nsis_report_status(const char* status) {
    setuservar(INST_2, status);  // $2 = status message
}

//==============================================================================
// DuiLib事件处理函数
//==============================================================================

// 窗口初始化回调
void on_installer_init(duilib_winimplbase_t window, void* user_data) {
    installer_window_t* installer = (installer_window_t*)user_data;
    installer->paint_manager = duilib_winimplbase_get_paint_manager(window);
    
    // 创建界面布局 (使用之前的代码)
    create_installer_layout(installer);
    
    // 从NSIS获取初始安装路径
    nsis_get_install_dir(installer->install_path, sizeof(installer->install_path));
    if (strlen(installer->install_path) > 0) {
        duilib_edit_set_text(installer->edit_install_path, installer->install_path);
    }
}

// 按钮点击事件处理
void on_installer_click(duilib_winimplbase_t window, const duilib_ui_event_t* msg, void* user_data) {
    installer_window_t* installer = (installer_window_t*)user_data;
    const char* control_name = duilib_control_get_name(msg->sender);
    
    if (strcmp(control_name, "btn_close") == 0) {
        // 用户取消安装
        installer->install_cancelled = TRUE;
        nsis_report_status("用户取消安装");
        duilib_winimplbase_close_window(window, IDCANCEL);
        
    } else if (strcmp(control_name, "btn_install") == 0) {
        // 开始安装 - 通知NSIS开始安装流程
        const char* current_path = duilib_edit_get_text(installer->edit_install_path);
        strcpy(installer->install_path, current_path);
        nsis_set_install_dir(installer->install_path);
        nsis_report_status("开始安装");
        
        // 更新界面状态
        duilib_label_set_text(installer->lbl_status, "状态: 正在安装...");
        duilib_button_set_text(installer->btn_install, "安装中...");
        duilib_control_set_enabled(duilib_button_to_control(installer->btn_install), false);
        duilib_control_set_visible(duilib_progress_to_control(installer->progress_install), true);
        
        // 通知NSIS可以开始安装
        duilib_winimplbase_close_window(window, IDOK);
        
    } else if (strcmp(control_name, "btn_custom_install") == 0) {
        // 切换自定义安装区域
        installer->custom_area_visible = !installer->custom_area_visible;
        duilib_control_set_visible(installer->custom_area, installer->custom_area_visible);
        duilib_winimplbase_invalidate(window);
        
    } else if (strcmp(control_name, "btn_choose_path") == 0) {
        // 选择安装路径
        char selected_path[MAX_PATH] = {0};
        if (browse_for_folder(selected_path, sizeof(selected_path))) {
            duilib_edit_set_text(installer->edit_install_path, selected_path);
        }
    }
}

//==============================================================================
// 界面布局创建函数 (简化版)
//==============================================================================

void create_installer_layout(installer_window_t* installer) {
    // 创建主布局容器
    duilib_control_t main_layout = duilib_create_layout_by_class("VerticalLayout");
    duilib_control_set_bk_color(main_layout, 0xFFFFFFFF);
    
    // 创建主要控件
    installer->lbl_title = duilib_label_create();
    duilib_control_t title_control = duilib_label_to_control(installer->lbl_title);
    duilib_label_set_text(installer->lbl_title, "应用程序安装向导");
    duilib_control_set_align(title_control, DUILIB_ALIGN_CENTER);
    duilib_control_set_font_size(title_control, 18);
    duilib_control_set_text_color(title_control, 0xFF000000);
    
    // 状态标签
    installer->lbl_status = duilib_label_create();
    duilib_control_t status_control = duilib_label_to_control(installer->lbl_status);
    duilib_label_set_text(installer->lbl_status, "准备安装");
    duilib_control_set_text_color(status_control, 0xFF666666);
    
    // 安装路径编辑框
    installer->edit_install_path = duilib_edit_create();
    duilib_control_t path_control = duilib_edit_to_control(installer->edit_install_path);
    duilib_edit_set_text(installer->edit_install_path, "C:\\Program Files\\MyApp");
    
    // 安装按钮
    installer->btn_install = duilib_button_create();
    duilib_control_t install_control = duilib_button_to_control(installer->btn_install);
    duilib_control_set_name(install_control, "btn_install");
    duilib_button_set_text(installer->btn_install, "立即安装");
    
    // 取消按钮
    installer->btn_close = duilib_button_create();
    duilib_control_t close_control = duilib_button_to_control(installer->btn_close);
    duilib_control_set_name(close_control, "btn_close");
    duilib_button_set_text(installer->btn_close, "取消");
    
    // 进度条
    installer->progress_install = duilib_progress_create();
    duilib_control_t progress_control = duilib_progress_to_control(installer->progress_install);
    duilib_control_set_visible(progress_control, false);
    duilib_progress_set_max_value(installer->progress_install, 100);
    duilib_progress_set_value(installer->progress_install, 0);
    
    // 布局组装
    duilib_layout_add_control(main_layout, title_control);
    duilib_layout_add_control(main_layout, status_control);
    duilib_layout_add_control(main_layout, path_control);
    duilib_layout_add_control(main_layout, install_control);
    duilib_layout_add_control(main_layout, close_control);
    duilib_layout_add_control(main_layout, progress_control);
    
    // 设置根控件
    duilib_manager_set_root_control(installer->paint_manager, main_layout);
}

//==============================================================================
// 文件夹选择对话框
//==============================================================================

BOOL browse_for_folder(char* selected_path, int max_len) {
    BROWSEINFO bi = {0};
    ITEMIDLIST* pidl;
    char display_name[MAX_PATH];
    
    bi.hwndOwner = (HWND)duilib_window_get_hwnd(duilib_winimplbase_to_window(g_pInstaller->window));
    bi.pszDisplayName = display_name;
    bi.lpszTitle = "选择安装目录";
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    
    pidl = SHBrowseForFolder(&bi);
    if (pidl) {
        SHGetPathFromIDList(pidl, selected_path);
        CoTaskMemFree(pidl);
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
// NSIS插件导出函数
//==============================================================================

// 显示自定义安装界面
extern "C" __declspec(dllexport) void ShowInstaller(HWND hwndParent, int string_size, 
                                                    TCHAR* variables, stack_t** stacktop,
                                                    extra_parameters* extra) {
    EXDLL_INIT();
    
    // 初始化COM
    CoInitialize(NULL);
    
    // 创建安装程序实例
    g_pInstaller = new installer_window_t();
    memset(g_pInstaller, 0, sizeof(installer_window_t));
    
    // 配置窗口
    duilib_winimpl_config_t config = {0};
    config.window_class_name = "NSISInstallerWindow";
    config.resource_type = DUILIB_RESOURCE_TYPE_FILE;
    config.class_style = CS_HREDRAW | CS_VREDRAW;
    config.window_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
    config.init_callback = on_installer_init;
    config.click_callback = on_installer_click;
    config.user_data = g_pInstaller;
    
    // 创建窗口
    g_pInstaller->window = duilib_winimplbase_create(&config);
    if (!g_pInstaller->window) {
        pushstring("ERROR: 无法创建安装界面");
        goto cleanup;
    }
    
    // 设置窗口标题
    duilib_winimplbase_set_window_text(g_pInstaller->window, "安装程序");
    
    // 创建并显示窗口
    duilib_winimplbase_create_window(g_pInstaller->window, hwndParent, "NSISInstallerWindow", 
                                    WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, 0);
    duilib_winimplbase_center_window(g_pInstaller->window);
    
    // 模态显示
    int result = duilib_winimplbase_show_modal(g_pInstaller->window, hwndParent);
    
    // 返回结果
    if (result == IDOK) {
        pushstring("OK");
    } else if (result == IDCANCEL) {
        pushstring("CANCEL");
    } else {
        pushstring("ERROR");
    }
    
cleanup:
    // 清理资源
    if (g_pInstaller) {
        if (g_pInstaller->window) {
            duilib_winimplbase_destroy(g_pInstaller->window);
        }
        delete g_pInstaller;
        g_pInstaller = NULL;
    }
    CoUninitialize();
}

// 更新安装进度
extern "C" __declspec(dllexport) void UpdateProgress(HWND hwndParent, int string_size,
                                                     TCHAR* variables, stack_t** stacktop,
                                                     extra_parameters* extra) {
    EXDLL_INIT();
    
    // 从堆栈获取进度值
    TCHAR progress_str[64];
    popstring(progress_str);
    int progress = _ttoi(progress_str);
    
    if (g_pInstaller && g_pInstaller->progress_install) {
        duilib_progress_set_value(g_pInstaller->progress_install, progress);
        
        // 更新状态文本
        TCHAR status_text[256];
        _stprintf(status_text, _T("正在安装... %d%%"), progress);
        duilib_label_set_text(g_pInstaller->lbl_status, status_text);
        
        // 刷新界面
        if (g_pInstaller->window) {
            duilib_winimplbase_invalidate(g_pInstaller->window);
        }
    }
    
    pushstring("OK");
}

// 获取安装路径
extern "C" __declspec(dllexport) void GetInstallPath(HWND hwndParent, int string_size,
                                                     TCHAR* variables, stack_t** stacktop,
                                                     extra_parameters* extra) {
    EXDLL_INIT();
    
    if (g_pInstaller && g_pInstaller->edit_install_path) {
        const char* path = duilib_edit_get_text(g_pInstaller->edit_install_path);
        pushstring(path ? path : "");
    } else {
        pushstring("");
    }
}

//==============================================================================
// DLL入口点
//==============================================================================

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            g_hInstance = hInst;
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}