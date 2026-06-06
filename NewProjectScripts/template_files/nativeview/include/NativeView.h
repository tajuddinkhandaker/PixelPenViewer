#ifndef NATIVE_VIEW_H
#define NATIVE_VIEW_H

#include "IView.h"
#include <string>

struct GLFWwindow;
struct GLFWmonitor;

namespace PixelPen::Rendering
{
    class Renderer;
}

namespace PixelPen::Views
{
    class NativeView : public IView
    {
    public:
        NativeView();
        virtual ~NativeView() override;
        virtual bool Create(const std::string& name, int width, int height) override;
        virtual void show() override;

    private:
        void OnFrameRender(const GLFWwindow* const window, PixelPen::Rendering::Renderer* const renderer);
        void Initialize() const;

    private:
        GLFWwindow* window = nullptr;
        GLFWmonitor* monitor = nullptr;
        GLFWwindow* share = nullptr;
        PixelPen::Rendering::Renderer* renderer = nullptr;
    };
}

#endif // NATIVE_VIEW_H
