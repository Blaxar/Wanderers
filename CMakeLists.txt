#/*
#-----------------------------------------------------------------------------
#Filename:    CMakeLists.txt
#-----------------------------------------------------------------------------
#*/
cmake_minimum_required(VERSION 2.6)
 
project(Wanderers)
 
set(CMAKE_DEBUG_POSTFIX "_d")
 
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/bin")

#Find all packages

find_package(OpenGL)

add_library(gl3w
            src/GL/gl3w.c
)

if(WIN32)
set(GL_LIBS glfw3 debug glfw3_d ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})
elseif (UNIX)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
set(GL_LIBS gl3w glfw X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL rt dl)
else()
set(GL_LIBS gl3w glfw)
endif()

set(DEFAULT_SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(DEFAULT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(DEFAULT_LINK_DIR ${CMAKE_SOURCE_DIR}/lib)
set(DEFAULT_BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

#Define all the include directories
include_directories(
    ${DEFAULT_INCLUDE_DIR}
)

add_definitions(-std=c++11 -O3)

link_directories(${DEFAULT_LINK_DIR})
add_subdirectory(src)

