cmake_minimum_required(VERSION 3.20)

project(MyProject LANGUAGES CXX)

# --- C++ standard ---
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Default build type ---
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")

# --- Generate compile_commands.json (handy for editors/clangd) ---
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Compiler flags per build type ---
if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "/utf-8 /Od /Zi /DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "/utf-8 /O2 /DNDEBUG")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall -Wextra -DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
endif()

# include(vcpkg)

find_package(pugixml CONFIG REQUIRED)
find_package(miniz CONFIG REQUIRED)
find_package(OpenXLSX CONFIG REQUIRED)
find_package(shapelib CONFIG REQUIRED)
find_package(wxWidgets CONFIG REQUIRED)

# --- Executable ---

file(GLOB SOURCES "src/*.cpp")

if(WIN32)
    # On Windows build as a GUI app so the wxWidgets-provided entry point is used
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
else()
    add_executable(${PROJECT_NAME} ${SOURCES})
endif()
target_include_directories(${PROJECT_NAME} PRIVATE inc)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenXLSX::OpenXLSX)
target_link_libraries(${PROJECT_NAME} PRIVATE shapelib::shp)
target_link_libraries(${PROJECT_NAME} PRIVATE wx::core wx::base)