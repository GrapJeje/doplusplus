cmake_minimum_required(VERSION 3.31)
project(do__)

set(CMAKE_CXX_STANDARD 20)

add_executable(do__ main.cpp
        src/models/Task.cpp
        src/utils/Json.cpp
        src/utils/Line.cpp
        src/utils/UI.cpp)

target_include_directories(do__ PRIVATE ${PROJECT_SOURCE_DIR}/libs)
target_include_directories(do__ PRIVATE ${PROJECT_SOURCE_DIR}/src)