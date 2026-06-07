#include "vendors.h"
#include "ShaderReader.h"

// #define DEBUG

using namespace PixelPen::Rendering::Shaders;

/**
 * @brief Reads the shader file and update the content
 * 
 */
std::string ShaderReader::Read(const std::string& srcFileName) const
{
    const std::filesystem::path cwd = std::filesystem::current_path();
    #ifdef DEBUG
    std::cout << "[I] Current working directory: " << cwd.string() << std::endl;
    #endif
    const std::filesystem::path candidates[] = {
        cwd / "res" / srcFileName,
        cwd.parent_path() / "res" / srcFileName,
        cwd.parent_path().parent_path() / "res" / srcFileName,
        cwd / ".." / "res" / srcFileName
    };

    std::ifstream stream;
    for (const auto& path : candidates) {
        stream.open(path, std::ios::in);
        if (stream.is_open()) {
            #ifdef DEBUG
            std::cout << "Loaded shader from: " << path.string() << std::endl;
            #endif
            break;
        }
        stream.clear();
    }

    if (!stream.is_open()) {
        std::cerr << "ERROR: Could not open shader file '" << srcFileName << "'." << std::endl;
        std::cerr << "Tried paths:" << std::endl;
        for (const auto& path : candidates) {
            std::cerr << "  " << path.string() << std::endl;
        }
        return {};
    }

    std::string content;

    std::string line;
    while (!stream.eof() && std::getline(stream, line))
    {
        content += line + "\n";
    }
    content += "\0";

    stream.close();

    return content.c_str();
}