# code style

## 1. 空格与空行

留白的艺术

## 2. 命名

> 变量、函数名和名字空间用 snake_case，全局变量加“g_”前缀；
> 自定义类名用 CamelCase，成员函数用 snake_case，成员变量加“m_”前缀；
> 宏和常量应当全大写，单词之间用下划线连接；
> 尽量不要用下划线作为变量的前缀或者后缀（比如 _local、name_），很难识别。

**变量 / 函数的名字长度与它的作用域成正比**

## 3. 注释

正确、清晰、有效，尽量言简意赅、点到为止

除了给代码、函数、类写注释，我还建议**最好在文件的开头写上本文件的注释**，里面有文件的版权声明、更新历史、功能描述，等等。

**todo** 作为功能的占位符

函数的注释 如果是对外发布的，就写在声明，如果是内部用的，就在定义处。

## 4. 必杀技 code review



    #define  MAX_PATH_LEN  256             //常量，全大写

    int g_sys_flag;                        // 全局变量，加g_前缀

    namespace linux_sys {                // 名字空间，全小写
      void get_rlimit_core();               // 函数，全小写
    }

    class FilePath final                 // 类名，首字母大写
    {
    public:
      void set_path(const string& str);    // 函数，全小写
    private:  
      string m_path;                      // 成员变量，m_前缀 
      int    m_level;                     // 成员变量，m_前缀
    };




格式化工具

1. clang-format

2. astyle

3. cpplint
