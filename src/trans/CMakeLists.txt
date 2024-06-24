project (Trans)

# Build
add_library (${PROJECT_NAME} SHARED)
target_sources (${PROJECT_NAME} PRIVATE TransFactory.cpp)
add_subdirectory (trans_p2p)
set_target_properties (${PROJECT_NAME} PROPERTIES AUTOMOC ON)
target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src ${Qt6Network_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} PRIVATE ${Qt6Network_LIBRARIES})

# Install
install (TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
