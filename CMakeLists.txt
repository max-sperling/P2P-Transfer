cmake_minimum_required (VERSION 3.5)
project (P2P-Transfer)

# ***** Setup **************************************************************************************
find_package (Qt6 COMPONENTS Core Network Widgets)
set (QT_PATH ${CMAKE_PREFIX_PATH})

file (GLOB TRANS_SRC src/trans/TransFactory.cpp src/trans/trans_p2p/*.cpp)

set (QT_TRANS src/trans/trans_p2p/Server.hpp src/trans/trans_p2p/Income.hpp
              src/trans/trans_p2p/Client.hpp src/trans/trans_p2p/Outcome.hpp)
qt_wrap_cpp (QT_TRANS_MOC ${QT_TRANS})

file (GLOB VIEW_SRC src/view/ViewFactory.cpp src/view/view_qt/*.cpp)

set (QT_VIEW src/view/view_qt/ViewQt.hpp)
qt_wrap_cpp (QT_VIEW_MOC ${QT_VIEW})

file (GLOB CONF_SRC src/conf/ConfFactory.cpp src/conf/conf_json/*.cpp)

set (MAIN_SRC app/Main.cpp src/TransferApp.cpp)

file (GLOB TEST_SRC app/Test.cpp test/TransferTest.cpp
                    test/trans/*.cpp test/conf/*.cpp test/view/*.cpp)
# **************************************************************************************************

# ***** Build **************************************************************************************
add_library (Trans SHARED ${TRANS_SRC} ${QT_TRANS_MOC})
target_include_directories (Trans PRIVATE src ${Qt6Network_INCLUDE_DIRS})
target_link_libraries (Trans PRIVATE ${Qt6Network_LIBRARIES})

add_library (View SHARED ${VIEW_SRC} ${QT_VIEW_MOC})
target_include_directories (View PRIVATE src ${Qt6Widgets_INCLUDE_DIRS})
target_link_libraries (View PRIVATE ${Qt6Widgets_LIBRARIES})

add_library (Conf SHARED ${CONF_SRC})
target_include_directories (Conf PRIVATE src)

add_executable ("${PROJECT_NAME}-App" ${MAIN_SRC})
target_include_directories ("${PROJECT_NAME}-App" PRIVATE src ${Qt6Widgets_INCLUDE_DIRS})
target_link_libraries ("${PROJECT_NAME}-App" PRIVATE Trans View Conf ${Qt6Widgets_LIBRARIES})

add_executable ("${PROJECT_NAME}-Test" ${TEST_SRC})
target_include_directories ("${PROJECT_NAME}-Test" PRIVATE test src ${Qt6Core_INCLUDE_DIRS})
target_link_libraries ("${PROJECT_NAME}-Test" PRIVATE Trans ${Qt6Core_LIBRARIES})

file (COPY res/conf/config.json DESTINATION ${CMAKE_BINARY_DIR})
# **************************************************************************************************
