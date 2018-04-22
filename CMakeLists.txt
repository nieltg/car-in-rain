cmake_minimum_required (VERSION 3.1)
project (ogl)

set (CMAKE_CXX_STANDARD 11)

# Dependencies
find_package (GLUT REQUIRED)
find_package (OpenGL REQUIRED)
find_package (GLEW REQUIRED)
find_package (GLM REQUIRED)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK3 REQUIRED gtk+-3.0)

link_libraries (
  ${GLUT_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${GLM_LIBRARIES}
  ${GTK3_LIBRARIES}
  -lpthread
)

link_directories (
  ${GTK3_LIBRARY_DIRS}
)

include_directories (
  ${GLUT_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
  ${GLM_INCLUDE_DIRS}
  ${GTK3_INCLUDE_DIRS}
)

ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

add_subdirectory (src)
