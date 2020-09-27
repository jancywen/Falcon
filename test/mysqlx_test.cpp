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

// 充值
void recharge(Session &session, std::string card_id, float balance);
// 借书
void borrowBook(Session &session, int book_id, std::string card_id);
// 还书
void returnBook(Session &session, int book_id, std::string card_id);


// 查询 类别图书
void searchBookRecord(Session &session, std::string category_name); 
// 查询所有借阅信息
void queryAllBorrowRecord(Session &session);



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

*/


    Session session(HOST, PORT, USER, PWD);

    // 充值
    // recharge(session, "4562135470", 50);

    // 借书
    // borrowBook(session, 20200911, "4562135471");

    // 还书
    // returnBook(session, 20200913, "4562135468");

    queryAllBorrowRecord(session);

    session.close();
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
void searchBookRecord(Session &session, std::string category_name)
{
    try {
        session.sql("use " + std::string(SCHEMA)).execute();
        SqlResult result = session.sql("select book_id, book_name, category, author" 
                                       " from bookinfo" 
                                       " inner join bookcategory" 
                                       " on bookinfo.book_category_id = bookcategory.category_id" 
                                       " where book_category_id =" 
                                       " (select category_id from bookcategory where category = ?)")
                                  .bind(category_name)
                                  .execute() ;

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
}

// 创建 费用表
void calculateCost(Session & session) 
{
    std::string quoted_name = std::string("`") + std::string(SCHEMA) + "`.`" + "readerfee" + "`";

    std::string create = "CREATE TABLE ";
    create += "IF NOT EXISTS";
    create += quoted_name;
    create += "(book_id int, card_id char(18), return_date date, actual_return_date date, book_fee decimal(7, 3));";

    session.sql(create).execute();

    // 插入数据
    session.sql("use " + std::string(SCHEMA)).execute();
    session.sql("insert into readerfee(book_id, card_id, return_date)" 
                " select book_id, card_id, return_date" 
                " from borrowinfo" " where datediff(sysdate(), return_date)>0" 
                " and status = '否';")
           .execute();

    SqlResult res = session.sql("select * from readerfee").execute();
    list<Row> list = res.fetchAll();
    int column_count = res.getColumnCount();
    for (Row row : list) 
        {
            for (int i = 0; i < column_count; i++)
            {
                cout << row[i] << " ";
            }
            cout << endl;
        }
}

// 充值
void recharge(Session &session, std::string card_id, float balance)
{
    session.startTransaction();
    try
    {
        session.sql("use " + std::string(SCHEMA)).execute();
        session.sql("SET @bal = ?").bind(balance).execute();
        session.sql("SET @cardid = ?").bind(card_id).execute();
        session.sql("update readerinfo" 
                    " set balance = balance + @bal" 
                    " where card_id = @cardid").execute();
        session.commit();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << e.what() <<endl;
        session.rollback();
    }
}

// 借书
void borrowBook(Session &session, int book_id, std::string card_id)
{   
    // 查询是否有未还的书
    session.sql("use " + std::string(SCHEMA)).execute();
    session.sql("SET @bookid = ?").bind(book_id).execute();
    session.sql("SET @cardid = ?").bind(card_id).execute();
    session.sql("SET @borrowinfo = ?").bind(BORROW_INFO).execute();
    SqlResult res = session.sql("select * from borrowinfo"  
                                " where book_id = @bookid" 
                                " and card_id = @cardid"
                                " and status = '否'")
                            .execute();
    if (!res.fetchOne())
    {
        session.startTransaction();
        try 
        {
            session.sql("insert into borrowinfo(book_id, card_id, borrow_date, return_date)"
                        " values(@bookid, @cardid, sysdate(), date_add(now(), interval 2 month))")
                   .execute();
            session.commit();
            cout << "借书成功！！！"<<endl;
        }
        catch (exception &e)
        {
            cout <<e.what() << endl;
            session.rollback();
            cout << "借书失败" << endl;
        }
    }
    else 
    {
        cout << "还有书没有还" <<endl;
    }
}

// 还书
void returnBook(Session &session, int book_id, std::string card_id)
{
    // 查询借阅记录
    Schema schema = session.getSchema(SCHEMA);
    Table table = schema.getTable(BORROW_INFO);
    RowResult res = table.select("return_date").where("book_id = :bookid and card_id = :cardId and status = '否'")
                  .bind("bookid", book_id)
                  .bind("cardId", card_id)
                  .execute();
    if (!res.fetchOne())
    {
        cout << "没有此书的借阅信息" << endl;
        return;
    }
    cout << "开始还书" <<endl;

    session.startTransaction();
    try
    {
        session.sql("use " + std::string(SCHEMA)).execute();
        session.sql("SET @bookid = ?").bind(book_id).execute();
        session.sql("SET @cardid = ?").bind(card_id).execute();

        session.sql("update borrowinfo t1 join readerinfo t2 on t1.card_id = t2.card_id" 
                    " set actual_return_date = sysdate()," 
                    " status = '是',"
                    " book_fee = (case when datediff(sysdate(), return_date) > 0 then datediff(sysdate(), return_date)*0.2 else 0.0 end)," 
                    " balance = (balance - (case when datediff(sysdate(), return_date) > 0 then datediff(sysdate(), return_date)*0.2 else 0.0 end))" 
                    " where t1.book_id = @bookid and t1.card_id = @cardid")
               .execute();
        session.commit();
    }
    catch(const std::exception& e)
    {
        cout <<e.what() << endl;
        session.rollback();
        cout << "还书失败" << endl;
        return;
    }

    cout << "还书成功" << endl;
}

// 查询某段时间所有借阅信息  xx 于 xx 借阅了 xxx，xx归还，费用：xx 或者 未归还
void queryAllBorrowRecord(Session &session)
{
    session.sql("use " + std::string(SCHEMA)).execute();

    SqlResult res = session.sql("select name, borrow_date, category, book_name, status, category" 
                                " from borrowinfo t1" 
                                " join bookinfo t2 on t1.book_id = t2.book_id" 
                                " join readerinfo t3 on t1.card_id = t3.card_id" 
                                ).execute();
    list<Row> list = res.fetchAll();
    int column_count = res.getColumnCount();
    for (Row row : list) 
        {
            for (int i = 0; i < column_count; i++)
            {
                cout << row[i] << " ";
            }
            cout << endl;
        }

}
