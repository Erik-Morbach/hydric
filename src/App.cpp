#include "App.h"


App::App(){
    if(not this->ctx.configuration.loadFromEEPROM())
        this->ctx.configuration.loadDefault();

    this->events.push(MeasureEventLoop(Time::getNow()+2000,&this->ctx));

    this->events.push(ScreenManagerEventLoop(Time::getNow(), &this->ctx));
}

App::~App(){
    for(auto w: {this->ctx.phValve, this->ctx.ecValve, this->ctx->mixValve})
        w.close();
    this->events.clear();
}


void App::update(){
    if(this->events.empty()) return;
    auto event = this->events.top();
    if(event.executeTime > Time::getNow()) return;
    events.pop();

    events.execute(this->events);
}
