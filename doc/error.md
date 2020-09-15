
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
    sudo ln -s /usr/local/mysql-connector-c++-8.0.21/lib64/libssl.1.1.dylib /usr/lib/libssl.1.1.dylib
    sudo ln -s /usr/local/mysql-connector-c++-8.0.21/lib64/libcrypto.1.1.dylib /usr/lib/libcrypto.1.1.dylib

报错

    ln: /usr/lib/libmysqlcppconn.7.dylib: Read-only file system

要先执行

    sudo mount -uw /
 
### CDK Error: unexpected message

在使用 MySql8.0 为 C++ 提供的库 mysqlcppconn8执行时报错

    libc++abi.dylib: terminating with uncaught exception of type mysqlx::abi2::r0::Error: CDK Error: unexpected message

库 mysqlcppconn8 默认端口是 33060 而不是 3306，如果使用 3306 端口进行连接，就会报这样的错误。改为以下代码进行连接即可：

    Session sess("localhost", 33060, "root", "rootpwd");
