# ----------------------
# Bloc Combat CMake List
# ----------------------

# Check CMake Version
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# Set Project
project(Terraformers)

# Set Version
set (Terraformers_VERSION_MAJOR 1)
set (Terraformers_VERSION_MINOR 0)

# Add Debug definition
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DLOCAL_DEBUG")

# Set Compiler Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Set include directory
# include_directories( inc )

# Set current directory
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Add sources
include( ${PROJECT_SOURCE_DIR}/Core/cmakelist.cmake)
include( ${PROJECT_SOURCE_DIR}/Components/cmakelist.cmake)
include( ${PROJECT_SOURCE_DIR}/Systems/cmakelist.cmake)
include( ${PROJECT_SOURCE_DIR}/AnimatedSprite/cmakelist.cmake)
include( ${PROJECT_SOURCE_DIR}/Map/cmakelist.cmake)

# Add Executable
add_executable(Terraformers ${SOURCE_FILES})

# Set Install
install(TARGETS Terraformers RUNTIME DESTINATION bin)

# Link SFML
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Terraformers ${SFML_LIBRARIES})
endif()
