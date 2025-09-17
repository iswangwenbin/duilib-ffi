//==============================================================================
// 安装程序界面 - 纯代码实现
// 使用 duilib_c API 创建安装软件界面，无需XML布局文件
//==============================================================================

#include "../duilib_c/duilib_c.h"
#include <windows.h>
#include <tchar.h>

//==============================================================================
// 安装程序窗口类
//==============================================================================

typedef struct {
    duilib_winimplbase_t window;
    duilib_manager_t paint_manager;
    
    // 主要控件引用
    duilib_button_t btn_close;
    duilib_button_t btn_minimize;
    duilib_button_t btn_install;
    duilib_button_t btn_custom_install;
    duilib_button_t btn_choose_path;
    
    duilib_label_t lbl_title;
    duilib_label_t lbl_status;
    duilib_label_t lbl_install_path;
    duilib_label_t lbl_space_required;
    duilib_label_t lbl_space_available;
    
    duilib_checkbox_t chk_agreement;
    duilib_checkbox_t chk_desktop_shortcut;
    duilib_checkbox_t chk_quick_launch;
    duilib_checkbox_t chk_auto_start;
    
    duilib_edit_t edit_install_path;
    duilib_progress_t progress_install;
    
    duilib_control_t custom_area;  // 自定义安装区域容器
    
    // 状态标志
    bool custom_area_visible;
    bool installation_in_progress;
    
} installer_window_t;

//==============================================================================
// 前向声明
//==============================================================================
void start_installation(installer_window_t* installer);
void simulate_installation_progress(installer_window_t* installer);
void finish_installation(installer_window_t* installer);
void toggle_custom_area(installer_window_t* installer);
void choose_install_path(installer_window_t* installer);

//==============================================================================
// 窗口事件处理函数
//==============================================================================

// 窗口初始化回调
void on_window_init(duilib_winimplbase_t window, void* user_data) {
    installer_window_t* installer = (installer_window_t*)user_data;
    installer->paint_manager = duilib_winimplbase_get_paint_manager(window);
    
    // 创建主布局容器
    duilib_control_t main_layout = duilib_create_layout_by_class("VerticalLayout");
    duilib_control_set_bk_color(main_layout, 0xFFFFFFFF);  // 白色背景
    
    // 设置窗口大小和位置
    duilib_rect_t window_rect = {0, 0, 600, 560};
    duilib_control_set_pos(main_layout, window_rect);
    
    //--------------------------------------------------------------------------
    // 创建标题栏控件（关闭、最小化按钮）
    //--------------------------------------------------------------------------
    
    // 关闭按钮
    installer->btn_close = duilib_button_create();
    duilib_control_t close_control = duilib_button_to_control(installer->btn_close);
    duilib_control_set_name(close_control, "btn_close");
    duilib_control_set_bk_image(close_control, "../nsis/windows_close.png");
    duilib_size_t close_size = {12, 12};
    duilib_control_set_fixed_size(close_control, close_size);
    duilib_rect_t close_padding = {570, 20, 0, 0};
    duilib_control_set_padding(close_control, close_padding);
    
    // 最小化按钮
    installer->btn_minimize = duilib_button_create();
    duilib_control_t minimize_control = duilib_button_to_control(installer->btn_minimize);
    duilib_control_set_name(minimize_control, "btn_minimize");
    duilib_control_set_bk_image(minimize_control, "../nsis/windows_small.png");
    duilib_size_t minimize_size = {12, 12};
    duilib_control_set_fixed_size(minimize_control, minimize_size);
    duilib_rect_t minimize_padding = {545, -7, 0, 0};
    duilib_control_set_padding(minimize_control, minimize_padding);
    
    //--------------------------------------------------------------------------
    // 创建主内容区域
    //--------------------------------------------------------------------------
    
    duilib_control_t content_layout = duilib_create_layout_by_class("VerticalLayout");
    duilib_rect_t content_inset = {0, 60, 0, 0};
    duilib_layout_set_inset(content_layout, content_inset);
    duilib_layout_set_child_padding(content_layout, 5);
    
    // Logo控件
    duilib_control_t logo_control = duilib_create_control_by_class("Control");
    duilib_control_set_bk_image(logo_control, "../nsis/logo.png");
    duilib_size_t logo_size = {64, 64};
    duilib_control_set_fixed_size(logo_control, logo_size);
    duilib_rect_t logo_padding = {270, 20, 0, 0};
    duilib_control_set_padding(logo_control, logo_padding);
    
    // 标题标签
    installer->lbl_title = duilib_label_create();
    duilib_control_t title_control = duilib_label_to_control(installer->lbl_title);
    duilib_label_set_text(installer->lbl_title, "精湛应用商店");
    duilib_control_set_align(title_control, DUILIB_ALIGN_CENTER);
    duilib_control_set_font_size(title_control, 25);
    duilib_control_set_text_color(title_control, 0xFF000000);
    duilib_control_set_font_bold(title_control, true);
    
    // 立即安装按钮
    installer->btn_install = duilib_button_create();
    duilib_control_t install_control = duilib_button_to_control(installer->btn_install);
    duilib_control_set_name(install_control, "btn_install");
    duilib_button_set_text(installer->btn_install, "立即安装");
    duilib_control_set_bk_image(install_control, "../nsis/install_normal.png");
    duilib_size_t install_size = {104, 35};
    duilib_control_set_fixed_size(install_control, install_size);
    duilib_rect_t install_padding = {250, 50, 0, -15};
    duilib_control_set_padding(install_control, install_padding);
    
    // 状态文本
    installer->lbl_status = duilib_label_create();
    duilib_control_t status_control = duilib_label_to_control(installer->lbl_status);
    duilib_control_set_name(status_control, "lbl_status");
    duilib_label_set_text(installer->lbl_status, "状态: 准备安装");
    duilib_control_set_text_color(status_control, 0xFF666666);
    duilib_control_set_bk_color(status_control, 0xFFF5F5F5);
    duilib_rect_t status_padding = {5, 2, 5, 2};
    duilib_control_set_padding(status_control, status_padding);
    
    //--------------------------------------------------------------------------
    // 用户协议区域
    //--------------------------------------------------------------------------
    
    duilib_control_t agreement_layout = duilib_create_layout_by_class("HorizontalLayout");
    duilib_rect_t agreement_padding = {210, 20, 0, 0};
    duilib_control_set_padding(agreement_layout, agreement_padding);
    duilib_control_set_fixed_height(agreement_layout, 35);
    
    // 协议复选框
    installer->chk_agreement = duilib_checkbox_create();
    duilib_control_t agreement_control = duilib_checkbox_to_control(installer->chk_agreement);
    duilib_control_set_name(agreement_control, "chk_agreement");
    duilib_size_t chk_size = {18, 18};
    duilib_control_set_fixed_size(agreement_control, chk_size);
    duilib_rect_t chk_padding = {0, 8, 10, 0};
    duilib_control_set_padding(agreement_control, chk_padding);
    duilib_control_set_foreground_image(agreement_control, "../nsis/checkbox_black_selected.png");
    
    // 协议文本
    duilib_label_t lbl_agreement1 = duilib_label_create();
    duilib_control_t agreement1_control = duilib_label_to_control(lbl_agreement1);
    duilib_label_set_text(lbl_agreement1, "阅读并同意 ");
    duilib_control_set_fixed_width(agreement1_control, 63);
    duilib_control_set_text_color(agreement1_control, 0xFF000000);
    
    duilib_label_t lbl_agreement2 = duilib_label_create();
    duilib_control_t agreement2_control = duilib_label_to_control(lbl_agreement2);
    duilib_label_set_text(lbl_agreement2, "用户协议、隐私条款");
    duilib_control_set_text_color(agreement2_control, 0xFF0066FF);
    duilib_control_set_cursor(agreement2_control, "hand");
    
    //--------------------------------------------------------------------------
    // 自定义安装区域
    //--------------------------------------------------------------------------
    
    duilib_control_t custom_header_layout = duilib_create_layout_by_class("HorizontalLayout");
    duilib_rect_t custom_header_padding = {270, 5, 250, 10};
    duilib_control_set_padding(custom_header_layout, custom_header_padding);
    duilib_control_set_fixed_height(custom_header_layout, 35);
    
    // 自定义安装按钮
    installer->btn_custom_install = duilib_button_create();
    duilib_control_t custom_install_control = duilib_button_to_control(installer->btn_custom_install);
    duilib_control_set_name(custom_install_control, "btn_custom_install");
    duilib_button_set_text(installer->btn_custom_install, "自定义安装");
    duilib_control_set_align(custom_install_control, DUILIB_ALIGN_LEFT);
    duilib_control_set_text_color(custom_install_control, 0xFF888888);
    
    // 下拉按钮
    duilib_button_t btn_dropdown = duilib_button_create();
    duilib_control_t dropdown_control = duilib_button_to_control(btn_dropdown);
    duilib_control_set_name(dropdown_control, "btn_dropdown");
    duilib_control_set_bk_image(dropdown_control, "../nsis/down.png");
    duilib_size_t dropdown_size = {20, 20};
    duilib_control_set_fixed_size(dropdown_control, dropdown_size);
    duilib_rect_t dropdown_padding = {-40, 7, 0, 0};
    duilib_control_set_padding(dropdown_control, dropdown_padding);
    
    // 自定义安装详情区域
    installer->custom_area = duilib_create_layout_by_class("VerticalLayout");
    duilib_control_set_name(installer->custom_area, "custom_area");
    duilib_control_set_visible(installer->custom_area, true);
    duilib_control_set_fixed_height(installer->custom_area, 160);
    duilib_rect_t custom_area_padding = {0, -10, 0, 0};
    duilib_control_set_padding(installer->custom_area, custom_area_padding);
    
    // 安装路径区域
    duilib_control_t path_area = duilib_create_layout_by_class("VerticalLayout");
    duilib_control_set_bk_color(path_area, 0xFFF7F7F7);
    duilib_control_set_bk_image(path_area, "../nsis/customInstallBg.png");
    duilib_rect_t path_area_padding = {20, 0, 20, 0};
    duilib_control_set_padding(path_area, path_area_padding);
    duilib_control_set_fixed_height(path_area, 109);
    
    // 安装位置标签
    installer->lbl_install_path = duilib_label_create();
    duilib_control_t path_label_control = duilib_label_to_control(installer->lbl_install_path);
    duilib_label_set_text(installer->lbl_install_path, "安装位置：");
    duilib_control_set_text_color(path_label_control, 0xFF000000);
    duilib_control_set_fixed_width(path_label_control, 85);
    duilib_rect_t path_label_padding = {20, 10, 0, 0};
    duilib_control_set_padding(path_label_control, path_label_padding);
    
    // 路径输入区域
    duilib_control_t path_input_layout = duilib_create_layout_by_class("HorizontalLayout");
    duilib_rect_t path_input_padding = {20, 5, 20, 0};
    duilib_control_set_padding(path_input_layout, path_input_padding);
    duilib_control_set_fixed_height(path_input_layout, 32);
    
    // 路径编辑框
    installer->edit_install_path = duilib_edit_create();
    duilib_control_t path_edit_control = duilib_edit_to_control(installer->edit_install_path);
    duilib_control_set_name(path_edit_control, "edit_install_path");
    duilib_edit_set_text(installer->edit_install_path, "C:\\Program Files\\MyApp");
    duilib_control_set_fixed_height(path_edit_control, 28);
    
    // 文件夹选择按钮
    installer->btn_choose_path = duilib_button_create();
    duilib_control_t choose_path_control = duilib_button_to_control(installer->btn_choose_path);
    duilib_control_set_name(choose_path_control, "btn_choose_path");
    duilib_control_set_bk_image(choose_path_control, "../nsis/folder.png");
    duilib_size_t choose_path_size = {20, 16};
    duilib_control_set_fixed_size(choose_path_control, choose_path_size);
    duilib_rect_t choose_path_padding = {5, 6, 0, 0};
    duilib_control_set_padding(choose_path_control, choose_path_padding);
    
    // 空间信息区域
    duilib_control_t space_layout = duilib_create_layout_by_class("HorizontalLayout");
    duilib_rect_t space_padding = {20, 8, 0, 5};
    duilib_control_set_padding(space_layout, space_padding);
    duilib_control_set_fixed_height(space_layout, 25);
    
    // 空间信息标签
    installer->lbl_space_required = duilib_label_create();
    duilib_control_t space_req_control = duilib_label_to_control(installer->lbl_space_required);
    duilib_label_set_text(installer->lbl_space_required, "所需空间：275MB");
    duilib_control_set_fixed_width(space_req_control, 135);
    duilib_control_set_text_color(space_req_control, 0xFF101010);
    
    installer->lbl_space_available = duilib_label_create();
    duilib_control_t space_avail_control = duilib_label_to_control(installer->lbl_space_available);
    duilib_label_set_text(installer->lbl_space_available, "磁盘剩余空间：8.5GB");
    duilib_control_set_text_color(space_avail_control, 0xFF666666);
    
    //--------------------------------------------------------------------------
    // 附加选项区域
    //--------------------------------------------------------------------------
    
    duilib_control_t options_layout = duilib_create_layout_by_class("HorizontalLayout");
    duilib_rect_t options_padding = {25, 12, 0, 20};
    duilib_control_set_padding(options_layout, options_padding);
    duilib_control_set_fixed_height(options_layout, 20);
    duilib_layout_set_child_padding(options_layout, 5);
    
    // 快捷启动栏选项
    installer->chk_quick_launch = duilib_checkbox_create();
    duilib_control_t quick_launch_control = duilib_checkbox_to_control(installer->chk_quick_launch);
    duilib_checkbox_set_checked(installer->chk_quick_launch, true);
    duilib_control_set_foreground_image(quick_launch_control, "../nsis/check_project_checked.png");
    duilib_size_t option_chk_size = {12, 12};
    duilib_control_set_fixed_size(quick_launch_control, option_chk_size);
    duilib_rect_t option_chk_padding = {0, 4, 0, 0};
    duilib_control_set_padding(quick_launch_control, option_chk_padding);
    
    duilib_label_t lbl_quick_launch = duilib_label_create();
    duilib_control_t quick_launch_label = duilib_label_to_control(lbl_quick_launch);
    duilib_label_set_text(lbl_quick_launch, "添加到快捷启动栏");
    duilib_control_set_fixed_width(quick_launch_label, 120);
    duilib_control_set_text_color(quick_launch_label, 0xFF000000);
    duilib_rect_t quick_label_padding = {0, 0, 10, 0};
    duilib_control_set_padding(quick_launch_label, quick_label_padding);
    
    // 桌面快捷方式选项
    installer->chk_desktop_shortcut = duilib_checkbox_create();
    duilib_control_t desktop_control = duilib_checkbox_to_control(installer->chk_desktop_shortcut);
    duilib_checkbox_set_checked(installer->chk_desktop_shortcut, true);
    duilib_control_set_foreground_image(desktop_control, "../nsis/check_project_checked.png");
    duilib_control_set_fixed_size(desktop_control, option_chk_size);
    duilib_control_set_padding(desktop_control, option_chk_padding);
    
    duilib_label_t lbl_desktop = duilib_label_create();
    duilib_control_t desktop_label = duilib_label_to_control(lbl_desktop);
    duilib_label_set_text(lbl_desktop, "添加到桌面快捷方式");
    duilib_control_set_fixed_width(desktop_label, 130);
    duilib_control_set_text_color(desktop_label, 0xFF000000);
    duilib_control_set_padding(desktop_label, quick_label_padding);
    
    // 开机自启动选项
    installer->chk_auto_start = duilib_checkbox_create();
    duilib_control_t auto_start_control = duilib_checkbox_to_control(installer->chk_auto_start);
    duilib_checkbox_set_checked(installer->chk_auto_start, true);
    duilib_control_set_foreground_image(auto_start_control, "../nsis/check_project_checked.png");
    duilib_control_set_fixed_size(auto_start_control, option_chk_size);
    duilib_control_set_padding(auto_start_control, option_chk_padding);
    
    duilib_label_t lbl_auto_start = duilib_label_create();
    duilib_control_t auto_start_label = duilib_label_to_control(lbl_auto_start);
    duilib_label_set_text(lbl_auto_start, "开机自启动");
    duilib_control_set_fixed_width(auto_start_label, 80);
    duilib_control_set_text_color(auto_start_label, 0xFF000000);
    duilib_control_set_padding(auto_start_label, quick_label_padding);
    
    //--------------------------------------------------------------------------
    // 进度条（初始隐藏）
    //--------------------------------------------------------------------------
    
    installer->progress_install = duilib_progress_create();
    duilib_control_t progress_control = duilib_progress_to_control(installer->progress_install);
    duilib_control_set_name(progress_control, "progress_install");
    duilib_control_set_visible(progress_control, false);
    duilib_control_set_fixed_height(progress_control, 20);
    duilib_rect_t progress_padding = {50, 10, 50, 0};
    duilib_control_set_padding(progress_control, progress_padding);
    duilib_progress_set_max_value(installer->progress_install, 100);
    duilib_progress_set_value(installer->progress_install, 0);
    
    //--------------------------------------------------------------------------
    // 组装界面布局
    //--------------------------------------------------------------------------
    
    // 添加控件到布局
    duilib_layout_add_control(main_layout, close_control);
    duilib_layout_add_control(main_layout, minimize_control);
    duilib_layout_add_control(content_layout, logo_control);
    duilib_layout_add_control(content_layout, title_control);
    duilib_layout_add_control(content_layout, install_control);
    duilib_layout_add_control(content_layout, status_control);
    
    // 协议区域
    duilib_layout_add_control(agreement_layout, agreement_control);
    duilib_layout_add_control(agreement_layout, agreement1_control);
    duilib_layout_add_control(agreement_layout, agreement2_control);
    duilib_layout_add_control(content_layout, agreement_layout);
    
    // 自定义安装区域
    duilib_layout_add_control(custom_header_layout, custom_install_control);
    duilib_layout_add_control(custom_header_layout, dropdown_control);
    duilib_layout_add_control(content_layout, custom_header_layout);
    
    // 路径输入区域
    duilib_layout_add_control(path_input_layout, path_edit_control);
    duilib_layout_add_control(path_input_layout, choose_path_control);
    duilib_layout_add_control(path_area, path_label_control);
    duilib_layout_add_control(path_area, path_input_layout);
    
    // 空间信息
    duilib_layout_add_control(space_layout, space_req_control);
    duilib_layout_add_control(space_layout, space_avail_control);
    duilib_layout_add_control(path_area, space_layout);
    
    // 选项区域
    duilib_layout_add_control(options_layout, quick_launch_control);
    duilib_layout_add_control(options_layout, quick_launch_label);
    duilib_layout_add_control(options_layout, desktop_control);
    duilib_layout_add_control(options_layout, desktop_label);
    duilib_layout_add_control(options_layout, auto_start_control);
    duilib_layout_add_control(options_layout, auto_start_label);
    
    // 自定义区域组装
    duilib_layout_add_control(installer->custom_area, path_area);
    duilib_layout_add_control(installer->custom_area, options_layout);
    duilib_layout_add_control(content_layout, installer->custom_area);
    
    // 进度条
    duilib_layout_add_control(content_layout, progress_control);
    
    // 主布局组装
    duilib_layout_add_control(main_layout, content_layout);
    
    // 设置根控件
    duilib_manager_set_root_control(installer->paint_manager, main_layout);
    
    // 初始化状态
    installer->custom_area_visible = true;
    installer->installation_in_progress = false;
}

// 按钮点击事件处理
void on_button_click(duilib_winimplbase_t window, const duilib_ui_event_t* msg, void* user_data) {
    installer_window_t* installer = (installer_window_t*)user_data;
    const char* control_name = duilib_control_get_name(msg->sender);
    
    if (strcmp(control_name, "btn_close") == 0) {
        // 关闭窗口
        duilib_winimplbase_close_window(window, 0);
        
    } else if (strcmp(control_name, "btn_minimize") == 0) {
        // 最小化窗口
        ShowWindow((HWND)duilib_window_get_hwnd(duilib_winimplbase_to_window(window)), SW_MINIMIZE);
        
    } else if (strcmp(control_name, "btn_install") == 0) {
        // 开始安装
        if (!installer->installation_in_progress) {
            start_installation(installer);
        }
        
    } else if (strcmp(control_name, "btn_custom_install") == 0) {
        // 切换自定义安装区域显示/隐藏
        toggle_custom_area(installer);
        
    } else if (strcmp(control_name, "btn_choose_path") == 0) {
        // 选择安装路径
        choose_install_path(installer);
    }
}

// 通知事件处理
void on_notify(duilib_winimplbase_t window, const duilib_ui_event_t* msg, void* user_data) {
    installer_window_t* installer = (installer_window_t*)user_data;
    
    if (msg->type == DUILIB_EVENT_CLICK) {
        on_button_click(window, msg, user_data);
    }
}

//==============================================================================
// 安装程序功能实现
//==============================================================================

// 开始安装
void start_installation(installer_window_t* installer) {
    installer->installation_in_progress = true;
    
    // 更新界面状态
    duilib_label_set_text(installer->lbl_status, "状态: 正在安装...");
    duilib_button_set_text(installer->btn_install, "安装中...");
    duilib_control_set_enabled(duilib_button_to_control(installer->btn_install), false);
    
    // 显示进度条
    duilib_control_t progress_control = duilib_progress_to_control(installer->progress_install);
    duilib_control_set_visible(progress_control, true);
    
    // 这里可以启动一个线程执行实际的安装逻辑
    // 为演示目的，我们使用定时器模拟进度
    simulate_installation_progress(installer);
}

// 模拟安装进度（在实际项目中应该用线程处理）
void simulate_installation_progress(installer_window_t* installer) {
    // 这是一个简化的示例，实际项目中应该使用定时器或线程
    for (int i = 0; i <= 100; i += 10) {
        duilib_progress_set_value(installer->progress_install, i);
        
        // 更新状态文本
        char status_text[256];
        sprintf(status_text, "状态: 正在安装... %d%%", i);
        duilib_label_set_text(installer->lbl_status, status_text);
        
        // 刷新界面
        duilib_winimplbase_invalidate(installer->window);
        
        // 模拟耗时操作
        Sleep(200);
    }
    
    // 安装完成
    finish_installation(installer);
}

// 完成安装
void finish_installation(installer_window_t* installer) {
    installer->installation_in_progress = false;
    
    duilib_label_set_text(installer->lbl_status, "状态: 安装完成！");
    duilib_button_set_text(installer->btn_install, "完成");
    duilib_control_set_enabled(duilib_button_to_control(installer->btn_install), true);
    
    // 隐藏进度条
    duilib_control_t progress_control = duilib_progress_to_control(installer->progress_install);
    duilib_control_set_visible(progress_control, false);
}

// 切换自定义安装区域
void toggle_custom_area(installer_window_t* installer) {
    installer->custom_area_visible = !installer->custom_area_visible;
    duilib_control_set_visible(installer->custom_area, installer->custom_area_visible);
    
    // 刷新布局
    duilib_winimplbase_invalidate(installer->window);
}

// 选择安装路径
void choose_install_path(installer_window_t* installer) {
    // 打开文件夹选择对话框
    char selected_path[MAX_PATH] = {0};
    
    // 这里应该使用Windows API打开文件夹选择对话框
    // 为简化示例，我们直接设置一个默认路径
    strcpy(selected_path, "C:\\Program Files\\MyApp");
    
    // 更新路径编辑框
    duilib_edit_set_text(installer->edit_install_path, selected_path);
}

//==============================================================================
// 主程序入口
//==============================================================================

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 初始化COM
    CoInitialize(NULL);
    
    // 创建安装程序窗口实例
    installer_window_t installer = {0};
    
    // 配置窗口创建参数
    duilib_winimpl_config_t config = {0};
    config.skin_folder = "../nsis";  // 资源文件夹
    config.window_class_name = "InstallerWindow";
    config.resource_type = DUILIB_RESOURCE_TYPE_FILE;
    config.class_style = CS_HREDRAW | CS_VREDRAW;
    config.window_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    
    // 设置回调函数
    config.init_callback = on_window_init;
    config.notify_callback = on_notify;
    config.user_data = &installer;
    
    // 创建窗口
    installer.window = duilib_winimplbase_create(&config);
    
    if (!installer.window) {
        MessageBox(NULL, _T("创建窗口失败！"), _T("错误"), MB_OK | MB_ICONERROR);
        CoUninitialize();
        return -1;
    }
    
    // 设置窗口标题和图标
    duilib_winimplbase_set_window_text(installer.window, "应用安装程序");
    
    // 创建并显示窗口
    duilib_winimplbase_create_window(installer.window, NULL, "InstallerWindow", 
                                    WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 0);
    
    // 居中显示
    duilib_winimplbase_center_window(installer.window);
    
    // 显示窗口
    duilib_winimplbase_show_window(installer.window, true, true);
    
    // 消息循环
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (!IsDialogMessage((HWND)duilib_window_get_hwnd(duilib_winimplbase_to_window(installer.window)), &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    
    // 清理资源
    duilib_winimplbase_destroy(installer.window);
    CoUninitialize();
    
    return (int)msg.wParam;
}

//==============================================================================
// 编译说明
//==============================================================================

/*
编译此文件需要：

1. 包含duilib_c目录到包含路径
2. 链接duilib_c库文件
3. 链接Windows系统库：user32.lib, gdi32.lib, ole32.lib, comctl32.lib

示例编译命令（使用MSVC）：
cl installer_window_code.cpp /I"../duilib_c" /link duilib_c.lib user32.lib gdi32.lib ole32.lib comctl32.lib

功能特性：
- 完全用C代码创建界面，无需XML
- 包含完整的安装程序界面元素
- 支持自定义安装选项
- 实时进度显示
- 事件驱动的交互逻辑
- 模块化的代码结构

这个示例展示了如何使用duilib_c API创建一个功能完整的安装程序界面，
所有界面元素都是通过代码动态创建和配置的。
*/