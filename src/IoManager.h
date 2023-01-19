#pragma once

#include <cstdint>
struct IoManager{
    uint64_t pressed = 0;
    uint64_t released = 0;
    union{
        uint8_t select:1, 
                left:1, 
                up:1, 
                down:1, 
                right:1,
                rest:3;
        uint8_t val;
    }flag;
    bool update();

    bool selectClicked();
    bool leftClicked();
    bool upClicked();
    bool downClicked();
    bool rightClicked();
    
};

