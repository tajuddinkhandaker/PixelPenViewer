#include "ShaderReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace PixelPen::Rendering
{
    std::string ShaderReader::Read(const std::string& filepath)
    {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Failed to open shader file: " << filepath << std::endl;
            return "";
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
}
