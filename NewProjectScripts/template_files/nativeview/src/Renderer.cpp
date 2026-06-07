#include "vendors.h"
#include "Renderer.h"
#include "ShaderReader.h"

using namespace PixelPen::Rendering;
using namespace Shaders;

/**
 * @brief Construct a new of this object
 * 
 */
Renderer::~Renderer()
{
    if (vao) glDeleteVertexArrays(1, &vao);
    if (vbo) glDeleteBuffers(1, &vbo);
    if (shaderProgram) glDeleteProgram(shaderProgram);
}

/**
 * @brief Initialize OpenGL shader program and mesh resources.
 * 
 * Loads shader source from disk, compiles shaders, links the program,
 * and sets up the vertex array and buffer objects.
 * 
 * @return true if initialization succeeded, false otherwise.
 */
bool Renderer::Initialize()
{
    ShaderReader shaderReader;
    std::string vertexSource = shaderReader.Read("BasicVS.glsl");
    std::string fragmentSource = shaderReader.Read("BasicFS.glsl");

    if (vertexSource.empty() || fragmentSource.empty()) {
        std::cerr << "Failed to load shaders" << std::endl;
        return false;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vSrc = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vSrc, nullptr);
    glCompileShader(vertexShader);

    int success = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                    << infoLog << std::endl;
        glDeleteShader(vertexShader);
        return false;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fSrc = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fSrc, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                    << infoLog << std::endl;
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                    << infoLog << std::endl;
        glDeleteProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }

    transformLoc = glGetUniformLocation(shaderProgram, "uTransform");
    if (transformLoc < 0) {
        std::cerr << "WARNING: Transform uniform 'uTransform' not found." << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return true;
}

/**
 * @brief Clear the color and depth buffers to a gray background.
 * 
 * This method does not modify renderer-owned resources, it only updates
 * OpenGL framebuffer state.
 */
void Renderer::ClearColorBuffer() const
{
    // Set the background to a neutral gray and clear both color and depth
    // buffers before rendering begins.
    glClearColor(0.18f, 0.18f, 0.18f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * @brief Render the current mesh using the active shader program.
 * 
 * The render step assumes the framebuffer has already been cleared.
 */
void Renderer::Render() const
{
    const float angle = static_cast<float>(glfwGetTime());
    const float c = std::cos(angle);
    const float s = std::sin(angle);

    const float transform[] = {
        c, 0.0f, -s, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        s, 0.0f,  c, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    if (transformLoc >= 0) {
        glUseProgram(shaderProgram);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transform);
    }

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
