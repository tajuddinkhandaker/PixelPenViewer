#ifndef IVIEW_H
#define IVIEW_H

#include <string>

namespace PixelPen::Views
{
    class IView
    {
    public:
        virtual ~IView() = default;
        virtual bool Create(const std::string& name, int width, int height) = 0;
        virtual void show() = 0;
    };
}

#endif // IVIEW_H
