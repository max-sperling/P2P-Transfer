project (Main-app)

# Build
set (MAIN_SRC Main.cpp)
add_executable (${PROJECT_NAME} ${MAIN_SRC})
set_target_properties (${PROJECT_NAME} PROPERTIES
    INSTALL_RPATH "${LIBRARY_OUTPUT_DIRECTORY};${CMAKE_INSTALL_PREFIX}/lib"
    BUILD_WITH_INSTALL_RPATH TRUE)
target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/libs ${Qt6Widgets_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} PRIVATE Trans View Conf ${Qt6Widgets_LIBRARIES})
file (COPY ${CMAKE_SOURCE_DIR}/conf/config.json DESTINATION ${CONFIG_OUTPUT_DIRECTORY})
