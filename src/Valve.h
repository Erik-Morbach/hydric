#pragma once

class Valve{
    private:
        int pin;
    public:
        Valve() = delete;
        Valve(int pin);

        void open();
        void close();
};
