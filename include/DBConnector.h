



class DBConnector {
    
private:
    
    std::string db_host;
    int db_port;
    std::string db_user;
    std::string db_pass;
        
public:
    
    DBConnector(std::string host, int port, std::string user, std::string pass);
    
    void AddAccount();
    void GenerateHash();
    void GenerateToken();
    
    
    bool isValidHash();
    bool isValidToken();
    
    
    void testShared();
    
    
};