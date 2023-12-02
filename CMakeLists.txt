cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
project(CTC)

set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

option(CTC_BUILD_TESTS "Build the test programs" ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

add_subdirectory(src)

if(CTC_BUILD_TESTS)
  add_subdirectory(tests)
endif()