cmake_minimum_required(VERSION 3.7)

project(ThreadPool)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(ENABLE_TESTING "Build the tests" OFF)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

file(GLOB LIB_SOURCE_FILES "src/*.cpp")

add_library(ThreadPool STATIC ${LIB_SOURCE_FILES})

target_include_directories(
  ThreadPool
  PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>"
)

target_link_libraries(
  ThreadPool
  Threads::Threads
)

set_target_properties(
  ThreadPool
  PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
)

target_compile_options(
  ThreadPool
  PUBLIC
  -Wall
  -Werror
  -Wextra
  -Wpedantic
  -pedantic-errors
)

if(ENABLE_TESTING)
  enable_testing()
  add_subdirectory(test)
  add_custom_target(
    check
    COMMAND ${CMAKE_CTEST_COMMAND}
    --force-new-ctest-process
    --verbose)
endif()

export(TARGETS ThreadPool NAMESPACE ThreadPool:: FILE ThreadPool-exports.cmake)