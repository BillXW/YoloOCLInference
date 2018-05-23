
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS  "-g -w -std=c++11")


include_directories(${INC_DIRS})

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)


add_executable(test testImg2Array7x7.cpp )
target_link_libraries(test  ${SHARED_OBJ})


enable_testing()
add_test(Mytest test)