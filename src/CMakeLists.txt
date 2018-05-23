

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS  "-g -w -std=c++11")

find_package(OpenCV REQUIRED)



include_directories(${INC_DIRS})

add_executable(YoloOCLInference ${SOURCES})

target_link_libraries( YoloOCLInference ${SHARED_OBJ} )
