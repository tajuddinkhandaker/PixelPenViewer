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

        virtual bool Create(const std::string& name, int width, int height) override;
        virtual void show() override;

    private:
        void OnFrameRender(const GLFWwindow* const window, PixelPen::Rendering::Renderer* const renderer);
        void Initialize();

    private:
        GLFWwindow* window = nullptr;
        GLFWmonitor* monitor = nullptr;
        GLFWwindow* share = nullptr;
        PixelPen::Rendering::Renderer* renderer = nullptr;
    };
}

#endif // NATIVE_VIEW_H