cmake_minimum_required(VERSION 3.10)

project(pong)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SFML_DIR "C:/msys64/mingw64/lib/cmake/SFML")
find_package(SFML 2.6.1 COMPONENTS system window graphics REQUIRED)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/bat.cpp
    src/ball.cpp 
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)