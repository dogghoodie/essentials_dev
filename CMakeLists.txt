cmake_minimum_required(VERSION 3.10)
project(essentials LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(essentials
  src/cpp/main.cpp
  src/cpp/interface.cpp
  src/cpp/scripts.cpp
  src/cpp/session.cpp
)

target_include_directories(essentials PRIVATE ${PROJECT_SOURCE_DIR}/src/include)
target_link_libraries(essentials ncurses)
