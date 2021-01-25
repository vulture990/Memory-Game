
PROJECT(MEMORY-GAME)
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
set(SRC_DIR ./src)
set(HEADERS_FOLDER include)
INCLUDE_DIRECTORIES(${SRC_DIR}/${HEADERS_FOLDER})
# set(SRC ./src/main.c ./src/menu.c )
set(SRCS
    ${SRC_DIR}/main.c
    ${SRC_DIR}/menu.c 
)
# Add an executable compiled from hello.c
ADD_EXECUTABLE(Match_Match_Up ${SRCS})

# Link the target to the GTK+ libraries
TARGET_LINK_LIBRARIES(Match_Match_Up ${GTK3_LIBRARIES} m)


