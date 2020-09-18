#include <iostream>
#include <string>
#include <mysqlx/xdevapi.h>

using namespace std;
using namespace mysqlx;


#define HOST "localhost"
#define PORT 33060
#define USER "root"
#define PWD "daxiong0213"
#define SCHEMA "book_schema"
#define BOOK_CATEGORY "bookcategory"
#define BOOK_INFO "bookinfo"
#define BORROW_INFO "borrowinfo"
#define READER_INFO "readerinfo"
#define READER_FEE "readerfee"

// 新建 类别
void insertCategoryData(const std::string category, int par_id);
// 录入新书
void insertBookData(int book_id,
                    int cate_id, 
                    std::string book_name, 
                    std::string author, 
                    float price, 
                    std::string pubdate, 
                    int store);
// 新建用户
void insertReaderData(std::string card_id, 
                      std::string name, 
                      std::string sex, 
                      int age, 
                      std::string tel, 
                      float balance);
// 借阅
void insertBorrowData(int book_id, std::string card_id);

// 查询 类别图书
void searchBookRecord(std::string category_name);

// 查询所有借阅信息
void queryAllBorrowRecord();
// 查询图书借阅信息 
void searchBorrowRecord(std::string book_name);
// 查询未归还的借阅信息
void queryBorrowRecord();

// 还书
void returnBook(int book_id, std::string card_id);

// 充值
void recharge(std::string card_id, float balance);


int main()
{
    // 插入 类别 数据
    /*
    insertCategoryData("机械", 0);
    insertCategoryData("计算机", 0);
    insertCategoryData("机械设计", 1);
    insertCategoryData("机械制造", 1);
    insertCategoryData("计算机原理", 2);
    insertCategoryData("C++基础", 2);
   
    //插入 图书 信息
    insertBookData(20200910, 3, "机械设计与制造", "作者", 46.5, "2019-04-01", 26);
    insertBookData(20200911, 4, "磨具制造", "作者", 36.5, "2019-04-01", 52);
    insertBookData(20200912, 5, "计算机原理", "作者", 76.5, "2019-04-01", 17);
    insertBookData(20200913, 6, "C++ 基础", "作者", 66.3, "2019-04-01", 49);
    insertBookData(20200914, 6, "JAVA 从入门到放弃", "作者", 120, "2019-04-01", 89);
    insertBookData(20200915, 6, "Swift 快速入门", "作者", 62.3, "2019-04-01", 59);

// 插入 用户
    insertReaderData("4562135466", "朱丽叶", "女", 25, "12739247", 200);
    insertReaderData("4562135467", "貂蝉", "女", 16, "12739247", 200);
    insertReaderData("4562135468", "西施", "女", 22, "12739247", 200);
    insertReaderData("4562135469", "昭君", "女", 23, "12739247", 200);
    insertReaderData("4562135470", "杨贵妃", "女", 28, "12739247", 200);
    insertReaderData("4562135471", "赵子龙", "男", 17, "12739247", 200);
    insertReaderData("4562135472", "典韦", "男", 25, "12739247", 200);

    // 插入 借阅信息
    insertBorrowData(20200913, "4562135468");
    insertBorrowData(20200915, "4562135465");
    insertBorrowData(20200911, "4562135472");
*/

    // searchBookRecord("机械工程");

    Session session(HOST, PORT, USER, PWD);

try {
        session.sql("use book_schema").bind(SCHEMA).execute();
        SqlResult result = session.sql("select category from bookcategory where category_id = ?;").bind(6).execute();
        // SqlResult result = session.sql("select book_id, book_name, category, author from bookinfo inner join bookcategory on bookinfo.book_category_id = bookcategory.category_id where (book_category_id = select category_id from bookcategory where category = 软件工程)").execute() ;
        list<Row> list  = result.fetchAll();
    
        int column_count = result.getColumnCount();

        // const Columns &columns = result.getColumns();
        
        for (Row row : list) 
        {
            for (int i = 0; i < column_count; i++)
            {
                cout << row[i] << " ";
            }
            cout << endl;
        }
    }catch (exception &e) {
        cout << e.what() <<endl;
    }

    return 0;
}



/*
*  创建表 session
*/

void createTable()
{
    Session session(HOST, PORT, USER, PWD);
    
    session.startTransaction();
    try {
        Schema db = session.getSchema(SCHEMA);
        
        session.sql("create table test(id int primary key not null auto_increment, name varchar(20))").execute();
        session.commit();
    } catch (exception& e){
        cout << e.what() << endl;
        session.rollback();
    }
    session.close();
}


/*
* 插入 类别 数据  
*/
void insertCategoryData(const std::string category, int par_id)
{
    Session session(HOST, PORT, USER, PWD);
    Schema db = session.getSchema(SCHEMA);
    Table table = db.getTable(BOOK_CATEGORY);
    session.startTransaction();
    try {
        table.insert("category","parent_id").values(category, par_id).execute();
        session.commit();
    }catch(exception &e) {
        cout << e.what() << endl;
        session.rollback();
    }

    session.close();

}

/*
* 插入 图书 数据
*/

void insertBookData(int book_id,
                    int cate_id, 
                    std::string book_name, 
                    std::string author, 
                    float price, 
                    std::string pubdate, 
                    int store)
{
    Session session(HOST, PORT, USER, PWD);
    Schema db = session.getSchema(SCHEMA);
    Table table = db.getTable(BOOK_INFO);
    session.startTransaction();
    try {
        table.insert("book_id", "book_category_id", "book_name", "author", "price", "pubdate", "store")
            .values(book_id, cate_id, book_name, author, price, pubdate, store)
            .execute();
        session.commit();
    }catch(exception &e) {
        cout << e.what() << endl;
        session.rollback();
    }

    session.close();
}

/*
* 插入 读者 数据
*/

void insertReaderData(std::string card_id, 
                      std::string name, 
                      std::string sex, 
                      int age, 
                      std::string tel, 
                      float balance)
{
    Session session(HOST, PORT, USER, PWD);
    Schema schema = session.getSchema(SCHEMA);
    Table table = schema.getTable(READER_INFO);

    session.startTransaction();
    try {
        table.insert().values(card_id, name, sex, age, tel, balance).execute();
        session.commit();
    }catch(exception &e) {
        cout << e.what() << endl;
        session.rollback();
    }
    session.close();
}

/*
* 插入 借阅 数据
*/

void insertBorrowData(int book_id, std::string card_id)
{
    Session session(HOST, PORT, USER, PWD);
    Schema schema = session.getSchema(SCHEMA);
    Table table = schema.getTable(BORROW_INFO);
    session.startTransaction();
    try {
        table.insert("book_id", "card_id", "borrow_date", "return_date").values(book_id, card_id, "2020-01-02", "2020-03-01").execute();
        session.commit();
    }catch (exception &e) {
        cout << e.what() << endl;
        session.rollback();
    }
    session.close();
}


// 查询 类别 图书
void searchBookRecord(std::string category_name)
{
    Session session(HOST, PORT, USER, PWD);
    
    try {
        session.sql("use book_schema").bind(SCHEMA).execute();
        SqlResult result = session.sql("select book_id, book_name, category, author from bookinfo inner join bookcategory on bookinfo.book_category_id = bookcategory.category_id where (book_category_id = select category_id from bookcategory where category = ?)").bind(category_name).execute() ;
        list<Row> list  = result.fetchAll();
    
        int column_count = result.getColumnCount();

        const Columns &columns = result.getColumns();

        for (Row row : list) 
        {
            for (int i = 0; i < column_count; i++)
            {
                cout << row[i] << " ";
            }
            cout << endl;
        }
    }catch (exception &e) {
        cout << e.what() <<endl;
    }

    session.close();

}

// 查询所有借阅信息
void queryAllBorrowRecord()
{

}
// 查询图书借阅信息 
void searchBorrowRecord(std::string book_name)
{

}
// 查询未归还的借阅信息
void queryBorrowRecord()
{

}

// 还书
void returnBook(int book_id, std::string card_id)
{

}

// 充值
void recharge(std::string card_id, float balance)
{

}
