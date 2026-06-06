#ifndef RENDERER_H
#define RENDERER_H

namespace PixelPen::Rendering
{
    class Renderer
    {
    public:
        Renderer();
        ~Renderer();
        bool Initialize();
        void Render();

    private:
        unsigned int vao = 0;
        unsigned int vbo = 0;
        unsigned int shaderProgram = 0;
    };
}

#endif // RENDERER_H
