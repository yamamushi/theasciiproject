#pragma once
//
//  TCP_Pool.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/1/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//
#include "TCP_Participant.h"
#include <boost/shared_ptr.hpp>
#include <memory>
#include <set>


class TCP_Pool {
    
private:
    
    std::set<tcp_participant_ptr> tcp_participants;
    
    
public:
    
    TCP_Pool(){};
    virtual ~TCP_Pool(){};
    
    
    void join(tcp_participant_ptr tcp_participant);
    void leave(tcp_participant_ptr tcp_participant);
    
    
};

typedef boost::shared_ptr<TCP_Pool> tcp_pool_ptr;
