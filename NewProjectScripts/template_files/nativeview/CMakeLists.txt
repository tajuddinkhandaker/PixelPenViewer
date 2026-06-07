cmake_minimum_required(VERSION 3.10)
project({{PROJECT_NAME}} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

# ============================================================
# Include external dependencies via vendor subdirectory
# ============================================================

add_subdirectory(vendor)

find_package(OpenGL REQUIRED)

if(TARGET OpenGL::GL)
  message(STATUS "OpenGL::GL target exists ✔")
else()
  message(FATAL_ERROR "OpenGL::GL target missing ❌")
endif()

# ============================================================
# Main executable
# ============================================================

add_executable({{PROJECT_NAME}})

target_sources({{PROJECT_NAME}} PRIVATE
    src/main.cpp
    src/NativeView.cpp
    src/Renderer.cpp
    src/ShaderReader.cpp
)

target_include_directories({{PROJECT_NAME}} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${vendor_glm_SOURCE_DIR}
)

target_link_libraries({{PROJECT_NAME}} PRIVATE
    glfw
    glad
)

target_compile_definitions({{PROJECT_NAME}} PRIVATE
    $<$<CONFIG:Debug>:_CRTDBG_MAP_ALLOC>
)

if(MSVC)
    target_compile_options({{PROJECT_NAME}} PRIVATE /W4)
else()
    target_compile_options({{PROJECT_NAME}} PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_custom_command(TARGET {{PROJECT_NAME}} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/res"
    "$<TARGET_FILE_DIR:{{PROJECT_NAME}}>/res"
)
