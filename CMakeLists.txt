cmake_minimum_required(VERSION 3.25)

project(imgui_desktop)


set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE}")

add_executable(imgui_desktop WIN32 source/main.cpp)

add_subdirectory(extlibs)
add_subdirectory(source)

target_link_libraries(imgui_desktop glfw opengl32 imgui)
