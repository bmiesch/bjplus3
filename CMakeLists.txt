cmake_minimum_required(VERSION 3.14)
project(bjplus3 VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(json)


# Recursively find all source files in the src directory
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Add executable based on source files
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC 
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/include/game"
    "${CMAKE_SOURCE_DIR}/include/strategies"
    "${CMAKE_SOURCE_DIR}/include/utils"
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
