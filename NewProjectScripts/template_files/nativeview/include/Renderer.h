#ifndef RENDERER_H
#define RENDERER_H

namespace PixelPen::Rendering
{
    class Renderer
    {
    public:
        Renderer() = default;
        ~Renderer();

        /**
         * @brief Initialize OpenGL shader program and mesh resources.
         *
         * Loads shader source from disk, compiles shaders, links the program,
         * and sets up the vertex array and buffer objects.
         *
         * @return true if initialization succeeded, false otherwise.
         */
        bool Initialize();

        /**
         * @brief Clear the color and depth buffers to a gray background.
         *
         * This method does not modify renderer-owned resources, it only updates
         * OpenGL framebuffer state.
         */
        void ClearColorBuffer() const;

        /**
         * @brief Render the current mesh using the active shader program.
         *
         * The render step assumes the framebuffer has already been cleared.
         */
        void Render() const;

    private:
        unsigned int vao = 0;
        unsigned int vbo = 0;
        unsigned int shaderProgram = 0;
        int transformLoc = -1;
    };
}

#endif // RENDERER_H
