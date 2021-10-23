#ifndef IVIEW_H
#define IVIEW_H

namespace PixelPen::Views
{
    class IView
    {
    public:
        IView() = default;
        virtual ~IView() = default;
        DEF_NO_COPY(IView);

        virtual bool Create(const std::string& name, uint32_t width, uint32_t height) = 0;
        virtual void show() = 0;
    };
}

#endif // IVIEW_H