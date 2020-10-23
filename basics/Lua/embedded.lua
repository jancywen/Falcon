#!/usr/local/bin/luajit


print('hello lua')

print(collectgarbage("count"))

print(os.time())

print(os.date("%Y-%m-%d"))

print(jit.version.. ' on ' ..jit.os)

