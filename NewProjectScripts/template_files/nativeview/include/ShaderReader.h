#ifndef SHADER_READER_H
#define SHADER_READER_H

namespace PixelPen::Rendering::Shaders
{
    class ShaderReader
    {
        public:
            ShaderReader() = default;
            ~ShaderReader() = default;

            std::string Read(const std::string& srcFileName) const;
    };
}

#endif // SHADER_READER_H