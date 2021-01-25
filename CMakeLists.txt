
PROJECT(project2)
# Set the minimum version of cmake required to build this project
CMAKE_MINIMUM_REQUIRED(VERSION 3.7)

# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

# Add other flags to the compiler
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm -O0 -Wall -Werror -fdump-rtl-expand")
set(HEADERS_FOLDER include)
include_directories(${HEADERS_FOLDER})

set(SRC  extra.c main.c spices.c)
# Add an executable compiled from hello.c
ADD_EXECUTABLE(main ${SRC})

# Link the target to the GTK+ libraries
TARGET_LINK_LIBRARIES(main ${GTK3_LIBRARIES})


