cmake_minimum_required (VERSION 3.1)
project (ogl)

set (CMAKE_CXX_STANDARD 11)

# SDL2
find_package (SDL2 REQUIRED)
# OpenGL
find_package (OpenGL REQUIRED)

link_libraries (
  ${SDL2_LIBRARIES}
  ${OPENGL_LIBRARIES})

include_directories (
  ${SDL2_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS})

add_subdirectory (src)
