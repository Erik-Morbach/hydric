#pragma once


class Pin{
    private:
        int id;
    public:
        void writeDigital(int level);
        void writeAnalog(double value);
        int getValue();
        double getAnalog();
};
