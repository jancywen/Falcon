#include <iostream>
#include <map>
#include <string>
#include <memory>
#include "mysql/jdbc.h"

using namespace std;


int main()
{
    cout << endl;
    cout << "Running ..." << endl;

    try {

    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;

    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "daxiong0213");
    con->setSchema("echain");
    stmt = con->createStatement();
    res = stmt->executeQuery("select * from a");
    while (res->next())
    {
        cout << "MySQL replies: ";

        cout << res->getString("name") <<endl;

        cout << "MySQL says it again: ";
        cout << res->getString(1) <<endl;
    }

    delete res;
    delete stmt;
    con->close();
    delete con;
    
    }
    catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " 
            << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }


    return 0;

}

