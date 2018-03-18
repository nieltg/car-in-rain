cmake_minimum_required (VERSION 3.7)
project (ogl)

set (CMAKE_CXX_STANDARD 11)

# OpenGL
find_package (OpenGL REQUIRED)
# SDL2pp
add_subdirectory (lib/libSDL2pp)

link_libraries (
  ${OPENGL_LIBRARIES}
  ${SDL2PP_LIBRARIES})

include_directories (
  ${OPENGL_INCLUDE_DIRS}
  ${SDL2PP_INCLUDE_DIRS})

add_subdirectory (src)
