#pragma once
#include "screen.h"

class MainScreen: public Screen{
public:
    virtual void onUp() override;
    virtual void onDown() override;
    virtual void onLeft() override;
    virtual void onRight() override;
    virtual void onSelect() override;
    virtual void onReset() override;

    virtual void onEnterScreen() override;
    virtual void onExitScreen() override;

    virtual std::vector<std::string> getLines() override;
};
