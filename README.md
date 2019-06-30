# C++ thread pool library

## Description

C++ thread pool library implementation.

## Cloning repository

```bash
git clone --recursive https://github.com/rsitko92/thread-pool.git
```

## Prerequisites

### Prerequisites for running thread pool unit tests

- with using Docker:
  - [Docker](https://www.docker.com)

- without using Docker:
  - [GCC with C++17 standard support](https://gcc.gnu.org)
  - [CMake >= 3.7](http://cmake.org)
  - [Git](https://git-scm.com)
  - pthread library

### Prerequisites for using thread pool in project with CMake

- [GCC with C++17 standard support](https://gcc.gnu.org)
- [CMake >= 3.7](http://cmake.org)
- [Git](https://git-scm.com)
- pthread library

## Running unit tests

### Running unit tests with using Docker

Being in root directory of project run in terminal:

```bash
sudo test/buildAndRunTestsDocker.sh
```

### Running unit tests without using Docker

Being in root directory of project run in terminal:

```bash
test/buildAndRunTests.sh
```

## Using thread pool library in project with CMake

1. Add thread pool project using ExternalProject_Add function in CMakeLists.txt file.
1. Link `libThreadPool.a` static library to project target in CMakeLists.txt file.
1. Include `DefaultFixedThreadPool.hpp` header file from `inc` directory in header/source file:

    ```cpp
    #include "DefaultFixedThreadPool.hpp"
    ```

1. Create thread pool instance:

    ```cpp
    auto pThreadPool = thread_pool::DefaultFixedThreadPool::create();
    ```

1. Enqueue task in thread pool:

    ```cpp
    auto exampleTask = [](int x)
      {std::this_thread::sleep_for(std::chrono::seconds(2));
      std::cout << "Hello from worker thread" << std::endl;
      std::cout << "Passed argument value = " << x << std::endl;};
    auto future = pThreadPool->enqueue(exampleTask, 10);
    ```

    **Notice 1**: In this example also `chrono` and `iostream` headers must be included.

    **Notice 2**: You can enqueue tasks and its arguments as rvalue objects. Then there will be invoked move constructors if exists for these class of objects.

1. Get result:

    ```cpp
    future.get();
    ```
