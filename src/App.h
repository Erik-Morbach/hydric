#pragma once
#include "Sensor.h"
#include "Valve.h"
#include "Event.h"
#include "Context.h"
#include <memory>
#include <queue>

class App{
    private:
        std::priority_queue<Event> events;
        Context ctx;
    public:
        App();
        ~App();
        void update();
};
