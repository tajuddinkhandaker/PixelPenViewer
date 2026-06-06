#include "Renderer.h"
#include "ShaderReader.h"
#include <glad/glad.h>
#include <iostream>

namespace PixelPen::Rendering
{
    Renderer::Renderer()
        : vao(0), vbo(0), shaderProgram(0)
    {
    }

    Renderer::~Renderer()
    {
        if (vao) glDeleteVertexArrays(1, &vao);
        if (vbo) glDeleteBuffers(1, &vbo);
        if (shaderProgram) glDeleteProgram(shaderProgram);
    }

    bool Renderer::Initialize()
    {
        ShaderReader shaderReader;
        std::string vertexSource = shaderReader.Read("res/BasicVS.glsl");
        std::string fragmentSource = shaderReader.Read("res/BasicFS.glsl");

        if (vertexSource.empty() || fragmentSource.empty()) {
            std::cerr << "Failed to load shaders" << std::endl;
            return false;
        }

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char* vSrc = vertexSource.c_str();
        glShaderSource(vertexShader, 1, &vSrc, nullptr);
        glCompileShader(vertexShader);

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fSrc = fragmentSource.c_str();
        glShaderSource(fragmentShader, 1, &fSrc, nullptr);
        glCompileShader(fragmentShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

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

    void Renderer::Render()
    {
        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}
