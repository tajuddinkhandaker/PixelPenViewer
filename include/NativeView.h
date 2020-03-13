#ifndef NATIVE_VIEW_H
#define NATIVE_VIEW_H

namespace PixelPen::Views
{
    class NativeView
    {
    public:
        NativeView();
        ~NativeView();

        bool Create(const std::string& name, uint32_t width, uint32_t height);

    private:
        void Initialize();
    };
}

#endif // NATIVE_VIEW_H