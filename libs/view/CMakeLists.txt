project (View)

# Build
add_library (${PROJECT_NAME} SHARED)
target_sources (${PROJECT_NAME} PRIVATE ViewFactory.cpp)
add_subdirectory (view_qt)
set_target_properties (${PROJECT_NAME} PROPERTIES AUTOMOC ON)
target_include_directories (${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/libs
    ${Qt6Widgets_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} PRIVATE ${Qt6Widgets_LIBRARIES})
