



class DBConnector {
    
private:
    

    
    
    bool hasRootAccount;
    
    void ValidateSchema();
    
public:
    
    std::string db_host;
    std::string db_port;
    std::string db_user;
    std::string db_pass;
    std::string db_name;
    
    DBConnector(std::string host, int port, std::string user, std::string pass, std::string db);
    
    pqxx::work *PrepareConn();
    
    
    
    bool AddAccount(const std::string user, const std::string pass);

    
    bool isValidHash(const std::string user, const std::string pass);
    
    std::string GenerateToken(const std::string user, const std::string pass);
    bool isValidToken(const std::string user, const std::string token);
    
    
    void testShared();
    
    
};