cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(app
src/main.cpp
src/getPaths.cpp
src/game.cpp
src/world.cpp
src/cell.cpp
src/cell_manager.cpp
src/get_random_number.cpp
)

target_compile_features(app PRIVATE cxx_std_17)
target_link_libraries(app PRIVATE SFML::Graphics)
