#pragma once

#include "Pin.h"


class Sensor{
    private:
        Pin pin;
        double min,max;
    public:
        double getNormalized();

        /**
         * @brief what should be done with the sensor enviroment to maintains min,max conditions
         *
         * @return  -1 -> control down; 1 -> control up; 0 do nothing
         */
        int shouldControl();
};

