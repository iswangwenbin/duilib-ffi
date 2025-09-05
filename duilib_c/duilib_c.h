#ifndef __DUILIB_C_H__
#define __DUILIB_C_H__

//=============================================================================
// DuiLib C API - Complete API
// 
// 此文件包含DuiLib所有模块的C语言接口
// 对应 duilib/DuiLib 目录下的所有功能
//
// duilib/DuiLib/Core -> duilib_c/core
// duilib/DuiLib/Control -> duilib_c/control
// duilib/DuiLib/Layout -> duilib_c/layout
// duilib/DuiLib/Utils -> duilib_c/utils
//=============================================================================

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
// 核心模块 - Core (对应 duilib/DuiLib/Core)
//=============================================================================
#include "core/duilib_c_base.h"          // 基础类型和结构定义 - UIDefine.h + UIBase.h
#include "core/duilib_c_window.h"        // 窗口API - UIBase.h (CWindowWnd)
#include "core/duilib_c_manager.h"       // 管理器API - UIManager.h (CPaintManagerUI) - must come before control.h
#include "core/duilib_c_control.h"       // 控件基类API - UIControl.h (CControlUI)
#include "core/duilib_c_container.h"     // 容器API - UIContainer.h (CContainerUI)
#include "core/duilib_c_dlgbuilder.h"    // 对话框构建器API - UIDlgBuilder.h (CDialogBuilder)
#include "core/duilib_c_markup.h"        // XML标记解析器API - UIMarkup.h (CMarkup/CMarkupNode)
#include "core/duilib_c_render.h"        // 渲染引擎API - UIRender.h (CRenderEngine/CRenderClip)

//=============================================================================
// 控件模块 - Control (对应 duilib/DuiLib/Control)
//=============================================================================
#include "control/duilib_c_controls.h"    // 所有控件的C API汇总

//=============================================================================
// 布局模块 - Layout (对应 duilib/DuiLib/Layout)
//=============================================================================
#include "layout/duilib_c_layouts.h"      // 所有布局的C API汇总

//=============================================================================
// 工具模块 - Utils (对应 duilib/DuiLib/Utils)
//=============================================================================
#include "utils/duilib_c_utils.h"         // 核心工具类API - Utils.h (STRINGorID, CDuiString, CDuiRect等)
#include "utils/duilib_c_delegate.h"      // 委托系统API - UIDelegate.h (CDelegateBase, CEventSource)
#include "utils/duilib_c_winimplbase.h"   // 窗口实现基类API - WinImplBase.h (WindowImplBase)
#include "utils/duilib_c_wndshadow.h"     // 窗口阴影API - WndShadow.h (CWndShadow)
#include "utils/duilib_c_flash.h"         // Flash事件处理API - FlashEventHandler.h

#ifdef __cplusplus
}
#endif

#endif // __DUILIB_C_H__