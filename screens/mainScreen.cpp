#include "mainScreen.h"

void MainScreen::onUp(){

}
void MainScreen::onDown(){

}
void MainScreen::onRight(){

}
void MainScreen::onLeft(){

}
void MainScreen::onSelect(){
    this->app->switchToScreen();
}
void MainScreen::onReset(){

}


std::vector<std::string> getLines(){
    return {"ph:%0.03f ec:%0.03f",
            "iterations: %5d"};
}
