
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS  "-g -w -std=c++11")


include_directories(${INC_DIRS})

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

set(testsrc)

#Remove YoloOCLmain.cpp to forbid main function conflict
FOREACH(src ${SOURCES})
    if (NOT (src MATCHES "YoloOCLMain.cpp"))
        set(testsrc ${testsrc} ${src})
    endif ()
endforeach()

add_executable(test testImg2Array7x7.cpp ${testsrc} )
target_link_libraries(test  ${SHARED_OBJ})

enable_testing()
add_test(Mytest test)


