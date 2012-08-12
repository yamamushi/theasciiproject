
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
    GenerateToken("Boosh", "password");
    
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

bool DBConnector::isValidHash(std::string user, std::string pass)
{
    std::regex e("[\\']");
    std::string cleanUser = std::regex_replace(user, e, "");
    std::string cleanPass = std::regex_replace(pass, e, "");
    
    pqxx::connection conn("host=" + db_host + " port=" + db_port + " user=" + db_user + " password=" + db_pass + " dbname=" + db_name);
    pqxx::work validatePass(conn);
    
    pqxx::result doesAccountExist = validatePass.exec("SELECT id FROM accounting WHERE username='" + cleanUser + "';");
    
    if(doesAccountExist.size() != 1)
    {
        
        validatePass.commit();
        return false;
                
    }
    else
    {

        pqxx::result md5hash = validatePass.exec("SELECT hash FROM accounting WHERE username='" + cleanUser + "';");
        pqxx::result tmphash = validatePass.exec("SELECT MD5('" + cleanPass + "');");
        
        validatePass.commit();
        
        std::string md5pass = md5hash[0][0].as<std::string>();
        std::string tmpHash = tmphash[0][0].as<std::string>();
        
        if ( md5pass.compare(tmpHash) != 0)
        {
            cout << "invalid pass" << endl;
            return false;
        }
        else
        {
            cout << "valid pass" << endl;
            return true;
        }
        
        
    }
    
}

std::string DBConnector::GenerateToken(std::string user, std::string pass)
{
    
    std::regex e("[\\']");
    std::string cleanUser = std::regex_replace(user, e, "");
    std::string cleanPass = std::regex_replace(pass, e, "");
    
    if(isValidHash(cleanUser, cleanPass))
    {
        pqxx::connection conn("host=" + db_host + " port=" + db_port + " user=" + db_user + " password=" + db_pass + " dbname=" + db_name);
        pqxx::work tokenGenerator(conn);
        
        pqxx::result md5hash = tokenGenerator.exec("SELECT hash FROM accounting WHERE username='" + cleanUser + "';");
        std::string md5pass = md5hash[0][0].as<std::string>();
        
        
        time_t rawtime;
        
        struct tm * timeinfo;
        time( &rawtime );
        timeinfo = localtime(&rawtime);
        string loctime = asctime(timeinfo);
        
        srand((unsigned int)time(&rawtime));
        
        std::stringstream tmpstream;
        tmpstream << rand();
        
        std::string tokenizeMe = md5pass;
        tokenizeMe += tmpstream.str();
        tokenizeMe += loctime;
        
        
        cout << tokenizeMe << endl;
        
        pqxx::result token = tokenGenerator.exec("SELECT MD5('" + tokenizeMe + "');");
        
        std::string finalToken = token[0][0].as<std::string>();
        
        
        tokenGenerator.exec("UPDATE accounting SET token='" + finalToken + "' WHERE username='" + cleanUser + "';");
        
        tokenGenerator.commit();
        
        return finalToken;
        
    }
    else
    {
        return string("invalid Credentials");
    }
}


bool DBConnector::isValidToken()
{
    return true;
}


void DBConnector::testShared()
{
    
    cout << "Working" << endl;
    
}