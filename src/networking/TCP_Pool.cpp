//
//  TCP_Pool.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/1/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "TCP_Pool.h"
#include "TCP_Participant.h"
#include <set>

void TCP_Pool::join(tcp_participant_ptr tcp_participant){
    
    tcp_participants.insert(tcp_participant);
    
}

void TCP_Pool::leave(tcp_participant_ptr tcp_participant){
    
    tcp_participants.erase(tcp_participant);
    
}