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

        virtual bool Create(const std::string& name, int width, int height) = 0;
        virtual void show() = 0;
    };
}

#endif // IVIEW_H