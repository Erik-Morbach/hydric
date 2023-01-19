#pragma once
#include <utility>
#include <vector>
#include <string>

#include "App.fwd.h"

struct Screen{
protected:
    std::pair<uint8_t, uint8_t> cursor;
    double debouncePlus = 0;
    double debounceMinus = 0;
    double debounceSelect = 0;
    App *app;

public:
    virtual void onUp() = 0;
    virtual void onDown() = 0;
    virtual void onLeft() = 0;
    virtual void onRight() = 0;
    virtual void onSelect() = 0;
    virtual void onReset() = 0;

    virtual void onEnterScreen() = 0;
    virtual void onExitScreen() = 0;

    virtual std::vector<std::string> getLines() = 0;
};
