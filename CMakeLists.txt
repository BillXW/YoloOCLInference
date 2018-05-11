cmake_minimum_required(VERSION 2.8.4)
project(YoloOCLInference)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS  "-g -w -std=c++11")
FIND_PACKAGE(Boost 1.54 REQUIRED COMPONENTS filesystem system)
find_package(OpenCV REQUIRED)


#include_directories(3rdparty)
#include_directories(3rdparty/cairo)
#include_directories(3rdparty/cairo/include)
#include_directories(3rdparty/CLBlast)
#include_directories(3rdparty/CLBlast/include)


include_directories(/usr/local/include)
include_directories(src/OpenCL/include)
include_directories(/usr/local/cuda-8.0/include)
include_directories(/usr/include/cairo)
include_directories(src/Utilities/include)
include_directories(src/VideoProcessing/include)
include_directories(${Boost_INCLUDE_DIRS})


add_executable(YoloOCLInference

        /usr/local/include/clblast.h
        /usr/local/include/clblast_c.h
        /usr/local/include/clblast_half.h
        #/usr/local/include/clblast_netlib_c.h

        src/Kernels/DeepNNFP16.cl
        src/Kernels/DeepNNFP32.cl
        src/OpenCL/include/buffer.h
        src/OpenCL/include/cl_wrapper.hpp
        src/OpenCL/include/clutils.h
        src/OpenCL/include/helpers.h
        src/OpenCL/include/image2D.h
        src/OpenCL/include/iv_common.h
        src/OpenCL/include/kernel_launcher.h
        src/OpenCL/include/OCLManager.h
        src/OpenCL/include/oclUtils.h
        src/OpenCL/include/program.h
        src/OpenCL/include/sampler.h
        src/OpenCL/include/shrUtils.h
        src/OpenCL/buffer.cpp
        src/OpenCL/cl_wrapper.cpp
        src/OpenCL/clutils.cpp
        src/OpenCL/helpers.cpp
        src/OpenCL/image2D.cpp
        src/OpenCL/iv_common.cpp
        src/OpenCL/kernel_launcher.cpp
        src/OpenCL/OCLManager.cpp
        src/OpenCL/oclUtils.cpp
        src/OpenCL/program.cpp
        src/OpenCL/sampler.cpp
        src/OpenCL/shrUtils.cpp
        src/Utilities/include/GlobalDefines.h
        src/Utilities/include/InitUtils.h
        src/Utilities/InitUtils.cpp
        src/Utilities/NetIniFileOp.cpp
        src/VideoProcessing/include/YoloOCLDNN.h
        src/VideoProcessing/YoloOCLDNN.cpp
        src/YoloOCLMain.cpp
        Capture.jpg
        Capture.PNG
        frame_000006.jpg
        LICENSE
        README.md src/Utilities/include/NetIniFileOp.h)


target_link_libraries(YoloOCLInference
        /usr/lib/x86_64-linux-gnu/libcairo.so
        /usr/local/lib/x86_64-linux-gnu/libclblast.so
        #/usr/local/cuda-8.0/lib64/libOpenCL.so
        /usr/lib/x86_64-linux-gnu/libOpenCL.so.1.0.0
        ${Boost_LIBRARIES}
        ${OpenCV_LIBS}
        )


message(WARNING "OpenCV_LIBS is ${OpenCV_LIBS}")
message(WARNING "GTK_LIBRARIES is ${GTKMM_LIBRARY_DIRS}")