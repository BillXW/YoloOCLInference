cmake_minimum_required(VERSION 2.8)

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
enable_testing()
add_executable(test testImg2Array7x7.cpp)

target_link_libraries(test ${Boost_LIBRARIES})

add_test(Mytest test)