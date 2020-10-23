小巧高效的 Lua，号称是“最快的脚本语言”。

标准的 Lua（PUC-Rio Lua）使用解释器运行，速度虽然很快，但和 C/C++ 比起来还是有差距的。所以，你还可以选择另一个兼容的项目：[LuaJIT](https://luajit.org/)。它使用了 JIT（Just in time）技术，能够把 Lua 代码即时编译成机器码，速度几乎可以媲美原生 C/C++ 代码。
推荐非官方分支：[OpenResty-LuaJIT](https://github.com/openresty/luajit2)

```
// macOS Catalina 10.15.6
git clone https://github.com/openresty/luajit2.git
cd luajit2
make MACOSX_DEPLOYMENT_TARGET=10.15 && make install
```

### Lua 调用 C

使用 LuaBridge 可以导出 C++ 的函数、类，但直接用 LuaJIT 的 ffi 库更好；

> ffi 只能识别纯 C 接口，不认识 C++,
```
extern "C" {                // 使用纯C语言的对外接口
int num = 10; 
int my_add(int a, int b); 
}

int my_add(int a, int b)    // 一个简单的函数，供Lua调用
{
    return a + b;
}
```

### C++ 里嵌入 Lua
使用 LuaBridge 也可以很容易地执行 Lua 脚本、调用 Lua 函数，让 Lua 跑在 C++ 里。

1. 创建 Lua 虚拟机

要调用函数 **luaL_newstate()**，创建出一个 Lua 虚拟机，所有的 Lua 功能都要在它上面执行。

因为 Lua 是用 C 语言写的，Lua 虚拟机用完之后必须要用函数 **lua_close()** 关闭

2. 使用 LuaBridge 访问 Lua 数据

在 LuaBridge 里，一切 Lua 数据都被封装成了 **LuaRef** 类，它可以隐式或者显式地转换成对应的数字、字符串等基本类型，如果是表，就可以用“[]”访问成员，如果是函数，也可以直接传参调用，
注意一点，LuaBridge 只能用函数 **getGlobal()** 看到全局变量

还可以调用 **luaL_dostring()** 和 **luaL_dofile()** 这两个函数，直接执行 Lua 代码片段或者外部的脚本文件。注意，luaL_dofile() 每次调用都会从磁盘载入文件，所以效率较低

