#include "IoManager.h"
#include <Arduino.h>
#include <vector>


bool IoManager::update(){
    int value = analogRead(A0);
    if(value < 60) return this->selectClicked();
    if(value < 100) return this->leftClicked();
    if(value < 150) return this->upClicked();
    if(value < 150) return this->downClicked();
    if(value < 200) return this->rightClicked();
    this->released = millis();
    return 0;
}


bool IoManager::selectClicked() {
    if(this->flag.select) return 1;
    this->flag.val = 0;
    this->flag.select = 1;
    this->pressed = millis();
    this->released = 0;
}

bool IoManager::leftClicked() {
    if(this->flag.left) return 1;
    this->flag.val = 0;
    this->flag.left = 1;
    this->pressed = millis();
    this->released = 0;
}

bool IoManager::upClicked() {
    if(this->flag.up) return 1;
    this->flag.val = 0;
    this->flag.up = 1;
    this->pressed = millis();
    this->released = 0;
}

bool IoManager::downClicked() {
    if(this->flag.down) return 1;
    this->flag.val = 0;
    this->flag.down = 1;
    this->pressed = millis();
    this->released = 0;
}

bool IoManager::rightClicked() {
    if(this->flag.right) return 1;
    this->flag.val = 0;
    this->flag.right = 1;
    this->pressed = millis();
    this->released = 0;
}

