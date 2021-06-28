cmake_minimum_required(VERSION 3.10)

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
