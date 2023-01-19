#pragma once
#include <queue>
#include <Arduino.h>

#include "Time.h"
#include "Context.h"

struct Event{
    protected: 
        Time executeTime;
        Context *ctx;
    public: 
        Event(Time executeTime, Context *ctx):
            executeTime(executeTime), ctx(ctx){
        }

        bool operator<(const Event &ev){
            return this->executeTime < ev.executeTime;
        }
        bool operator==(const Event &ev){
            return this->executeTime == ev.executeTime;
        }

        bool operator<=(const Event &ev){
            return (*this < ev) or (*this == ev);
        }

        virtual void execute(std::priority_queue<Event> &eventQueue) = 0;
};


struct OpenPhEvent: public Event{
    OpenPhEvent(Time executeTime, Context *ctx):
        executeTime(executeTime), ctx(ctx){
    }
    void execute(std::priority_queue<Event> &eventQueue){
        this->ctx->phValve.open();
    }
};
struct ClosePhEvent: public Event{
    ClosePhEvent(Time executeTime, Context *ctx):
        executeTime(executeTime), ctx(ctx){
    }
    void execute(std::priority_queue<Event> &eventQueue){
        this->ctx->phValve.close();
    }
};
struct OpenEcEvent: public Event{
    OpenEcEvent(Time executeTime, Context *ctx):
        executeTime(executeTime), ctx(ctx){
    }
    void execute(std::priority_queue<Event> &eventQueue){
        this->ctx->ecValve.open();
    }
};
struct CloseEcEvent: public Event{
    CloseEcEvent(Time executeTime, Context *ctx):
        executeTime(executeTime), ctx(ctx){
    }
    void execute(std::priority_queue<Event> &eventQueue){
        this->ctx->ecValve.close();
    }
};
struct OpenMixEvent: public Event{
    OpenMixEvent(Time executeTime, Context *ctx):
        executeTime(executeTime), ctx(ctx){
    }
    void execute(std::priority_queue<Event> &eventQueue){
        this->ctx->mixValve.open();
    }
};
struct CloseMixEvent: public Event{
    CloseMixEvent(Time executeTime, Context *ctx):
        executeTime(executeTime), ctx(ctx){
    }
    void execute(std::priority_queue<Event> &eventQueue){
        this->ctx->mixValve.close();
    }
};

struct EventLoop: public Event{
    private:
        Time period;
    public:
        EventLoop(Time beginTime, Time period, Context *ctx):
                executeTime(executeTime), period(period), ctx(ctx) {
        }

        void execute(std::priority_queue<Event> &eventQueue){
            loop(eventQueue);
            this->beginTime = this->beginTime + period;
            eventQueue.push(*this);
        }
        virtual void loop(std::priority_queue<Event> &eventQueue) = 0;
};


struct MeasureEventLoop: public EventLoop{
    MeasureEventLoop(Time executeTime, Time period, Context *ctx):
        EventLoop(executeTime, period, ctx){
    }
    void loop(std::priority_queue<Event> &eventQueue){
        bool phControl = this->ctx->phSensor.shouldControl()!=0;
        bool ecControl = this->ctx->ecSensor.shouldControl()!=0;
        if(not phControl and not ecControl) return;
        Time currentTime = millis();
        eventQueue.push(OpenMixEvent(currentTime, this->ctx));
        this->ctx->mixValveStopTime = currentTime + this->ctx->config.mixWaitTime;
        if(phControl){
            eventQueue.push(OpenPhEvent(currentTime, this->ctx));
            this->ctx->phValveStopTime = currentTime + this->ctx->config.phWaitTime;
            eventQueue.push(ClosePhEvent(this->ctx->phValveStopTime, this->ctx));
        }
        if(ecControl){
            eventQueue.push(OpenEcEvent(currentTime, this->ctx));
            this->ctx->ecValveStopTime = currentTime + this->ctx->config.ecWaitTime;
            eventQueue.push(CloseEhEvent(this->ctx->ecValveStopTime, this->ctx));
        }
        this->ctx->mixValveStopTime = max(this->ctx->mixWaitTime, this->ctx->phValveStopTime);
        this->ctx->mixValveStopTime = max(this->ctx->mixWaitTime, this->ctx->ecValveStopTime);
        eventQueue.push(CloseMixEvent(this->ctx->mixValveStopTime, this->ctx));
    }
};


struct IOEventLoop: public EventLoop {
    IOEventLoop(Time executeTime, Time period, Context *ctx):
        EventLoop(executeTime, period, ctx){
    }
    uint8_t getPins(){
        static constexpr std::vector<int> values{60,200,400,600,800};
        auto value = analogRead(A0);
        for(size_t i=0;i<values.size();i++)
            if(value < values[i])
                return 1<<i;
    }

    void loop(std::priority_queue<Event> &eventQueue){
        auto pins = getPins();
        if(not (this->ctx->clicked & pins)){
            if(pins){
                this->ctx->beginClickTime = Time::getTimeNow();
                this->ctx->onPress = 1;
                this->ctx->onRelease = 0;
            }
            else{
                this->ctx->onPress = 0;
                this->ctx->onRelease = 1;
            }
        }
        this->ctx->clicked = pins;
    }
};

struct ScreenManagerEventLoop: public EventLoop{
    private:
        ScreenManager sm;
    public:
        ScreenManagerEventLoop(Time executeTime, Time period, Context *ctx):
            EventLoop(executeTime, period, ctx){
        }
        void loop(std::priority_queue<Event> &eventQueue){
            if(this->ctx->ioManager.released!=0){
                this->ctx->ioManager.released = 0;
                this->sm.onRelease(this->ctx->ioManager.flag, this->ctx->ioManager.released - this->ctx->ioManager.pressed);
            }
            this->sm.display();
        }
};

struct IoManagerEventLoop: public EventLoop{
    IoManagerEventLoop(Time executeTime, Time period, Context *ctx):
            EventLoop(beginTime, period, *ctx){
    }
    void loop(std::priority_queue<Event> &eventQueue){
        this->ctx->ioManager.update();
    }
};
