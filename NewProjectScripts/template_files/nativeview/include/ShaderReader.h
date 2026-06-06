#ifndef SHADER_READER_H
#define SHADER_READER_H

#include <string>

namespace PixelPen::Rendering
{
    class ShaderReader
    {
    public:
        ShaderReader() = default;
        ~ShaderReader() = default;
        std::string Read(const std::string& filepath);
    };
}

#endif // SHADER_READER_H
