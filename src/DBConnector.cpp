
#include "Headers.h"


DBConnector::DBConnector(std::string host, int port, std::string user, std::string pass, std::string db)
{
    
    db_host = host;
    
    
    
    std::stringstream tmpstream;
    tmpstream << port;
    
    db_port = tmpstream.str();
    
    db_user = user;
    db_pass = pass;
    db_name = db;
    
    ValidateSchema();
    
    AddAccount("Boosh", "password");
    GenerateHash("Boosh", "password");
    
}



void DBConnector::ValidateSchema()
{
    
    try
    {
        
        pqxx::connection conn("host=" + db_host + " port=" + db_port + " user=" + db_user + " password=" + db_pass + " dbname=" + db_name);
        
        pqxx::work schemaCheck(conn);
        
        
        schemaCheck.exec("CREATE TABLE IF NOT EXISTS accounting(id SERIAL PRIMARY KEY, username varchar(16), timestamp timestamp(6), hash varchar(255), token varchar(255), filename varchar(255));");
        
        
        pqxx::result rootCheck = schemaCheck.exec("SELECT id FROM accounting WHERE username = 'root'");
        
        if (rootCheck.size() != 1)
        {
            
            std::cerr << "root account does not exist" << endl;
            
            
            time_t rawtime;
            
            struct tm * timeinfo;
            time( &rawtime );
            timeinfo = localtime(&rawtime);
            string loctime = asctime(timeinfo);
            
            srand((unsigned int)time(NULL));
            
            std::stringstream tmpstream;
            tmpstream << rand();
            
            
            schemaCheck.exec("INSERT INTO accounting (username, timestamp, hash) VALUES ('root', '" + loctime + "', MD5('"  + tmpstream.str() + "'));" );
            
            hasRootAccount = true;
        }
        
        schemaCheck.commit();
        
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        
    }
    catch(...)
    {
        std::cerr << "Unknown Exception in DBConnector::ValidateSchema()" << std::endl;
    }
    
    
}



bool DBConnector::AddAccount(std::string user, std::string pass)
{
    
    std::regex e("[\\']");
    std::string cleanUser = std::regex_replace(user, e, "");
    std::string cleanPass = std::regex_replace(pass, e, "");
    
    pqxx::connection conn("host=" + db_host + " port=" + db_port + " user=" + db_user + " password=" + db_pass + " dbname=" + db_name);
    pqxx::work addAccount(conn);
    
    pqxx::result doesAccountExist = addAccount.exec("SELECT id FROM accounting WHERE username='" + cleanUser + "';");
    
    if(doesAccountExist.size() != 1)
    {
        
        time_t rawtime;
        
        struct tm * timeinfo;
        time( &rawtime );
        timeinfo = localtime(&rawtime);
        string loctime = asctime(timeinfo);
        
        srand((unsigned int)time(NULL));
        
        std::stringstream tmpstream;
        tmpstream << rand();
        
        addAccount.exec("INSERT INTO accounting (username, timestamp, hash) VALUES ('" + cleanUser + "', '" + loctime + "', MD5('"  + cleanPass + "'));" );
        addAccount.commit();
        return true;
    }
    else
    {
        addAccount.commit();
        return false;
    }
    
    
}

void DBConnector::GenerateHash(std::string user, std::string pass)
{
    std::regex e("[\\']");
    std::string cleanUser = std::regex_replace(user, e, "");
    std::string cleanPass = std::regex_replace(pass, e, "");
    
    pqxx::connection conn("host=" + db_host + " port=" + db_port + " user=" + db_user + " password=" + db_pass + " dbname=" + db_name);
    pqxx::work validatePass(conn);
    
    pqxx::result md5hash = validatePass.exec("SELECT hash FROM accounting WHERE username= '" + cleanUser + "';");
    
    validatePass.commit();
    
    std::string md5pass = md5hash[0][0].as<std::string>();
    
    cout << md5pass << endl;
    
}

void DBConnector::GenerateToken()
{
    
}


bool DBConnector::isValidHash()
{
    return true;
}

bool DBConnector::isValidToken()
{
    return true;
}


void DBConnector::testShared()
{
    
    cout << "Working" << endl;
    
}