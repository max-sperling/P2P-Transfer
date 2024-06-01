project (Test)

add_library (${PROJECT_NAME} SHARED)

add_subdirectory (doubles)
add_subdirectory (utests)

target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/test/doubles ${CMAKE_SOURCE_DIR}/test/utests)
target_link_libraries (${PROJECT_NAME} PRIVATE ${GTEST_LIBRARIES} ${Qt6Widgets_LIBRARIES})
