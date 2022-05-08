#include"../core/include/Core.h"
#include"../game/include/Game.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 1280
const char* WidnowTitle = "2D Shooting!";

int main()
{
    CustomSpace::Log::Init();

    srand(time(NULL));

    CORE_WARN("Initialized tag!");
    auto Game = new ShootingGame(WINDOW_WIDTH, WINDOW_HEIGHT, WidnowTitle, false, VSYNC);

    GAME_WARN("Start Running");
    Game->Run();

    glfwTerminate();
    return 0;
}