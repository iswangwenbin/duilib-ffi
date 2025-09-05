● 优秀的问题！让我详细解释一下 C++ 类到 C API 的 1:1 对齐方案。

  🔄 C++ 类到 C API 的映射方案

  1. 不透明指针 (Opaque Pointer) 模式

  这是我们使用的核心方案：

  // C API 头文件中 - 只有前置声明，不暴露内部结构
  typedef struct duilib_window* duilib_window_t;
  typedef struct duilib_control* duilib_control_t;
  typedef struct duilib_manager* duilib_manager_t;

  // C++ 实现文件中 - 实际包装结构体
  struct duilib_window {
      CWindowWnd* cpp_object;     // 指向实际的C++对象
      void* user_data;            // 用户自定义数据
      // 可能的其他包装数据...
  };

  struct duilib_control {
      CControlUI* cpp_object;
      void* user_data;
  };

  2. 对象生命周期管理

  // 创建对象 - 分配包装器并创建C++对象
  DUILIB_C_API duilib_window_t duilib_window_create(void) {
      duilib_window* wrapper = new duilib_window();
      wrapper->cpp_object = new CWindowWnd();  // 或者具体的派生类
      wrapper->user_data = nullptr;
      return wrapper;
  }

  // 销毁对象 - 清理C++对象和包装器
  DUILIB_C_API void duilib_window_destroy(duilib_window_t window) {
      if (window && window->cpp_object) {
          delete window->cpp_object;
          delete window;
      }
  }

  3. 方法调用转发 (Method Forwarding)

  每个 C API 函数都转发到对应的 C++ 方法：

  // C++ 类方法：CWindowWnd::ShowWindow(bool show, bool takeFocus)
  // C API 封装：
  DUILIB_C_API duilib_result_t duilib_window_show_window(duilib_window_t window, bool show, bool take_focus) {
      if (!window || !window->cpp_object) {
          return DUILIB_ERROR_INVALID_PARAM;
      }

      try {
          window->cpp_object->ShowWindow(show, take_focus);
          return DUILIB_OK;
      } catch (...) {
          return DUILIB_ERROR_UNKNOWN;
      }
  }

  4. 虚函数和回调处理

  对于 C++ 的虚函数，我们使用回调机制：

  // C++ 虚函数：virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
  // C API 方式：

  // 1. 定义回调类型
  typedef int (*duilib_window_message_handler_t)(duilib_window_t window, uint32_t msg, uintptr_t wparam, intptr_t lparam, intptr_t* result);

  // 2. 包装器类继承并重写虚函数
  class CWindowWndWrapper : public CWindowWnd {
  private:
      duilib_window_message_handler_t m_handler;
      duilib_window_t m_wrapper;

  public:
      void SetMessageHandler(duilib_window_message_handler_t handler, duilib_window_t wrapper) {
          m_handler = handler;
          m_wrapper = wrapper;
      }

      virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override {
          if (m_handler) {
              intptr_t result = 0;
              int ret = m_handler(m_wrapper, uMsg, wParam, lParam, &result);
              if (ret == 0) return result;  // 用户处理了消息
          }
          return CWindowWnd::HandleMessage(uMsg, wParam, lParam);  // 调用基类默认处理
      }
  };

  // 3. C API 设置回调
  DUILIB_C_API duilib_result_t duilib_window_set_message_handler(duilib_window_t window, duilib_window_message_handler_t handler) {
      if (!window || !window->cpp_object) return DUILIB_ERROR_INVALID_PARAM;

      CWindowWndWrapper* wrapper_obj = dynamic_cast<CWindowWndWrapper*>(window->cpp_object);
      if (wrapper_obj) {
          wrapper_obj->SetMessageHandler(handler, window);
          return DUILIB_OK;
      }
      return DUILIB_ERROR_UNKNOWN;
  }

  5. 静态方法处理

  C++ 静态方法直接映射为 C 函数：

  // C++ 静态方法：CPaintManagerUI::MessageLoop()
  // C API：
  DUILIB_C_API int duilib_paint_manager_message_loop(void) {
      return CPaintManagerUI::MessageLoop();
  }

  6. 枚举和常量映射

  // C++ 枚举
  enum DuiSig {
      DuiSig_end = 0,
      DuiSig_lwl,
      DuiSig_vn
  };

  // C API 枚举
  typedef enum {
      DUILIB_SIG_END = 0,
      DUILIB_SIG_LWL,
      DUILIB_SIG_VN
  } duilib_sig_t;

  7. 结构体映射

  // C++ 结构体
  struct TNotifyUI {
      CDuiString sType;
      CControlUI* pSender;
      DWORD dwTimestamp;
      POINT ptMouse;
      // ...
  };

  // C API 结构体（简化和C兼容）
  typedef struct {
      const char* type;           // 字符串指针替代 CDuiString
      duilib_control_t sender;    // 不透明指针替代原生指针
      uint32_t timestamp;         // 标准化类型
      duilib_point_t mouse;       // C兼容的点结构
  } duilib_event_t;

  8. 错误处理统一化

  // C++ 异常 → C API 错误码
  typedef enum {
      DUILIB_OK = 0,
      DUILIB_ERROR_INVALID_PARAM = -1,
      DUILIB_ERROR_NOT_INITIALIZED = -2,
      DUILIB_ERROR_NOT_FOUND = -3,
      DUILIB_ERROR_MEMORY = -4,
      DUILIB_ERROR_UNKNOWN = -999
  } duilib_result_t;

  🎯 完整的映射示例

  以 CControlUI 类为例：

  // === C++ 原始类 ===
  class CControlUI {
  public:
      virtual CDuiString GetName() const;
      virtual void SetName(LPCTSTR pstrName);
      virtual bool IsVisible() const;
      virtual void SetVisible(bool bVisible = true);
      // ... 更多方法
  };

  // === C API 封装结构 ===
  struct duilib_control {
      CControlUI* cpp_object;
      void* user_data;
      char* cached_name;  // 缓存字符串，避免内存管理问题
  };

  // === C API 函数 ===
  DUILIB_C_API const char* duilib_control_get_name(duilib_control_t control) {
      if (!control || !control->cpp_object) return nullptr;

      // 获取C++字符串并缓存为C字符串
      CDuiString cpp_name = control->cpp_object->GetName();

      // 释放旧的缓存
      if (control->cached_name) {
          free(control->cached_name);
      }

      // 分配新的缓存
      const char* name_str = cpp_name.GetData();  // 假设有这个方法
      control->cached_name = strdup(name_str);

      return control->cached_name;
  }

  DUILIB_C_API duilib_result_t duilib_control_set_name(duilib_control_t control, const char* name) {
      if (!control || !control->cpp_object || !name) {
          return DUILIB_ERROR_INVALID_PARAM;
      }

      try {
          control->cpp_object->SetName(name);  // 自动转换为CDuiString
          return DUILIB_OK;
      } catch (...) {
          return DUILIB_ERROR_UNKNOWN;
      }
  }

  🔧 实现架构总结

  ┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
  │   C 应用程序    │───→│   C API 层      │───→│   C++ 对象层    │
  │                 │    │                 │    │                 │
  │ duilib_window_t │    │ 不透明指针包装器  │    │ CWindowWnd*     │
  │ duilib_control_t│    │ 方法转发函数      │    │ CControlUI*     │
  │ 回调函数        │    │ 错误处理        │    │ CPaintManager*   │
  └─────────────────┘    └─────────────────┘    └─────────────────┘

  这种方案的优势：
  - ✅ 完全隐藏 C++ 复杂性：C 用户无需了解 C++ 类结构
  - ✅ 内存安全：通过包装器管理对象生命周期
  - ✅ ABI 稳定：C API 接口不依赖 C++ ABI
  - ✅ 功能完整：可以完全映射所有 C++ 功能
  - ✅ 错误处理统一：将 C++ 异常转换为错误码

  这就是我们实现 1:1 功能对等 的核心技术方案！