#include "vendors.h"
#include "ShaderReader.h"

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
    std::cout << "Current working directory: " << GetCurrentWorkingDir() << std::endl;
    #endif
    std::ifstream stream(GetCurrentWorkingDir() + "/../res/" + m_srcFileName);

    if (stream.is_open())
    {
        m_content.clear();

        std::string line;
        while (!stream.eof())
        {
            std::getline(stream, line);
            m_content += line + "\n";
        }
        m_content += "\0";

        stream.close();
    }
}