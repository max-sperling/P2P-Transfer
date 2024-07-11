cmake_minimum_required (VERSION 3.13)
project (P2P-Transfer)

set (CMAKE_CXX_STANDARD 17)

find_package (Qt6 COMPONENTS Core Network Widgets)
find_package (LibArchive)
find_package (GTest)

add_subdirectory (app)
add_subdirectory (src)
add_subdirectory (test)
