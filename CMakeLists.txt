cmake_minimum_required(VERSION 3.29)
project(LogOutMan C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

add_executable(LogOutMan main.c
        json-handler.h
        json-handler.c
        cJSON.c)

target_link_libraries(LogOutMan ${GTK3_LIBRARIES})

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

# Add other flags to the compiler
add_definitions(${GTK3_CFLAGS_OTHER})
# Add an executable compiled from hello.c
# Link the target to the GTK+ libraries



