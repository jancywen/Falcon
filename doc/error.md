
### 1.链接 `libmysqlcppconn` 出错

    dyld: Library not loaded: @rpath/libmysqlcppconn.7.dylib

解决办法：

1.关闭 csrutil  关闭安全机制

- 重启按住command+R,进入恢复模式,在做上角 实用工具栏 找到终端 启动运行;

输入: `csrutil disable`

这样就可以操作了

操作完再改回来: `csrutil enable`

2.找到 `mysql-connector-c++` 安装路径，建立软连接

    sudo ln -s /usr/local/mysql-connector-c++-8.0.21/lib64/libmysqlcppconn.7.8.0.21.dylib /usr/lib/libmysqlcppconn.7.dylib 
