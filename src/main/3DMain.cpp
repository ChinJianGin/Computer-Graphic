#include"../core/include/Core.h"
#include"../lightscene/include/3DScene.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
const char* WidnowTitle = "3D World";

int main()
{
    CustomSpace::Log::Init();

    srand(time(NULL));

    CORE_WARN("Initialized tag!");
    auto LightScene = new LightTestRoom(WINDOW_WIDTH, WINDOW_HEIGHT, WidnowTitle, false, VSYNC);

    GAME_WARN("Start Running");
    LightScene->Run();

    glfwTerminate();
    return 0;
}