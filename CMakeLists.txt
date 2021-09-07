cmake_minimum_required(VERSION 3.16)
project(HockeyProject VERSION 1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

# Test code
# if(NOT CMAKE_BUILD_TYPE)
#     set(CMAKE_BUILD_TYPE "RELEASE")
#     message(STATUS "Build type not specified, building Release as default.")
#     set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release)
# endif(NOT CMAKE_BUILD_TYPE)
#
# if(CMAKE_BUILD_TYPE EQUAL "DEBUG")
#     message("Building Debug Mode.")
#     set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/debug)
# endif (CMAKE_BUILD_TYPE EQUAL "DEBUG")
    #End Test

#CMake Modules for Dynamic Libs
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

#Static Libs
set(EXTERNALS_DIR "${PROJECT_SOURCE_DIR}/externals")
set(LUA_DIR "${EXTERNALS_DIR}/lua")
set(SOL2_DIR "${EXTERNALS_DIR}/sol")
       

#Source Organization
set(APP_SOURCE_DIR "${PROJECT_SOURCE_DIR}/source")
set(DATA_DIR "${APP_SOURCE_DIR}/Data")
set(COMPONENTS_DIR "${APP_SOURCE_DIR}/Components")
set(COMMANDS_DIR "${APP_SOURCE_DIR}/Commands")


find_package(Box2D REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED) 
find_package(SDL2_image REQUIRED)

file(GLOB SOURCES "source/**.cpp" 
                  "source/Components/**.cpp" 
                  "source/Commands/**.cpp" 
                  "source/lHockey.lua" 
                  "source/lColors.lua" ) 

add_library(
    lua STATIC
    ${LUA_DIR}/lapi.c
    ${LUA_DIR}/lauxlib.c
    ${LUA_DIR}/lbaselib.c
    ${LUA_DIR}/lcode.c
    ${LUA_DIR}/lcorolib.c
    ${LUA_DIR}/lctype.c
    ${LUA_DIR}/ldblib.c
    ${LUA_DIR}/ldebug.c
    ${LUA_DIR}/ldo.c
    ${LUA_DIR}/ldump.c
    ${LUA_DIR}/lfunc.c
    ${LUA_DIR}/lgc.c
    ${LUA_DIR}/linit.c
    ${LUA_DIR}/liolib.c
    ${LUA_DIR}/llex.c
    ${LUA_DIR}/lmathlib.c
    ${LUA_DIR}/lmem.c
    ${LUA_DIR}/loadlib.c
    ${LUA_DIR}/lobject.c
    ${LUA_DIR}/lopcodes.c
    ${LUA_DIR}/loslib.c
    ${LUA_DIR}/lparser.c
    ${LUA_DIR}/lstate.c
    ${LUA_DIR}/lstring.c
    ${LUA_DIR}/lstrlib.c
    ${LUA_DIR}/ltable.c
    ${LUA_DIR}/ltablib.c
    ${LUA_DIR}/ltm.c
    ${LUA_DIR}/lua.c
    ${LUA_DIR}/lundump.c
    ${LUA_DIR}/lutf8lib.c
    ${LUA_DIR}/lvm.c
    ${LUA_DIR}/lzio.c
)

add_executable(HockeyExe ${SOURCES})

target_link_libraries( HockeyExe 
                       PRIVATE Box2D 
                               SDL2::Main 
                               SDL2::TTF 
                               SDL2::Image
                               lua )

target_include_directories( HockeyExe 
                        PRIVATE ${EXTERNALS_DIR} 
                                ${LUA_DIR}
                                ${DATA_DIR} )
 
target_compile_options( HockeyExe 
                        PRIVATE 
                        "-ggdb" 
                        "-Wall" "-Wpedantic" "-Wextra" "-Wno-unused-parameter" )
