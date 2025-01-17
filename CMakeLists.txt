cmake_minimum_required(VERSION 3.5.0)
project(caching LANGUAGES C CXX)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_TWEAK 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optionally, you can enable testing
option(BUILD_TESTING "Build the testing tree." ON)

include_directories(include)

set(INC_CACHE include/Caching.hpp)
set(INC include/cache/Cache.hpp
        include/cache/Fifo.hpp
        include/cache/LFU.hpp
        include/cache/LRU.hpp)

include(CTest)
enable_testing()

set(LIB_NAME _${PROJECT_NAME}-${PROJECT_VERSION})
# Add the library with the header files and a dummy source file
add_library(${LIB_NAME} ${INC} ${INC_CACHE} sources/cache/Caching.cpp)

# Add the executable
add_executable(${PROJECT_NAME}_test test/main.cpp)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME}_test Threads::Threads)
add_test(TEST_ALL_CACHES ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)

# Link the library to the executable
target_link_libraries(${PROJECT_NAME}_test ${LIB_NAME})
target_include_directories(${PROJECT_NAME}_test PRIVATE include)

include(cpack/CMakeLists.txt)