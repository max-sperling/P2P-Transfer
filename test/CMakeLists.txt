project (Test)

add_library (${PROJECT_NAME} SHARED)

add_subdirectory (conf)
add_subdirectory (trans)
add_subdirectory (view)

target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/test)
target_link_libraries (${PROJECT_NAME} PRIVATE ${Qt6Widgets_LIBRARIES})
