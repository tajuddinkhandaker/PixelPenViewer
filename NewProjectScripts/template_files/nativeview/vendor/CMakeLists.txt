# https://github.com/Dav1dde/glad/issues/174
# Also, https://cmake.org/cmake/help/v3.17/module/FetchContent.html

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

include(FetchContent)

# GLFW - Windowing library
FetchContent_Declare(
    vendor_glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(vendor_glfw)
FetchContent_GetProperties(vendor_glfw)
if(NOT vendor_glfw_POPULATED)
  FetchContent_Populate(vendor_glfw)
  add_subdirectory(
    ${vendor_glfw_SOURCE_DIR}
    ${vendor_glfw_BINARY_DIR}
    EXCLUDE_FROM_ALL)
endif()

# GLAD - OpenGL function loader
FetchContent_Declare(
    vendor_glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG        v0.1.36
)
FetchContent_MakeAvailable(vendor_glad)
FetchContent_GetProperties(vendor_glad)
if(NOT vendor_glad_POPULATED)
  FetchContent_Populate(vendor_glad)
  set(GLAD_INSTALL ON)
  add_subdirectory(
    ${vendor_glad_SOURCE_DIR}
    ${vendor_glad_BINARY_DIR}
    EXCLUDE_FROM_ALL)
endif()

# GLM - Math library
FetchContent_Declare(
    vendor_glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1
)
FetchContent_MakeAvailable(vendor_glm)
FetchContent_GetProperties(vendor_glm)
if(NOT vendor_glm_POPULATED)
  FetchContent_Populate(vendor_glm)
  add_subdirectory(
    ${vendor_glm_SOURCE_DIR}
    ${vendor_glm_BINARY_DIR}
    EXCLUDE_FROM_ALL)
endif()
set(vendor_glm_SOURCE_DIR ${vendor_glm_SOURCE_DIR} PARENT_SCOPE)
