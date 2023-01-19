#pragma once
#include <cstdio>
#include <vector>
#include <string>
#include "Configuration.h"
#include "Context.h"
#include "Screen.fwd.h"
#include "ScreenManager.h"

byte on[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte off[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

struct Screen{
    ScreenManager *sm;
    Context *ctx;
    void onSelect(Time timeClicked){}
    void onLeft(){}
    void onRight(){}
    void onUp(){}
    void onDown(){}

    std::vector<std::string> getLines(){
        return {"a BJM ",
                "Program"};
    }
    char charOn() { return 0b11111111; }
    char charOff() { return 0b11111110; }
};

struct MainScreen : public Screen{
    void onSelect(Time timeClicked){
        this->sm->setScreen(VALVSCREEN);
    }

    std::vector<std::string> getLines(){
        double ph = this->ctx->phSensor.getNormalized()*this->ctx->phCoef;
        double ec = this->ctx->ecSensor.getNormalized()*this->ctx->ecCoef;
        char line[2][16];
        sprintf(line[0], "Ph %-5.2f     M%c",ph, (this->ctx->mixValve.active()?charOn():charOff());
        sprintf(line[1], "Ec %-5.2f  E%c P%c",ph, (this->ctx->ecValve.active()?charOn():charOff()),
                                                  (this->ctx->phValve.active()?charOn():charOff()));
        return {line[0],line[1]};
    }
};

struct ValvScreen: public Screen{
    void onSelect(Time timeClicked){
        this->sm->setScreen(CONFIGSCREEN);
    }

    std::vector<std::string> getLines(){
        return {"PhV XXX EcV XXX",
                "MxV XXX"};
    }
};

struct TestScreen: public Screen{
    void onSelect(Time clicked){
        this->sm->setScreen(MAINSCREEN);
    }

    void onRight(){

    }
    void onLeft(){

    }
    void onUp(){

    }
    void onDown(){

    }

    std::vector<std::string> getLines(){
        return {"PhV X EcV X",
                "MxV X"};
    }
};


struct ConfigScreen: public Screen {
    uint8_t cursorType = 0;
    uint8_t configCode = 0;
    int cursorPower = 0;
    std::pair<std::string, double> currentConfig;
    uint8_t getCursorRow(){
        return 16 - (cursorPower+3);
    }
    void sumOnDigit(){
        double val = 1;
        for(int i=0;i<cursorPower;i++) val *= 10;
        for(int i=0;i>=cursorPower;--i) val /= 10;
        this->currentConfig.second += val;
    }
    void subOnDigit(){
        double val = 1;
        for(int i=0;i<cursorPower;i++) val *= 10;
        for(int i=0;i>=cursorPower;--i) val /= 10;
        this->currentConfig.second -= val;
    }
    void saveConfig(){
        this->ctx->config.saveConfig(configCode, currentConfig.second);
    }

    void updateConfig(){
        this->currentConfig = this->ctx->config.getConfig()[configCode];
    }
    void onSelect(uint64_t periodMs){
        this->sm->nocursor();
        if(periodMs < 1000) {
            cursorType = (cursorType+1)%2;
            if(cursorType==1) this->sm->cursor();
            this->saveConfig();
        }
        else this->sm->setScreen(MAINSCREEN);
    }
    void onRight(){
        if(cursorType==0){
            if(configCode < config.getConfig().size())
                configCode++;
            this->updateConfig();
        }
        else{
            cursorPower = max(cursorPower - 1, -3);
            this->sm->setCursor(this->getCursorRow(), 1);
        }
    }
    void onLeft(){
        if(cursorType==0){
            if(configCode>0)
                configCode--;
            this->updateConfig();
        }
        else{
            cursorPower = min(cursorPower + 1, 6);
            this->sm->setCursor(this->getCursorRow(), 1);
        }
    }
    void onUp(){
        if(cursorType==1) this->sumOnDigit();
    }
    void onDown(){
        if(cursorType==1) this->subOnDigit();
    }
    std::vector<std::string> getLines(){
        char value[16];
        auto configValue = config.getConfig()[configCode]; 
        sprintf(value, "%-10.3f", configValue.second);
        return {std::string("Name ") + configValue.first,
                std::string("Value ") + value};
    }

};
