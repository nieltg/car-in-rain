cmake_minimum_required (VERSION 3.1)
project (ogl)

set (CMAKE_CXX_STANDARD 11)

# Dependencies
find_package (GLUT REQUIRED)
find_package (OpenGL REQUIRED)
find_package (GLEW REQUIRED)
find_package (GLM REQUIRED)

link_libraries (
  ${GLUT_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${GLM_LIBRARIES})

include_directories (
  ${GLUT_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS}
  ${GLEW_LIBRARIES}
  ${GLM_LIBRARIES})

add_subdirectory (src)
