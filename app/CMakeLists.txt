cmake_minimum_required (VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Dependencies
find_package (SDL2 REQUIRED)
find_package (SDL2_image REQUIRED)
find_package (OpenGL REQUIRED)
find_package (GLM REQUIRED)
find_package (glbinding REQUIRED)
find_package (globjects REQUIRED)

link_libraries (
  ${SDL2_LIBRARY}
  ${SDL2_IMAGE_LIBRARIES}
  ${GLM_LIBRARIES}
  ${OpenGL_LIBRARIES}
  glbinding::glbinding
  globjects::globjects
)

include_directories (
  ${SDL2_INCLUDE_DIRS}
  ${SDL2_IMAGE_INCLUDE_DIRS}
  ${OpenGL_INCLUDE_DIRS}
  ${GLM_INCLUDE_DIRS}
)

add_subdirectory (src)
