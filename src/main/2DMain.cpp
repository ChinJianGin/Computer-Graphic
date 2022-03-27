#include"../core/include/Core.h"
#include"../game/src/Game.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
const char* WidnowTitle = "2D Shooting!";

int main()
{
    CustomSpace::Log::Init();

    CORE_WARN("Initialized tag!");
    auto Game = new ShootingGame(WINDOW_WIDTH, WINDOW_HEIGHT, WidnowTitle, false, VSYNC);

    GAME_WARN("Start Running");
    Game->Run();

    glfwTerminate();
    return 0;
}