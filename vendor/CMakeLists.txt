# https://github.com/Dav1dde/glad/issues/174
# Also, https://cmake.org/cmake/help/v3.17/module/FetchContent.html

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Multi-Language Vulkan/GL/GLES/EGL/GLX/WGL Loader-Generator based on
# the official specs. http://glad.dav1d.de/
include(FetchContent)
FetchContent_Declare(
  vendor_glad

  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        v0.1.33)
  
# After the following call, the CMake targets defined by vendor_glad
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
  
FetchContent_Declare(
  vendor_glfw

  GIT_REPOSITORY https://github.com/glfw/glfw
  GIT_TAG        3.4)
  
# After the following call, the CMake targets defined by vendor_glfw
FetchContent_MakeAvailable(vendor_glfw)

FetchContent_GetProperties(vendor_glfw)

if(NOT vendor_glfw_POPULATED)
  FetchContent_Populate(vendor_glfw)

  add_subdirectory(
    ${vendor_glfw_SOURCE_DIR}
    ${vendor_glfw_BINARY_DIR}
    EXCLUDE_FROM_ALL)
endif()