project(config)

SET(FILEPATH_DATA ${CMAKE_SOURCE_DIR}/data)
configure_file( config.h.in ${CMAKE_SOURCE_DIR}/include/config.h)
