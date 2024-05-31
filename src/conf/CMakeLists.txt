project (Conf)

add_library (${PROJECT_NAME} SHARED)

target_sources (${PROJECT_NAME} PRIVATE ConfFactory.cpp)

add_subdirectory (conf_json)

target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
