cmake_minimum_required(VERSION 3.10)

# Test code
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
    message(STATUS "Build type not specified, building Release as default.")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release)
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE EQUAL "DEBUG")
    message("Building Debug Mode.")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/debug)
endif (CMAKE_BUILD_TYPE EQUAL "DEBUG")
#End Test

project(HockeyProject VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(Box2D REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED) 

message("SDL2_ttf FOUND???" ${SDL2_ttf_FOUND})

file(GLOB SOURCES "**.cpp" "Components/**.cpp" "Commands/**.cpp") 
add_executable(HockeyExe ${SOURCES}) 

target_link_libraries( HockeyExe PRIVATE Box2D SDL2::Main SDL2::TTF )
target_include_directories( HockeyExe PRIVATE ${HockeyExe_SOURCE_DIR} ${HockeyExe_SOURCE_DIR}/Commands ${HockeyExe_SOURCE_DIR}/Components ) 
target_compile_options( HockeyExe PRIVATE "-ggdb" "-Wall" "-Wpedantic" "-Wextra" "-Wno-unused-parameter")


