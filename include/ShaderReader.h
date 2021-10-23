#ifndef SHADER_READER_H
#define SHADER_READER_H

namespace PixelPen::Rendering::Shaders
{
    class ShaderReader
    {
        public:
            ShaderReader(const std::string& srcFileName);
            ~ShaderReader() = default;

            void Read();
            const GLchar* GetContent() const { return m_content.c_str(); }

        private:
            std::string m_srcFileName;
            std::string m_content;
    };
}

#endif // SHADER_READER_H