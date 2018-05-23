cmake_minimum_required(VERSION 2.8)
project(YoloOCLInference)
find_package(OpenCV REQUIRED)
FIND_PACKAGE(Boost 1.54 REQUIRED COMPONENTS filesystem system unit_test_framework)


file(GLOB_RECURSE SS "./src/*.cpp" "./src/*.cl")
file(GLOB_RECURSE HS "./src/*.h" "./src/*.hpp")


set(SOURCES "${SS}")
set(HEADERS "${HS}"  CACHE INTERNAL "header files")

set(INC_DIRS "/usr/local/include" "${CMAKE_CURRENT_LIST_DIR}/src/OpenCL/include" "/usr/local/cuda-8.0/include" "/usr/include/cairo" "${CMAKE_CURRENT_LIST_DIR}/src/Utilities/include" "${CMAKE_CURRENT_LIST_DIR}/src/VideoProcessing/include" "${Boost_INCLUDE_DIRS}" "${HEADERS}")

message(STATUS "${INC_DIRS}")


set(SHARED_OBJ   "${Boost_LIBRARIES}" "${OpenCV_LIBS}" "/usr/lib/x86_64-linux-gnu/libcairo.so" "/usr/local/lib/x86_64-linux-gnu/libclblast.so" "/usr/lib/x86_64-linux-gnu/libOpenCL.so.1.0.0")


add_subdirectory(src)
add_subdirectory(test)





