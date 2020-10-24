// g++ luajit.cpp -std=c++11 -I../../common -I/usr/local/include/luajit-2.1 -lluajit-5.1 -ldl -o a.out ; ./a.out

#include <cassert>
#include <iostream>
#include <memory>

extern "C" {
    #include <luajit-2.1/luajit.h>
    #include <luajit-2.1/lualib.h>
    #include <luajit-2.1/lauxlib.h>
}

#include <LuaBridge/LuaBridge.h>

using namespace luabridge;

using namespace std;

// lambda表达式创建虚拟机
auto make_luavm = []()
{
    std::shared_ptr<lua_State> vm(      // 智能指针
        luaL_newstate(), lua_close      // 创建虚拟机对象，设置删除函数
    );
    assert(vm);

    luaL_openlibs(vm.get());            // 打开Lua基本库

    return vm;
};

#define L vm.get()                      // 获取原始指针，宏定义方便使用

void case1()
{
    auto vm = make_luavm();

    auto package = getGlobal(L, "package");

    string path = package["path"];
    string cpath = package["cpath"];

    cout << package <<endl;
    cout <<path << endl;
    cout <<cpath <<endl;
}


void case2()
{
    auto vm = make_luavm();
    int status;

    status = luaL_dostring(L, "print('hello world')");

    // status = luaL_dofile(L, "./shared.lua");

    status = luaL_dofile(L, "./embedded.lua");

    cout << status << endl;

    assert(status == 0);
}

void case3()
{

    auto vm = make_luavm();

    int status;
    string chunk = R"(
        function say(s)
            print(s)
        end
        function add(a, b)
            return a+b
        end
    )";

    status = luaL_dostring(L, chunk.c_str());
    assert(status == 0);

    auto f1 = getGlobal(L, "say");
    f1("say something");

    auto f2 = getGlobal(L, "add");
    auto sum =f2(10, 20);
    assert(sum == 30);
    cout << sum <<endl;

}

void case4()
{
    auto vm = make_luavm();

    int status;
    status = luaL_dofile(L, "./somefunc.lua");
    assert(status == 0);

    auto f1 = getGlobal(L, "say");
    f1("say something");

    auto f2 = getGlobal(L, "add");
    auto sum =f2(10, 20);
    assert(sum == 30);
    cout << sum <<endl;

}

void case5()
{
    auto vm = make_luavm();

    int status;
    status = luaL_dofile(L, "../../bookstore/conf.lua");
    assert(status == 0);
}

int main()
{
    // case1();

    // case2();

    // case3();

    // case4();

    case5();

    cout <<"luajit demo"<<endl;
}