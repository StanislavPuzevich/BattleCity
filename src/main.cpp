#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>

#include "Resources/ResourceManager.h"
#include "Game/Game.h"
#include "Renderer/Renderer.h"

glm::ivec2 g_WindowSize(13 * 16, 14 * 16);
std::unique_ptr<Game> g_game = std::make_unique<Game>(g_WindowSize);

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_WindowSize.x = width;
    g_WindowSize.y = height;
    RenderEngine::Renderer::setViewport(width, height);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
    g_game->setKey(key, action);
}

void error_callback(int error, const char* msg) 
{
    std::string s;
    s = " [" + std::to_string(error) + "] " + msg + '\n';
    std::cerr << s << std::endl;
}

int main(int argc, char** argv)
{
    /* Initialize the library */
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        std::cerr << "glfwInit failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_WindowSize.x, g_WindowSize.y, "Battle City", nullptr, nullptr);
    if (!pWindow)
    {
        std::cerr << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);
    
    /* Make the window's context current */
    glfwMakeContextCurrent (pWindow);
	
	if(!gladLoadGL())
	{
		std::cout << "Can't load GLAD" << std::endl;
		return -1;
	}
	
    std::cout << "Renderer: " << RenderEngine::Renderer::getString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL Version: " << RenderEngine::Renderer::getString(GL_VERSION) << std::endl;
	
    RenderEngine::Renderer::setClearColor(0, 0, 0, 1);

    {
        ResourceManager::setExecutablePath(argv[0]);
        g_game->init();

        auto lastTime = std::chrono::high_resolution_clock::now();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(pWindow))
        {
            auto currentTime = std::chrono::high_resolution_clock::now();
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
            lastTime = currentTime;

            g_game->update(duration);

            /* Render here */
            RenderEngine::Renderer::clear();

            g_game->render();

            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();
        }

        ResourceManager::unloadAllReasources();
    }

    glfwTerminate();
    return 0;
}