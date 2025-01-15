cmake_minimum_required(VERSION 3.5.0)
project(caching LANGUAGES C CXX)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_TWEAK 0)
set(VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optionally, you can enable testing
option(BUILD_TESTING "Build the testing tree." ON)

include_directories(include)

set(INC include/cache/Cache.hpp
        include/cache/Fifo.hpp
        include/cache/LFU.hpp
        include/cache/LRU.hpp)

include(CTest)
enable_testing()

include(CPack)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# Add the library with the header files and a dummy source file
add_library(_${PROJECT_NAME}-${VERSION} ${INC} sources/cache/Caching.cpp)

# Add the executable
add_executable(${PROJECT_NAME}_test test/main.cpp)
add_test(TEST_ALL_CACHES ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)

# Link the library to the executable
target_link_libraries(${PROJECT_NAME}_test _${PROJECT_NAME}-${VERSION})
target_include_directories(${PROJECT_NAME}_test PRIVATE include)