cmake_minimum_required(VERSION 3.7)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_subdirectory(
  "${PROJECT_SOURCE_DIR}/third_party/googletest"
  "${CMAKE_CURRENT_BINARY_DIR}/third_party/googletest"
)

macro(package_add_test TESTNAME)
  add_executable(${TESTNAME} ${ARGN})
  target_include_directories(
    ${TESTNAME}
    PRIVATE
    "${PROJECT_SOURCE_DIR}/test/mocks"
    "${PROJECT_SOURCE_DIR}/third_party/googletest/googletest/include"
    "${PROJECT_SOURCE_DIR}/third_party/googletest/googlemock/include"
  )

  target_link_libraries(
    ${TESTNAME}
    ThreadPool
    Threads::Threads
    gtest
    gmock
    gtest_main
  )

  set_target_properties(
    ${TESTNAME}
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
  )

  add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
endmacro()

package_add_test(
  ThreadPoolTests
  "src/ConcurrentQueueTest.cpp"
  "src/ThreadTaskTest.cpp"
  "src/ThreadWorkerTest.cpp"
  "src/FixedThreadPoolTest.cpp"
)

package_add_test(
  ThreadPoolFullTests
  "src/DefaultFixedThreadPool.cpp"
)