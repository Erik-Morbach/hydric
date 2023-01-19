#pragma once
#include "Valve.h"
#include "Sensor.h"
#include "Configuration.h"
#include "Time.h"
#include "IoManager.h"

struct Context{
    Time phValveStopTime;
    Time ecValveStopTime;
    Time ixValveStopTime;
    Valve phValve;
    Valve ecValve;
    Valve mixValve;
    Sensor phSensor;
    Sensor ecSensor;

    double phCoef;
    double ecCoef;

    IoManager ioManager;
    Configuration config;
};

