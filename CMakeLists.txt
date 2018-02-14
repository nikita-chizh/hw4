cmake_minimum_required(VERSION 3.9)
MESSAGE(STATUS $ENV{TRAVIS_BUILD_NUMBER})
project(Print_IP)

set(CMAKE_CXX_STANDARD 14)

add_executable(print_ip main.cpp)
set(CMAKE_CXX_STANDARD 14)

set_target_properties(print_ip PROPERTIES
        CXX_STANDART 14
        CXX_STANDART_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set( CPACK_PACKAGE_FILE_NAME print_ip)
set(CPACK_PACKAGE_CONTACT nikita1993chizh@gmail.com)
include(CPack)
enable_testing()
