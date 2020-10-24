

#ifndef _CONFIG_HPP
#define _CONFIG_HPP

#include "cpplang.hpp"

extern "C" {
    #include <luajit-2.1/luajit.h>
    #include <luajit-2.1/lualib.h>
    #include <luajit-2.1/lauxlib.h>
}

#include <LuaBridge.h>

BEGIN_NAMESPACE(cpp_study)

class Config final
{
public:
    using vm_type           = std::shared_ptr<lua_State>;
    using value_type        = luabridge::LuaRef;

    using string_type       = std::string;
    using string_view_type  = std::string_view;
    using regex_type        = std::regex;
    using match_type        = std::smatch;

public:
    Config() noexcept
    {
        assert(m_vm);

        luaL_openlibs(m_vm.get());                  //打开Lua基础库
    }
    ~Config() = default;

public:
    void load(string_view_type filename) const      // 解析配置文件
    {
        auto status = luaL_dofile(m_vm.get(), filename.c_str());

        if (status != 0) {                          // 出错就抛出异常
            throw std::runtime_error("failed to parse config");
        }
    }

    template<typename T>                                    // 转换配置值的类型
    T get(string_view_type key) const                       // const常函数
    {
        if (!std::regex_match(key, m_what, m_reg)) {        // 正则匹配
            throw std::runtime_error("config key error");   // 格式错误抛异常
        }

        auto w1 = m_what[1].str();                          // 取出两个key
        auto w2 = m_what[2].str();

        using namespace luabridge;

        auto v = getGlobal(                                 // 获取Lua表
                m_vm.get(), w1.c_str()
        );

        return LuaRef_cast<T>(v[w2]);                       // 取表里的值，再做类型转换
    }

private:
    vm_type m_vm                            // 类型别名定义Lua虚拟机
        {luaL_newstate(), lua_close};       // 成员变量初始化

    const regex_type    m_reg {R"(^(\w+)\.\(w+)$)"};
    mutable match_type  m_what;
};

END_NAMESPACE(cpp_study)


#endif 