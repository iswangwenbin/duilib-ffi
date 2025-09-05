#include <windows.h>
#include <tchar.h>
#include "nsis/pluginapi.h"

__declspec(dllexport) void __cdecl MyCallback(
    HWND hwndParent,
    int string_size,
    char* variables,
    stack_t **stacktop,
    extra_parameters *extra
) {
    EXDLL_INIT();

    // 假定第一个参数为回调函数地址
    int funcAddr = popint();

    // 执行回调，没参数可以直接这样调用
    if (extra && extra->ExecuteCodeSegment && funcAddr != 0) {
        OutputDebugString("About to call ExecuteCodeSegment...\n");
        extra->ExecuteCodeSegment(funcAddr, hwndParent);
        OutputDebugString("ExecuteCodeSegment returned\n");
    }


    
    // 执行成功后返回一个字符串
    if (funcAddr != 0) {
        pushstring(_T("Callback executed successfully"));
        OutputDebugString("Callback executed successfully");
    } else {
        pushstring("No callback function provided");
        OutputDebugString(_T("No callback function provided"));
    }
}
