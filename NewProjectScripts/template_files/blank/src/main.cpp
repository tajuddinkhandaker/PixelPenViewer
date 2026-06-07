#include "vendors.h"

// ============================================================
// Window Callback Functions
// ============================================================
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Adjust OpenGL viewport when window is resized
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Close window on ESC key press
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

// ============================================================
// Main Program
// ============================================================
int main()
{
    // ========================================================
    // 1. Initialize GLFW
    // ========================================================
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    // Configure GLFW window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    
    // ========================================================
    // 2. Create the Window
    // ========================================================
    // Signature: glfwCreateWindow(width, height, title, monitor, share)
    //   - monitor: NULL for windowed mode
    //   - share: NULL for independent context or another window to share resources
    const int WIDTH = 800;
    const int HEIGHT = 600;
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL GLFW Window", NULL, NULL);
    
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // Make the new OpenGL context current on this thread
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    // ========================================================
    // 3. Initialize GLAD
    // ========================================================
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    
    // ========================================================
    // 4. Configure viewport and callbacks
    // ========================================================
    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    // ========================================================
    // 5. Render loop
    // ========================================================
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // TODO: Add rendering code here
        
        glfwSwapBuffers(window);
    }
    
    // ========================================================
    // 6. Cleanup
    // ========================================================
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
