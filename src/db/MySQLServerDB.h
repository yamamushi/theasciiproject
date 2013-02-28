/*
 
 MySQLServerDB.h
 
 Jonathan Rumion (Yamamushi)
 02-06-2013
 
 Our MySQL version of a database connector.
 
 This won't explicitly setup our databases, this is just an interface
 to the MySQL C libraries for use in our engine.
 
 */

#include <string>
#include <mysql.h>


class MySQLServerDB {
    
private:
    
    bool ConnectionOpen;
    
    MYSQL *connection;
    
    std::string hostname;
    int port;
    std::string username;
    std::string pass;
    std::string database;
    
public:
    
    MySQLServerDB(std::string Hostname, int Port, std::string Username, std::string Pass, std::string Database);
    
    // We close our connection in our destructor
    // Note that this won't error if connection == NULL
    virtual ~MySQLServerDB(){CloseConnection();};
    
    void CloseConnection();
    int RowCount(std::string query);
    void PrintVersion();
    void Query(std::string query);
    
};
