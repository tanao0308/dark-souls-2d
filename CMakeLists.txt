# Require CMake 3.31 or higher
cmake_minimum_required(VERSION 3.22)

# Define the project name (Lab02 here)
project(dark-souls-2d)

# Build for C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# Add dependencies (helper script)
include(./cmake/AddDependencies.cmake)

# This grabs all files in this directory that end with .cpp, .h
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCE_FILES})

# Enable some specific compile flags on Windows/Mac
include(./cmake/SetCompileFlags.cmake)

# Build target and specify source files
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

# 手动指定头文件查找目录（根目录）
target_include_directories(dark-souls-2d PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
# target_include_directories(dark-souls-2d PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/third_party/spdlog/include
# )

# 增加 spdlog
add_subdirectory(third_party/spdlog)

# Link against SDL3
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3_image::SDL3_image SDL3::SDL3 spdlog)

# On Windows, we also need to copy the DLLs to the target directory
if(WIN32)
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}> $<TARGET_RUNTIME_DLLS:${CMAKE_PROJECT_NAME}>
        COMMAND_EXPAND_LISTS)
endif()
