#include"Game.h"

ShootingGame* ShootingGame::Instance = nullptr;

ShootingGame::ShootingGame(int width, int height, const char* title, bool screen, bool vsync)
{
    using namespace CustomSpace;
    Instance = this;
    M_Window = Windows::CreateWindow(WindowProps(width, height, title, screen, vsync));

    TriangleVAO = VAO::Create();

    glm::vec3 TrianglePoints[6] = 
    {
        glm::vec3(-.5f, -.5f * float(sqrt(3)) / 3, 0.f), glm::vec3(1.f, 0.f, 0.f),
        glm::vec3( .5f, -.5f * float(sqrt(3)) / 3, 0.f), glm::vec3(.2f, .3f, .8f),
        glm::vec3( 0.f,  .5f * float(sqrt(3)) * 2 / 3, 0.f), glm::vec3(.8f, .8f, .2f)
    };

    CustomSpace::Ref<VBO> TriangleVBO = VBO::Create(TrianglePoints, sizeof(TrianglePoints));

    CustomSpace::BufferLayout TriangleLayout = 
    {
        {CustomSpace::ShaderDataType::f_Vec3, "vPosition"},
        {CustomSpace::ShaderDataType::f_Vec3, "vColor"}
    };
    TriangleVBO->SetLayout(TriangleLayout);
    TriangleVAO->AddVBO(TriangleVBO);

    GLuint TriangleIndices[] =
    {
        0, 1, 2
    };

    CustomSpace::Ref<EBO> TriangleEBO = EBO::Create(TriangleIndices, sizeof(TriangleIndices));
    TriangleVAO->SetEBO(TriangleEBO);

    TriangleShaderProgram = CustomSpace::CreateRef<Shader>(Shader("../src/shader/Example3a.vert", "../src/shader/Example3a.frag"));;
}

void ShootingGame::Close()
{
    B_Running =  false;
}

void ShootingGame::Run()
{
    while(B_Running)
    {
        B_Running = !glfwWindowShouldClose((GLFWwindow*)M_Window->GetWindow());
        glClearColor(0.f, 1.f, 1.f, 1.f);
        glClear( GL_COLOR_BUFFER_BIT);

        TriangleShaderProgram->Activate();
        TriangleVAO->Bind();
        glDrawElements(GL_TRIANGLES, (TriangleVAO->GetEBO()->GetCount() / sizeof(GLuint)), GL_UNSIGNED_INT, 0);

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_ESCAPE)) exit(EXIT_SUCCESS);

        M_Window->Update();        
    }
}