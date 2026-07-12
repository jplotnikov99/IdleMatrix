cmake_minimum_required(VERSION 3.22)

project(
 IdleMatrix 
 VERSION 0.1
 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(backend_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/backend/include)
set(frontend_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/frontend/include)
set(gameLoop_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/game_loop/include)
set(fontmanager_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/fonts)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/backend/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/game_loop/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/frontend/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fonts)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    fontmanager 
    backend 
    frontend 
    gameLoop 
    Qt6::Widgets
)