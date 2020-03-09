#ifndef RENDERER_H
#define RENDERER_H

namespace Rendering
{
    class Renderer
    {
    private:
        /* data */
    public:
        Renderer(/* args */);
        ~Renderer();

        virtual void Update(){}
        virtual void Render(){}
    };
}

#endif // RENDERER_H