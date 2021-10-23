#ifndef NATIVE_VIEW_H
#define NATIVE_VIEW_H

namespace PixelPen::Rendering
{
    class Renderer;
}

namespace PixelPen::Views
{
    class NativeView
        : public PixelPen::Views::IView
    {
    public:
        NativeView();
        virtual ~NativeView() override;

        virtual bool Create(const std::string& name, uint32_t width, uint32_t height) override;
        virtual void show() override;

    private:
        void OnFrameRender(const GLFWwindow* const window, PixelPen::Rendering::Renderer* const renderer);
        void Initialize();

    private:
        GLFWwindow* window = nullptr;
        PixelPen::Rendering::Renderer* renderer = nullptr;
    };
}

#endif // NATIVE_VIEW_H