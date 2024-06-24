project (Main-app)

# Build
set (MAIN_SRC Main.cpp)
add_executable (${PROJECT_NAME} ${MAIN_SRC})
target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src ${Qt6Widgets_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} PRIVATE Trans View Conf ${Qt6Widgets_LIBRARIES})

# Install
install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
install (FILES ${CMAKE_SOURCE_DIR}/res/conf/config.json DESTINATION conf)
set_target_properties (${PROJECT_NAME} PROPERTIES INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib" BUILD_WITH_INSTALL_RPATH TRUE)
