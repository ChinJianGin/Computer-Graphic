#pragma once

#include"Core.h"



class CoreTimer
{
private:
    int FrameRate;

    double t;
    double dt;

    double currentTime;
    double accumulator;    

    bool Continue = false;

public:
    CoreTimer(const int framerate = 30);

    void Init();

    bool CalculateTimer();

    double GetTick();
    double GetDeltaTick();
};