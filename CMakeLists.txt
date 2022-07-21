cmake_minimum_required(VERSION 3.0)
project(Some-game VERSION 0.0.1)

set(TARGET some-game)
file(GLOB_RECURSE Some-game_SRC "Source/*")
add_executable(${TARGET} ${Some-game_SRC})
target_include_directories(${TARGET} PRIVATE "Source")

# Nlohmann_json
target_sources(${TARGET} PRIVATE "../libs/nlohmann_json/single_include/nlohmann/json.hpp")
target_include_directories(${TARGET} PRIVATE "../libs/nlohmann_json/single_include")

# SFML
set(SFML_DIR "../libs/SFML-2.5.1/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS system window graphics network audio main)
target_link_libraries(${TARGET} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-main)