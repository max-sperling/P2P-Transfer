project (Test)

add_library (${PROJECT_NAME} SHARED)

add_subdirectory (doubles)
add_subdirectory (utests)

target_include_directories (${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/libs
    ${CMAKE_SOURCE_DIR}/tests/doubles
    ${CMAKE_SOURCE_DIR}/tests/utests)
target_link_libraries (${PROJECT_NAME} PRIVATE ${GTEST_LIBRARIES} ${Qt6Widgets_LIBRARIES})
