#include "vendors.h"
#include "ShaderReader.h"
#include <filesystem>
#include <iostream>

// #define DEBUG

using namespace PixelPen::Rendering::Shaders;

namespace
{
    /**
     * @brief Get the Current Working Dir object
     * 
     * @return std::string 
     */
    std::string GetCurrentWorkingDir( void )
    {
        char buff[FILENAME_MAX];
        GetCurrentDir( buff, FILENAME_MAX );
        std::string current_working_dir(buff);
        return current_working_dir;
    }
}

ShaderReader::ShaderReader(const std::string& srcFileName)
  : m_srcFileName(srcFileName)
{}

/**
 * @brief Reads the shader file and update the content
 * 
 */
void ShaderReader::Read()
{
    #ifdef DEBUG
    std::cout << "[I] Current working directory: " << GetCurrentWorkingDir() << std::endl;
    #endif

    const std::filesystem::path cwd = std::filesystem::current_path();
    const std::filesystem::path candidates[] = {
        cwd / "res" / m_srcFileName,
        cwd.parent_path() / "res" / m_srcFileName,
        cwd.parent_path().parent_path() / "res" / m_srcFileName,
        cwd / ".." / "res" / m_srcFileName
    };

    std::ifstream stream;
    for (const auto& path : candidates)
    {
        stream.open(path, std::ios::in);
        if (stream.is_open())
        {
            #ifdef DEBUG
            std::cout << "Loaded shader from: " << path.string() << std::endl;
            #endif
            break;
        }
        stream.clear();
    }

    if (!stream.is_open())
    {
        std::cerr << "ERROR: Could not open shader file '" << m_srcFileName << "'." << std::endl;
        std::cerr << "Tried paths:" << std::endl;
        for (const auto& path : candidates)
        {
            std::cerr << "  " << path.string() << std::endl;
        }
        return;
    }

    m_content.clear();

    std::string line;
    while (!stream.eof() && std::getline(stream, line))
    {
        m_content += line + "\n";
    }
    m_content += "\0";

    stream.close();
}