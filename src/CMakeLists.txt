find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(TGUI 0.9 REQUIRED)

add_library(filterki STATIC 
	${CMAKE_SOURCE_DIR}/src/filterki.cpp
	${CMAKE_SOURCE_DIR}/include/filterki/filterki.h
	${CMAKE_SOURCE_DIR}/include/config.h
	)

target_link_libraries(filterki sfml-graphics sfml-audio sfml-system sfml-window)
target_link_libraries(filterki tgui)
target_include_directories(filterki PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(filterki PRIVATE cxx_std_17)

