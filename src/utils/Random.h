#pragma once
//
//  Random.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/3/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include <boost/random/random_device.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

const int MAX_RANDOM_RANGE = 100000000;

class Random {
  
private:
    
    int seed;
    boost::random::mt19937 mersenneGen;
    
public:
    
    Random(int s=0) : seed(s){if(seed != 0){mersenneGen.seed(s);}};
    
    int roll_die(int sides=6);
    int role_die_crypt(int sides=6);
    
    int rand(int range=MAX_RANDOM_RANGE);
    int rand_range(int begin, int range=MAX_RANDOM_RANGE);
    int rand_crypt(int range=MAX_RANDOM_RANGE);
    int rand_crypt_range(int begin, int range=MAX_RANDOM_RANGE);
    
};