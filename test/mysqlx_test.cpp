#include <iostream>
#include <string>
#include <mysqlx/xdevapi.h>

using namespace std;
using namespace mysqlx;

int main()
{

    Session sess("localhost", 33060, "root", "daxiong0213");
/*
    cout <<"本地数据库："<<endl;
    list<Schema> schemaList = sess.getSchemas();
    for (Schema schema : schemaList)
    {
        cout << schema.getName() << endl;
    }
    cout << endl;

    Schema db= sess.getSchema("echain");
    // or Schema db(sess, "echain");

    cout << "数据库echain里所有的表：" <<endl;
    list<Table> tableList = db.getTables();
    for (Table t : tableList)
    {
        cout << t.getName() << endl;
    }

    cout << endl;

    Table table = db.getTable("a");
    cout << table.count() << endl;
    
    RowResult res = table.select("name", "age")
                        .where("name like :param")
                        .bind("param", "L%")
                        .execute();

    cout<<"RowResult: "<< res.count() <<endl;


    // RowResult result = sess.sql("SELECT name, age"
    //                             "FROM a" 
    //                             "WHERE name like ?" )
    //                         .bind("L%").execute();
    // cout << res.count() <<endl;


    Collection myColl = db.createCollection("my_collection");
    myColl.add(R"({"name": "Laurie", "age": 19})").execute();
    myColl.add(R"({"name": "Nadya", "age": 54})").execute();
    myColl.add(R"({"name": "Lukas", "age": 32})").execute();

    // Find a document
    DocResult docs = myColl.find("name like :param1 AND age < :param2").limit(1)
                        .bind("param1","L%").bind("param2",20).execute();

    // Print document
    cout << docs.fetchOne() << endl;

    // Drop the collection
    db.dropCollection("my_collection");

*/
/*
    // 在表中插入数据

    Table table_a = db.getTable("a");
    table_a.insert("name", "age").values("无法", 20).execute();
    table_a.insert("name", "age").values("无天", 25).execute();

    //删
    table_a.remove().where("name = :param").bind("param", "无天").execute();
    
    // 改
    table_a.update().set("name" ,"param").where("name = :param").bind("param", "无法").execute();

    // 查

    RowResult a_res = table_a.select().execute();
    list<Row> a_rows = a_res.fetchAll();
    
    int column_count = a_res.getColumnCount();

    const Columns &columns = a_res.getColumns();


    for (Row row : a_rows)
    {
        cout << "id: " <<row[0]<< endl;
        cout << "name: " << row[1] << endl;
        cout << "age: " << row[2] << endl;
        cout << endl;
    }
*/
    // *** 
    cout<< "\n\n******\n\n" << endl;

    Schema db= sess.getSchema("echain");
    Table table_a = db.getTable("a");
    RowResult res = table_a.select("name", "age").execute();

    // Row row;
    // while ((row = res.fetchOne()))
    // {
    //     cout << "name: " << row[0] << endl;
    //     cout << "age: " << row[1] <<endl;
    //     cout << endl;
    // }
    

    const Columns &columns = res.getColumns();
    Row record = res.fetchOne();
    while (record)
    {
        for (unsigned index=0; index < res.getColumnCount(); ++index)
        {
            cout << columns[index].getColumnName() << ":" << record[index] << endl;
        }
        record = res.fetchOne();
        cout << endl;
    }
    


    sess.close();

    return 0;
}