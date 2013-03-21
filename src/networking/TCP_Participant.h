#pragma once
//
//  TCP_Participant.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/1/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include <memory>
#include <boost/shared_ptr.hpp>

class TCP_Participant {
    
private:
    
public:
    
    virtual ~TCP_Participant(){};
    
};


typedef boost::shared_ptr<TCP_Participant> tcp_participant_ptr;