#include "ScreenManager.h"



void ScreenManager::onRelease(uint8_t buttons, Time timeClicked){
    if(buttons&(1<<0)) this->screens[this->currentScreen].onSelect(timeClicked);
    if(buttons&(1<<1)) this->screens[this->currentScreen].onLeft();
    if(buttons&(1<<2)) this->screens[this->currentScreen].onUp();
    if(buttons&(1<<3)) this->screens[this->currentScreen].onDown();
    if(buttons&(1<<4)) this->screens[this->currentScreen].onRight();
}

void ScreenManager::dispay(){
    auto lines = this->screens[currentScreen].getLines();
    for(int i=0;i<=min(1, lines.size());i++){
        lcd.setCursor(0,i);
        lcd.print(lines[i]);
    }
}
