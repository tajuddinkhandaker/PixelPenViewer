cmake_minimum_required(VERSION 3.10)
project({{PROJECT_NAME}})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

include(FetchContent)

FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

FetchContent_Declare(glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v0.1.36
)

FetchContent_Declare(glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw glad glm)

add_executable({{PROJECT_NAME}})

target_sources({{PROJECT_NAME}} PRIVATE
    src/main.cpp
    src/NativeView.cpp
    src/Renderer.cpp
    src/ShaderReader.cpp
)

target_include_directories({{PROJECT_NAME}} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${glm_SOURCE_DIR}
)

target_link_libraries({{PROJECT_NAME}} PRIVATE
    glfw
    glad
)

if(MSVC)
    target_compile_options({{PROJECT_NAME}} PRIVATE /W4)
else()
    target_compile_options({{PROJECT_NAME}} PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_custom_command(TARGET {{PROJECT_NAME}} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/res"
    "$<CONFIG_GENERATOR:$<CONFIG>:./res>"
)
