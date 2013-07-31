project(heartlenv-panel)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)
find_package(X11 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(heartlenv-panel_SRCS applet-menu.cpp heartlenv-panel.cpp main.cpp)
qt4_automoc(${heartlenv-panel_SRCS})
add_executable(heartlenv-panel ${heartlenv-panel_SRCS})
target_link_libraries(heartlenv-panel ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} heartlenv)
install(TARGETS heartlenv-panel RUNTIME DESTINATION bin)
