//
//  Random.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/3/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "Random.h"


int Random::roll_die(int sides){
    boost::random::uniform_int_distribution<> dist(1, sides);
    return dist(mersenneGen);
}


int Random::role_die_crypt(int sides){
    boost::random::uniform_int_distribution<> dist(1, sides);
    boost::random::random_device randomDevice;
    return dist(randomDevice);
}

int Random::rand(int range){
    boost::random::uniform_int_distribution<> dist(1, range);
    return dist(mersenneGen);
}

int Random::rand_range(int begin, int range){
    boost::random::uniform_int_distribution<> dist(begin, range);
    return dist(mersenneGen);
}

int Random::rand_crypt(int range){
    boost::random::uniform_int_distribution<> dist(1, range);
    boost::random::random_device randomDevice;
    return dist(randomDevice);
}

int Random::rand_crypt_range(int begin, int range){
    boost::random::uniform_int_distribution<> dist(begin, range);
    boost::random::random_device randomDevice;
    return dist(randomDevice);
}