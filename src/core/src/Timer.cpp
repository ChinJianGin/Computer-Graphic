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

double CoreTimer::GetTick() const
{
    return t;
}

double CoreTimer::GetDeltaTick() const
{
    return dt;
}

double CoreTimer::GetFrameTime() const
{
    return FrameTime;
}

bool CoreTimer::CalculateTimer()
{
    double newTime = glfwGetTime();
    double frameTime = newTime - currentTime;

    currentTime = newTime;

    accumulator += frameTime;

    FrameTime = frameTime;
    t = 0;

    while(accumulator >= dt)
    {
        Continue = false;
        accumulator -= dt;
        t += dt;  
#ifdef DISPLAY_FPS
        FPS++;  
#endif
    }
    Continue = true;
#ifdef DISPLAY_FPS
    if(t >= dt)
    {
        double F = (1.f / t) * FPS;
        std::cout << F << std::endl;
        FPS = 0;
    } 
#endif   
    return Continue;
}