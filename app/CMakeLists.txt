cmake_minimum_required(VERSION 3.1)

project(Filterki)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(TGUI 0.8 REQUIRED)

add_executable(Filterki main.cpp)

target_link_libraries(Filterki sfml-graphics sfml-audio sfml-system sfml-window)
target_link_libraries(Filterki tgui)
target_include_directories(Filterki PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_features(Filterki PRIVATE cxx_std_17)