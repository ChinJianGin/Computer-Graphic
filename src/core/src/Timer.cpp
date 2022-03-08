#include"../include/Timer.h"

CoreTimer::CoreTimer(const int framerate)
{
    FrameRate = framerate;
    this->Init();
}

void CoreTimer::Init()
{
    t = 0.f;
    dt = (double)1 / FrameRate;
    currentTime = glfwGetTime();
    accumulator = 0.f;
}

double CoreTimer::GetTick()
{
    return t;
}

double CoreTimer::GetDeltaTick()
{
    return dt;
}

bool CoreTimer::CalculateTimer()
{
    double newTime = glfwGetTime();
    double frameTime = newTime - currentTime;
    currentTime = newTime;

    accumulator += frameTime;

    while(accumulator >= dt)
    {
        Continue = false;
        accumulator -= dt;
        t += dt;        
    }
    Continue = true;

    return Continue;
}