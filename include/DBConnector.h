



class DBConnector {
    
private:
    
    std::string db_host;
    std::string db_port;
    std::string db_user;
    std::string db_pass;
    std::string db_name;
    
    
    bool hasRootAccount;
    
    void ValidateSchema();
    
public:
    
    DBConnector(std::string host, int port, std::string user, std::string pass, std::string db);
    
    pqxx::work *PrepareConn();
    
    
    
    bool AddAccount(std::string user, std::string pass);

    
    bool isValidHash(std::string user, std::string pass);
    
    std::string GenerateToken(std::string user, std::string pass);
    bool isValidToken();
    
    
    void testShared();
    
    
};