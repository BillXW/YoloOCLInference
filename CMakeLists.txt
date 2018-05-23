cmake_minimum_required(VERSION 2.8)

project(yolo_opencl)




file(GLOB_RECURSE SS "./src/*.cpp" "./src/*.cl")
file(GLOB_RECURSE HS "./src/*.h" "./src/*.hpp")

set(SOURCES "${SS}")
#set(SOURCES "${SS}"  CACHE INTERNAL "kk")
set(HEADERS "${HS}"  CACHE INTERNAL "header files")

add_subdirectory(src)
add_subdirectory(test)





