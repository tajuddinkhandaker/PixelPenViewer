#ifndef RENDERER_H
#define RENDERER_H

// How to use glad directly from CMAKE
// https://github.com/Dav1dde/glad/issues/186
// Also, https://github.com/Dav1dde/glad/issues/174
#include <glad/glad.h>
// GLFW
#include <GLFW/glfw3.h>

namespace Rendering
{
    class Renderer
    {
    private:
        /* data */
    public:
        Renderer(/* args */);
        ~Renderer();

        virtual void Update(){
            BuildShaderProgram();
        }
        virtual void Render(){
            Draw();
        }

        void Clean()
        {    
            // optional: de-allocate all resources once they've outlived their purpose:
            // ------------------------------------------------------------------------
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
        }
        
    private: 
        void Draw(); 
        void BuildShaderProgram();
        void DrawTriangle();
        void DrawTriangle1();

        unsigned int VBO, VAO;
        int shaderProgram = 0;
    };
}

#endif // RENDERER_H