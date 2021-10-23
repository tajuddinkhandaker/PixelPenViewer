#ifndef RENDERER_H
#define RENDERER_H

namespace PixelPen::Rendering
{
    class Renderer
    {
    public:
        Renderer(/* args */);
        ~Renderer();

        virtual void Update() {
            BuildShaderProgram();
        }
        virtual void Render() {
            Draw();
        }

        void ClearColorBuffer();
        void SetViewport(int x, int y, size_t width, size_t height);
        
    private: 
        void Draw(); 
        void BuildShaderProgram();

        unsigned int VBO, VAO;
        int shaderProgram = 0;
    };
}

#endif // RENDERER_H