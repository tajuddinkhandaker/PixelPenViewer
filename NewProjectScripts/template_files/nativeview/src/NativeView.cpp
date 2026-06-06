#include "NativeView.h"
#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace PixelPen::Views
{
    void resize_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }

    NativeView::NativeView()
        : window(nullptr), monitor(nullptr), share(nullptr), renderer(nullptr)
    {
    }

    NativeView::~NativeView()
    {
        if (renderer) {
            delete renderer;
        }
        if (window) {
            glfwDestroyWindow(window);
        }
        glfwTerminate();
    }

    bool NativeView::Create(const std::string& name, int width, int height)
    {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        monitor = glfwGetPrimaryMonitor();
        window = glfwCreateWindow(width, height, name.c_str(), nullptr, share);

        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return false;
        }

        glViewport(0, 0, width, height);
        glfwSetFramebufferSizeCallback(window, resize_callback);
        glfwSetKeyCallback(window, key_callback);

        renderer = new PixelPen::Rendering::Renderer();
        if (!renderer->Initialize()) {
            std::cerr << "Failed to initialize renderer" << std::endl;
            return false;
        }

        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
        return true;
    }

    void NativeView::show()
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            OnFrameRender(window, renderer);
            glfwSwapBuffers(window);
        }
    }

    void NativeView::OnFrameRender(const GLFWwindow* const window, PixelPen::Rendering::Renderer* const renderer)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderer->Render();
    }

    void NativeView::Initialize() const
    {
    }
}
