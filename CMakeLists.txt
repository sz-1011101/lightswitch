# thanks http://derekmolloy.ie/hello-world-introductions-to-cmake/ for the cmake tutorial
# uses: https://github.com/brendanwhitfield/collector/blob/master/cmake/FindSDL2.cmake
cmake_minimum_required (VERSION 3.2.2)
project (lightswitch)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# header files
include_directories(${CMAKE_SOURCE_DIR})

# glm header files
include_directories(glm)
# SDL2
find_package (SDL2)
include_directories(${SDL2_INCLUDE_DIR})

# source files
file(GLOB SOURCES "src/*.cpp")

add_executable(lightswitch ${SOURCES})

target_link_libraries(lightswitch ${SDL2_LIBRARY})