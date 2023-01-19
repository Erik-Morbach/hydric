#pragma once

#include <cstdint>
#include <utility>
#include <vector>
#include <LiquidCrystal.h>
#include "Context.h"
#include "Time.h"
#include "Screen.fwd.h"

#define MAINSCREEN 0
#define VALVSCREEN 1
#define TESTSCREEN 2
#define CONFIGSCREEN 3


class LiquidCrystal;
class ScreenManager{
    friend class Screen;
    private:
        std::vector<Screen> screens;
        uint8_t currentScreen;
        std::pair<uint8_t, uint8_t> cursor;
        LiquidCrystal lcd(8,9,4,5,6,7);
        Context *ctx;
    public:
        void cursor(){ this->lcd.cursor(); }
        void noCursor(){ this->lcd.noCursor(); }
        void setCursor(uint8_t col, uint8_t row){ this->lcd.setCursor(col, row); }
        void setScreen(uint8_t index){
            this->currentScreen = index;
        }
        ScreenManager(Context *ctx): ctx(ctx){
        }
        void onRelease(uint8_t buttons, Time timeClicked);
        void dispay();

};
