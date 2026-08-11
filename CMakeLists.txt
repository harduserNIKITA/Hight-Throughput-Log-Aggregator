cmake_minimum_required(VERSION 3.20)
project(log_aggregator VERSION 0.1.0 LANGUAGES CXX)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "Disable network updates")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost REQUIRED COMPONENTS system thread)

include(FetchContent)

set(CLICKHOUSE_CLIENT_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(CLICKHOUSE_CLIENT_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    simdjson
    GIT_REPOSITORY https://github.com/simdjson/simdjson.git
    GIT_TAG        v3.10.0
)

FetchContent_Declare(
    clickhouse-cpp
    GIT_REPOSITORY https://github.com/ClickHouse/clickhouse-cpp.git
    GIT_TAG        master
)

FetchContent_MakeAvailable(simdjson clickhouse-cpp)

add_executable(log_aggregator src/main.cpp)

target_include_directories(log_aggregator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

if(NOT MSVC)
    target_compile_options(log_aggregator PRIVATE -Wall -Wextra -Wpedantic -Wno-maybe-uninitialized)
endif()

target_link_libraries(log_aggregator PRIVATE
    Boost::system
    Boost::thread
    simdjson
    clickhouse-cpp-lib
)
