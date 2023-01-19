#include <Arduino.h>
#include "App.h"

App *app;
void setup(){
    app = new App();
}
void loop(){
    app->update();
}
