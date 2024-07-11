project (Conf)

# Build
add_library (${PROJECT_NAME} SHARED)
target_sources (${PROJECT_NAME} PRIVATE ConfFactory.cpp)
add_subdirectory (conf_json)
set_target_properties (${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Install
install (TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
