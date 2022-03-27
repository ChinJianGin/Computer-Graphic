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

    double FrameTime;

    bool Continue = false;

    unsigned int FPS = 0;
public:
    CoreTimer(const int framerate = 60);

    void Init();

    bool CalculateTimer();

    double GetTick() const;
    double GetDeltaTick() const;
    double GetFrameTime() const;
};