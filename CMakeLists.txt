cmake_minimum_required(VERSION 3.17)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
endif()

project(glRendering VERSION 1.0.1 LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
 
# However, the file(GLOB...) allows for wildcard additions:
# file(GLOB SOURCES "src/*.cpp")
#
# https://stackoverflow.com/questions/13703647/how-to-properly-add-include-directories-with-cmake

include_directories(include)
file(GLOB_RECURSE SOURCES "include/*.h" "src/*.cpp")

# For exporting as library
# https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/
 
add_executable(glRendering src/glmain.cpp ${SOURCES}) 

find_package(OpenGL REQUIRED)

if(TARGET OpenGL::GL)
  message(STATUS "OpenGL::GL target exists ✔")
else()
  message(FATAL_ERROR "OpenGL::GL target missing ❌")
endif()

# https://github.com/Dav1dde/glad/issues/174
add_subdirectory(vendor)
target_link_libraries(glRendering
  PUBLIC
  glad

  PRIVATE
  ${CMAKE_DL_LIBS})

# Uncomment if you find this package System-installed GLFW Installed via vcpkg / apt / brew:
# When we fetch GLFW using FetchContent_Declare() the following doesn't require
# find_package(glfw3 CONFIG REQUIRED)

# to check memory leaks
target_compile_definitions(glRendering PRIVATE
    $<$<CONFIG:Debug>:_CRTDBG_MAP_ALLOC>
)

target_link_libraries(glRendering PRIVATE glfw)