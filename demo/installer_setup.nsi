;==============================================================================
; NSIS 安装脚本 - 配合 DuiLib_C 自定义界面
; 使用自定义DuiLib界面替代默认NSIS界面
;==============================================================================

!include "LogicLib.nsh"
!include "MUI2.nsh"
!include "FileFunc.nsh"

;==============================================================================
; 安装程序基本信息
;==============================================================================

Name "我的应用程序"
OutFile "MyAppInstaller.exe"
InstallDir "$PROGRAMFILES\MyApp"
RequestExecutionLevel admin

; 版本信息
VIProductVersion "1.0.0.0"
VIAddVersionKey "ProductName" "我的应用程序"
VIAddVersionKey "CompanyName" "我的公司"
VIAddVersionKey "LegalCopyright" "© 2024 我的公司"
VIAddVersionKey "FileDescription" "我的应用程序安装程序"
VIAddVersionKey "FileVersion" "1.0.0.0"

;==============================================================================
; 变量定义
;==============================================================================

Var CustomInstallDir
Var InstallResult
Var ProgressValue
Var StatusMessage
Var UserCancelled

;==============================================================================
; 页面配置
;==============================================================================

; 禁用默认NSIS页面，使用自定义界面
;!insertmacro MUI_PAGE_WELCOME
;!insertmacro MUI_PAGE_LICENSE
;!insertmacro MUI_PAGE_DIRECTORY  
;!insertmacro MUI_PAGE_INSTFILES
;!insertmacro MUI_PAGE_FINISH

; 设置语言
!insertmacro MUI_LANGUAGE "SimpChinese"

;==============================================================================
; 安装程序节
;==============================================================================

Section "-PrepareInstaller"
    ; 初始化插件目录
    InitPluginsDir
    SetOutPath "$PLUGINSDIR"
    
    ; 复制DuiLib插件和资源文件
    File "nsis_installer.dll"
    File "../nsis/bg.png"
    File "../nsis/logo.png"
    File "../nsis/install_normal.png"
    File "../nsis/windows_close.png"
    File "../nsis/windows_small.png"
    File "../nsis/checkbox_black_selected.png"
    File "../nsis/check_project_checked.png"
    File "../nsis/down.png"
    File "../nsis/folder.png"
    File "../nsis/customInstallBg.png"
    
    ; 设置默认安装路径
    StrCpy $CustomInstallDir "$INSTDIR"
    
SectionEnd

Section "ShowCustomInstaller"
    ; 调用自定义安装界面插件
    DetailPrint "显示自定义安装界面..."
    
    ; 调用DuiLib插件显示安装界面
    nsis_installer::ShowInstaller
    Pop $InstallResult
    
    ; 检查用户操作结果
    ${If} $InstallResult == "CANCEL"
        DetailPrint "用户取消了安装"
        StrCpy $UserCancelled "true"
        Abort "安装已被用户取消"
    ${ElseIf} $InstallResult == "ERROR"
        DetailPrint "显示安装界面时发生错误"
        Abort "无法显示安装界面"
    ${ElseIf} $InstallResult == "OK"
        DetailPrint "用户确认开始安装"
        
        ; 获取用户选择的安装路径
        nsis_installer::GetInstallPath
        Pop $CustomInstallDir
        
        ${If} $CustomInstallDir != ""
            DetailPrint "用户选择的安装路径: $CustomInstallDir"
            StrCpy $INSTDIR $CustomInstallDir
        ${EndIf}
    ${Else}
        DetailPrint "未知的界面返回值: $InstallResult"
        Abort "安装界面返回未知结果"
    ${EndIf}
    
SectionEnd

Section "InstallFiles" SecInstallFiles
    ; 设置输出路径
    SetOutPath "$INSTDIR"
    
    ; 模拟文件安装过程，同时更新进度
    DetailPrint "开始安装文件到: $INSTDIR"
    
    ; 创建一些示例文件并显示进度
    Call InstallWithProgress
    
    ; 写入卸载程序
    WriteUninstaller "$INSTDIR\uninstall.exe"
    
    ; 创建开始菜单快捷方式
    CreateDirectory "$SMPROGRAMS\我的应用程序"
    CreateShortCut "$SMPROGRAMS\我的应用程序\我的应用程序.lnk" "$INSTDIR\MyApp.exe"
    CreateShortCut "$SMPROGRAMS\我的应用程序\卸载.lnk" "$INSTDIR\uninstall.exe"
    
    ; 创建桌面快捷方式
    CreateShortCut "$DESKTOP\我的应用程序.lnk" "$INSTDIR\MyApp.exe"
    
    ; 写入注册表信息
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\MyApp" \
                     "DisplayName" "我的应用程序"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\MyApp" \
                     "UninstallString" "$INSTDIR\uninstall.exe"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\MyApp" \
                     "InstallLocation" "$INSTDIR"
    WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\MyApp" \
                       "NoModify" 1
    WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\MyApp" \
                       "NoRepair" 1
                       
    DetailPrint "安装完成!"
    
SectionEnd

;==============================================================================
; 安装进度更新函数
;==============================================================================

Function InstallWithProgress
    ; 模拟安装多个文件，每个文件更新一次进度
    Var /GLOBAL FileCount
    Var /GLOBAL CurrentFile
    StrCpy $FileCount "10"  ; 假设要安装10个文件
    StrCpy $CurrentFile "0"
    
    ; 文件1
    IntOp $CurrentFile $CurrentFile + 1
    IntOp $ProgressValue $CurrentFile * 100
    IntDiv $ProgressValue $ProgressValue $FileCount
    nsis_installer::UpdateProgress "$ProgressValue"
    DetailPrint "安装文件 $CurrentFile/$FileCount (进度: $ProgressValue%)"
    File "/oname=$INSTDIR\MyApp.exe" "MyApp.exe"  ; 替换为实际文件
    Sleep 500  ; 模拟文件复制时间
    
    ; 文件2
    IntOp $CurrentFile $CurrentFile + 1
    IntOp $ProgressValue $CurrentFile * 100
    IntDiv $ProgressValue $ProgressValue $FileCount
    nsis_installer::UpdateProgress "$ProgressValue"
    DetailPrint "安装文件 $CurrentFile/$FileCount (进度: $ProgressValue%)"
    File "/oname=$INSTDIR\config.ini" "config.ini"
    Sleep 300
    
    ; 文件3-10 (简化循环)
    ${For} $CurrentFile 3 10
        IntOp $ProgressValue $CurrentFile * 100
        IntDiv $ProgressValue $ProgressValue $FileCount
        nsis_installer::UpdateProgress "$ProgressValue"
        DetailPrint "安装文件 $CurrentFile/$FileCount (进度: $ProgressValue%)"
        
        ; 这里可以添加实际的File命令
        ; File "actual_file_$CurrentFile.ext"
        
        Sleep 200  ; 模拟文件复制时间
    ${Next}
    
    ; 完成
    nsis_installer::UpdateProgress "100"
    DetailPrint "所有文件安装完成 (进度: 100%)"
    
FunctionEnd

;==============================================================================
; 卸载程序节
;==============================================================================

Section "Uninstall"
    ; 删除文件
    Delete "$INSTDIR\MyApp.exe"
    Delete "$INSTDIR\config.ini"
    Delete "$INSTDIR\uninstall.exe"
    RMDir "$INSTDIR"
    
    ; 删除快捷方式
    Delete "$SMPROGRAMS\我的应用程序\我的应用程序.lnk"
    Delete "$SMPROGRAMS\我的应用程序\卸载.lnk"
    RMDir "$SMPROGRAMS\我的应用程序"
    Delete "$DESKTOP\我的应用程序.lnk"
    
    ; 删除注册表项
    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\MyApp"
    
SectionEnd

;==============================================================================
; 初始化函数
;==============================================================================

Function .onInit
    ; 检查管理员权限
    UserInfo::GetAccountType
    Pop $0
    ${If} $0 != "admin"
        MessageBox MB_ICONSTOP "此程序需要管理员权限才能安装。请右键点击安装程序并选择'以管理员身份运行'。"
        SetErrorLevel 740 ;ERROR_ELEVATION_REQUIRED
        Quit
    ${EndIf}
    
    ; 检查是否已安装
    ReadRegStr $0 HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\MyApp" "UninstallString"
    ${If} $0 != ""
        MessageBox MB_YESNO|MB_ICONQUESTION "检测到已安装的版本。是否要先卸载它?" IDYES +2
        Abort
        ExecWait '$0 _?=$INSTDIR'
    ${EndIf}
FunctionEnd

Function un.onInit
    MessageBox MB_YESNO "确定要完全卸载我的应用程序及其所有组件吗?" IDYES +2
    Abort
FunctionEnd

;==============================================================================
; 编译说明
;==============================================================================

/*
编译此NSIS脚本需要：

1. 安装NSIS (Nullsoft Scriptable Install System)
2. 编译nsis_installer.cpp为nsis_installer.dll
3. 准备要安装的应用程序文件
4. 在script目录下有资源文件

编译命令：
makensis installer_setup.nsi

生成的文件：
MyAppInstaller.exe - 带自定义DuiLib界面的安装程序

特点：
- 使用DuiLib创建美观的安装界面
- 支持自定义安装路径选择
- 实时显示安装进度
- 完整的卸载支持
- 创建快捷方式和注册表项
- 管理员权限检查
*/