cmake_minimum_required(VERSION 3.21.4)

project(tasx)
set(CMAKE_CXX_STANDARD 20)


find_package(fmt REQUIRED)
find_package(nlohmann_json 3.10.4 REQUIRED)


file(GLOB ALL_SRCS
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/include/*.hpp"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    )

add_executable(tasx ${ALL_SRCS})
target_link_libraries(tasx fmt::fmt)
target_link_libraries(tasx nlohmann_json::nlohmann_json)

