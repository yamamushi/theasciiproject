//
//  Keyboard.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 10/16/12.
//  Copyright (c) 2012 Jonathan Rumion. All rights reserved.
//

#ifndef The_ASCII_Project_Keyboard_h
#define The_ASCII_Project_Keyboard_h

#include <string>
#include "Display.h"


enum KEYS {
    
    KEY_NONE,
    
    KEY_UP,
    KEY_DOWN,
    KEY_RIGHT,
    KEY_LEFT,
    
    KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,
    KEY_EXCLAMATION, KEY_AT, KEY_NUMBER, KEY_DOLLAR, KEY_PERCENT, KEY_CARROT,
    KEY_AND, KEY_STAR, KEY_LEFT_PAREN, KEY_RIGHT_PAREN,
    
    KEY_MINUS, KEY_UNDERSCORE, KEY_PLUS, KEY_EQUALS, KEY_SPACEBAR, KEY_TILDE, KEY_BACKTICK,
    KEY_FORWARDSLASH, KEY_BACKSLASH, KEY_QUESTION, KEY_LEFT_BRACKET, KEY_RIGHT_BRACKET,
    KEY_LEFT_CURLY_BRACKET, KEY_RIGHT_CURLY_BRACKET, KEY_COLON, KEY_SEMICOLON,
    KEY_DOUBLEQUOTE, KEY_SINGLEQUOTE, KEY_COMMA, KEY_PERIOD, KEY_LESSTHAN, KEY_GREATERTHAN,
    KEY_PIPE,
    
    
    KEY_a,KEY_A,
    KEY_b,KEY_B,
    KEY_c,KEY_C,
    KEY_d,KEY_D,
    KEY_e,KEY_E,
    KEY_f,KEY_F,
    KEY_g,KEY_G,
    KEY_h,KEY_H,
    KEY_i,KEY_I,
    KEY_j,KEY_J,
    KEY_k,KEY_K,
    KEY_l,KEY_L,
    KEY_m,KEY_M,
    KEY_n,KEY_N,
    KEY_o,KEY_O,
    KEY_p,KEY_P,
    KEY_q,KEY_Q,
    KEY_r,KEY_R,
    KEY_s,KEY_S,
    KEY_t,KEY_T,
    KEY_u,KEY_U,
    KEY_v,KEY_V,
    KEY_w,KEY_W,
    KEY_x,KEY_X,
    KEY_y,KEY_Y,
    KEY_z,KEY_Z
    
    
};




class Keyboard {
  
private:
    
    Display *attachedDisplay;
    
    
public:
    
    
    Keyboard(Display *attachTo);
    
    int parseKey(std::string input);
    
    
    
    
    
    virtual ~Keyboard(){};
    
    
};



#endif
