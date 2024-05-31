project (Transfer-App)

set (MAIN_SRC Main.cpp ${CMAKE_SOURCE_DIR}/src/TransferApp.cpp)

add_executable (${PROJECT_NAME} ${MAIN_SRC})
target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src ${Qt6Widgets_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} PRIVATE Trans View Conf ${Qt6Widgets_LIBRARIES})

file (COPY ${CMAKE_SOURCE_DIR}/res/conf/config.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
