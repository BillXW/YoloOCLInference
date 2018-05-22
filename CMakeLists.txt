cmake_minimum_required(VERSION 2.8.4)
project(YoloOCLInference)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS  "-g -w -std=c++11")
FIND_PACKAGE(Boost 1.54 REQUIRED COMPONENTS filesystem system)
find_package(OpenCV REQUIRED)

include_directories("/usr/local/include" "src/OpenCL/include" "/usr/local/cuda-8.0/include" "/usr/include/cairo"
        "src/Utilities/include" "src/VideoProcessing/include" "${Boost_INCLUDE_DIRS}")

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.cl")
file(GLOB_RECURSE HEADERS "src/*.h" "src/*.hpp")

add_executable(YoloOCLInference
${SOURCES} )

target_link_libraries(YoloOCLInference
        /usr/lib/x86_64-linux-gnu/libcairo.so
        /usr/local/lib/x86_64-linux-gnu/libclblast.so
        /usr/lib/x86_64-linux-gnu/libOpenCL.so.1.0.0
        ${Boost_LIBRARIES}
        ${OpenCV_LIBS}
        )
