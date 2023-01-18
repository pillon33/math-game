cmake_minimum_required(VERSION 3.10)
project(mathgame)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(JSONC REQUIRED json-c)


include_directories(${GTK3_INCLUDE_DIRS} ${JSONC_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS} ${JSONC_LIBRARY_DIRS})


add_executable(mathgame main.c)

target_link_libraries(mathgame ${GTK3_LIBRARIES} ${JSONC_LIBRARIES})

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})