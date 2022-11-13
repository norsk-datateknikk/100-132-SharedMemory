# CMake minimum version requirement
cmake_minimum_required(VERSION 3.0)

project(producer)

# Compile all the cpp files in src
file(GLOB SOURCES
"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)      

# Build an executable.
add_executable(${PROJECT_NAME} ${SOURCES})