#include "vendors.h"
#include "Renderer.h"
#include "ShaderReader.h"

using namespace PixelPen::Rendering;
using namespace Shaders;

namespace
{
    const char *vertexShaderSource = "#version 330 core\n"
                                    "layout (location = 0) in vec3 aPos;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                    "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   FragColor = vec4(1.0f, 0.0f, 0.0f, 0.5f);\n"
                                    "}\n\0";

    // vertex data arrays (private to this translation unit)
    static float twoTriangleVertices[] = {
        // first triangle
        -0.9f, -0.5f, 0.0f, // left
        -0.0f, -0.5f, 0.0f, // right
        -0.45f, 0.5f, 0.0f, // top
        // second triangle
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top
    };

    // triangle vertices centered in the viewport (normalized device coordinates)
    static float singleTriangleVertices[] = {
        -0.5f, -0.4f, 0.0f,
         0.5f, -0.4f, 0.0f,
         0.0f,  0.8f, 0.0f
    };
}

/**
 * @brief Construct a new of this object
 * 
 */
Renderer::Renderer(/* args */)
    : VAO(0), VBO(0), shaderProgram(0) 
{
}

/**
 * @brief Destroy this object
 * 
 */
Renderer::~Renderer()
{
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (shaderProgram) glDeleteProgram(shaderProgram);
}

/**
 * @brief Build the shader program
 * 
 *  //https://learnopengl.com/Getting-started/Hello-Triangle
 */
bool Renderer::BuildShaderProgram()
{
    // http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-10-transparency/
    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // BasicRotateVS.glsl -> apply rotation transformation to the vertex shader
    // BasicVS.glsl -> no transformation applied to the vertex shader
    
    ShaderReader shaderReader;
    std::string vertexSource = shaderReader.Read("BasicRotateVS.glsl");
    std::string fragmentSource = shaderReader.Read("BasicFS.glsl");

    if (vertexSource.empty() || fragmentSource.empty()) {
        std::cerr << "Failed to load shaders" << std::endl;
        return false;
    }

    // std::cout << vertexShaderSrc << std::endl;

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // load shader source code from text memory
    // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    // load shader source code from file
    const char* vSrc = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vSrc, nullptr);
    glCompileShader(vertexShader);

    // check for shader compile errors
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        return false;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // load shader source code from file
    const char* fSrc = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fSrc, nullptr); 
    
    // load shader source code from text memory
    // glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(fragmentShader);

    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        return false;
    }
    // link shaders
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
                  
        if (shaderProgram) glDeleteProgram(shaderProgram);
        return false;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    transformLoc = glGetUniformLocation(shaderProgram, "uTransform");
    if (transformLoc < 0) {
        std::cerr << "WARNING: Transform uniform 'uTransform' not found." << std::endl;
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(singleTriangleVertices), singleTriangleVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    return true;
}

/**
 * @brief Draw the models
 * 
 */
void Renderer::Draw()
{
    // draw our first triangle
    glUseProgram(shaderProgram);

    // update rotation transform and set uniform
    UpdateRotationToCenterTransformUniform(transformLoc);
    
    glBindVertexArray(VAO);           // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 6); // set the count to 6 since we're drawing 6 vertices now (2 triangles); not 3!

    // glBindVertexArray(0); // no need to unbind it every time
}

/**
 * @brief Clear renderer's color buffer
 * 
 */
void Renderer::ClearColorBuffer() const
{
    // Clear the colorbuffer
    glClearColor(0.5f, 0.1f, 0.5f, 1.0f);

    // glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * @brief Sets window viewport for target view rendering
 * 
 * @param x 
 * @param y 
 * @param width 
 * @param height 
 */
void Renderer::SetViewport(int x, int y, size_t width, size_t height) const
{
    // Define the viewport dimensions
    glViewport(x, y, width, height);
}

void Renderer::UpdateRotationToCenterTransformUniform(GLint transformLoc)
{
    float angle = static_cast<float>(glfwGetTime()); // rotate over time
    float c = cos(angle);
    float s = sin(angle);

    // compute triangle centroid
    float cx = (singleTriangleVertices[0] + singleTriangleVertices[3] + singleTriangleVertices[6]) / 3.0f;
    float cy = (singleTriangleVertices[1] + singleTriangleVertices[4] + singleTriangleVertices[7]) / 3.0f;
    float cz = (singleTriangleVertices[2] + singleTriangleVertices[5] + singleTriangleVertices[8]) / 3.0f;

    // rotate around Y axis about the centroid
    float tx = cx - (c * cx - s * cz);
    float ty = 0.0f; // Y is unchanged by Y-axis rotation
    float tz = cz - (s * cx + c * cz);

    float transformRotationToCenter[] = {
        c, 0.0f, -s, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        s, 0.0f,  c, 0.0f,
        tx, ty, tz, 1.0f
    };

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transformRotationToCenter);
}

void Renderer::UpdateRotationToEdgeTransformUniform(GLint transformLoc)
{
    float angle = static_cast<float>(glfwGetTime()); // rotate over time
    float c = cos(angle);
    float s = sin(angle);

    float transformRotationToEdge[] = {
        c, 0.0f, -s, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        s, 0.0f,  c, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transformRotationToEdge);
}