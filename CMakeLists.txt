cmake_minimum_required (VERSION 3.13)
project (P2P-Transfer)

set (CMAKE_CXX_STANDARD 17)

find_package (Qt6 COMPONENTS Core Network Widgets)
find_package (LibArchive)
find_package (GTest)

set (RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib)
set (CONFIG_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/conf)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIRECTORY})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})

add_subdirectory (apps)
add_subdirectory (libs)
add_subdirectory (tests)
