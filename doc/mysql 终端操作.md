### 安装

[MySQL](https://dev.mysql.com/downloads/)

### 启动

设置软链接

    ln -s /usr/local/mysql/bin/mysql /usr/local/bin/

打开终端输入
  
    mysql -u root -p

输入密码

退出

    exit; 或者 quit;


### 数据库操作
1.创建一个数据库 echain

    create database echain;

2.查看数据库

    show databases;

3.进入数据库
    
    use echain;

4.查看当前选中的数据库

    select database();

5.查看数据库中的表

    show tables;

### 表操作
1.创建一个表 echain_user

    create table echain_user(id int primary key not null auto_increment,name varchar(20), age int)

2.查看是否创建成功

    show tables;

3.查看表结构、表中字段信息
    
    desc echain_user;
    describe echain_user;
    show columns from echain_user;

4.修改表名 

    # rename table <旧表名> to <新表名>;
    rename table echain_user to user;

    # alter table <旧表名> rename <新表名>;
    alter table echain_user rename user;

5.修改字段：新增（add)、修改、重命名、删除、
  
    # 新增 alter table <表名> add <字段名> <数据类型> <位置(默认最后)>;
    alter table echain_user add vip_level int first;

    # 修改 alter table <表名> modify <字段名> <数据类型> <位置>;
    alter table echain_user modify gender char(4) after id;

    # 重命名 alter table <表名> change <旧字段名> <新字段名> <数据类型>;
    alter table echain_user change gender sex int;

    # 删除 alter table <表名> drop <字段名>;
    alter table echain_user drop height;

6.删除数据表

    drop table <表一>, <表二>,....;

#### 数据操作
1.插入数据

    # 全表字段
    insert into echain_user values(1, 'Lilei', 14);

    # 指定字段
    insert into echain_user（name) values('HanMeimei');

2.查询 
    
    # select * from table_name [where条件];
    select * from echain_user;

3.更新

    # update table_name set 字段=值[where条件];
    update echain_user set name='天霸' where id=1;

4.删除
    
    # delete from table_name [where条件];
    delete from echain_user where id=2;


********

中文数据问题本质是字符集问题，set names  gbk;   一定要设置字符集。

外键：如果一张表中有一个字键段（非主键）指向另外一张表的主键，那么将该字段称之为外键。

主键问题

主键直接在字段之后，可以有多个字段作为主键，这样的主键称为复合主键。

没有主键，追加主键    alter  table  my_database  modify  course  char(10)  primary key;

没有主键，追加复合主键  alter table  my_student  add  primary key (sno,cno);

更新主键 & 删除主键  alter  table  表名 drop primary  key;

查询数据完整语法

select 字段名/*

from  数据源

[where 条件子句]

[group by 子句]

[having 子句]

[order by 子句]

[limit 子句];



### 内连接，外连接，自然连接，交叉连接

内连接，从左表中取出每一条记录，和右表中所有的记录进行匹配，匹配必须是左表中与右表中某个条件相同，最终会保留结果，否则不保留。

基本语法：  左表 [inner] join 右表  on 左表.字段 = 右表.字段;

select * from my_student inner join my_class on my_student.C_id = mu_class.id;



左外连接：左表为主，然后每条记录与右表进行连接，不管能不能匹配的上，左表都会保留。能匹配，右表某条记录保留，不能匹配，某条记录置为NULL，最终记录数至少不少于左表已有的记录。

基本语法：  左表  left join  右表  on  左表.字段 = 右表.字段;

a表


| id   | name  |
|-----:|------:|
|    1 | 张三   |
|    2 | 李四   |
|    3 | 王二   |

b 表

| id   | job       | parent_id |
|-----:|----------:|----------:|
|    1 | 工程师    |         1 |
|    2 | 程序员    |         2 |
|    3 | 导游      |         4 |

a.id同parent_id   存在关系   

 1） 内连接   
     
    select a.*,b.* from a inner join b on a.id=b.parent_id;
   
    +------+--------+------+-----------+-----------+
    | id   | name   | id   | job       | parent_id |
    +------+--------+------+-----------+-----------+
    |    1 | 张三   |    1 | 工程师    |         1 |
    |    2 | 李四   |    2 | 程序员    |         2 |
    +------+--------+------+-----------+-----------+

  2）左连接
   
    select a.*,b.* from a left join b on a.id=b.parent_id;
    +------+--------+------+-----------+-----------+
    | id   | name   | id   | job       | parent_id |
    +------+--------+------+-----------+-----------+
    |    1 | 张三   |    1 | 工程师    |         1 |
    |    2 | 李四   |    2 | 程序员    |         2 |
    |    3 | 王二   | NULL | NULL      |      NULL |
    +------+--------+------+-----------+-----------+
 

 3） 右连接  
 
    select a.*,b.* from a right join b on a.id=b.parent_id;
    +------+--------+------+-----------+-----------+
    | id   | name   | id   | job       | parent_id |
    +------+--------+------+-----------+-----------+
    |    1 | 张三   |    1 | 工程师    |         1 |
    |    2 | 李四   |    2 | 程序员    |         2 |
    | NULL | NULL   |    3 | 导游      |         4 |
    +------+--------+------+-----------+-----------+ 
    
 4） 完全连接 
  
    select a.*,b.* from a full join b on a.id=b.parent_id;  
     
    1   张3                  1     23     1   
    2   李四                 2     34     2   
    null               　　  3     34     4   
    3   王武                 null




参考：

[Mac终端操作Mysql，以及Mysql的操作](https://blog.csdn.net/ivolcano/article/details/53728161)

[Mac下使用终端操作MySQL数据库](https://blog.csdn.net/bendan233/article/details/86644293)
