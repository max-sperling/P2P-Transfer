cmake_minimum_required (VERSION 3.5)

project (P2P-Transfer)

find_package (Qt6 COMPONENTS Core Network Widgets)
set (QT_PATH ${CMAKE_PREFIX_PATH})

add_subdirectory (src)
add_subdirectory (test)
add_subdirectory (app)
