project(Filterki)

add_executable(Filterki main.cpp)

target_link_libraries(Filterki PUBLIC filterki)
target_include_directories(Filterki PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(Filterki PRIVATE cxx_std_17)