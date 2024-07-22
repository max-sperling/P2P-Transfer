project (Test-app)

# Build
set (TEST_SRC Test.cpp)
add_executable (${PROJECT_NAME} ${TEST_SRC})
target_include_directories (${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/libs
    ${CMAKE_SOURCE_DIR}/tests
    ${CMAKE_SOURCE_DIR}/tests/doubles
    ${CMAKE_SOURCE_DIR}/tests/utests
    ${Qt6Core_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} PRIVATE Test Trans ${Qt6Core_LIBRARIES})
