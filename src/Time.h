#pragma once

#include <Arduino.h>

struct Time{
    private:
        static const unsigned long diffLimit = ((unsigned long)-1)/2;
    public:
        unsigned long ms;
        Time(unsigned long ms):ms(ms){};
        static Time getNow(){ return Time(millis()); }

        Time operator-(const Time &t){
            return this->ms - t.ms;
        }

        Time operator+(const Time &t){
            return this->ms + t.ms;
        }
        
        bool operator>(const Time &t){
            auto diff = *this - t;
            if(diff.ms > diffLimit)
                return this->ms < t.ms;
            return this->ms > t.ms;
        }
        bool operator==(const Time &t){
            return this->ms == t.ms;
        }
        bool operator<(const Time &t){
            return not (*this > t) or (*this == t);
        }
};
