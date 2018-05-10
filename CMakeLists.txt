cmake_minimum_required (VERSION 3.1)
project (ogl)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Dependencies
find_package (SDL2 REQUIRED)
find_package (SDL2_image REQUIRED)
find_package (OpenGL REQUIRED)
find_package (GLEW REQUIRED)
find_package (GLM REQUIRED)

link_libraries (
  ${SDL2_LIBRARY}
  ${SDL2_IMAGE_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${GLM_LIBRARIES})

include_directories (
  ${SDL2_INCLUDE_DIRS}
  ${SDL2_IMAGE_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS}
  ${GLEW_LIBRARIES}
  ${GLM_LIBRARIES})

add_subdirectory (src)
