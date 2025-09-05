// 简单的编译测试，验证C API头文件
#include "duilib_c/duilib_c.h"
#include <iostream>
#include <cassert>

int main() {
    std::cout << "=== DuiLib C API 编译测试 ===" << std::endl;
    
    // 测试宏定义
    duilib_color_t red = DUILIB_COLOR_RGB(255, 0, 0);
    std::cout << "红色值: 0x" << std::hex << red << std::endl;
    assert(red == 0x00FF0000);
    
    duilib_rect_t rect = DUILIB_RECT(10, 20, 100, 200);
    std::cout << "矩形: (" << std::dec << rect.left << "," << rect.top 
              << "," << rect.right << "," << rect.bottom << ")" << std::endl;
    
    duilib_size_t size = DUILIB_SIZE(800, 600);
    std::cout << "尺寸: " << size.width << "x" << size.height << std::endl;
    
    // 测试错误码
    std::cout << "错误码 OK: " << DUILIB_OK << std::endl;
    std::cout << "错误码 INVALID_PARAM: " << DUILIB_ERROR_INVALID_PARAM << std::endl;
    
    // 测试事件类型
    std::cout << "点击事件类型: " << DUILIB_EVENT_CLICK << std::endl;
    
    std::cout << "✓ C API 头文件编译成功！" << std::endl;
    std::cout << "✓ 所有宏定义和类型定义正常" << std::endl;
    
    return 0;
}