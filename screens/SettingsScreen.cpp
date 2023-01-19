#include "SettingsScreen.h"
#include "App.h"

void SettingsScreen::onUp(){

}
void SettingsScreen::onDown(){

}
void SettingsScreen::onRight(){

}
void SettingsScreen::onLeft(){

}
void SettingsScreen::onSelect(){
    this->app->switchToScreen(MENUSETTINGS);
}
void SettingsScreen::onReset(){

}


std::vector<std::string> getLines(){
    return {"ph:%0.03f ec:%0.03f",
            "iterations: %5d"};
}
