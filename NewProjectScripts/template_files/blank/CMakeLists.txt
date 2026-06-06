cmake_minimum_required(VERSION 3.10)
project({{PROJECT_NAME}})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

# ============================================================
# Fetch external dependencies
# ============================================================

include(FetchContent)

# GLFW
FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

# GLAD (for OpenGL function loading)
FetchContent_Declare(glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v0.1.36
)

# GLM (Math library)
FetchContent_Declare(glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw glad glm)

# ============================================================
# Main executable
# ============================================================

add_executable({{PROJECT_NAME}})

target_sources({{PROJECT_NAME}} PRIVATE
    src/main.cpp
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
