cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Fetch SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Source files
set(SOURCE_FILES
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
)

# Include directories
include_directories(include)

# Create executable
add_executable(main ${SOURCE_FILES})

# Set C++ standard
target_compile_features(main PRIVATE cxx_std_17)

# Link SFML
target_link_libraries(main PRIVATE SFML::Graphics)

# Copy assets to build directory
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})