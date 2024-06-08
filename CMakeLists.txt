cmake_minimum_required (VERSION 3.13)
project (P2P-Transfer)

find_package (Qt6 COMPONENTS Core Network Widgets)
find_package (GTest)

add_subdirectory (app)
add_subdirectory (src)
add_subdirectory (test)
