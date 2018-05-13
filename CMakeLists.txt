cmake_minimum_required (VERSION 3.1)

include (${CMAKE_ROOT}/Modules/ExternalProject.cmake)

ExternalProject_Add (
  glbinding

  GIT_REPOSITORY "https://github.com/cginternals/glbinding"
  GIT_TAG "v2.1"

  CMAKE_ARGS
  "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/vendor"
  -DBUILD_SHARED_LIBS:BOOL=OFF
  -DOPTION_BUILD_EXAMPLES:BOOL=OFF
  -DOPTION_BUILD_DOCS:BOOL=OFF
  -DOPTION_BUILD_TESTS:BOOL=OFF
)

ExternalProject_Add (
  globjects

  DEPENDS glbinding
  GIT_REPOSITORY "https://github.com/cginternals/globjects"
  GIT_TAG "v2.0"

  CMAKE_ARGS
  "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/vendor"
  -DBUILD_SHARED_LIBS:BOOL=OFF
  -DOPTION_BUILD_EXAMPLES:BOOL=OFF
  -DOPTION_BUILD_DOCS:BOOL=OFF
  -DOPTION_BUILD_TESTS:BOOL=OFF
)

ExternalProject_Add (
  app

  DEPENDS globjects
  SOURCE_DIR "${CMAKE_SOURCE_DIR}/app"

  CMAKE_ARGS
  "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/vendor"

  INSTALL_COMMAND ""
)
