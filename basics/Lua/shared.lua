#!/usr/local/bin/luajit

-- 使用 Luajit 的ffi加载C++方法

local ffi = require "ffi"           -- 加载ffi库

local ffi_load = ffi.load           -- 函数别名
local ffi_null = ffi.null
local ffi_cdef = ffi.cdef
local ffi_typeof = ffi.typeof
local ffi_new = ffi.new
local ffi_C = ffi.C

ffi_cdef[[                          // 声明C接口
    int num;
    int my_add(int a, int b);
]]

print(jit.version)
print(jit.os)
print(jit.arch)
print(jit.status())

local shared = ffi_load("./liblau_shared.so")       -- 加载动态库

print(shared.num)                                   -- 调用C接口

local x = shared.my_add(1, 2)                       -- 调用C接口
print(x)


-- debug: luajit shared.lua