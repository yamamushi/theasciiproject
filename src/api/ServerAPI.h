#pragma once
//
//  ServerAPI.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/1/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "../db/MySQLServerDB.h"
#include "../server/ServerInit.h"
#include "../utils/FileLogger.h"

#include <memory>

extern FileLogger *fileLogger;


class ServerAPI : public std::enable_shared_from_this<ServerAPI>{
    
private:
    
    
    
public:
    
    ServerAPI(){};
    ~ServerAPI(){};
    
    // I don't believe all of the commands need to be static, but it would still be nice..
    // static <return type> functionname(params);
    
};