project (Transfer-Test)

set (TEST_SRC Test.cpp ${CMAKE_SOURCE_DIR}/test/TransferTest.cpp)

add_executable (${PROJECT_NAME} ${TEST_SRC})

target_include_directories (${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/test
    ${CMAKE_SOURCE_DIR}/test/doubles
    ${CMAKE_SOURCE_DIR}/test/utests
    ${Qt6Core_INCLUDE_DIRS})

target_link_libraries (${PROJECT_NAME} PRIVATE Test Trans ${Qt6Core_LIBRARIES})
